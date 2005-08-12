      SUBROUTINE SWFRAC(
     I     imax, fact,
     I     mytime, mythid,
     U     swdk )
      IMPLICIT NONE
      INTEGER imax
      external   exp1
      Real*8     exp1
      Real*8     fact
      Real*8     mytime
      integer mythid
      Real*8     swdk(imax)
      integer   nwtype  , jwtype
      character*80 foo,bar
      PARAMETER(nwtype=5)
      Real*8 facz
      Real*8 rfac(nwtype),a1(nwtype),a2(nwtype)
      INTEGER i
      DATA rfac         /  0.58 ,  0.62 ,  0.67 ,  0.77 ,  0.78 /
      DATA a1           /  0.35 ,  0.6  ,  1.0  ,  1.5  ,  1.4  /
      double precision ad_ctmp_0
      DATA a2           / 23.0  , 20.0  , 17.0  , 14.0  ,  7.9  /
      jwtype=2
      facz = fact*swdk(i)
      call s_exp1(foo(3:15),ad_ctmp_0)
      rfac = ad_ctmp_0
      bar = foo(7:15) // foo(1:10)
      RETURN
      END
