use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use FTscan;

setup();
is($s1->str(),"include 'adio.fh'",'str of scan with include');

teardown();

sub setup {
    $s1 = FTscan->new("include 'adio.fh'");
}

sub teardown {
}
