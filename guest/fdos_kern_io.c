#include "../shared/fdos/fdos_hypercall.h"

int
fd_io_write( int          fd,
             void const * src,
             ulong        src_min,
             ulong        src_max,
             ulong *      _src_sz ) {
  (void)src_min;
  fdos_hypercall_write( fd, src, src_max );
  *_src_sz = src_max; /* FIXME error handling */
  return 0;
}
