C ***********************************************************
C Fortran file translated from WHIRL XXX
C ***********************************************************
C ***********************************************************

      SUBROUTINE head(X, Y)
      use w2f__types
      IMPLICIT NONE
C
C     **** Global Variables ****
C
      REAL(w2f__8) OpenAD_Symbol_0
      REAL(w2f__8) OpenAD_Symbol_1
      REAL(w2f__8) OpenAD_Symbol_10
      REAL(w2f__8) OpenAD_Symbol_2
      REAL(w2f__8) OpenAD_Symbol_11
      REAL(w2f__8) OpenAD_Symbol_3
      REAL(w2f__8) OpenAD_Symbol_12
      REAL(w2f__8) OpenAD_Symbol_4
      REAL(w2f__8) OpenAD_Symbol_13
      REAL(w2f__8) OpenAD_Symbol_5
      REAL(w2f__8) OpenAD_Symbol_14
      REAL(w2f__8) OpenAD_Symbol_6
      REAL(w2f__8) OpenAD_Symbol_20
      REAL(w2f__8) OpenAD_Symbol_15
      REAL(w2f__8) OpenAD_Symbol_7
      REAL(w2f__8) OpenAD_Symbol_21
      REAL(w2f__8) OpenAD_Symbol_16
      REAL(w2f__8) OpenAD_Symbol_8
      REAL(w2f__8) OpenAD_Symbol_17
      REAL(w2f__8) OpenAD_Symbol_9
      REAL(w2f__8) OpenAD_Symbol_18
      REAL(w2f__8) OpenAD_Symbol_19
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) X
      INTENT(IN)  X
      REAL(w2f__8) Y
C
C     **** Local Variables and functions ****
C
      REAL(w2f__8) T1
      REAL(w2f__8) T2
      REAL(w2f__8) OpenAD_Symbol_22
      REAL(w2f__8) OpenAD_Symbol_23
      REAL(w2f__8) OpenAD_Symbol_24
      REAL(w2f__8) OpenAD_Symbol_25
      REAL(w2f__8) OpenAD_Symbol_26
      REAL(w2f__8) OpenAD_Symbol_27
      INTEGER(w2f__i4) OpenAD_Symbol_28
      INTEGER(w2f__i4) OpenAD_Symbol_29
C
C     **** statements ****
C
C     $OpenAD$ BEGIN REPLACEMENT 1
      __value__(T1) = (__value__(X) * __value__(Y))
      __value__(T2) = (__value__(Y) + __value__(X) * __value__(T1))
      __value__(Y) = (__value__(T1) + __value__(T2))
      RETURN
C     $OpenAD$ END REPLACEMENT
C     $OpenAD$ BEGIN REPLACEMENT 2
      __value__(OpenAD_Symbol_2) = (__value__(X) * __value__(Y))
      __value__(OpenAD_Symbol_0) = __value__(Y)
      __value__(OpenAD_Symbol_1) = __value__(X)
      __value__(T1) = __value__(OpenAD_Symbol_2)
      __value__(OpenAD_Symbol_7) = (__value__(Y) + __value__(X) *
     >  __value__(T1))
      __value__(OpenAD_Symbol_3) = 1
      __value__(OpenAD_Symbol_5) = __value__(T1)
      __value__(OpenAD_Symbol_6) = __value__(X)
      __value__(OpenAD_Symbol_4) = 1
      __value__(T2) = __value__(OpenAD_Symbol_7)
      __value__(Y) = (__value__(T1) + __value__(T2))
      __value__(OpenAD_Symbol_8) = 1
      __value__(OpenAD_Symbol_9) = 1
      __value__(OpenAD_Symbol_10) = (__value__(OpenAD_Symbol_5) +
     >  __value__(OpenAD_Symbol_0) * __value__(OpenAD_Symbol_6))
      __value__(OpenAD_Symbol_11) = (__value__(OpenAD_Symbol_1) *
     >  __value__(OpenAD_Symbol_6))
      __value__(OpenAD_Symbol_12) = (__value__(OpenAD_Symbol_0) *
     >  __value__(OpenAD_Symbol_8))
      __value__(OpenAD_Symbol_13) = (__value__(OpenAD_Symbol_1) *
     >  __value__(OpenAD_Symbol_8))
      __value__(OpenAD_Symbol_14) = (__value__(OpenAD_Symbol_10) *
     >  __value__(OpenAD_Symbol_4))
      __value__(OpenAD_Symbol_16) = (__value__(OpenAD_Symbol_3) +
     >  __value__(OpenAD_Symbol_11) * __value__(OpenAD_Symbol_4))
      __value__(OpenAD_Symbol_18) = (__value__(OpenAD_Symbol_13) +
     >  __value__(OpenAD_Symbol_16) * __value__(OpenAD_Symbol_9))
      __value__(OpenAD_Symbol_19) = (__value__(OpenAD_Symbol_12) +
     >  __value__(OpenAD_Symbol_14) * __value__(OpenAD_Symbol_9))
      __value__(OpenAD_Symbol_20) = __value__(OpenAD_Symbol_0)
      __value__(OpenAD_Symbol_21) = __value__(OpenAD_Symbol_1)
