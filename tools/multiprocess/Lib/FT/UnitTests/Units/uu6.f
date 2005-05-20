
      subroutine write_state_netcdf( fname, nx, ny, it, uname, u )

      implicit none

      integer nx, ny, it
      real u(nx,ny)

      integer errmsg

      integer start(3), count(3)

c     put the data
      if ( uname .eq. 'TIME' ) then
         errmsg = nf_put_vara_double( fid, uid, it, 1, u(1,1) )
      else
         errmsg = nf_put_vara_double( fid, uid, start, count, u )
      end if

      end subroutine write_state_netcdf
