// sender.cpp,v 1.4 2001/04/02 03:39:20 yamuna Exp

#include "sender.h"
#include "tao/debug.h"
#include "ace/Get_Opt.h"
#include "ace/High_Res_Timer.h"

typedef ACE_Singleton<Sender, ACE_Null_Mutex> SENDER;
// Create a singleton instance of the Sender.

int
Sender_StreamEndPoint::get_callback (const char *,
                                     TAO_AV_Callback *&callback)
{
  // Create and return the sender application callback to AVStreams
  // for further upcalls.
  callback = &this->callback_;
  return 0;
}

int
Sender_StreamEndPoint::set_protocol_object (const char *,
                                            TAO_AV_Protocol_Object *object)
{
  // Set the sender protocol object corresponding to the transport
  // protocol selected.
  SENDER::instance ()->protocol_object (object);
  return 0;
}

Sender::Sender (void)
  : sender_mmdevice_ (0),
    streamctrl_ (0),
    frame_count_ (0),
    filename_ ("input"),
    input_file_ (0),
    protocol_ ("UDP"),
    frame_rate_ (30),
    mb_ (BUFSIZ)
{
}

void
Sender::protocol_object (TAO_AV_Protocol_Object *object)
{
  // Set the sender protocol object corresponding to the transport
  // protocol selected.
  this->protocol_object_ = object;
}

int
Sender::parse_args (int argc,
                    char **argv)
{
  // Parse command line arguments
  ACE_Get_Opt opts (argc, argv, "f:p:r:d");

  int c;
  while ((c= opts ()) != -1)
    {
      switch (c)
        {
        case 'f':
          this->filename_ = opts.optarg;
          break;
        case 'p':
          this->protocol_ = opts.optarg;
          break;
        case 'r':
          this->frame_rate_ = ACE_OS::atoi (opts.optarg);
          break;
        case 'd':
          TAO_debug_level++;
          break;
        default:
          ACE_DEBUG ((LM_DEBUG, "Unknown Option\n"));
          return -1;
        }
    }
  return 0;
}

// Method to get the object reference of the receiver
int
Sender::bind_to_receiver (CORBA::Environment &ACE_TRY_ENV)
{
  CosNaming::Name name (1);
  name.length (1);
  name [0].id =
    CORBA::string_dup ("Receiver");

  // Resolve the receiver object reference from the Naming Service
  CORBA::Object_var receiver_mmdevice_obj =
    this->naming_client_->resolve (name,
                                   ACE_TRY_ENV);
  ACE_CHECK_RETURN (-1);

  this->receiver_mmdevice_ =
    AVStreams::MMDevice::_narrow (receiver_mmdevice_obj.in (),
                                  ACE_TRY_ENV);
  ACE_CHECK_RETURN (-1);

  if (CORBA::is_nil (this->receiver_mmdevice_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       "Could not resolve Receiver_MMdevice in Naming service <%s>\n"),
                      -1);

  return 0;
}

