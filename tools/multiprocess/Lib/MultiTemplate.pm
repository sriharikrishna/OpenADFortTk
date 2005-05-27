package MultiTemplate;

use Ffile;
use ADtemplate;

@ISA = qw(Exporter);
@EXPORT = qw(multi_inst);

sub multi_inst {
    my(@template) = $_[0]->map(\&get_templ);
    my($t) = ADtemplate->new(Ffile->new($template[0]));
    return $t->instantiate($_[0]);
}

sub get_templ {
    local($_) = @_;

    if (/^c \s* \$OpenAD \s+ XXX \s+ TEMPLATE \s+ (\S+) \s* $/ix){
	return $1;
    }
    return ();
}

1;
