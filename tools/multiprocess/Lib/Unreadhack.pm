package Unreadhack;

use Ffile;
use FTscan;
use FTpat;

use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(unreadhack);



sub unreadhack {
    my($scn) = FTscan->new(shift @_);
    my(%tr) = @_;
    if (my($unit,$args) = $scn->match(qr/^ call $TB readhack $TB 
			        \( $TB (\w+) $TB , $TB (.+) $TB \)
			        /ix)){
	$args = $args->str();
	$args =~ s/__deriv__/__value__/g;
	return $scn->leading() .  'read' . 
	    $tr{$unit->str()} . $args . "\n";
    }
    return($UNCHANGED);
}

1;
