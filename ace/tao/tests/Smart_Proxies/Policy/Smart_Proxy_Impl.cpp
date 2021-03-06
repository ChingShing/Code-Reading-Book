// Smart_Proxy_Impl.cpp,v 1.1 2000/08/11 03:31:09 kirthika Exp

#include "Smart_Proxy_Impl.h"

Smart_Test_Factory::Smart_Test_Factory (int one_shot_factory)
  : TAO_Test_Default_Proxy_Factory (one_shot_factory)
{
  ACE_DEBUG ((LM_DEBUG,
              "Smart_Test_Factory\n"));
}

Test_ptr
Smart_Test_Factory::create_proxy (Test_ptr proxy,
                                  CORBA::Environment &)
 {
   ACE_DEBUG ((LM_DEBUG,
               "create_smart_proxy\n"));

   if (CORBA::is_nil (proxy) == 0)
       ACE_NEW_RETURN (proxy, Smart_Test_Proxy (proxy), 0);

   return proxy;
   
 }

Smart_Test_Proxy::Smart_Test_Proxy (Test_ptr proxy)
  : TAO_Smart_Proxy_Base (proxy)
{
}

CORBA::Short 
Smart_Test_Proxy::method (CORBA::Short boo,
                          CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   Test::Oops))
{
  ACE_DEBUG ((LM_DEBUG,
              "Yahoo, I am smart\n"));
  
  CORBA::Short retval = 0;
  ACE_TRY 
    {
      retval = TAO_Test_Smart_Proxy_Base::method (boo,
                                                  ACE_TRY_ENV);
      ACE_TRY_CHECK;
    }
  ACE_CATCH (Test::Oops, reason)
    {
      ACE_PRINT_EXCEPTION (reason,
                           "User Exception");
      return -1;
    }
  ACE_ENDTRY;
  
  return retval;
}
