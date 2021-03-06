// -*- c++ -*-
// Object_A_i.h,v 1.4 1999/09/03 06:36:04 mk1 Exp

// ============================================================================
//
// = LIBRARY
//    TAO/tests/NestedUpCalls/Triangle_Test
//
// = FILENAME
//    Object_A_i.h
//
// = DESCRIPTION
//    This class implements the Object A of the
//    Nested Upcalls - Triangle test.
//
// = AUTHORS
//    Michael Kircher
//
// ============================================================================

#ifndef OBJECT_B_IMPL_H
#  define OBJECT_B_IMPL_H

#include "Triangle_TestS.h"

class Object_A_i : public POA_Object_A
{
  // = TITLE
  //     Implement the <Object_A> IDL interface.
public:
  Object_A_i (void);
  // Constructor.

  virtual ~Object_A_i (void);
  // Destructor.

  virtual void foo (Initiator_ptr theInitiator_ptr,
                    CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));

  virtual void finish (CORBA::Environment &env)
    ACE_THROW_SPEC ((CORBA::SystemException));

  unsigned long finish_two_way_call_;
};

#endif /* OBJECT_B_IMPL_H */
