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
use MultiTemplate;

use PPsetup;
use File::Basename;
use Getopt::Long;

my($ifile) = 'ad_inline.f';
my($tfile) = 'ad_template.f';

my($forward,$real) = (0,0);
my($result) = GetOptions("forward" => \$forward,
			 "real" => \$real,
			 "template=s" => \$tfile,
			 "inline=s" => \$ifile,);

ADxaif::set_old() if ($real);


my($infile) = $ARGV[0];
my($name,$dir,$ext) = fileparse($infile,'\.[Ff]');
my($outfile) = $dir . $name . ".pp" . $ext;
my($inl,$default_template);

unless ($forward){
    $inl = ADinline->new(Ffile->new($ifile));
    $default_template = ADtemplate->new(Ffile->new($tfile));
}

my($ffi) = Ffile->new($infile)->rewrite_sem(\&xaifpp);
unless ($forward){
    $ffi = $ffi->rewrite($inl->inline());
    $ffi = fconcat( map {multi_inst($_,$default_template)}
		     FTUnit->new($ffi)->units() );
}
$ffi->write($outfile);
