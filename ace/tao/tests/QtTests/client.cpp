// client.cpp,v 1.3 2001/03/26 21:17:13 coryan Exp

#include "testC.h"
#include "ace/Get_Opt.h"

ACE_RCSID(QtTests, client, "client.cpp,v 1.3 2001/03/26 21:17:13 coryan Exp")

#if !defined (ACE_HAS_QT)

int
main (int, char *[])
{
  ACE_ERROR ((LM_INFO,
              "Qt not supported on this platform\n"));
  return 0;
}

#else
#include "client.h"

int
main (int argc, char *argv[])
{
  QApplication app (argc, argv);
  TAO_QtResource_Factory::set_context (&app);

  ACE_DECLARE_NEW_CORBA_ENV;

  ACE_TRY
    {
      CORBA::ORB_var orb =
        CORBA::ORB_init (argc, argv, "", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      Client client (orb.in (), app);

      client.parse_args (argc, argv, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // Creates the Qt widgets
      client.create_widgets (ACE_TRY_ENV);
      ACE_TRY_CHECK;

      // This may look a bit suspect, but Qt wants the manager widget
      // as the toplevel widget unlike Xt for display purposes.
      app.setMainWidget (&(client.box_));

      // Show them on Screen
      client.show ();

      app.exec ();
    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "Caught exception:");
      return 1;
    }
  ACE_ENDTRY;
  return 0;
}

Client::Client (CORBA::ORB_ptr orb,
                QApplication &qapp)
  : orb_ (CORBA::ORB::_duplicate (orb)),
    qapp_ (&qapp)
{
}

Client::~Client (void)
{
  delete this->slider_;
  delete this->push_button_;
}

void
Client::parse_args (int argc,
                    char *argv[],
                    CORBA::Environment &ACE_TRY_ENV)
{
  const char *ior = "file://test.ior";

  ACE_Get_Opt get_opts (argc, argv, "k:");
  int c;

  while ((c = get_opts ()) != -1)
    switch (c)
      {
      case 'k':
        ior = get_opts.optarg;
        break;
      case '?':
      default:
        ACE_ERROR ((LM_ERROR,
                    "usage:  %s "
                    "-k <ior> "
                    "\n",
                    argv [0]));
      }

  CORBA::Object_var object =
    this->orb_->string_to_object (ior, ACE_TRY_ENV);
  ACE_CHECK;

  this->server_ =
    LCD_Display::_narrow (object.in (), ACE_TRY_ENV);
  ACE_CHECK;

  if (CORBA::is_nil(this->server_.in ()))
    {
      ACE_DEBUG ((LM_DEBUG,
                  "\n The server value is nil "));
    }
}

void
Client::create_widgets (CORBA::Environment &/*ACE_TRY_ENV*/)
{
  // Ewsize the box
  this->box_.resize (200,120);

  // Make a pushbutton widget
  ACE_NEW (this->push_button_,
           QPushButton ("Quit",
                        &this->box_));

  // Connect the click () SIGNAL routine with the SLOT handler that we
  // have defined
  QObject::connect (this->push_button_,
                    SIGNAL (clicked()),
                    this,
                    SLOT (shutdown_call ()));

  // Create a slider widget
  ACE_NEW (this->slider_,
           QSlider (QSlider::Horizontal,
                    &this->box_,
                    "Slider"));

  // Add resource for the slider
  this->slider_->setRange (0, 99);
  this->slider_->setValue (0);

  // Connect the valuechanged SIGNAL routine with the slot that we
  // have defined. THe slot routine would invoke the remote call.
  QObject::connect (this->slider_,
                    SIGNAL (valueChanged (int)),
                    this,
                    SLOT (remote_call (int)));

}

void
Client::show (void)
{
  this->box_.show ();
}

void
Client::remote_call (int val)
{
  this->server_->send_val (val);
}

void
Client::shutdown_call (void)
{
  this->server_->shutdown ();
}

#endif /* ACE_HAS_QT*/
