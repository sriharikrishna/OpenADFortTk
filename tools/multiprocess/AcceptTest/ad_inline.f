        subroutine push(x)
C $OpenAD$  INLINE DECLS
          use OpenAD_tape
          implicit none
          double precision :: x

C   $OpenAD$ END DECLS
          double_tape(double_tape_pointer)=x
          double_tape_pointer=double_tape_pointer+1
        end subroutine push
        subroutine pop(x)
C $OpenAD$  INLINE DECLS
          use OpenAD_tape
          implicit none
          double precision :: x

C   $OpenAD$ END DECLS
          double_tape_pointer=double_tape_pointer-1
          x=double_tape(double_tape_pointer)
        end subroutine pop
        subroutine saxpy(a,x,y)
C $OpenAD$  INLINE DECLS
          double precision, intent(in) :: a
          type(active), intent(in) :: x
          type(active), intent(inout) :: y
        
C   $OpenAD$ END DECLS
          y%d=y%d+x%d*a
        end subroutine saxpy
        subroutine zeroderiv(x)
C $OpenAD$  INLINE DECLS
          type(active), intent(out) :: x

C   $OpenAD$ END DECLS
          x%d=0.0d0
        end subroutine zeroderiv
