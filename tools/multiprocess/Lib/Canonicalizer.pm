package Canonicalizer;

use Exporter;
use Ffile;
use FTpat;
use FTproc;
use FortranSourceLine;

@ISA = qw(Exporter);
@EXPORT = qw( $fn2sub 
	      add_fun_repl_decls
	    );

$fn2sub = FTproc->new(\&__init,\&rw_fn_w_tmp);

sub __init {
    my($st) = @_;

    $st->{_is_fun}     = _gen_pred($st);
    $st->{_repl_fun}   = _gen_repl($st);
}

sub _gen_pred {
    my($st) = @_;

    return sub {
	my($a_ref) = @_;
	return _has_paren($a_ref) && !$st->lookup_dims($a_ref->[0]);
    };
}

sub _gen_repl {
    my($st) = @_;

    return sub {
	my($term) = @_;
	my($current_tmp_idx) = $st->{_tmp_cntr} + 0;
	my($new_tmp_var) = 'ad_ctmp_' . $current_tmp_idx;
	my($new_term) = FTscan->new($new_tmp_var);

	$st->{_tmp_cntr}++;
	push @{ $st->{_new_calls} }, _new_call($new_tmp_var,$term);
	push @{ $st->{_canon_decls} },_new_decl($new_tmp_var,$term,$st);

	return $new_term;
    }
}

sub _new_call {
    my($v,$term) = @_;

    my($head,@args) = $term->term_split();
    $head = 's_' . $head;
    push @args,FTscan->new($v);

    return FTscan->empty()->concatd('call',FTscan->make_term($head,@args));

}

sub _new_decl {
    my($tmp_var,$fun_term,$st) = @_;

    my($head) = $fun_term->term_split();
    my($type) = $st->lookup_type($head);

    return FTscan->empty()->concatd($type,$tmp_var);
}

sub _is_call {
    my($l) = @_;

    return $l->lmatch('call');
}

sub _repl_w_tmp_in_call {
    my($l,$st,$is_fun,$repl_fun) = @_;

    my($head,$args)
	= $l->match(qr/call $TB (\w+) $TB (.*)/ixms);

    my($new_line) = $l->same_leading('call');
    $new_line->concatd($head,$args->grterm($is_fun,$repl_fun));
    return $new_line;
}

sub _repl_fn_w_tmp {
    my($l,$st,$is_fun,$repl_fun) = @_;
    my($repl_line);

    $st->{_new_calls} = [];
    if (_is_call($l)){
	$repl_line = _repl_w_tmp_in_call($l,$st,$is_fun,$repl_fun);
    }
    else {
	$repl_line = $l->grterm($is_fun,$repl_fun);
    }
    my(@new_calls) = map {$l->same_level($_)} @{ $st->{_new_calls} };

    @new_calls
	= map {_rw_fn_w_tmp_aux($_,$st,$is_fun,$repl_fun)} @new_calls;

    return (@new_calls,$repl_line);
}

sub _rw_fn_w_tmp_aux {
    my($l,$st,$is_fun,$repl_fun) = @_;

    if (fn_in_l($l,$is_fun)) {
	return _repl_fn_w_tmp($l,$st,$is_fun,$repl_fun);
    }

    return ($l);
}

sub rw_fn_w_tmp {
    my($l,$st) = @_;

    return ($l) unless (_in_exec_stmts($l,$st));

    return _rw_fn_w_tmp_aux($l,
			    $st,
			    $st->{_is_fun},
			    $st->{_repl_fun},);
}

sub mark_fn2sub {
    my($l,$st) = @_;

    return ($l) unless (_in_exec_stmts($l,$st));

    my($is_fun) = _gen_pred($st);

    if (fn_in_l($l,$is_fun)){
	return(<<'C1',$l);

c This is the thing

C1
    }
    return ($l);
}

sub _in_exec_stmts {
    my($l,$st) = @_;

    $st->{_exec} = 1 if ((! $st->{_exec}) && ($l->getprop('_first_exec')));

    return $st->{_exec};
}

sub _has_paren {
    my($tl_ref) = @_;
    return ($tl_ref->[0] =~ qr/\w+/) && ( $tl_ref->[1] eq '(' );
}

sub fn_in_l {
    my($l,$is_fun) = @_;

    if (my($call_args) = $l->match(
	      qr/^ call $TB \w+ $TB \( $TB (.*) $TB \)/ix)){
	return fn_in_l($call_args,$is_fun);
    }
    
    my($b,$t,$a) = $l->mterm($is_fun);
    return !$t->is_nil();
}

sub add_fun_repl_decls {
    my($l,$st) = @_;

    if ($l->getprop('_last_decl')){
	return (
	    ( map {$l->same_level($_)} @{ $st->{_canon_decls} } ),
	    $l,
	);
    }

    return($l);
}
1;
