use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use FTcontext;
use FTpat;
use FTproc;
use FTscan;
use FTscanUtils;
use ADtypes;

setup();

ok($f1->module_table(),'f1 module table constructed');
is(join('|',sort(keys(%{$f1->module_table()}))),
	'eeparams_mod|size_mod',
        'all f1 modules detected');
is($f1->module_table()->{'size_mod'}->lookup_type_str('nPx'),
   'integer',
   'nPx is integer in module table lookup');

ok($f2->module_table(),'f2 module table constructed');
is(join('|',sort(keys(%{$f2->module_table()}))),
	'',
        'f2 module table is empty');

teardown();

sub setup {
    $f1 = FTcontext->file("$RealBin/FortranFiles/tmod.f");
    $f2 = FTcontext->file("$RealBin/FortranFiles/tmods.2.f");
}
sub teardown {
}
