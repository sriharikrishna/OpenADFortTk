
      subroutine add_coordinates_netcdf( fname, nx, x, ny, y, units )

      integer nx, ny
      real x(nx), y(ny)
c     local variables
      integer errmsg

c     put the data
      errmsg = nf_put_var_double(fid, xid, x)

      errmsg = nf_put_var_double(fid, yid, y)

      return

      end! subroutine add_coordinates_netcdf
