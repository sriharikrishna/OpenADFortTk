use FindBin qw($RealBin);
use lib "$RealBin/Lib";
use lib "$RealBin/Lib/FT";

use Ffile;
use FTscan;
use FTpat;

use Unreadhack;

%tr = (
       iadrh0 => '(20,*)',
       iadrh1 => "(20,'(A80)')",
       );

sub doit {
    $fn = $_[0];
    $bak = $fn . '.urh';
    rename $fn,$bak;
    local(*F);

    print STDERR  "unreadhack $fn ...\n";
    Ffile->new($bak)->rewrite_sem(\&unreadhack,%tr)
         ->write($fn);
    
}

map {doit($_)} @ARGV;

