package ADxaif;

use Ffile;
use FTscan;
use FTpat;

use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(xaifpp);

BEGIN {
    $decl1_re = qr/real\(w2f__8\)/i;
    $active1_re = qr/^\s+$decl1_re\s+/i;
    $decl2_re = qr/type \s+ \( \s* openadty_active(?:_init)? \s* \)/ix;
    $active2_re = qr/^ \s+  $decl2_re/ix;
    $active_re = $active2_re;
    $decl_re = $decl2_re;
}

sub set_old {
    $active_re = $active1_re;
    $decl_re = $decl1_re;
}

sub xaifpp {
    my($line) = @_;
    my($scn) = FTscan->new($line);
    if ($scn->match(qr/use $TB w2f__types $TBE /x)){
	return($line,<<'U');
      use active_module
U
    }
    if($line =~ /$active_re/) {
	$line =~s/$decl_re/type(active) ::/i;
	return $line;
    }
    if($scn->match(qr/ __(?: value | deriv )__ $TB \( $TB/x)){
	return ($scn->grterm(qr/__value__/,\&xaifv_t)
	            ->grterm(qr/__deriv__/,\&xaifd_t)
		    ->lstring() . "\n");
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

1;
