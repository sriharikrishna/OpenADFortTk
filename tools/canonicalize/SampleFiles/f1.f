C
C     **** Statements ****
C
      t__922 = IMAX
      t__924 = MAX(t__922, 0_w2f__i8)
      JWTYPE = 2
      doloop_ub = IMAX
      DO I = 1, doloop_ub, 1
        FACZ = SWDK(I) * FACT
        IF(FACZ .LT.(-2.0D+02)) THEN
          SWDK(I) = 0.0
        ELSE
          SWDK(I) = (RFAC(JWTYPE) * EXP(FACZ / A1(JWTYPE)) + EXP(FACZ /
     >  A2(JWTYPE)) *(1.0D00 - RFAC(JWTYPE)))
        ENDIF
      END DO
      RETURN
      RETURN
      END SUBROUTINE
