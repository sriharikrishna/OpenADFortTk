#
# post process whirl2f for adiforc
#
# insert use active_type for all subroutines/functions
# change REAL() to active_real
#
# change __values__(ANY) to ANY%v
#
use FindBin qw($RealBin);
use lib "$RealBin/Lib";
use lib "$RealBin/Lib/FT";

use Ffile;
use FTscan;
use FTpat;
use FTUnit;

use ADxaif;
use ADinline;
use ADtemplate;

use PPsetup;
use File::Basename;

my($infile) = $ARGV[0];
my($name,$dir,$ext) = fileparse($infile,'\.[Ff]');
my($outfile) = $dir . $name . ".pp" . $ext;

my($inl) = ADinline->new(Ffile->new('ad_inline.f'));
my($template) = ADtemplate->new(Ffile->new('ad_template.f'));

my($ffi) = Ffile->new($infile)->rewrite_sem(\&xaifpp)
           ->rewrite($inl->inline());

my($ffit) = fconcat( map {$template->instantiate($_)}
		     FTUnit->new($ffi)->units() );

$ffit->write($outfile);


