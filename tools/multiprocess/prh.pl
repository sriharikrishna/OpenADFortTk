use FindBin qw($RealBin);
use lib "$RealBin/Lib";
use lib "$RealBin/Lib/FT";

use Ffile;
use FTscan;
use FTpat;

use Readhack;
use InsertAftImplNone;

use File::Basename;

sub doit {
    my($fn) = $_[0];
    my($name,$dir,$ext) = fileparse($fn,'\.[Ff]');
    my($ofn) = $dir . $name . ".prh" . $ext;

    print STDERR  "readhack $fn -> $ofn ...\n";
    Ffile->new($fn)->rewrite_sem(\&readhack)
         ->rewrite_sem(dcls_ins('read_data_file'),readhackdecls())
         ->write($ofn);
}

map {doit($_)} @ARGV;

