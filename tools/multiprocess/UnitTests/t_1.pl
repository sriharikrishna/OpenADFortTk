use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use Ffile;
use FTscan;
use FTpat;

use PPsetup;

setup();
ok(1,'read from FT library');
ok($FTList::_RETAIN_CASE,'retain case variable set');
is(ref($ff),'Ffile','test ffile built correctly');
is($ff->rewrite_sem(\&x2w1)->to_string(),$w2f1_add_use,'add use statement');
is($ff->rewrite_sem(\&x2w2)->to_string(),$w2f1_active,'changed types');
is($ff->rewrite_sem(\&x2w3)->to_string(),$w2f1_noval,'changed __value'); 
# is($ff->rewrite_sem(\&x2w3)->to_string(),'','changed __value'); 
teardown();

sub setup{
    $w2f1 = <<'W2F1';
C ***********************************************************
C Fortran file translated from WHIRL Tue Sep  2 09:54:45 2003
C ***********************************************************
	module w2f__types

	integer :: w2f__4, w2f__8, w2f__16
	parameter (w2f__4 = kind(0.0))
	parameter (w2f__8 = kind(0.0d0))
	parameter (w2f__16 = selected_real_kind(p=30))

	integer :: w2f__i1, w2f__i2, w2f__i4,w2f__i8
	parameter (w2f__i1 = selected_int_kind(r=2))
	parameter (w2f__i2 = selected_int_kind(r=3))
	parameter (w2f__i4 = selected_int_kind(r=8))
	parameter (w2f__i8 = selected_int_kind(r=16))

	end module w2f__types
C ***********************************************************

      SUBROUTINE head(X, Y, Z)
      use w2f__types
      IMPLICIT NONE
      REAL(w2f__8) X
      INTENT(IN)  X
      REAL(w2f__8) Y
      REAL(w2f__8) Z
      INTENT(IN)  Z
      
      
      
C
C     **** Variables and functions ****
C
      REAL(w2f__8) SymbolTable_0x82c9e58_2
      REAL(w2f__8) SymbolTable_0x82c9e58_3
      REAL(w2f__8) SymbolTable_0x82c9e58_4
      REAL(w2f__8) SymbolTable_0x82c9e58_5
      REAL(w2f__8) SymbolTable_0x82c9e58_6
      REAL(w2f__8) SymbolTable_0x82c9e58_7
      REAL(w2f__8) SymbolTable_0x82c9e58_8
      REAL(w2f__8) SymbolTable_0x82c9e58_9
      REAL(w2f__8) SymbolTable_0x82c9e58_10
      REAL(w2f__8) SymbolTable_0x82c9e58_11
      REAL(w2f__8) SymbolTable_0x82c9e58_12
      REAL(w2f__8) SymbolTable_0x82c9e58_13
      REAL(w2f__8) SymbolTable_0x82c9e58_14
      REAL(w2f__8) SymbolTable_0x82c9e58_15
      REAL(w2f__8) SymbolTable_0x82c9e58_16
      REAL(w2f__8) SymbolTable_0x82c9e58_17
      REAL(w2f__8) SymbolTable_0x82c9e58_18
      REAL(w2f__8) SymbolTable_0x82c9e58_19
      REAL(w2f__8) SymbolTable_0x82c9e58_0
      REAL(w2f__8) SymbolTable_0x82c9e58_1
C
C     **** statements ****
C
      __value__(SymbolTable_0x82c9e58_19) = __value__(Y)
      __value__(SymbolTable_0x82c9e58_17) = __value__(X)
      __value__(SymbolTable_0x82c9e58_14) = __value__(Z)
      __value__(SymbolTable_0x82c9e58_5) = (__value__(X) * __value__(Y)
     > )
      __value__(SymbolTable_0x82c9e58_2) = (__value__(Z) * __value__(
     > SymbolTable_0x82c9e58_5))
      __value__(SymbolTable_0x82c9e58_10) = (__value__(Z) +(__value__(X
     > ) * __value__(SymbolTable_0x82c9e58_2)))
      __value__(SymbolTable_0x82c9e58_0) = 1
      __value__(SymbolTable_0x82c9e58_3) = __value__(
     > SymbolTable_0x82c9e58_2)
      __value__(SymbolTable_0x82c9e58_6) = __value__(
     > SymbolTable_0x82c9e58_5)
      __value__(SymbolTable_0x82c9e58_8) = __value__(Y)
      __value__(SymbolTable_0x82c9e58_9) = __value__(X)
      __value__(SymbolTable_0x82c9e58_7) = __value__(Z)
      __value__(SymbolTable_0x82c9e58_4) = __value__(X)
      __value__(SymbolTable_0x82c9e58_1) = 1
      __value__(Y) = __value__(SymbolTable_0x82c9e58_10)
      __value__(SymbolTable_0x82c9e58_11) = (__value__(
     > SymbolTable_0x82c9e58_3) * __value__(SymbolTable_0x82c9e58_1))
      __value__(SymbolTable_0x82c9e58_12) = (__value__(
     > SymbolTable_0x82c9e58_4) * __value__(SymbolTable_0x82c9e58_1))
      __value__(SymbolTable_0x82c9e58_13) = (__value__(
     > SymbolTable_0x82c9e58_0) +(__value__(SymbolTable_0x82c9e58_6) *
     >  __value__(SymbolTable_0x82c9e58_12)))
      __value__(SymbolTable_0x82c9e58_15) = (__value__(
     > SymbolTable_0x82c9e58_7) * __value__(SymbolTable_0x82c9e58_12))
      __value__(SymbolTable_0x82c9e58_16) = (__value__(
     > SymbolTable_0x82c9e58_11) +(__value__(SymbolTable_0x82c9e58_8) *
     >  __value__(SymbolTable_0x82c9e58_15)))
      __value__(SymbolTable_0x82c9e58_18) = (__value__(
     > SymbolTable_0x82c9e58_9) * __value__(SymbolTable_0x82c9e58_15))
      CALL sax_a_a(__value__(SymbolTable_0x82c9e58_13), __value__(
     > SymbolTable_0x82c9e58_14), __value__(Y))
      CALL saxpy_a_a(__value__(SymbolTable_0x82c9e58_16), __value__(
     > SymbolTable_0x82c9e58_17), __value__(Y))
      CALL saxpy_a_a(__value__(SymbolTable_0x82c9e58_18), __value__(
     > SymbolTable_0x82c9e58_19), __value__(Y))
      RETURN
      END SUBROUTINE
W2F1
    $w2f1_add_use = <<'W2F1U';
C ***********************************************************
C Fortran file translated from WHIRL Tue Sep  2 09:54:45 2003
C ***********************************************************
	module w2f__types

	integer :: w2f__4, w2f__8, w2f__16
	parameter (w2f__4 = kind(0.0))
	parameter (w2f__8 = kind(0.0d0))
	parameter (w2f__16 = selected_real_kind(p=30))

	integer :: w2f__i1, w2f__i2, w2f__i4,w2f__i8
	parameter (w2f__i1 = selected_int_kind(r=2))
	parameter (w2f__i2 = selected_int_kind(r=3))
	parameter (w2f__i4 = selected_int_kind(r=8))
	parameter (w2f__i8 = selected_int_kind(r=16))

	end module w2f__types
C ***********************************************************

      SUBROUTINE head(X, Y, Z)
      use w2f__types
      use active_module
      IMPLICIT NONE
      REAL(w2f__8) X
      INTENT(IN)  X
      REAL(w2f__8) Y
      REAL(w2f__8) Z
      INTENT(IN)  Z
      
      
      
C
C     **** Variables and functions ****
C
      REAL(w2f__8) SymbolTable_0x82c9e58_2
      REAL(w2f__8) SymbolTable_0x82c9e58_3
      REAL(w2f__8) SymbolTable_0x82c9e58_4
      REAL(w2f__8) SymbolTable_0x82c9e58_5
      REAL(w2f__8) SymbolTable_0x82c9e58_6
      REAL(w2f__8) SymbolTable_0x82c9e58_7
      REAL(w2f__8) SymbolTable_0x82c9e58_8
      REAL(w2f__8) SymbolTable_0x82c9e58_9
      REAL(w2f__8) SymbolTable_0x82c9e58_10
      REAL(w2f__8) SymbolTable_0x82c9e58_11
      REAL(w2f__8) SymbolTable_0x82c9e58_12
      REAL(w2f__8) SymbolTable_0x82c9e58_13
      REAL(w2f__8) SymbolTable_0x82c9e58_14
      REAL(w2f__8) SymbolTable_0x82c9e58_15
      REAL(w2f__8) SymbolTable_0x82c9e58_16
      REAL(w2f__8) SymbolTable_0x82c9e58_17
      REAL(w2f__8) SymbolTable_0x82c9e58_18
      REAL(w2f__8) SymbolTable_0x82c9e58_19
      REAL(w2f__8) SymbolTable_0x82c9e58_0
      REAL(w2f__8) SymbolTable_0x82c9e58_1
C
C     **** statements ****
C
      __value__(SymbolTable_0x82c9e58_19) = __value__(Y)
      __value__(SymbolTable_0x82c9e58_17) = __value__(X)
      __value__(SymbolTable_0x82c9e58_14) = __value__(Z)
      __value__(SymbolTable_0x82c9e58_5) = (__value__(X) * __value__(Y)
     > )
      __value__(SymbolTable_0x82c9e58_2) = (__value__(Z) * __value__(
     > SymbolTable_0x82c9e58_5))
      __value__(SymbolTable_0x82c9e58_10) = (__value__(Z) +(__value__(X
     > ) * __value__(SymbolTable_0x82c9e58_2)))
      __value__(SymbolTable_0x82c9e58_0) = 1
      __value__(SymbolTable_0x82c9e58_3) = __value__(
     > SymbolTable_0x82c9e58_2)
      __value__(SymbolTable_0x82c9e58_6) = __value__(
     > SymbolTable_0x82c9e58_5)
      __value__(SymbolTable_0x82c9e58_8) = __value__(Y)
      __value__(SymbolTable_0x82c9e58_9) = __value__(X)
      __value__(SymbolTable_0x82c9e58_7) = __value__(Z)
      __value__(SymbolTable_0x82c9e58_4) = __value__(X)
      __value__(SymbolTable_0x82c9e58_1) = 1
      __value__(Y) = __value__(SymbolTable_0x82c9e58_10)
      __value__(SymbolTable_0x82c9e58_11) = (__value__(
     > SymbolTable_0x82c9e58_3) * __value__(SymbolTable_0x82c9e58_1))
      __value__(SymbolTable_0x82c9e58_12) = (__value__(
     > SymbolTable_0x82c9e58_4) * __value__(SymbolTable_0x82c9e58_1))
      __value__(SymbolTable_0x82c9e58_13) = (__value__(
     > SymbolTable_0x82c9e58_0) +(__value__(SymbolTable_0x82c9e58_6) *
     >  __value__(SymbolTable_0x82c9e58_12)))
      __value__(SymbolTable_0x82c9e58_15) = (__value__(
     > SymbolTable_0x82c9e58_7) * __value__(SymbolTable_0x82c9e58_12))
      __value__(SymbolTable_0x82c9e58_16) = (__value__(
     > SymbolTable_0x82c9e58_11) +(__value__(SymbolTable_0x82c9e58_8) *
     >  __value__(SymbolTable_0x82c9e58_15)))
      __value__(SymbolTable_0x82c9e58_18) = (__value__(
     > SymbolTable_0x82c9e58_9) * __value__(SymbolTable_0x82c9e58_15))
      CALL sax_a_a(__value__(SymbolTable_0x82c9e58_13), __value__(
     > SymbolTable_0x82c9e58_14), __value__(Y))
      CALL saxpy_a_a(__value__(SymbolTable_0x82c9e58_16), __value__(
     > SymbolTable_0x82c9e58_17), __value__(Y))
      CALL saxpy_a_a(__value__(SymbolTable_0x82c9e58_18), __value__(
     > SymbolTable_0x82c9e58_19), __value__(Y))
      RETURN
      END SUBROUTINE
W2F1U
    $w2f1_active = <<'W2F1A';
C ***********************************************************
C Fortran file translated from WHIRL Tue Sep  2 09:54:45 2003
C ***********************************************************
	module w2f__types

	integer :: w2f__4, w2f__8, w2f__16
	parameter (w2f__4 = kind(0.0))
	parameter (w2f__8 = kind(0.0d0))
	parameter (w2f__16 = selected_real_kind(p=30))

	integer :: w2f__i1, w2f__i2, w2f__i4,w2f__i8
	parameter (w2f__i1 = selected_int_kind(r=2))
	parameter (w2f__i2 = selected_int_kind(r=3))
	parameter (w2f__i4 = selected_int_kind(r=8))
	parameter (w2f__i8 = selected_int_kind(r=16))

	end module w2f__types
C ***********************************************************

      SUBROUTINE head(X, Y, Z)
      use w2f__types
      IMPLICIT NONE
      type(active) :: X
      INTENT(IN)  X
      type(active) :: Y
      type(active) :: Z
      INTENT(IN)  Z
      
      
      
C
C     **** Variables and functions ****
C
      type(active) :: SymbolTable_0x82c9e58_2
      type(active) :: SymbolTable_0x82c9e58_3
      type(active) :: SymbolTable_0x82c9e58_4
      type(active) :: SymbolTable_0x82c9e58_5
      type(active) :: SymbolTable_0x82c9e58_6
      type(active) :: SymbolTable_0x82c9e58_7
      type(active) :: SymbolTable_0x82c9e58_8
      type(active) :: SymbolTable_0x82c9e58_9
      type(active) :: SymbolTable_0x82c9e58_10
      type(active) :: SymbolTable_0x82c9e58_11
      type(active) :: SymbolTable_0x82c9e58_12
      type(active) :: SymbolTable_0x82c9e58_13
      type(active) :: SymbolTable_0x82c9e58_14
      type(active) :: SymbolTable_0x82c9e58_15
      type(active) :: SymbolTable_0x82c9e58_16
      type(active) :: SymbolTable_0x82c9e58_17
      type(active) :: SymbolTable_0x82c9e58_18
      type(active) :: SymbolTable_0x82c9e58_19
      type(active) :: SymbolTable_0x82c9e58_0
      type(active) :: SymbolTable_0x82c9e58_1
C
C     **** statements ****
C
      __value__(SymbolTable_0x82c9e58_19) = __value__(Y)
      __value__(SymbolTable_0x82c9e58_17) = __value__(X)
      __value__(SymbolTable_0x82c9e58_14) = __value__(Z)
      __value__(SymbolTable_0x82c9e58_5) = (__value__(X) * __value__(Y)
     > )
      __value__(SymbolTable_0x82c9e58_2) = (__value__(Z) * __value__(
     > SymbolTable_0x82c9e58_5))
      __value__(SymbolTable_0x82c9e58_10) = (__value__(Z) +(__value__(X
     > ) * __value__(SymbolTable_0x82c9e58_2)))
      __value__(SymbolTable_0x82c9e58_0) = 1
      __value__(SymbolTable_0x82c9e58_3) = __value__(
     > SymbolTable_0x82c9e58_2)
      __value__(SymbolTable_0x82c9e58_6) = __value__(
     > SymbolTable_0x82c9e58_5)
      __value__(SymbolTable_0x82c9e58_8) = __value__(Y)
      __value__(SymbolTable_0x82c9e58_9) = __value__(X)
      __value__(SymbolTable_0x82c9e58_7) = __value__(Z)
      __value__(SymbolTable_0x82c9e58_4) = __value__(X)
      __value__(SymbolTable_0x82c9e58_1) = 1
      __value__(Y) = __value__(SymbolTable_0x82c9e58_10)
      __value__(SymbolTable_0x82c9e58_11) = (__value__(
     > SymbolTable_0x82c9e58_3) * __value__(SymbolTable_0x82c9e58_1))
      __value__(SymbolTable_0x82c9e58_12) = (__value__(
     > SymbolTable_0x82c9e58_4) * __value__(SymbolTable_0x82c9e58_1))
      __value__(SymbolTable_0x82c9e58_13) = (__value__(
     > SymbolTable_0x82c9e58_0) +(__value__(SymbolTable_0x82c9e58_6) *
     >  __value__(SymbolTable_0x82c9e58_12)))
      __value__(SymbolTable_0x82c9e58_15) = (__value__(
     > SymbolTable_0x82c9e58_7) * __value__(SymbolTable_0x82c9e58_12))
      __value__(SymbolTable_0x82c9e58_16) = (__value__(
     > SymbolTable_0x82c9e58_11) +(__value__(SymbolTable_0x82c9e58_8) *
     >  __value__(SymbolTable_0x82c9e58_15)))
      __value__(SymbolTable_0x82c9e58_18) = (__value__(
     > SymbolTable_0x82c9e58_9) * __value__(SymbolTable_0x82c9e58_15))
      CALL sax_a_a(__value__(SymbolTable_0x82c9e58_13), __value__(
     > SymbolTable_0x82c9e58_14), __value__(Y))
      CALL saxpy_a_a(__value__(SymbolTable_0x82c9e58_16), __value__(
     > SymbolTable_0x82c9e58_17), __value__(Y))
      CALL saxpy_a_a(__value__(SymbolTable_0x82c9e58_18), __value__(
     > SymbolTable_0x82c9e58_19), __value__(Y))
      RETURN
      END SUBROUTINE
W2F1A

    $w2f1_noval = <<'W2F1NV';
C ***********************************************************
C Fortran file translated from WHIRL Tue Sep  2 09:54:45 2003
C ***********************************************************
	module w2f__types

	integer :: w2f__4, w2f__8, w2f__16
	parameter (w2f__4 = kind(0.0))
	parameter (w2f__8 = kind(0.0d0))
	parameter (w2f__16 = selected_real_kind(p=30))

	integer :: w2f__i1, w2f__i2, w2f__i4,w2f__i8
	parameter (w2f__i1 = selected_int_kind(r=2))
	parameter (w2f__i2 = selected_int_kind(r=3))
	parameter (w2f__i4 = selected_int_kind(r=8))
	parameter (w2f__i8 = selected_int_kind(r=16))

	end module w2f__types
C ***********************************************************

      SUBROUTINE head(X, Y, Z)
      use w2f__types
      IMPLICIT NONE
      REAL(w2f__8) X
      INTENT(IN)  X
      REAL(w2f__8) Y
      REAL(w2f__8) Z
      INTENT(IN)  Z
      
      
      
C
C     **** Variables and functions ****
C
      REAL(w2f__8) SymbolTable_0x82c9e58_2
      REAL(w2f__8) SymbolTable_0x82c9e58_3
      REAL(w2f__8) SymbolTable_0x82c9e58_4
      REAL(w2f__8) SymbolTable_0x82c9e58_5
      REAL(w2f__8) SymbolTable_0x82c9e58_6
      REAL(w2f__8) SymbolTable_0x82c9e58_7
      REAL(w2f__8) SymbolTable_0x82c9e58_8
      REAL(w2f__8) SymbolTable_0x82c9e58_9
      REAL(w2f__8) SymbolTable_0x82c9e58_10
      REAL(w2f__8) SymbolTable_0x82c9e58_11
      REAL(w2f__8) SymbolTable_0x82c9e58_12
      REAL(w2f__8) SymbolTable_0x82c9e58_13
      REAL(w2f__8) SymbolTable_0x82c9e58_14
      REAL(w2f__8) SymbolTable_0x82c9e58_15
      REAL(w2f__8) SymbolTable_0x82c9e58_16
      REAL(w2f__8) SymbolTable_0x82c9e58_17
      REAL(w2f__8) SymbolTable_0x82c9e58_18
      REAL(w2f__8) SymbolTable_0x82c9e58_19
      REAL(w2f__8) SymbolTable_0x82c9e58_0
      REAL(w2f__8) SymbolTable_0x82c9e58_1
C
C     **** statements ****
C
      SymbolTable_0x82c9e58_19%v = Y%v
      SymbolTable_0x82c9e58_17%v = X%v
      SymbolTable_0x82c9e58_14%v = Z%v
      SymbolTable_0x82c9e58_5%v = (X%v*Y%v)
      SymbolTable_0x82c9e58_2%v = (Z%v*SymbolTable_0x82c9e58_5%v)
      SymbolTable_0x82c9e58_10%v = (Z%v+(X%v*SymbolTable_0x82c9e58_2%v))
      SymbolTable_0x82c9e58_0%v = 1
      SymbolTable_0x82c9e58_3%v = SymbolTable_0x82c9e58_2%v
      SymbolTable_0x82c9e58_6%v = SymbolTable_0x82c9e58_5%v
      SymbolTable_0x82c9e58_8%v = Y%v
      SymbolTable_0x82c9e58_9%v = X%v
      SymbolTable_0x82c9e58_7%v = Z%v
      SymbolTable_0x82c9e58_4%v = X%v
      SymbolTable_0x82c9e58_1%v = 1
      Y%v = SymbolTable_0x82c9e58_10%v
      SymbolTable_0x82c9e58_11%v = (SymbolTable_0x82c9e58_3%v*SymbolTabl
     +e_0x82c9e58_1%v)
      SymbolTable_0x82c9e58_12%v = (SymbolTable_0x82c9e58_4%v*SymbolTabl
     +e_0x82c9e58_1%v)
      SymbolTable_0x82c9e58_13%v = (SymbolTable_0x82c9e58_0%v+(SymbolTab
     +le_0x82c9e58_6%v*SymbolTable_0x82c9e58_12%v))
      SymbolTable_0x82c9e58_15%v = (SymbolTable_0x82c9e58_7%v*SymbolTabl
     +e_0x82c9e58_12%v)
      SymbolTable_0x82c9e58_16%v = (SymbolTable_0x82c9e58_11%v+(SymbolTa
     +ble_0x82c9e58_8%v*SymbolTable_0x82c9e58_15%v))
      SymbolTable_0x82c9e58_18%v = (SymbolTable_0x82c9e58_9%v*SymbolTabl
     +e_0x82c9e58_15%v)
      CALL sax_a_a(SymbolTable_0x82c9e58_13%v,SymbolTable_0x82c9e58_14%v
     +,Y%v)
      CALL saxpy_a_a(SymbolTable_0x82c9e58_16%v,SymbolTable_0x82c9e58_17
     +%v,Y%v)
      CALL saxpy_a_a(SymbolTable_0x82c9e58_18%v,SymbolTable_0x82c9e58_19
     +%v,Y%v)
      RETURN
      END SUBROUTINE
W2F1NV
    $ff = Ffile->new_from_heredoc($w2f1);
}

sub x2w1 {
    my($line) = @_;
    my($scn) = FTscan->new($line);
    if ($scn->match(qr/use $TB w2f__types $TBE /x)){
	return($line,<<'U');
      use active_module
U
    }
    return($UNCHANGED);
}

sub x2w2 {
    my($line) = @_;
    my($scn) = FTscan->new($line);
    if($line =~ /^\s+real\(w2f__8\)\s+/i) {
	$line =~s/real\(w2f__8\)/type(active) ::/i;
	return $line;
    }
    return($UNCHANGED);
}

sub x2w3 {
    my($line) = @_;
    my($scn) = FTscan->new($line);
    if($scn->match(qr/ __value__ $TB \( $TB/x)){
	return ($scn->grterm(qr/__value__/,\&xaif_t)->lstring());
    }
    return($UNCHANGED);
}

sub xaif_t {
    my($v) = $_[0]->copy();
    my(@tl) = $v->tl();
    $v->set_tl(@tl[2 .. $#tl-1]); # pick up arg tokens
    my($s) = $v->str();

    return FTscan->new("$s%v");
}

sub teardown{
}
