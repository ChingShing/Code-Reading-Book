/* wait.h,v 1.6 2000/07/12 15:27:04 luther Exp

 * ============================================================================
 *
 * = LIBRARY
 *    pace
 *
 * = FILENAME
 *    pace/win32/wait.h
 *
 * = AUTHOR
 *    Luther Baker
 *
 * ============================================================================ */

#ifndef PACE_WAIT_H_WIN32
#define PACE_WAIT_H_WIN32

#include "pace/sys/types.h"

#if defined (PACE_HAS_CPLUSPLUS)
extern "C" {
#endif /* PACE_HAS_CPLUSPLUS */

#define PACE_WEXITSTATUS WEXITSTATUS
#define PACE_WIFEXITED WIFEXITED
#define PACE_WIFSIGNALED WISIGNALED
#define PACE_WIFSTOPPED WIFSTOPPED
#define PACE_WNOHANG WNOHANG
#define PACE_WSTOPSIG WSTOPSIG
#define PACE_WTERMSIG WTERMSIG
#define PACE_WUNTRACED WUNTRACED

#if defined (PACE_HAS_CPLUSPLUS)
}
#endif /* PACE_HAS_CPLUSPLUS */

#endif /* PACE_WAIT_H_WIN32 */
