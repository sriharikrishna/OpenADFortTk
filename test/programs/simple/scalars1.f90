!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
! A simple program with scalar addition and multiplication
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

subroutine head(x, y) 
  double precision, intent(in) :: x
  double precision, intent(inout) :: y
  double precision t1, t2

  t1=x*y
  t2=t1*x+y
  y=t1+t2

end subroutine
