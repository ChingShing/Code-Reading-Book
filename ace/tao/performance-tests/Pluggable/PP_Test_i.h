// PP_Test_i.h,v 1.2 1999/06/15 19:50:13 parsons Exp

// ============================================================================
//
// = LIBRARY
//    TAO/performance-tests/Pluggable
//
// = FILENAME
//    PP_Test_i.h
//
// = AUTHOR
//    Jeff Parsons <parsons@cs.wustl.edu>
//
// ============================================================================

#ifndef _PP_TEST_I_H
#define _PP_TEST_I_H

#include "PP_TestS.h"

class PP_Test_i : public POA_Pluggable_Test
{
  // = TITLE
  //    Illustrates how to integrate a servant with the generated
  //    skeleton.
  //
  // = DESCRIPTION
  //    Implementation of the example at the servant side.
  //    Sends a no-op oneway and twoway request.
public:
  PP_Test_i (CORBA::ORB_ptr orb);
  // Constructor

  ~PP_Test_i (void);
  // Destructor

  virtual void send_oneway (CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // Test a oneway call.

  virtual void send_void (CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // Test a twoway call.

  virtual void shutdown (CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // Shutdown routine.

protected:
  CORBA::ORB_var orb_;
  // Keep a pointer to the ORB so we can shut it down.
};

class Pluggable_Test_Factory_i: public POA_Pluggable_Test_Factory
{
  // = TITLE
  //   Pluggable_Test_Factory_i
  //
  // = DESCRIPTION
  //   Factory object returning the Pluggable_Test objrefs
public:
  Pluggable_Test_Factory_i (CORBA::ORB_ptr orb);
  // Constructor.

  ~Pluggable_Test_Factory_i (void);
  // Destructor.

  virtual Pluggable_Test_ptr make_pluggable_test (CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));
  // Make a Pluggable Test object.

private:
  PP_Test_i my_pluggable_test_;
};

#endif /* _PP_TEST_I_H */