C     $OpenAD$ INLINE push(subst)
      CALL push(__deriv__(OpenAD_Symbol_14))
C     $OpenAD$ INLINE push(subst)
      CALL push(__deriv__(OpenAD_Symbol_16))
C     $OpenAD$ INLINE push(subst)
      CALL push(__deriv__(OpenAD_Symbol_18))
C     $OpenAD$ INLINE push(subst)
      CALL push(__deriv__(OpenAD_Symbol_19))
C     $OpenAD$ INLINE push(subst)
      CALL push(__deriv__(OpenAD_Symbol_20))
C     $OpenAD$ INLINE push(subst)
      CALL push(__deriv__(OpenAD_Symbol_21))
      RETURN
C     $OpenAD$ END REPLACEMENT
C     $OpenAD$ BEGIN REPLACEMENT 3
C     $OpenAD$ INLINE Pop(subst)
      CALL Pop(__deriv__(OpenAD_Symbol_22))
C     $OpenAD$ INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(__deriv__(OpenAD_Symbol_22), __deriv__(T1), __deriv__(
     > OpenAD_Symbol_17))
C     $OpenAD$ INLINE Pop(subst)
      CALL Pop(__deriv__(OpenAD_Symbol_23))
C     $OpenAD$ INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(__deriv__(OpenAD_Symbol_23), __deriv__(T1), __deriv__(
     > OpenAD_Symbol_15))
C     $OpenAD$ INLINE ZeroDeriv(subst)
      CALL ZeroDeriv(__deriv__(T1))
C     $OpenAD$ INLINE Pop(subst)
      CALL Pop(__deriv__(OpenAD_Symbol_24))
C     $OpenAD$ INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(__deriv__(OpenAD_Symbol_24), __deriv__(Y), __deriv__(
     > OpenAD_Symbol_15))
C     $OpenAD$ INLINE Pop(subst)
      CALL Pop(__deriv__(OpenAD_Symbol_25))
C     $OpenAD$ INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(__deriv__(OpenAD_Symbol_25), __deriv__(Y), __deriv__(
     > OpenAD_Symbol_17))
C     $OpenAD$ INLINE ZeroDeriv(subst)
      CALL ZeroDeriv(__deriv__(Y))
C     $OpenAD$ INLINE Pop(subst)
      CALL Pop(__deriv__(OpenAD_Symbol_26))
C     $OpenAD$ INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(__deriv__(OpenAD_Symbol_26), __deriv__(T2), __deriv__(
     > OpenAD_Symbol_17))
C     $OpenAD$ INLINE Pop(subst)
      CALL Pop(__deriv__(OpenAD_Symbol_27))
C     $OpenAD$ INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(__deriv__(OpenAD_Symbol_27), __deriv__(T2), __deriv__(
     > OpenAD_Symbol_15))
C     $OpenAD$ INLINE ZeroDeriv(subst)
      CALL ZeroDeriv(__deriv__(T2))
      OpenAD_Symbol_28 = 1
C     $OpenAD$ INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(OpenAD_Symbol_28, __deriv__(OpenAD_Symbol_15),
     >  __deriv__(X))
C     $OpenAD$ INLINE ZeroDeriv(subst)
      CALL ZeroDeriv(__deriv__(OpenAD_Symbol_15))
      OpenAD_Symbol_29 = 1
C     $OpenAD$ INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(OpenAD_Symbol_29, __deriv__(OpenAD_Symbol_17),
     >  __deriv__(Y))
C     $OpenAD$ INLINE ZeroDeriv(subst)
      CALL ZeroDeriv(__deriv__(OpenAD_Symbol_17))
C     $OpenAD$ END REPLACEMENT
      END SUBROUTINE
