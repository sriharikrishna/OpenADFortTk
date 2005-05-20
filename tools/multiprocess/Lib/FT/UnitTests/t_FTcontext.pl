use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use FTcontext;
use Ffile;
use FTUnit;

setup();

is(FTcontext->file('i1.f')->to_string(),
   fconcat(FTUnit->new(Ffile->new('i1.f'))->units())->to_string(),
   'FT context file for i1.f');

is(FTcontext->here($ff)->to_string(),
   fconcat(FTUnit->new(Ffile->new_from_heredoc($ff))->units())->to_string(),
   'FT context heredoc');

teardown();

sub setup {
    $ff = <<'FF';
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
FF
}

sub teardown {
}
