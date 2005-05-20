use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use FTscan;

setup();

@a = ('foo','bar'); @b = ('foo','bar');

ok(! FTscan::checkit(['foo', 'bar', 'baz'],[@a]),'checkit for different lists');
ok(FTscan::checkit([ 'foo','bar'],['foo','bar']),'checkit |foo bar|');

ok(FTscan::checkit(@a,@b),'checkit for 2 actual lists');


ok($s1->token_scan('active'),'token scan for active');
ok($s1->token_scan('type','active'),'token scan for "type active"');
ok(! $s1->token_scan('active1'),'token scan for active1 NOT found');
ok($s2->token_scan('active'),'s2 has active');

is($s1->g_repl_token([ 'active' ] ,[ 'active1' ])->str(),
   'type active1',
   'change to "type active1"');
is($s2->g_repl_token([ 'active' ] ,[ 'active1' ])->str(),
   'type(active1) :: x,y(20)',
   'change to "type(active1) :: ..."');

teardown();

sub setup {
    $s1 = FTscan->new("type active");
    $s2 = FTscan->new('type(active) :: x,y(20)')
}

sub teardown {
}
