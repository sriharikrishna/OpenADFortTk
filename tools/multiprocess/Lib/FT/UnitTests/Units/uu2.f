
      subroutine add_gatta_netcdf( fname, aname, a )

      errmsg = nf_open( fname, nf_write, fid )
      lchar = lastchar(a)
      if ( lchar .eq. 0 ) then
         lchar = 1
      end if
      return
      end subroutine add_gatta_netcdf
