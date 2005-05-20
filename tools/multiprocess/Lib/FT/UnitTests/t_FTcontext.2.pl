use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use FTcontext;
use FTpat;
use FTproc;

setup();

is($ff1->crewrite_sem(FTproc->new(\&init_assgn,\&set_assgn))
       ->crewrite_sem(\&add_call)->to_string(),
   $f1rw2,'add context to stmt');

teardown();

sub setup {
    $f1 = <<'F1';
       subroutine foo(x,y)
       real*4 x,y
       dimension x(10,11),y(100)

       x(1,1) = y(31) * sin(x(9,9)

       y(5) = y(3) + y(27)

       end

       subroutine bar(x,y)
       real*4 x,y
       dimension x(10,11),y(100)

       x(1,1) = y(31) * sin(x(9,9)

       y(5) = y(3) + y(27)

       end
F1
    $ff1 = FTcontext->here($f1);

    $f1rw = <<'F1RW';
       subroutine foo(x,y)
! here is a comment preceding the line
       real*4 x,y
       double precision ffx
       double precision ffy
       dimension x(10,11),y(100)

       x(1,1) = y(31) * sin(x(9,9)

       y(5) = y(3) + y(27)

       end

       subroutine bar(x,y)
! here is a comment preceding the line
       real*4 x,y
       double precision ffx
       double precision ffy
       dimension x(10,11),y(100)

       x(1,1) = y(31) * sin(x(9,9)

       y(5) = y(3) + y(27)

       end
F1RW

    $f1rw2 = <<'F1RW2';
       subroutine foo(x,y)
       real*4 x,y
       dimension x(10,11),y(100)

! Here is a trace
       call traceme()
       x(1,1) = y(31) * sin(x(9,9)

       y(5) = y(3) + y(27)

       end

       subroutine bar(x,y)
       real*4 x,y
       dimension x(10,11),y(100)

! Here is a trace
       call traceme()
       x(1,1) = y(31) * sin(x(9,9)

       y(5) = y(3) + y(27)

       end
F1RW2

    $FLAST = '';



}

sub teardown {
}

sub t1 {
    my($line) = @_;

    if(my($v) = $line->match(qr/^ real (?: $TB \* $TB 4 $TB )? (.+) $/ix)){
	my(@new);
	for ($v->cbreak) {
	    my($vv) =  $_->match(qr/^ (\w+)/x);
	    $vv = 'double precision ff' . $vv->str();
	    push @new,FTscan->new($vv)->set_indent($line->indent());
	}
	return (<<'C1',$line,@new);
! here is a comment preceding the line
C1
    }
    return ($line);
}
sub set_assgn {
    $_[0]->clearprop('a1');
    return ($_[0]) if ($_[1]->{fnd});
    if ( $_[0]->match(qr/ $TB = $TB /ix) ) {
	$_[1]->{fnd} = 1;
	$_[0]->putprop('a1',1);
    }
    return ($_[0]);
}
sub init_assgn {
    $_[0]->{fnd} = 0;
}
sub add_call {
    $C1 = <<'C1';
! Here is a trace
C1
    if ($_[0]->getprop('a1')) {
	return ($C1,
		$_[0]->same_level('call traceme()'),
		$_[0],
		);
    }
    return ($_[0]);
}

