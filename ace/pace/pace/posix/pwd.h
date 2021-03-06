/* pwd.h,v 1.6 2000/07/07 22:23:13 luther Exp

 * ============================================================================
 *
 * = LIBRARY
 *    pace
 *
 * = FILENAME
 *    pace/posix/pwd.h
 *
 * = AUTHOR
 *    Luther Baker
 *
 * ============================================================================ */

#ifndef PACE_PWD_H_POSIX
#define PACE_PWD_H_POSIX

#include <pwd.h>
#include "pace/sys/types.h"

#if defined (PACE_HAS_CPLUSPLUS)
extern "C" {
#endif /* PACE_HAS_CPLUSPLUS */

#ifndef PACE_PASSWD
#define PACE_PASSWD
  typedef struct passwd pace_passwd;
#endif /* PACE_PASSWD */

#if defined (PACE_HAS_CPLUSPLUS)
}
#endif /* PACE_HAS_CPLUSPLUS */

#endif /* PACE_PWD_H_POSIX */
