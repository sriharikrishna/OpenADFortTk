use FindBin qw($RealBin);
use lib "$RealBin/..";
use Test::More qw(no_plan);
use FTcontext;

my($ctx) = setup();
my(@u)= $ctx->units();
is(@u+0,1,'context has 1 unit');
($f,$s) = ($u[0]->{_unit},$u[0]->{_symtab});
is($s->lookup_type('a1'),'double precision','type a1 is real*8');
is($s->lookup_dims('a1')+0,1,'# dims a1 is 1');

sub setup{

    my($f) = FTcontext->here(<<'F');
      SUBROUTINE SWFRAC(
     I     imax, fact,
     I     mytime, mythid,
     U     swdk )
      IMPLICIT NONE
      INTEGER imax
      Real*8     fact
      Real*8     mytime
      integer mythid
      Real*8     swdk(imax)
      integer   nwtype  , jwtype
      PARAMETER(nwtype=5)
      Real*8 facz
      Real*8 rfac(nwtype),a1(nwtype),a2(nwtype)
      INTEGER i
      DATA rfac         /  0.58 ,  0.62 ,  0.67 ,  0.77 ,  0.78 /
      DATA a1           /  0.35 ,  0.6  ,  1.0  ,  1.5  ,  1.4  /
      DATA a2           / 23.0  , 20.0  , 17.0  , 14.0  ,  7.9  /
      jwtype=2
      DO i = 1,imax
         facz = fact*swdk(i)
         IF (facz .LT. (-200.)) THEN
            swdk(i) = 0.
         ELSE
            swdk(i) =       rfac(jwtype)  * exp(facz/a1(jwtype))
     $                + (1.-rfac(jwtype)) * exp(facz/a2(jwtype))
         ENDIF
      ENDDO
      RETURN
      END
F

    return $f;

}
sub teardown {
}
