// -*- C++ -*-
// Bank_Client_i.h,v 1.2 1999/06/07 17:43:13 schmidt Exp

// ============================================================================
//
// = LIBRARY
//    TAO/tests/Simple/bank
//
// = FILENAME
//    Bank_Client_i.h
//
// = DESCRIPTION
//    This class implements the  interface calls for RMI.
//
// = AUTHOR
//    
//   Balachandran Natarajan <bala@cs.wustl.edu>
//    
// ============================================================================

#ifndef BANK_CLIENT_I_H
#define BANK_CLIENT_I_H

#include "../Simple_util.h"
#include "BankC.h"

class Bank_Client_i
{
  // = TITLE
  //   Grid_Client interface subclass.
  //
  // = DESCRIPTION
  //   This class implements the interface between the interface
  //   objects and the client .
public:
  // = Initialization and termination methods.
  Bank_Client_i (void);
  // Constructor

  virtual ~Bank_Client_i (void);
  // Destructor

  virtual int run (const char *, int, char *[]);
  // Execute the methods.

private:
  Client<Bank::AccountManager, Bank::AccountManager_var> client;
  // Instantiate the client object.

  int check_accounts (void);
  // Method that calls all the test functions

  void test_for_different_name (CORBA::Environment &env);
  // Tests if accounts opened with different names return a different account
  // reference.

  void test_for_same_name (CORBA::Environment &env);
  // Tests if accounts opened with the same name return the same 
  // object reference.
  
  void test_for_overdraft (CORBA::Environment &env);
  // Tests for the Overdraft Exception when the client tries to
  // withdraw more money than the current balance.
};

#endif /* TIME_CLIENT_I_H */
