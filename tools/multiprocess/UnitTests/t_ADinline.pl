use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use Ffile;
use FTscan;
use FTpat;
# use FTutil;
use ADinline;

use PPsetup;

our($f1,$inl,$f2,$inl2);

setup();

$inl = ADinline->new($f1); # read AD inline file
is((keys %$inl) + 0,2,'proper number of defs');
ok($inl->{push_argument},'name of 1st inline');
ok($inl->{pop_argument},'name of 2nd inline');
is($inl->{push_argument}->{src}->[0],<<L1,'1st line of 1st inline');
          double_argument_checkpoints(dct(call_nr)%dble_argcp_base+dble_argcp_offset)=x
L1

is($inl->{push_argument}->{args}->[0],'x','1st arg of 1st inline');
is($inl->{pop_argument}->{args}->[0],'x','1st arg of 2nd inline');

is(@{$inl->{push_argument}->{args}}+0,1,'total of 1 arg, 1st inline');
is(@{$inl->{pop_argument}->{args}}+0,1,'total of 1 arg, 1st inline');

$inl2 = ADinline->new($f2);
is((keys %$inl2)+0,1,'num entries inl2');
ok($inl2->{saxpy},'inl2 routine');
is($inl2->{saxpy}->{src}->[0],<<S2,'inl2 src');
          y%d=y%d+x%d*a
S2

%b = $inl->mkbind('push_argument',['zzz+top']);
is($b{x},'zzz+top','binding ok');

$s1 = <<S1;
          double_argument_checkpoints(dct(call_nr)%dble_argcp_base+dble_argcp_offset) = zzz+top
          dble_argcp_offset = dble_argcp_offset+1
          double_arguments_pointer = double_arguments_pointer+1

S1

is(join("\n",$inl->mksubs('push_argument',['zzz+top'])),$s1,'subst');

$s2 = <<S2;
          bletch%d = bletch%d+bar%d*foo
S2

is(join("\n",$inl2->mksubs('saxpy',['foo','bar','bletch'])) . "\n",
   $s2,'subst 2');

#is($f3->rewrite($inl->inline())->to_string,'','inlining');

teardown();

sub setup {
    local($Ffile::NO_TRIM) = 1;

    $f1 = Ffile->new_from_heredoc(<<'F1');
        subroutine push_argument(x)
C $OpenAD$  INLINE DECLS
! >>> just to make compile
          use OpenAD_dct
          use OpenAD_checkpoints
          implicit none

          double precision x
          integer dble_argcp_offset, call_nr
! <<<

! to be inlined with whatever actual argument push is called with
! substituted for x >>>
C   $OpenAD$ END DECLS
          double_argument_checkpoints(dct(call_nr)%dble_argcp_base+dble_argcp_offset)=x
          dble_argcp_offset=dble_argcp_offset+1
          double_arguments_pointer=double_arguments_pointer+1

        end subroutine push_argument

        subroutine pop_argument(x)
C   $OpenAD$ INLINE DECLS

          use OpenAD_dct
          use OpenAD_checkpoints
          implicit none

          double precision x
          integer dble_argcp_offset, call_nr

C   $OpenAD$ END DECLS
          x=double_argument_checkpoints(dct(call_nr)%dble_argcp_base+dble_argcp_offset)
          dble_argcp_offset=dble_argcp_offset+1
        end subroutine pop_argument
F1

    $f2 = Ffile->new_from_heredoc(<<'F2');
        subroutine saxpy(a,x,y)
C   $OpenAD$ INLINE DECLS

          double precision, intent(in) :: a
          type(active), intent(in) :: x
          type(active), intent(inout) :: y

C   $OpenAD$ END DECLS
          y%d=y%d+x%d*a
        end subroutine saxpy
F2

    $f3 = Ffile->new_from_heredoc(<<'F3');
        subroutine saxpy(a,x,y)

        type(active) :: OpenAD_Symbol_26
        type(active) :: OpenAD_Symbol_27
        INTEGER(w2f__i4) OpenAD_Symbol_28
        INTEGER(w2f__i4) OpenAD_Symbol_29

      OpenAD_Symbol_20%v = OpenAD_Symbol_0%v
      OpenAD_Symbol_21%v = OpenAD_Symbol_1%v
C     $OpenAD$ INLINE push(subst)
      CALL push_argument(OpenAD_Symbol_14)
C     $OpenAD$ INLINE push(subst)
      CALL push(OpenAD_Symbol_16)
        end subroutine saxpy
F3
}

sub teardown {
    ;
}
