       subroutine foo()

      do cp_loop_variable_1 = lbound(U,1),ubound(U,1)
         call cp_store_real_vector(U(cp_loop_variable_1,:),theArgFStack,
     +theArgFStackoffset,theArgFStackSize)
      end do

       end
