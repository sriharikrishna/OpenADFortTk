!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
! A simple program with some pragmas
!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

program pragmatest
  implicit none

  double precision :: x
  double precision :: y
  double precision, dimension(10) :: a, b
  integer :: ix, i
  integer :: jjj
  
  !*$*align_symbol(x, 16)
  !*$*align_symbol(ix, 32)
  x = x * x + 3.1415 - y
  ix = ix / ix + jjj

  a = 3
  b = 5
  
  !*$* UNROLL (2)
  DO i = 1, 10
     a(i) = a(i) + b(i)
  END DO

  !DIR$ IVDEP
  !do i = 1, 10
  !   b(i) = a(i) + 3.0
  !enddo
  
  ! Some other pragmas
  !!MIC$ NUMCPUS
  !!MIC$ CNCALL
  !!MIC$ DO PARALLEL
  !!MIC$ PARALLEL
  !!MIC$ GUARD
  !!MIC$ END GUARD
  !!DIR$ BOUNDS
  !!DIR$ NOBOUNDS
  !!DIR$ FREE
  !!DIR$ FIXED
  !!DIR$ ID
  !!DIR$ IVDEP
  !!DIR$ NAME

  !$OMP SECTIONS
  !$OMP SECTION  
  !$OMP END SECTIONS

end program
