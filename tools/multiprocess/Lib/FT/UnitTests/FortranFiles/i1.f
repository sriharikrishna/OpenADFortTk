      subroutine create_netcdf(fname,tname,nx,ny)

      errmsg = nf_create(fname,nf_clobber,fid)

      end! subroutine create_netcdf

      subroutine add_gatta_netcdf( fname, aname, a )

      errmsg = nf_open( fname, nf_write, fid )
      lchar = lastchar(a)
      if ( lchar .eq. 0 ) then
         lchar = 1
      end if
      return
      end! subroutine add_gatta_netcdf

      subroutine add_gatti_netcdf( fname, aname, a )

      call handle_err( errmsg, str1 )

      end! subroutine add_gatti_netcdf

      subroutine add_coordinates_netcdf( fname, nx, x, ny, y, units )

      integer nx, ny
      real x(nx), y(ny)
c     local variables
      integer errmsg

c     put the data
      errmsg = nf_put_var_double(fid, xid, x)

      errmsg = nf_put_var_double(fid, yid, y)

      return

      end ! subroutine add_coordinates_netcdf

      subroutine add_pfield_netcdf( fname, nx, ny, u, 
     &     uname, ulongname, uunits )

      implicit none

      integer nx, ny
      real u

      integer errmsg

c     write the data
      errmsg = nf_put_var_double( fid, uid, u )
      str1 = 'nf_put_var_double: '//uname 
      call handle_err( errmsg, str1 )

      end ! subroutine add_pfield_netcdf

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

      end! subroutine write_state_netcdf

      subroutine read_vector_netcdf( fname, aname, n, a )

      implicit none

      integer n
      real a(n)

      integer errmsg
      errmsg = nf_get_var_double( fid, aid, a )

      return
      end ! read_vector_netcdf

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
      subroutine read_weight_depth_netcdf( fname, aname, a, nx, ny, n )

      implicit none

      integer nx, ny, n
      real a(nx,nx,ny,ny)
            errmsg = nf_get_var_double( fid, aid, a )

      end ! subroutine read_weight_depth_netcdf
