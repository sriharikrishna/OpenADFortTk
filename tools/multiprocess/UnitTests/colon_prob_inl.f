      subroutine cp_arg_store_real_matrix(x,cp_loop_variable_1,
     +cp_loop_variable_2)
C $OpenAD$ INLINE DECLS
      implicit none
      double precision, dimension(::) :: x
C $OpenAD$ END DECLS
      do cp_loop_variable_1=lbound(x,1),ubound(x,1)
         call cp_store_real_vector(x(cp_loop_variable_1,:),
     +theArgFStack,theArgFStackoffset,
     +theArgFStackSize)
      end do
      end subroutine
