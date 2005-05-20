use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use Ffile;
use FTUnit;

setup();

@units = FTUnit->new($ff)->units();

is(@units+0,9,'number of units');
foreach (1 .. @units+0){
    is($units[$_-1]->to_string(),
       Ffile->new("$RealBin/Units/u$_.f")->to_string(),
       "unit $_");
}

teardown();

sub setup {
    $ff = Ffile->new("$RealBin/FortranFiles/i1.f");
}

sub teardown {
}

1;
