package FTdecl;

use FTpat;
use FTscan;
use FTscanUtils;

use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(is_decl is_stmt_fn);

my(%decl1) = (
"common"   => 1,
"logical"  => 1,
"data"     => 1,
"implicit" => 1,
"equivalence"  => 1,
"parameter" => 1,
"save"  => 1,
"external"  => 1,
"character"  => 1,
"intrinsic"  => 1,
"include"    => 1, # hmmm
"real"  => 1,
"double precision"  => 1, # the tokenizer makes this one token
"integer"  => 1,
"dimension"  => 1,
"namelist"   => 1,
"complex"    => 1,
"subroutine" => 1,
"program"    => 1,
"function"   => 1,
"module"   => 1,
	      );

sub is_stmt_fn {
    my($l,$st) = @_;
    my($b,$c,$a) = $l->mterm(qr/[a-z_] \w*/ix);
    my($eq) = $a->tl();
    my($v,$paren) = $c->tl();
    my(@dims) = $st->lookup_dims($v);
    return (($eq eq '=') && ($paren eq '(')
	    && (! @dims));
}

sub is_decl {
    my($w1,$w2) = map(lc,($_[0]->tl()));

    return ($decl1{$w1}
	    || (($w1 eq 'block') && ($w2 eq 'data'))
	    ||	is_stmt_fn(@_));
}


1;
