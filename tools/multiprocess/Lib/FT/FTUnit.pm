#
# from an Ffile, create a 'list of Ffiles' object, each a single unit
#
package FTUnit;
use Ffile;
use FTscan;
use FTpat;

sub new {
    return bless { _units => fsplit($_[1])},$_[0];
}
sub fsplit {
    my($ff) = @_;

    my($units_ref_list) = [];
    my($current_unit) = Ffile->empty();
    my($end_ref) = 0;

    $ff->map(\&split_unit,$units_ref_list,\$current_unit,\$end_ref);
    return $units_ref_list;
}

sub split_unit {
    my($line,$units_ref_list,$current_unit_r,$end_ref) = @_;

    to_unit($line,$end_ref,$$current_unit_r);
    if ($$end_ref){
	push @$units_ref_list,$$current_unit_r;
	$$current_unit_r = Ffile->empty();
	$$end_ref = 0;
    }
}

sub to_unit {
    my($line,$end_ref,$unit) = @_;

    $unit->add_text_lines($line);
    $$end_ref = FTscan->new($line)
	        ->match(qr/^ end (?: $TB (?: module (?: $TB \w+)?|
		                       program (?: $TB \w+)?|
				       subroutine (?: $TB \w+)?|
				       function (?: $TB \w+)? ))? $/ix);
}

sub units {
    return @{$_[0]->{_units}};
}
1;
