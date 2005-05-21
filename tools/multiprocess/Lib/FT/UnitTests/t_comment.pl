use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use Ffile;

setup();

is($f1->rewrite_sem(\&at_front)->to_string(),
   $f1ok->to_string(),
   '! comments internal');

teardown();

sub setup {
    $f1 = Ffile->new("$RealBin/FortranFiles/comment1.f");
    $f1ok = Ffile->new("$RealBin/FortranFiles/comment1.ok.f");
}

sub teardown {
}

sub at_front {
    return "c%l% $_[0]";
}
