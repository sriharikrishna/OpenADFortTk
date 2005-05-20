use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use FTcontext;

setup();

is(ref($l1),'FortranSourceLine','l1 setup');
$l1_save = $l1->line();
is($l1->line(),
   "        open(uuu+12,file = 'foobar',    err=1000,end = 2000)\n",
   'l1 setup text');

is($l1->ignore('io')->rawline(),$l1_ig,'l1 ignore');
is(join('',map {$_->rawline()} $l1->comment()),$l1_comm,'L1 comment');

is($l1->line,$l1_save,'L1 unchanged by line ops');

is($l2->ignore()->rawline(),$l2_ig,'l2 ignore');
is(join('',map {$_->rawline()} $l2->comment('$AD4')),$l2_comm,'L2 comment');

teardown();

sub setup{
    $f1 = FTcontext->here(<<'F1');
        subroutine f
        open(uuu+12,file = 'foobar',
     +    err=1000,end = 2000)
        call nonrou(x,y,z,'This is jerry''s string')
        end
F1

    ($l1,$l2) = (($f1->ffiles())[0]->lines())[ 1 .. 2];
    $l1_ig = <<'L1IG';
        call ignoreio('open(uuu+12,file = ''foobar'',    err=1000,end = 
     +2000)')
L1IG

    $l1_comm = <<'L1COMM';
c         open(uuu+12,file = 'foobar',
c      +    err=1000,end = 2000)
L1COMM

    $l2_ig = <<'L2IG';
        call ignore('call nonrou(x,y,z,''This is jerry''''s string'')')
L2IG
    $l2_comm = <<'L2COMM';
c$AD4         call nonrou(x,y,z,'This is jerry''s string')
L2COMM
}

sub teardown {
}
