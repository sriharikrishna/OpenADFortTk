package Symtab;
use FTList qw(:DEFAULT :SKIP);
use FTTerm;
use Ffile;
use FTparse;
use FTscan;
use File::Spec;
use File::Basename;

sub new {
    my($class,$fs,$file_global) = @_;
    my($rv) = bless {},$class;

    $rv->{_file_global} = $file_global;

    _populate($fs,$rv);

    return $rv;
}
#
# The common code to build or redo a symbol table part of
# a context
#
sub _populate {
    my($fs,$rv) = @_;

    $module_table = $rv->{_file_global}->{_module_table};

    $module_table ||= {};

    $path = $rv->{_file_global}->{_path};

    my(@lines) = map {$_->line()} $fs->lines();
    
    # install std implicit
    # integer (i-n), rest real

    $rv->set_implicit_map(nlftlist('real(a-z)'));
    $rv->set_implicit_map(nlftlist('integer(i-n)'));

    while(@lines) {
	local($_) = shift @lines;
	next if (/$comment/o || /$bl/o);
	my($ln,@tl) = ftlist($_);
	last if ($ln);
	if (my($incl) = parse_include(@tl)) {
	    unshift @lines,map {$_->line()}
	                   Ffile->new($incl)->lines();
	    next;
	}
	if (lc($tl[0]) eq 'use') {
	    my($tbl) = $module_table->{$tl[1]};
	    if ($tbl){
		$rv->_module_merge($tbl);
	    }
	    else {
		warn "WARNING: Module $tl[1] not previously loaded!\n";
	    }
	    next;
	}
	if (my($u,$n,$t,@v) = parse_unit(@tl)) {
	    grep {$rv->{_type_decl}->{$_}->{_vclass} = 'arg'}
	         @v;
	    $rv->{_unit}->{_type} = $u;
	    $rv->{_unit}->{_name} = $n;
	    $rv->{_unit}->{_retn_type} = $t;
	    @{$rv->{_unit}->{_args}} = @v;
	    next;
	}
	if (my($t,@vdt) = parse_type(@tl)) {
	    @vdt = parse_var_dims(@vdt);
	    grep {my($v,$d) = @$_;
		  $rv->{_type_decl}->{$v}->{_type} = $t;
		  $rv->{_type_decl}->{$v}->{_dim} = $d;
		  $rv->{_type_decl}->{$v}->{_decl} = 1;
		  $rv->{_type_decl}->{$v}->{_vclass} ||= 'local';
	      } @vdt;
	    next;
	}
	if (my($cb,@vdt) = parse_common(@tl)){
	    @vdt = parse_var_dims(@vdt);
	    grep {my($v,$d) = @$_;
		  $rv->{_type_decl}->{$v}->{_dim} = $d if (@{$d->[0]});
#		  $rv->{_type_decl}->{$v}->{_decl} = 1;
		  $rv->{_type_decl}->{$v}->{_vclass} = "common:$cb";
	      } @vdt;
	    @{$rv->{_common_blks}->{$cb}} = map {$_->[0]} @vdt;
	    next;
	}
	if ($tl[0] eq 'dimension') {
	    shift @tl;
	    my(@vdt) = parse_var_dims( tlcsv(@tl));
	    grep {my($v,$d) = @$_;
		  $rv->{_type_decl}->{$v}->{_dim} = $d;
#		  $rv->{_type_decl}->{$v}->{_decl} = 1;
		  $rv->{_type_decl}->{$v}->{_vclass} ||= 'local';
	      } @vdt;
	    next;
	}
	if ($tl[0] eq 'implicit') {
	    shift @tl;
	    if ($tl[0] eq 'none'){
		$rv->{_impl_map} = {};
		next;
	    }
	    grep {$rv->set_implicit_map(@$_)} tlcsv(@tl);
	}
    }
    return $rv;
}
#
# given a context, redo the symbol table entries
#
sub redo {
    my($rv,$fs) = @_;

    _populate($fs,$rv);

    return $rv;
}
sub set_implicit_map {
    my($self,@tl) = @_;
    
    my($type,@e) = @{(parse_implicit(@tl))[0]};

    foreach (@e) {
	if (! ref($_)){
	    $self->{_impl_map}->{$_} = $type;
	    next;
	}
	foreach ($_->[0] .. $_->[1]){
	    $self->{_impl_map}->{$_} = $type;
	}
    }
#
#  HACK: default setting of vars beginning with _ ??
#   arbitrarily decide that _ has same type as a
#
    $self->{_impl_map}->{'_'} = $self->{_impl_map}->{'a'};
}
sub implicit_type {
    my($self,$var) = @_;

    return $self->{_impl_map}->{substr($var,0,1)} || 'none'
}
sub unit_type {
    my($self) = @_;

    return $self->{_unit}->{_type};
}
sub unit_name {
    my($self) = @_;

    return $self->{_unit}->{_name};
}
sub unit_args {
    my($self) = @_;

    return @{$self->{_unit}->{_args}};
}
sub lookup_type{
    my($self,$var) = @_;

    $var = lc $var;
    return $self->{_type_decl}->{$var}->{_type} || $self->implicit_type($var);
}
#
# HACK, since character declarations are special
#
sub lookup_type_str {
    my($pre_type) = $_[0]->lookup_type($_[1]);
    return $pre_type unless (ref($pre_type) eq 'ARRAY');
    return join('',@$pre_type);
}
sub lookup_type_cls {
    my($pre_type) = $_[0]->lookup_type($_[1]);
    return $pre_type unless (ref($pre_type) eq 'ARRAY');
    return 'character';
}
sub lookup_dim {
    my($self,$var) = @_;

    $var = lc $var;
    return @{$self->{_type_decl}->{$var}->{_dim}};
}
#
# This is separate, because lookup_dim interface already working
# Here I want the actual array of dimension objects.
# Should be empty for scalars (NOT a ref to empty list).
#
sub lookup_dims {
    my($self,$var) = @_;
    my(@l) = @{$self->{_type_decl}->{lc $var}->{_dim}};
    return () if (@l && (! @{$l[0]}));
    return @l;
}
sub dims_str_of {
    my(@dims) = $_[0]->lookup_dims($_[1]);
    return @dims ? '(' . join(',',map {join('',@$_)} @dims) . ')' : '';
}

sub lookup_decl {
    my($self,$var) = @_;

    $var = lc $var;
    return $self->{_type_decl}->{$var}->{_decl};
}
sub lookup_vclass {
    my($self,$var) = @_;

    $var = lc $var;
    return $self->{_type_decl}->{$var}->{_vclass} || 'local';
}
sub raw_vclass_of {
    my($v) = $_[0]->lookup_vclass($_[1]);
    $v =~ s/common:.*$/common/;
    return $v;
}
sub common_blocks {
    my($self) = @_;

    return keys %{$self->{_common_blks}}
}
sub lookup_cb {
    my($self,$cb) = @_;

    return $self->{_common_blks}->{$cb} + 0;
}
sub vars_in_common_block {
    my($self,$cb) = @_;

    return @{$self->{_common_blks}->{$cb}};
}
sub _module_merge {
    my($self,$st) = @_; # $st is the module symbol table to be merged

    my($modname) = "module:".$st->unit_name();
    foreach $v (keys(%{$st->{_type_decl}})){
	$self->{_type_decl}->{$v}->{_type}   = $st->lookup_type($v);
	$self->{_type_decl}->{$v}->{_dim}    = [ $st->lookup_dim($v) ];
	$self->{_type_decl}->{$v}->{_vclass} = $modname; 
    }
}

1;
