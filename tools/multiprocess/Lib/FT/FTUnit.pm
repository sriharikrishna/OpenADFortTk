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

    my($env);
    $env->{units_ref_list} = [];
    $env->{current_unit} = Ffile->empty();
    $env->{end_ref} = 0;

    $ff->cmap(\&split_unit,$env);
    return $env->{units_ref_list};
}

sub split_unit {
    my($line,$env) = @_;

    to_unit($line,$env);
    if ($env->{end_ref}){
	push @{$env->{units_ref_list}},$env->{current_unit};
	$env->{current_unit} = Ffile->empty();
	$env->{end_ref} = 0;
    }
}

sub to_unit {
    my($line,$env) = @_;

    $env->{current_unit}->add_lines($line);
    $env->{end_ref} = $line->match(qr/^ 
				   end (?: $TB (?: module (?: $TB \w+)?|
		                       		   program (?: $TB \w+)?|
				       		   subroutine (?: $TB \w+)?|
				       		   function (?: $TB \w+)? ))?
				   $/ix);
}

sub units {
    return @{$_[0]->{_units}};
}
1;
