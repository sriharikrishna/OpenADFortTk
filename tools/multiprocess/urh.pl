use FindBin qw($RealBin);
use lib "$RealBin/Lib";
use lib "$RealBin/Lib/FT";

use Ffile;
use FTscan;
use FTpat;

use Unreadhack;
use File::Basename;

%tr = (
       iadrh0 => '(20,*)',
       iadrh1 => "(20,'(A80)')",
       );

sub doit {
    my($fn) = $_[0];
    my($name,$dir,$ext) = fileparse($fn,'\.[Ff]');
    my($ofn) = $dir . $name . ".urh" . $ext;

    print STDERR  "unreadhack $fn ...\n";
    Ffile->new($fn)->rewrite_sem(\&unreadhack,%tr)
         ->write($ofn);
}

map {doit($_)} @ARGV;

