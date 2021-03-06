//
// Simple.h,v 1.1 2001/05/09 21:43:06 coryan Exp
//

#ifndef SIMPLE_H
#define SIMPLE_H
#include "ace/pre.h"

#include "TestS.h"

#if defined (_MSC_VER)
# if (_MSC_VER >= 1200)
#  pragma warning(push)
# endif /* _MSC_VER >= 1200 */
# pragma warning (disable:4250)
#endif /* _MSC_VER */

/// Implement the Test::Simple interface
class Simple
  : public virtual POA_Test::Simple
  , public virtual PortableServer::RefCountServantBase
{
public:
  /// Constructor
  Simple (void);

  // = The skeleton methods

  virtual void destroy (CORBA::Environment &ACE_TRY_ENV)
    ACE_THROW_SPEC ((CORBA::SystemException));
};

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* SIMPLE_H */
