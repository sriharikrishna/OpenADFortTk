package InsertAftImplNone;

use Ffile;
use FTscan;
use FTpat;

use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(insert_after_impl_none dcls_ins);

my($insert) = 0;

sub insert_after_impl_none {
    return ($UNCHANGED) if ($insert);
    my($scn) = FTscan->new(shift @_);
    if ($scn->match(qr/^ implicit $TB none/ix)){
	$insert = 1;
	return ($UNCHANGED,@_);
    }
    return ($UNCHANGED);
}

sub dcls_ins {
    my($rou) = shift @_;
    my($roure) = qr/^subroutine $TB $rou/ix;
    my($outre) = qr/^end $/ix;
    my($in_rou) = 0;
    return sub {
	my($scn) = FTscan->new($_[0]);
	$in_rou = 1 if ($scn->match($roure));
	$in_rou = 0 if ($scn->match($outre));
	return insert_after_impl_none(@_) if ($in_rou);
	return ($UNCHANGED);
    }
}

1;
