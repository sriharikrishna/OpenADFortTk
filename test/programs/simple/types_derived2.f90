!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
! A program with a user defined type.
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

module coord2d

  type cart
     real :: x
     real :: y
     character(len=20) :: msg
  end type cart

  type polar
     real :: r
     real :: theta ! radians
     character(len=20) :: msg
  end type polar

end module coord2d


subroutine cart2polar(c, p)
  use coord2d

  type(cart), intent(in) :: c
  type(polar), intent(out) :: p
  
  ! r^2 = x^2 + y^2
  p%r = sqrt((c%x)**2 + (c%y)**2)
  
  ! sin(theta) = y/r (more convenient than tan(theta) = y/x)
  if (p%r .eq. 0) then
     p%theta = 0
  else
     p%theta = asin(c%y/p%r)
  end if
  
  p%msg = "because"
end subroutine cart2polar


program dosomething
  use coord2d
  implicit none

  type(cart) :: c
  type(polar) :: p
  integer :: n
  
  c = cart(n, 9, 'why?')

  call cart2polar(c, p)
  
  write(*,*) 'cart c =', c
  write(*,*) 'polar p =', p
  
end program dosomething
