// supplier.cpp,v 4.7 1998/12/17 19:05:33 schmidt Exp

#include "ace/Service_Config.h"

#include "Notifier_Handler.h"
#include "Input_Handler.h"

ACE_RCSID(Supplier, supplier, "supplier.cpp,v 4.7 1998/12/17 19:05:33 schmidt Exp")

#if defined (ACE_HAS_ORBIX) && (ACE_HAS_ORBIX != 0)

class Supplier : public ACE_Event_Handler
{
  // = TITLE
  //   Supplier driver for the Orbix Publish/Subscribe example.
  //
  // = DESCRIPTION
  //   The executable file generated from this code should be
  //   registered (under the name 'logger') using the 'putit' command.
public:
  Supplier (int argc, char *argv[]);
  ~Supplier (void);

  void run (void);
  // Execute the supplier.

private:
  virtual int handle_signal (int signum, siginfo_t *, ucontext_t *);

  virtual int handle_close (ACE_HANDLE, ACE_Reactor_Mask);

  Input_Handler *ih_;
  // Handler for keyboard input.

  Notifier_Handler *nh_;
  // Handler for CORBA Notifier.

  ACE_Service_Config daemon_;
  // ACE server event-loop mechanism.
};

int
Supplier::handle_close (ACE_HANDLE, ACE_Reactor_Mask)
{
  ACE_DEBUG ((LM_DEBUG,
              "closing down Supplier\n"));
  return 0;
}

int 
Supplier::handle_signal (int signum, siginfo_t *, ucontext_t *)
{
  ACE_Reactor::end_event_loop ();
  return 0;
}

void
Supplier::run (void)
{
  if (ACE_Reactor::run_event_loop () == -1)
    ACE_ERROR ((LM_ERROR,
                "%p\n",
                "run_reactor_event_loop"));
}

Supplier::Supplier (int argc, char *argv[])
  : ih_ (0), 
    nh_ (0)
{
  // Initialize the server.
  if (this->daemon_.open (argc, argv) == -1)
    {
      if (errno == ENOENT) // There's no svc.conf file, so use static linking...
	{
	  ACE_DEBUG ((LM_DEBUG,
                      "no config file, using static binding\n"));
	  // The constructor registers the handlers...
	  int putit = argc > 1 ? 1 : 0;

          // Pass in program exec name to use a service_location!
	  ACE_NEW (this->nh_,
                   Notifier_Handler (argv[0],
                                     "notifier",
                                     putit));
	  ACE_NEW (this->ih_,
                   Input_Handler (this->nh_));
	}
      else
	ACE_ERROR ((LM_ERROR,
                    "%p\n%a",
                    "open",
                    1));
    }

  ACE_DEBUG ((LM_DEBUG,
              "starting up server %s\n",
	     CORBA::Orbix.myImplementationName ()));

  if (ACE_Reactor::instance ()->register_handler (SIGINT, this) == -1)
    ACE_ERROR ((LM_ERROR,
                "%p\n",
                "register_handler"));
}

Supplier::~Supplier (void)
{
  // Free up the handlers if they were statically bound.
  this->ih_->handle_close ();
  this->nh_->handle_close ();
}

int
main (int argc, char *argv[]) 
{
  // Initialize server daemon.
  Supplier supplier (argc, argv);

  // Loop forever handling events.
  supplier.run ();

  return 0;
}
#else /* !defined ACE_HAS_ORBIX */
int
main (int argc, char *argv[])
{
  ACE_ERROR_RETURN ((LM_ERROR,
                     "you must have Orbix to run application %s\n",
                     argv[0]),
                    1);
}
#endif /* ACE_HAS_ORBIX */
