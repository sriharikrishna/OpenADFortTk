!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
! A simple program to test control flow (if-then)
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

! the goto jumps out a level
subroutine controlflow_if(xx)
      implicit none
      double precision, intent(in) :: xx
      double precision :: x, y
  
      x = xx
      if ( x .ge. 0. ) then
         goto 10
      else
         y = 3
      endif
      
      x = 89
      
 10   y = 89
      
end subroutine controlflow_if
    
