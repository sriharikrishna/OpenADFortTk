!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
! A simple program with scalar operations
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

subroutine d_head(x, d_x, y, d_y) 
  double precision, intent(in) :: x, d_x
  double precision, intent(inout) :: y, d_y
  double precision t1, t2, xb_aux_1__, xb_aux_2__ 
  double precision xb_aux_3__, xb_aux_4__, xb_aux_5__
  integer i

  i=1
  xb_aux_1__=sin(x)
  xb_aux_2__=cos(x)
  t1=xb_aux_1__*y
  t2=t1*x+i
  y=t1+t2

  xb_aux_3__=x+1
  xb_aux_4__=t1+xb_aux_2__*y*xb_aux_3__
  xb_aux_5__=xb_aux_1__*xb_aux_3__

  d_y = d_x*xb_aux_4__+d_y*xb_aux_5__

end subroutine


program simple2

  double precision :: x, d_x, y, d_y
  x = 45
  d_x = 9;
  y = 60
  d_y = 13;

  call d_head(x, d_x, y, d_y)
  write(*,*) y
  write(*,*) d_y

end program

