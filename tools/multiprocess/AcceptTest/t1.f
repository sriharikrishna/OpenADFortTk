      SUBROUTINE top(z)
      use w2f__types
      REAL(w2f__8) OpenAD_Symbol_0
      REAL(w2f__8) z
      REAL(w2f__8) T2
C
C     **** statements ****
C
C     $OpenAD$ BEGIN REPLACEMENT 1
c$OpenAD XXX Template ad_template.f
      __value__(T1) = (__value__(X) * __value__(Y))
      RETURN
C     $OpenAD$ END REPLACEMENT
C     $OpenAD$ BEGIN REPLACEMENT 2
      __value__(OpenAD_Symbol_7) = (__value__(junk) + __value__(X) *
     >  __value__(T1))
C     $OpenAD$ INLINE push(subst)
      CALL push(__deriv__(OpenAD_Symbol_14))
      RETURN
C     $OpenAD$ END REPLACEMENT
C     $OpenAD$ BEGIN REPLACEMENT 3
C     $OpenAD$ INLINE Pop(subst)
      CALL Pop(__deriv__(OpenAD_Symbol_22))
      OpenAD_Symbol_29 = 1
C     $OpenAD$ END REPLACEMENT
      END SUBROUTINE

c  No template specified, so use default template
c
      SUBROUTINE head(X, Y)
      use w2f__types
      IMPLICIT NONE
      REAL(w2f__8) OpenAD_Symbol_0
      REAL(w2f__8) OpenAD_Symbol_1
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) X
      INTENT(IN)  X
      REAL(w2f__8) Y

      REAL(w2f__8) T1
      REAL(w2f__8) T2
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
      __value__(OpenAD_Symbol_7) = (__value__(Y) + __value__(X) *
     >  __value__(T1))
C     $OpenAD$ INLINE push(subst)
      CALL push(__deriv__(OpenAD_Symbol_14))
C     $OpenAD$ INLINE push(subst)
      CALL push(__deriv__(OpenAD_Symbol_16))
      RETURN
C     $OpenAD$ END REPLACEMENT
C     $OpenAD$ BEGIN REPLACEMENT 3
C     $OpenAD$ INLINE Pop(subst)
      CALL Pop(__deriv__(OpenAD_Symbol_22))
C     $OpenAD$ INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(__deriv__(OpenAD_Symbol_22), __deriv__(T1), __deriv__(
     > OpenAD_Symbol_17))
C     $OpenAD$ INLINE ZeroDeriv(subst)
      CALL ZeroDeriv(__deriv__(OpenAD_Symbol_15))
      OpenAD_Symbol_29 = 1
C     $OpenAD$ END REPLACEMENT
      END SUBROUTINE
