      subroutine create_netcdf(fname,tname,nx,ny)

      errmsg = nf_create(fname,nf_clobber,fid)

      end! subroutine create_netcdf
