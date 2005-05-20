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

is($f1->crewrite_sem(\&real_com)->to_string(),$f1rw,'F1 rewrite');

teardown();

sub setup {
    $f1 = FTcontext->here(<<'F1');
      subroutine t(x,y)
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
      if (adio(16)) then
          write(adunit(16),*) g_y
      endif
      write(16,*) i,x,j
      if (adio(16)) then
          write(adunit(16),*) i,g_x,j
      endif
      write(16,*) i,j
      if (adio(16)) then
          write(adunit(16),*) i,j
      endif
      write(16,*) x
      if (adio(16)) then
          write(adunit(16),*) g_x
      endif

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

sub real_com {
    if ($_[0]->match(qr/^ write/ix)){
	return fix(@_);
    }
    return ($_[0]);
}
sub fix {
    my($line,$st) = @_;

    my($spec,$args) = $line->match(qr/^ write $TB \( $TB (.+) $TB \) $TB
                                      (.+) $/ix);

    my($newargs) = sl_join(',',map {alter($_,$st)} $args->cbreak());
    my($pre,$nspec) = spec($spec);
    $pre = $line->same_level($pre);
    my($endif) = $line->same_level('endif');
    my($new) = $line->same_level('write')->concatd($nspec,$newargs)
	       ->plus_indent(' ' x 4);
    return ($line,$pre,$new,$endif);
}
sub alter {
    if (adtype($_[1]->lookup_type($_[0]->str()))){
	return FTscan->new('g_' . $_[0]->str())
    }
    return $_[0];
}
sub spec {
    my(@s) = $_[0]->cbreak();
    my($u);
    if (grep {$_->match(qr/^ unit $TB = $TB /ix)} @s ){
	for (@s) {
	    if (($u) = $_->match(qr/^ unit $TB = $TB (.+) $/)){
		$_->set_tl('unit','=','adunit','(')->concatd($u,')');
	    }
	}
    } else {
	$u = shift @s;
	unshift @s,FTscan->new('adunit(')->concatd($u,')');
    }
    return (FTscan->new('if (adio(')->concatd($u,')',')','then'),
	    FTscan->new('(')->concatd(sl_join(',',@s),')'),);
}
