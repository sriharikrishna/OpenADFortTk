       subroutine foo(x,y,call_nr,version)
!          implicit none
       use w2f__types
      use active_module
C
C     **** statements ****
C
          integer, intent(in) :: call_nr

          print *,'in subroutine foo'
      do cp_loop_variable_1 = lbound(U,1),ubound(U,1)
         call cp_store_real_vector(U(cp_loop_variable_1,:),theArgFStack,
     +theArgFStackoffset,theArgFStackSize)
      end do
      end subroutine foo
       subroutine bar(x,y,call_nr,version)
!          implicit none
       use w2f__types
      use active_module
C
C     **** statements ****
C
          integer, intent(in) :: call_nr

          print *,'in subroutine bar'
      do cp_loop_variable_1 = lbound(V,1),ubound(V,1)
         call cp_store_real_vector(V(cp_loop_variable_1,:),theArgFStack,
     +theArgFStackoffset,theArgFStackSize)
      end do
      end subroutine bar
