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

use PPsetup;
use File::Basename;

my($infile) = $ARGV[0];
my($name,$dir,$ext) = fileparse($infile,'\.[Ff]');
my($outfile) = $dir . $name . ".pp" . $ext;

Ffile->new($infile)->rewrite_sem(\&xaifpp)->write($outfile);

sub xaifpp {
    my($line) = @_;
    my($scn) = FTscan->new($line);
    if ($scn->match(qr/use $TB w2f__types $TBE /x)){
	return($line,<<'U');
      use active_module
U
    }
    if($line =~ /^\s+real\(w2f__8\)\s+/i) {
	$line =~s/real\(w2f__8\)/type(active) ::/i;
	return $line;
    }
    if($scn->match(qr/ __(?: value | deriv )__ $TB \( $TB/x)){
	return ($scn->grterm(qr/__value__/,\&xaifv_t)
	            ->grterm(qr/__deriv__/,\&xaifd_t)
		    ->lstring());
    }
    return($UNCHANGED);
}
sub xaifv_t {
    my($v) = $_[0]->copy();
    my(@tl) = $v->tl();
    $v->set_tl(@tl[2 .. $#tl-1]); # pick up arg tokens
    my($s) = $v->str();

    return FTscan->new("$s%v");
}

sub xaifd_t {
    my($v) = $_[0]->copy();
    my(@tl) = $v->tl();
    $v->set_tl(@tl[2 .. $#tl-1]); # pick up arg tokens
    my($s) = $v->str();

    return FTscan->new("$s");
}

