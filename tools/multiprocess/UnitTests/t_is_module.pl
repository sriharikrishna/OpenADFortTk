use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use Ffile;
use FTscan;
use FTpat;

use PPsetup;
use ADtemplate;


setup();

ok(ADtemplate::is_module($ff),'First case is a module');
ok(! ADtemplate::is_module($ff2),'2nd case is NOT a module');

teardown();

sub setup{
    $w2f1 = <<'W2F1';
C ***********************************************************
C Fortran file translated from WHIRL Tue Sep  2 09:54:45 2003
C ***********************************************************
	module w2f__types

	integer :: w2f__4, w2f__8, w2f__16
	parameter (w2f__4 = kind(0.0))
	parameter (w2f__8 = kind(0.0d0))
	parameter (w2f__16 = selected_real_kind(p=30))

	integer :: w2f__i1, w2f__i2, w2f__i4,w2f__i8
	parameter (w2f__i1 = selected_int_kind(r=2))
	parameter (w2f__i2 = selected_int_kind(r=3))
	parameter (w2f__i4 = selected_int_kind(r=8))
	parameter (w2f__i8 = selected_int_kind(r=16))

	end module w2f__types
C ***********************************************************
W2F1
    $ff = Ffile->new_from_heredoc($w2f1);

    $ff2 = <<'FF2';

      SUBROUTINE head(X, Y, Z)
      use w2f__types
      IMPLICIT NONE
      REAL(w2f__8) X
      INTENT(IN)  X
      REAL(w2f__8) Y
      REAL(w2f__8) Z
      INTENT(IN)  Z

      END SUBROUTINE
FF2
    $ff2 = Ffile->new_from_heredoc($ff2);
}

sub teardown{
}
