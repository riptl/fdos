#include "../shared/fdos/fdos_abi.h"
#include "../shared/fdos/fdos_pvclock.h"
#include "../shared/util/log/fd_log.h"
#include <immintrin.h>

static fd_pvclock_t * g_pvclock;

__attribute__((noreturn)) void
fdos_kern_main( fdos_kern_args_t * args ) {
  g_pvclock = (fd_pvclock_t *)args->pvclock_gvaddr;
  fd_log_thread_set( "kvm0" );
  fd_log_wallclock_set( fd_pvclock_now, g_pvclock );
  fd_log_colorize_set( 1 );

  FD_LOG_NOTICE(( "Hello world!" ));
  FD_LOG_ERR(( "Exiting" ));
}
