use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use Ffile;
use FTscan;
use FTpat;
#use FTutil;
use ADinline;

use PPsetup;

our($f1,$inl,$f2);

setup();

$inl = ADinline->new($f1); # read AD inline file

is($f2->rewrite($inl->inline())->to_string,$r2,'inlining operation');

teardown();

sub setup {
    local($Ffile::NO_TRIM) = 1;

    $f1 = Ffile->new_from_heredoc(<<'F1');
        subroutine push_argument(x)
C $OpenAD  INLINE DECLS
! >>> just to make compile
          use OpenAD_dct
          use OpenAD_checkpoints
          implicit none

          double precision x
          integer dble_argcp_offset, call_nr
! <<<

! to be inlined with whatever actual argument push is called with
! substituted for x >>>
C   $OpenAD END DECLS
          double_argument_checkpoints(dct(call_nr)%dble_argcp_base+dble_argcp_offset)=x
          dble_argcp_offset=dble_argcp_offset+1
          double_arguments_pointer=double_arguments_pointer+1

        end subroutine push_argument

        subroutine pop_argument(x)
C   $OpenAD INLINE DECLS

          use OpenAD_dct
          use OpenAD_checkpoints
          implicit none

          double precision x
          integer dble_argcp_offset, call_nr

C   $OpenAD END DECLS
          x=double_argument_checkpoints(dct(call_nr)%dble_argcp_base+dble_argcp_offset)
          dble_argcp_offset=dble_argcp_offset+1
        end subroutine pop_argument

        subroutine saxpy(a,x,y)
C   $OpenAD INLINE DECLS

          double precision, intent(in) :: a
          type(active), intent(in) :: x
          type(active), intent(inout) :: y

C   $OpenAD END DECLS
          y%d=y%d+x%d*a
        end subroutine saxpy

        subroutine push(x)
C   $OpenAD INLINE DECLS
          use OpenAD_tape
          implicit none
          double precision :: x

C   $OpenAD END DECLS
          double_tape(double_tape_pointer)=x
          double_tape_pointer=double_tape_pointer+1
        end subroutine push

        subroutine pop(x)
C   $OpenAD INLINE DECLS
          use OpenAD_tape
          implicit none
          double precision :: x

C   $OpenAD END DECLS
          double_tape_pointer=double_tape_pointer-1
          x=double_tape(double_tape_pointer)
        end subroutine pop

F1

    $f2 = Ffile->new_from_heredoc(<<'F2');
        subroutine foo1(a,x,y)

        type(active) :: OpenAD_Symbol_26
        type(active) :: OpenAD_Symbol_27
        INTEGER(w2f__i4) OpenAD_Symbol_28
        INTEGER(w2f__i4) OpenAD_Symbol_29

      OpenAD_Symbol_20%v = OpenAD_Symbol_0%v
      OpenAD_Symbol_21%v = OpenAD_Symbol_1%v
C     $OpenAD INLINE push(subst)
      CALL push_argument(OpenAD_Symbol_14)
C     $OpenAD INLINE push(subst)
      CALL push(OpenAD_Symbol_16)
C     $OpenAD INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(OpenAD_Symbol_22,T1,OpenAD_Symbol_17)
        end subroutine foo1

        subroutine foo2(a)

        type(active) :: OpenAD_Symbol_26
        type(active) :: OpenAD_Symbol_27
        INTEGER(w2f__i4) OpenAD_Symbol_28
        INTEGER(w2f__i4) OpenAD_Symbol_29

      OpenAD_Symbol_20%v = OpenAD_Symbol_0%v
      OpenAD_Symbol_21%v = OpenAD_Symbol_1%v
C     $OpenAD INLINE push(subst)
      CALL push_argument(OpenAD_Symbol_14)
C     $OpenAD INLINE push_result(subst)
      CALL push_result(OpenAD_Symbol_16)
C     $OpenAD INLINE Saxpy(subst,subst,subst)
      CALL Saxpy(T1+25.2*(t2+t3),OpenAD_Symbol_22,OpenAD_Symbol_17)
        end subroutine foo2
F2

    $r2 = <<'R2';
        subroutine foo1(a,x,y)

        type(active) :: OpenAD_Symbol_26
        type(active) :: OpenAD_Symbol_27
        INTEGER(w2f__i4) OpenAD_Symbol_28
        INTEGER(w2f__i4) OpenAD_Symbol_29

      OpenAD_Symbol_20%v = OpenAD_Symbol_0%v
      OpenAD_Symbol_21%v = OpenAD_Symbol_1%v
          double_argument_checkpoints(dct(call_nr)%dble_argcp_base+dble_
     +argcp_offset) = OpenAD_Symbol_14
          dble_argcp_offset = dble_argcp_offset+1
          double_arguments_pointer = double_arguments_pointer+1


          double_tape(double_tape_pointer) = OpenAD_Symbol_16
          double_tape_pointer = double_tape_pointer+1
          OpenAD_Symbol_17%d = OpenAD_Symbol_17%d+T1%d*OpenAD_Symbol_22
        end subroutine foo1

        subroutine foo2(a)

        type(active) :: OpenAD_Symbol_26
        type(active) :: OpenAD_Symbol_27
        INTEGER(w2f__i4) OpenAD_Symbol_28
        INTEGER(w2f__i4) OpenAD_Symbol_29

      OpenAD_Symbol_20%v = OpenAD_Symbol_0%v
      OpenAD_Symbol_21%v = OpenAD_Symbol_1%v
          double_argument_checkpoints(dct(call_nr)%dble_argcp_base+dble_
     +argcp_offset) = OpenAD_Symbol_14
          dble_argcp_offset = dble_argcp_offset+1
          double_arguments_pointer = double_arguments_pointer+1


C!! requested inline of 'push_result' has no defn
      CALL push_result(OpenAD_Symbol_16)
          OpenAD_Symbol_17%d = OpenAD_Symbol_17%d+OpenAD_Symbol_22%d*T1+
     +25.2*(t2+t3)
        end subroutine foo2
R2
}

sub teardown {
    ;
}
