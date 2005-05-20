package FTtypes;

use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(is_char_type);

sub is_char_type {
    return (ref($_[0]) eq  'ARRAY');
}

1;
