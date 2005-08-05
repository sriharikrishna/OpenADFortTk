package Canonicalizer;

use Exporter;
use Ffile;
use FTpat;
use FTproc;
use FortranSourceLine;
use Intrinsic;

@ISA = qw(Exporter);
@EXPORT = qw( $fn2sub 
	      $add_fun_repl_decls
	      add_fun_repl_decls
	    );

$fn2sub             = FTproc->new(\&__init ,\&rw_fn_w_tmp);
$add_fun_repl_decls = FTproc->new(\&__init2,\&add_fun_repl_decls);

#my(@subtree_pat) = (
#    \qw(select case),
#    \(call \qr/\A \w+ \z/xms),
#    \qw(if),
#    \qw(do while),
#    \qw(open),
#    \qw(close),
#    \qw(read),
#    \qw(write),
#    \qw(print),
#);

$__VERBOSE = 0;

sub __set_verbose {
    $__VERBOSE = $_[0];
}

sub __init {
    my($st) = @_;

    print STDERR 'canonicalizing routine ',$st->unit_name(),"\n"
	if ($__VERBOSE);

    $st->{_is_fun}     = _gen_pred($st);
    $st->{_repl_fun}   = _gen_repl($st);
}

sub __init2 {
    my($st) = @_;

    print STDERR 'declaring vars for ',$st->unit_name(),"\n"
	if ($__VERBOSE);
}

sub _gen_pred {
    my($st) = @_;

    return sub {
	my($a_ref) = @_;
	return _has_paren($a_ref) && !$st->lookup_dims($a_ref->[0])
	    && ! _is_intrinsic($a_ref);
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

sub _is_if {
    return $_[0]->lmatch('if');
}

sub _repl_w_tmp_in_call {
    my($l,$st,$is_fun,$repl_fun) = @_;

    my($head,$args)
	= $l->match(qr/call $TB (\w+) $TB (.*)/ixms);

    my($new_line) = $l->same_leading('call');
    $new_line->concatd($head,$args->grterm($is_fun,$repl_fun));
    return $new_line;
}

sub _repl_w_tmp_in_if {
    my($l,$st,$is_fun,$repl_fun) = @_;

    my($b,$t,$a) = $l->mterm(qr/\A if \z/ixms);
    my(@tl) = $t->tl();
    shift @tl;
    $t->set_tl(@tl);
    $t = $t->grterm($is_fun,$repl_fun);
    my($new_line) = $l->same_leading('if')->concatd($t,$a);
    return $new_line;
}

sub _should_repl_in_subtree {
    my($l) = @_;
}

sub _repl_fn_w_tmp {
    my($l,$st,$is_fun,$repl_fun) = @_;
    my($repl_line);

    $st->{_new_calls} = [];
    if (_is_call($l)){
	$repl_line = _repl_w_tmp_in_call($l,$st,$is_fun,$repl_fun);
    }
    elsif (_is_if($l)){
	$repl_line = _repl_w_tmp_in_if($l,$st,$is_fun,$repl_fun);
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
    return ($tl_ref->[0] =~ qr/\A \w+ \z/xms) && ( $tl_ref->[1] eq '(' );
}

sub _is_intrinsic {
    my($tl_ref) = @_;

    return $Intrinsic::table{ $tl_ref->[0] };
}

sub fn_in_l {
    my($l,$is_fun) = @_;

    if (my($call_args) = $l->match(
	      qr/^ call $TB \w+ $TB \( $TB (.*) $TB \)/ix)){
	return fn_in_l($call_args,$is_fun);
    }

    if (_is_if($l)) {
	return fn_in_l($l->scan()->args_as_scan(),$is_fun);
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
