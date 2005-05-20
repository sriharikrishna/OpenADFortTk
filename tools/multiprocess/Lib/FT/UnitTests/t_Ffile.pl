#
#
# test the context rewrite & map ops of Ffile
#  -- prelude to testing them for FTcontext
#

use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use FTscan;
use FTpat;
use Ffile;
use FTproc;

setup();

is($f2->to_string(),$f2f,'oksi-tools.f');

is($ff1->crewrite(\&t1)->to_string,$f1rw,'F1 crewrite');
is($ff1->crewrite_sem(\&t1)->to_string,$f1rw,'F1 crewrite sem');
my($fnd);

is($ff1->crewrite_sem(FTproc->new(\&init_assgn,\&set_assgn),\$fnd)
       ->crewrite_sem(\&add_call)->to_string(),
   $f1rw2,'add context to stmt');

teardown();

sub setup {
    $f2 = Ffile->new("$RealBin/FortranFiles/oksi-tools.f");
    {
	local($/);
	undef($/);
	local(*F);

	open(F,"$RealBin/FortranFiles/oksi-tools.f");
	$f2f = <F>;
	$f2f =~ s/\r//gmix;
	close(F);
    }

    
    $f1 = <<'F1';
       subroutine foo(x,y)
       real*4 x,y
       dimension x(10,11),y(100)

       x(1,1) = y(31) * sin(x(9,9)

       y(5) = y(3) + y(27)

       end
F1
    $ff1 = Ffile->new_from_heredoc($f1);

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
    return ($_[0]) if (${$_[1]});
    if ( $_[0]->match(qr/ $TB = $TB /ix) ) {
	${$_[1]} = 1;
	$_[0]->putprop('a1',1);
    }
    return ($_[0]);
}
sub init_assgn {
    ${$_[0]} = 0;
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
