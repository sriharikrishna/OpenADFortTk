package FTpat;
use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw($TB $TBC $TBE);

$_TBC = "\cB";
$TB = qr/$_TBC/;
$TBE = qr/(?:^|$_TBC|$)/;
$TBC = $_TBC;
1;
