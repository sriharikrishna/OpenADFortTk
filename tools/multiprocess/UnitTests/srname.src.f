       subroutine foo(x,y)
       use w2f__types
C
C     **** statements ****
C
C     $OpenAD$ BEGIN REPLACEMENT 1
C      $OpenAD$ INLINE cp_arg_store_real_matrix(subst)
       CALL cp_arg_store_real_matrix(__deriv__(U))
C     $OpenAD$ END REPLACEMENT

       end

       subroutine bar(x,y)
       use w2f__types
C
C     **** statements ****
C
C     $OpenAD$ BEGIN REPLACEMENT 1
C      $OpenAD$ INLINE cp_arg_store_real_matrix(subst)
       CALL cp_arg_store_real_matrix(__deriv__(V))
C     $OpenAD$ END REPLACEMENT

       end
