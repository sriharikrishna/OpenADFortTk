package ADtypes;
use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(adtype adletter);

my(%adtypes) = 
    (
     real => 1,
     'double precision' => 1,
     complex => 1,
     'double complex' => 1,
     );
my(%adletters) =
    (
     real => 'r',
     'double precision' => 'd',
     complex => 'c',
     'double complex' => 'z',
     integer => 'i',
     logical => 'l',
     );

sub adtype {
    return $adtypes{$_[0]};
}

sub adletter {
    return $adletters{$_[0]} || '??';
}
1;
