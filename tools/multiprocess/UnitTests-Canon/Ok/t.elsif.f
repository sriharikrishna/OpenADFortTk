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
      PARAMETER(nwtype=5)
      Real*8 facz
      Real*8 rfac(nwtype),a1(nwtype),a2(nwtype)
      INTEGER i
      DATA rfac         /  0.58 ,  0.62 ,  0.67 ,  0.77 ,  0.78 /
      DATA a1           /  0.35 ,  0.6  ,  1.0  ,  1.5  ,  1.4  /
      double precision ad_ctmp_0
      double precision ad_ctmp_1
      double precision ad_ctmp_2
      none ad_ctmp_3
      DATA a2           / 23.0  , 20.0  , 17.0  , 14.0  ,  7.9  /
      jwtype=2
      DO i = 1,imax
         facz = fact*swdk(i)
         IF (facz .LT. (-200.)) THEN
            swdk(i) = 0.
         ELSeif (facz .lt. (-100.))
            call s_exp1(facz/a1(jwtype),ad_ctmp_0)
            call s_exp1(facz/a2(jwtype),ad_ctmp_1)
            swdk(i) = rfac(jwtype)*ad_ctmp_0+(1.-rfac(jwtype))*ad_ctmp_1
         ELSE
            call s_exp1(a1(jwtype,ad_ctmp_2)
            swdk(i) = rfac(jwtype)*ad_ctmp_2
         ENDIF
      ENDDO
      call s_do_this(facz,ad_ctmp_3)
      if (ad_ctmp_3) then
         swdk(i) = rfac(jwtype) * 2
c !!! WARNING ---- elsif has a function call !!!
      elseif (do_that(facz))
         swdk(i) = rfac(jwtype) / jwtype
      else
         swdk(i) = swdk(i) - 1.
      endif
      RETURN
      END
