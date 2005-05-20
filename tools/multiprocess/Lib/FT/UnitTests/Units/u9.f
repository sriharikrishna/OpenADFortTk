      subroutine read_weight_depth_netcdf( fname, aname, a, nx, ny, n )

      implicit none

      integer nx, ny, n
      real a(nx,nx,ny,ny)
            errmsg = nf_get_var_double( fid, aid, a )

      end ! subroutine read_weight_depth_netcdf
