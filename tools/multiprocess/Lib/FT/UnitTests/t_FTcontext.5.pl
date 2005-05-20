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

is($f1->to_string(),$f1f,'oksi-tools.f');

teardown();

sub setup {
    $f1 = FTcontext->file("$RealBin/FortranFiles/oksi-tools.f");
    {
	local($/);
	undef($/);
	local(*F);

	open(F,"$RealBin/FortranFiles/oksi-tools.f");
	$f1f = <F>;
	$f1f =~ s/\r//gmix;
	close(F);
    }
}

sub teardown {
}