int
Sender::init (int argc,
              char **argv,
              CORBA::Environment &ACE_TRY_ENV)
{
  // Initialize the endpoint strategy with the orb and poa.
  int result =
    this->endpoint_strategy_.init (TAO_AV_CORE::instance ()->orb (),
                                   TAO_AV_CORE::instance ()->poa ());
  if (result != 0)
    return result;

  // Initialize the naming services
  result =
    this->naming_client_.init (TAO_AV_CORE::instance ()->orb ());
  if (result != 0)
    return result;

  // Parse the command line arguments
  result =
    this->parse_args (argc,
                      argv);
  if (result != 0)
    return result;

  // Open file to read.
  this->input_file_ =
    ACE_OS::fopen (this->filename_.c_str (),
                   "r");

  if (this->input_file_ == 0)
    ACE_ERROR_RETURN ((LM_DEBUG,
                       "Cannot open input file %s\n",
                       this->filename_.c_str ()),
                      -1);
  else
    ACE_DEBUG ((LM_DEBUG,
                "File opened successfully\n"));

  // Resolve the object reference of the receiver from the Naming Service.
  result = this->bind_to_receiver (ACE_TRY_ENV);
  ACE_CHECK_RETURN (-1);
  
  if (result != 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "(%P|%t) Error binding to the naming service\n"),
                      -1);


  // Initialize the  QoS
  AVStreams::streamQoS_var the_qos (new AVStreams::streamQoS);

  // Create the forward flow specification to describe the flow.
  TAO_Forward_FlowSpec_Entry entry ("Data_Receiver",
                                    "IN",
                                    "USER_DEFINED",
                                    "",
                                    this->protocol_.c_str (),
                                    0);

  AVStreams::flowSpec flow_spec (1);
  flow_spec.length (1);
  flow_spec [0] = CORBA::string_dup (entry.entry_to_string ());

  // Register the sender mmdevice object with the ORB
  ACE_NEW_RETURN (this->sender_mmdevice_,
                  TAO_MMDevice (&this->endpoint_strategy_),
                  -1);

  // Servant Reference Counting to manage lifetime
  PortableServer::ServantBase_var safe_mmdevice =
    this->sender_mmdevice_;

  AVStreams::MMDevice_var mmdevice =
    this->sender_mmdevice_->_this (ACE_TRY_ENV);
  ACE_CHECK_RETURN (-1);

  ACE_NEW_RETURN (this->streamctrl_,
                  TAO_StreamCtrl,
                  -1);

  PortableServer::ServantBase_var safe_streamctrl =
    this->streamctrl_;

  // Bind/Connect the sender and receiver MMDevices.
  CORBA::Boolean bind_result =
    this->streamctrl_->bind_devs (mmdevice.in (),
                                  this->receiver_mmdevice_.in (),
                                  the_qos.inout (),
                                  flow_spec,
                                  ACE_TRY_ENV);
  ACE_CHECK_RETURN (-1);

  if (bind_result == 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       "streamctrl::bind_devs failed\n"),
                      -1);

  return 0;
}

