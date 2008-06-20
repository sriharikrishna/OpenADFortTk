
        module OAD_active
        use w2f__types
        implicit none
        private
        public :: active, saxpy, sax, setderiv, zero_deriv

        
        !
        ! active needs to be a sequence type
        !  with no initialization
        !
        type active
          sequence
          double precision :: v 
          double precision :: d
        end type active
        
        interface saxpy
          module procedure saxpy_a_a
        end interface
        
        interface setderiv
          module procedure setderiv_a_a
        end interface

        interface zero_deriv
          module procedure zero_deriv_a
        end interface
        
        interface sax
          module procedure sax_d_a_a, sax_i_a_a
        end interface
        
        contains
        
        !
        ! chain rule saxpy to be used in forward and reverse modes
        !
        
        subroutine saxpy_a_a(a,x,y)
          double precision, intent(in) :: a
          type(active), intent(in) :: x
          type(active), intent(inout) :: y
        
          y%d=y%d+x%d*a
        end subroutine saxpy_a_a
        
        !
        ! chain rule saxpy to be used in forward and reverse modes
        ! derivative component of y is equal to zero initially
        ! note: y needs to be inout as otherwise value component gets
        ! zeroed out
        !
        
        subroutine sax_d_a_a(a,x,y)
          double precision, intent(in) :: a
          type(active), intent(in) :: x
          type(active), intent(inout) :: y
        
          y%d=x%d*a
        end subroutine sax_d_a_a

        subroutine sax_i_a_a(a,x,y)
          integer(kind=w2f__i8), intent(in) :: a
          type(active), intent(in) :: x
          type(active), intent(inout) :: y
        
          y%d=x%d*a
        end subroutine sax_i_a_a
        
        !
        ! set derivative of y to be equal to derivative of x
        ! note: making y inout allows for already existing active
        ! variables to become the target of a derivative assignment
        !
        
        subroutine setderiv_a_a(y,x)
          type(active), intent(inout) :: y
          type(active), intent(in) :: x
        
          y%d=x%d
        end subroutine setderiv_a_a

        !
        ! set derivative components to 0.0
        !
        subroutine zero_deriv_a(x)
          type(active), intent(out) :: x

          x%d=0.0d0
        end subroutine zero_deriv_a
        
        end module OAD_active

