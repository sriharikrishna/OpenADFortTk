!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
! A program with a user defined type.
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

module coordrec

  type cart
     real :: x
     real :: y
  end type cart

end module coordrec


function distanceFromOrigin(c) result(r)
  use coordrec
  
  type(cart), intent(in) :: c
  
  ! r^2 = x^2 + y^2
  r = sqrt((c%x)**2 + (c%y)**2)

end function distanceFromOrigin


program dosomething
  use coordrec

  type(cart) :: c
  integer :: n = 7
  real :: d
  
  c = cart(n, n)

  d = distanceFromOrigin(c)
  
end program dosomething
