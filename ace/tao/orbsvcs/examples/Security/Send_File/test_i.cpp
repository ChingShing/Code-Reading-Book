// test_i.cpp,v 1.2 2001/03/26 21:17:01 coryan Exp

#include "test_i.h"

#if !defined(__ACE_INLINE__)
#include "test_i.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(Send_File, test_i, "test_i.cpp,v 1.2 2001/03/26 21:17:01 coryan Exp")

void
Simple_Server_i::send_line (const char *line,
                            CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_DEBUG ((LM_DEBUG, "%s\n", line));
}

void
Simple_Server_i::shutdown (CORBA::Environment&)
    ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->orb_->shutdown (0);
}