// Method to send data at the specified rate
int
Sender::pace_data (CORBA::Environment &ACE_TRY_ENV)
{
  // The time that should lapse between two consecutive frames sent.
  ACE_Time_Value inter_frame_time;

  // The time between two consecutive frames.
  inter_frame_time.set (1 / (double) this->frame_rate_);

  if (TAO_debug_level > 0)
    ACE_DEBUG ((LM_DEBUG,
                "Frame Rate = %d / second\n"
                "Inter Frame Time = %d (msec)\n",
                this->frame_rate_,
                inter_frame_time.msec ()));

  ACE_TRY
    {
      // The time taken for sending a frame and preparing for the next frame
      ACE_High_Res_Timer elapsed_timer;

      // Continue to send data till the file is read to the end.
      while (1)
        {
          // Read from the file into a message block.
          int n = ACE_OS::fread (this->mb_.wr_ptr (),
                                 1,
                                 this->mb_.size (),
                                 this->input_file_);

          if (n < 0)
            ACE_ERROR_RETURN ((LM_ERROR,
                               "Sender::pace_data fread failed\n"),
                              -1);

          if (n == 0)
            {
              // At end of file break the loop and end the sender.
              if (TAO_debug_level > 0)
                ACE_DEBUG ((LM_DEBUG,"Handle_Start:End of file\n"));
              break;
            }

          this->mb_.wr_ptr (n);

          if (this->frame_count_ > 1)
            {
              //
              // Second frame and beyond
              //

              // Stop the timer that was started just before the previous frame was sent.
              elapsed_timer.stop ();

              // Get the time elapsed after sending the previous frame.
              ACE_Time_Value elapsed_time;
              elapsed_timer.elapsed_time (elapsed_time);

              if (TAO_debug_level > 0)
                ACE_DEBUG ((LM_DEBUG,
                            "Elapsed Time = %d\n",
                            elapsed_time.msec ()));

              // Check to see if the inter frame time has elapsed.
              if (elapsed_time < inter_frame_time)
                {
                  // Inter frame time has not elapsed.

                  // Calculate the time to wait before the next frame needs to be sent.
                  ACE_Time_Value wait_time (inter_frame_time - elapsed_time);

                  if (TAO_debug_level > 0)
                    ACE_DEBUG ((LM_DEBUG,
                                "Wait Time = %d\n",
                                wait_time.msec ()));

                  // Run the orb for the wait time so the sender can
                  // continue other orb requests.
                  TAO_AV_CORE::instance ()->orb ()->run (wait_time,
                                                         ACE_TRY_ENV);
                  ACE_TRY_CHECK;
                }
            }

          // Start timer before sending the frame.
          elapsed_timer.start ();

          // Send frame.
          int result =
            this->protocol_object_->send_frame (&this->mb_);

          if (result < 0)
            ACE_ERROR_RETURN ((LM_ERROR,
                               "send failed:%p",
                               "Sender::pace_data send\n"),
                              -1);

          ACE_DEBUG ((LM_DEBUG,
                      "Sender::pace_data frame %d was sent succesfully\n",
                      ++this->frame_count_));

          // Reset the message block.
          this->mb_.reset ();

        } // end while

      // File reading is complete, destroy the stream.
      AVStreams::flowSpec stop_spec;
      this->streamctrl_->destroy (stop_spec,
                                  ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Shut the orb down.
      TAO_AV_CORE::instance ()->orb ()->shutdown (0,
                                                  ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Sender::pace_data Failed\n");
      return -1;
    }
  ACE_ENDTRY;
  return 0;
}

int
main (int argc,
      char **argv)
{
  ACE_DECLARE_NEW_CORBA_ENV;
  ACE_TRY
    {
      CORBA::ORB_var orb =
        CORBA::ORB_init (argc,
                         argv,
                         0,
                         ACE_TRY_ENV);

      CORBA::Object_var obj
        = orb->resolve_initial_references ("RootPOA",
                                           ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Get the POA_var object from Object_var
      PortableServer::POA_var root_poa
        = PortableServer::POA::_narrow (obj.in (),
                                        ACE_TRY_ENV);
      ACE_TRY_CHECK;

      PortableServer::POAManager_var mgr
        = root_poa->the_POAManager (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      mgr->activate (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Initialize the AV Stream components.
      TAO_AV_CORE::instance ()->init (orb.in (),
                                      root_poa.in (),
                                      ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Initialize the Sender.
      int result = 0;
      result = SENDER::instance ()->init (argc,
                                          argv,
                                          ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (result < 0)
        ACE_ERROR_RETURN ((LM_ERROR,
                           "Sender::init failed\n"),
                          -1);

      // Start sending data.
      result = SENDER::instance ()->pace_data (ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION,
                           "Sender Failed\n");
      return -1;
    }
  ACE_ENDTRY;
  ACE_CHECK_RETURN (-1);
  return 0;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class ACE_Singleton <Sender,ACE_Null_Mutex>;
template class TAO_AV_Endpoint_Reactive_Strategy_A<Sender_StreamEndPoint,TAO_VDev,AV_Null_MediaCtrl>;
template class TAO_AV_Endpoint_Reactive_Strategy<Sender_StreamEndPoint,TAO_VDev,AV_Null_MediaCtrl>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate ACE_Singleton <Sender,ACE_Null_Mutex>
#pragma instantiate TAO_AV_Endpoint_Reactive_Strategy_A<Sender_StreamEndPoint,TAO_VDev,AV_Null_MediaCtrl>
#pragma instantiate TAO_AV_Endpoint_Reactive_Strategy<Sender_StreamEndPoint,TAO_VDev,AV_Null_MediaCtrl>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
