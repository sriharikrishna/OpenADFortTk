
      subroutine write_state_netcdf( fname, nx, ny, it, uname, u )

      implicit none
c#include "netcdf.inc"

      integer nx, ny, it
      real u(nx,ny)

      integer errmsg
      integer fid, uid
      integer start(3), count(3)

c     put the data
      if ( uname .eq. 'TIME' ) then
         errmsg = nf_put_var_double( fid, uid, u )
      else
         errmsg = nf_put_var_double( fid, uid, u )
      end if

      end! subroutine write_state_netcdf
