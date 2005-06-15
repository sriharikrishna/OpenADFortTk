#
# preprocess codes for OpenAD
#
use FindBin qw($RealBin);
use lib "$RealBin/Lib";
use lib "$RealBin/Lib/FT";

use Ffile;
use Active_Chg;

use File::Basename;

my($infile) = $ARGV[0];
my($name,$dir,$ext) = fileparse($infile,'\.[Ff][0-9]*');
my($outfile) = $dir . $name . ".pre" . $ext;

Ffile->new($infile)->rewrite_sem(\&active_chg)->write($outfile);
