// EC_Factory.cpp,v 1.4 1999/04/24 13:52:18 coryan Exp

#include "EC_Factory.h"
#include "ace/Dynamic_Service.h"

#if ! defined (__ACE_INLINE__)
#include "EC_Factory.i"
#endif /* __ACE_INLINE__ */

ACE_RCSID(Event, EC_Factory, "EC_Factory.cpp,v 1.4 1999/04/24 13:52:18 coryan Exp")

TAO_EC_Factory::~TAO_EC_Factory (void)
{
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

template class ACE_Dynamic_Service<TAO_EC_Factory>;

#elif defined(ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#pragma instantiate ACE_Dynamic_Service<TAO_EC_Factory>

#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */
