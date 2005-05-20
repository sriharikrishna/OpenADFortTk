
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

      end subroutine add_pfield_netcdf
