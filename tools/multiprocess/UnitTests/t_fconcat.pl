use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use Ffile;
use FTUnit;

setup();

@units = FTUnit->new(Ffile->new_from_heredoc($ff))->units();
is(@units+0,2,'num units');
is($units[0]->to_string(),$u1,'unit 1');
is($units[1]->to_string(),$u2,'unit 2');
@new_units = map {$_->rewrite(\&chgy)} @units;
is($new_units[1]->to_string(),$f1t,'rewrite 2nd unit');
$final = Ffile->fconcat(@new_units);
is($final->to_string(),$fstr,'concat files');

teardown();

sub setup {
    $u2 = <<'U2';

      subroutine bar(y,zz)

      double complex y
      real zz

      zz = real(y) + 13.25 * imag(y)
      call foo(real(y),zz)
      end subroutine bar
U2
    $u1 = <<'U1';
      subroutine foo(x,y)
      integer x
      real y(4)

      y(1) = x ** y(3)
      end subroutine foo
U1
    $fstr = <<'FSTR';
      subroutine foo(x,YY-WHOO)
      integer x
      real YY-WHOO(4)

      YY-WHOO(1) = x ** YY-WHOO(3)
      end subroutine foo

      subroutine bar(YY-WHOO,zz)

      double complex YY-WHOO
      real zz

      zz = real(YY-WHOO) + 13.25 * imag(YY-WHOO)
      call foo(real(YY-WHOO),zz)
      end subroutine bar
FSTR
    $f1t = <<'F1T';

      subroutine bar(YY-WHOO,zz)

      double complex YY-WHOO
      real zz

      zz = real(YY-WHOO) + 13.25 * imag(YY-WHOO)
      call foo(real(YY-WHOO),zz)
      end subroutine bar
F1T
    $ff = <<'FF';
      subroutine foo(x,y)
      integer x
      real y(4)

      y(1) = x ** y(3)
      end subroutine foo

      subroutine bar(y,zz)

      double complex y
      real zz

      zz = real(y) + 13.25 * imag(y)
      call foo(real(y),zz)
      end subroutine bar
FF
}

sub teardown {
    ;
}

sub chgy {
    my($line) = @_;

    if ($line =~ /\by\b/i) {
	$line =~ s/y/YY-WHOO/g;
	return ($line);
    }
    return ($UNCHANGED);
}
