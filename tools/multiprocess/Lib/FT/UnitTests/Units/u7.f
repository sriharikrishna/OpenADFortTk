
      subroutine read_vector_netcdf( fname, aname, n, a )

      implicit none

      integer n
      real a(n)

      integer errmsg
      errmsg = nf_get_var_double( fid, aid, a )

      return
      end ! read_vector_netcdf
