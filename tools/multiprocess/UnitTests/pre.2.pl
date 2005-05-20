use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use Ffile;
use Active_Chg;

setup();

is($ff->rewrite_sem(\&active_chg)->to_string(),
   $ff_ok->to_string(),
   'active change ok');	

teardown();

sub setup {
    $ff = Ffile->new("$RealBin/Pre-Tfiles/t2.f");
    $ff_ok = Ffile->new("$RealBin/Pre-Ok/t2.f");
}

sub teardown {
}
