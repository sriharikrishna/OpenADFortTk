package Readhack;

use Ffile;
use FTscan;
use FTpat;

use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(readhack readhackvar readhackdecls);

sub ft_single_quote {
    local($_) = @_;

    s/\'/\'\'/g;
    return "'$_'";
}

%unit = ();
$vcnt = 0;

sub readhackdecls {
    return map {' ' x 8 . "integer $_\n"} sort(values(%unit));
}

sub uvar {
    my($str) = @_;
    $unit{$str} ||= 'iadrh' . $vcnt++;
    return $unit{$str};
}

sub readhackvar {
    return %unit;
}

sub readhack {
    my($scn) = FTscan->new($_[0]);
    if (my($unit,$args) = $scn->match(qr/^ read $TB (\( .* \)) $TB (.+)/ix)){
	return $scn->leading() .  'call readhack(' . 
	    uvar($unit->str()) . ',' .
	    $args->str() . ")\n";
    }
    return($UNCHANGED);
}

1;
