use FindBin qw($RealBin);
use lib "$RealBin/Lib";
use lib "$RealBin/Lib/FT";

use Ffile;
use FTscan;
use FTpat;

use Readhack;
use InsertAftImplNone;

sub doit {
    $fn = $_[0];
    $bak = $fn . '.rh';
    rename $fn,$bak;
    local(*F);

    print STDERR  "readhack $fn ...\n";
    Ffile->new($bak)->rewrite_sem(\&readhack)
         ->rewrite_sem(dcls_ins('read_data_file'),readhackdecls())
         ->write($fn);
    
}

map {doit($_)} @ARGV;

