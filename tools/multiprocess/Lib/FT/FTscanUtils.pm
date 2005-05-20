package FTscanUtils;
use FTscan;
use Symtab;
use FTList qw(:NUMRE);
use FTpat;
use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(sl_join approxType);

sub sl_join {
    my($join_tok,@scns) = @_;

    return FTscan->empty() unless(@scns);
    my($s1) = shift @scns;
    return FTscan::_nln($s1->tl(),map {($join_tok,$_->tl())} @scns);
}

sub approxType {
    my($scn,$s) = @_;

    return 'double precision' if ($scn->match(qr/^(?:[-+] $TBE)? $dblRE/x));
    return 'real' if ($scn->match(qr/^(?:[-+] $TBE)? $realRE/x));
    return 'integer' if ($scn->match(qr/^(?:[-+] $TBE)? \d+/x));
    return 'character' if ($scn->match(qr/$TBE [\'\"]/x));
    return 'logical' if ($scn->match(qr/$TBE \.(?:true|false) $TBE/x));
    my($lv) = $scn->match(qr/^(?:[-+] $TBE)? (\w+)/x);

    return $s->lookup_type($lv->str());
}

1;
