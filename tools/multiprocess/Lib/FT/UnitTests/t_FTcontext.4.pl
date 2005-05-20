use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use FTcontext;
use FTpat;
use FTproc;
use FTscan;
use FTscanUtils;
use ADtypes;

setup();

is(join('',$f1->cmap_sem(\&last_decl)),$ld,'last decl F1');
is(join('',$f1->cmap_sem(\&first_exec)),$fe,'first exec F1');
is($f1->crewrite_sem(\&add_incl)->to_string,$f1rw,'add incl');

teardown();

sub setup {
    $ld = 'real xtmp,ytmp';
    $fe = "open(unit = 15,file = 'tfile.txt',form = 'formatted')";

    $f1 = FTcontext->here(<<'F1');
      subroutine t(x,y)
      implicit double precision (a-h,o-z)
      real x,y
      integer i,j,i1,j1,i2,j2
      real xtmp,ytmp

      open(unit=15,file='tfile.txt',form='formatted')
      read(15,*) x
      read(15,*) i,j

c      print *,'x,i,j = ',x,i,j

      y = x * x

      open(unit=16,file='tfile2.txt',form='formatted')
      write(16,*) y
      write(16,*) i,x,j
      write(16,*) i,j
      write(16,*) x

      rewind 16

      read(16,*)xtmp
c      print *,'xtmp after rewind = ',xtmp
      call a(xtmp)
      y = y + xtmp

      read(16,*)i1,xtmp,j1
      read(16,*)  i2,j2
      read(16,*) xtmp

      backspace 16
      backspace 16
      backspace 16

      read(16,*) i2,xtmp,j2
c      print *,'x,i,j after backspace = ',xtmp,i2,j2

      y = y + 3. * xtmp

      close(15)
      close(16)
      end
F1

    $f1rw = <<'F1RW';
      subroutine t(x,y)
      implicit double precision (a-h,o-z)
      real x,y
      integer i,j,i1,j1,i2,j2

      include 'adio.fh'

      real xtmp,ytmp

      open(unit=15,file='tfile.txt',form='formatted')
      read(15,*) x
      read(15,*) i,j

c      print *,'x,i,j = ',x,i,j

      y = x * x

      open(unit=16,file='tfile2.txt',form='formatted')
      write(16,*) y
      write(16,*) i,x,j
      write(16,*) i,j
      write(16,*) x

      rewind 16

      read(16,*)xtmp
c      print *,'xtmp after rewind = ',xtmp
      call a(xtmp)
      y = y + xtmp

      read(16,*)i1,xtmp,j1
      read(16,*)  i2,j2
      read(16,*) xtmp

      backspace 16
      backspace 16
      backspace 16

      read(16,*) i2,xtmp,j2
c      print *,'x,i,j after backspace = ',xtmp,i2,j2

      y = y + 3. * xtmp

      close(15)
      close(16)
      end
F1RW

    $FLAST = '';
}

sub teardown {
}

sub last_decl {
#    return $_[0]->scan()->str() if ($_[0]->getprop('_last_decl'));
    if ($_[0]->getprop('_last_decl')){
	return $_[0]->scan()->str();
    }
    return ();
}

sub first_exec {
    return $_[0]->scan()->str() if ($_[0]->getprop('_first_exec'));
    return ();
}

sub add_incl {
    if ($_[0]->getprop('_last_decl')){
	return('',
	       $_[0]->same_level("include 'adio.fh'"),
	       '',
	       $_[0]);

    }
    return ($_[0]);
}
