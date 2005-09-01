package FTcontext;
use FindBin qw($RealBin);
use File::Basename;
use File::Spec;
use Ffile;
use FTUnit;
use FTpat;
use FTscan;
use FTscanUtils;
use FTdecl;

#
# the 'new' operation from a file
#
sub file {
    my($path) = $_[2];
    unless($path){
	$path = [ dirname($_[1]) ];
    }
    return bless _common(Ffile->new($_[1]),$path),$_[0];
}

#
# the 'new' operation from a string (ie a 'here' document)
#
sub here {
    my($path) = $_[2];
    unless($path){
	$path = [ $RealBin ];
    }
    return bless _common(Ffile->new_from_heredoc($_[1]),$path),$_[0];
}

#
# The common ops to perform for either creation
#
sub _common {
    my($u,$path) = @_;
    my($module_table) = {};

    my($u) = FTUnit->new($u);

    my($file_context) = {
	_module_table  => {},
	_path          => $path,
    };

    return {_units        =>
		[ map {_add_context($_,$file_context)} $u->units() ],
	   };
}

sub _add_context {
    my($st) = Symtab->new($_[0],$_[1]);
    add_markers($_[0],$st);
    if ($st->unit_type() eq 'module'){
	$st->{_file_global}->{_module_table}->{$st->unit_name()} = $st;
    }
    return {_unit => $_[0],
	    _symtab => $st,
	   };
}
sub _redo_context {
    my($ctx,$st) = @_;

    $st = $st->redo($ctx);
    add_markers($ctx,$st);
    return {_unit => $ctx,
	    _symtab => $st,
	   };
}
sub units {
    return @{$_[0]->{_units}};
}
sub module_table {
    $tbl = $_[0]->{_units}->[0]->{_symtab}->{_file_global}->{_module_table};
    return $tbl if $tbl;
    return {};
}
sub path {
    $p = $_[0]->{_units}->[0]->{_symtab}->{_file_global}->{_path};
    return $p if $p;
    return [];
}
sub ffiles {
    return (map {$_->{_unit}} @{$_[0]->{_units}});
}
sub contexts {
    return (map {$_->{_symtab}} @{$_[0]->{_units}});
}
sub to_string {
    return fconcat($_[0]->ffiles())->to_string();
}

sub write {
    return fconcat($_[0]->ffiles())->write($_[1]);
}

sub _mapper {
    my($self,$map,$proc,@args) = @_;

    return map {$_->{_unit}->$map($proc,$_->{_symtab},@args)}
               @{$self->{_units}}
}

sub cmap {
    my($self,$proc,@args) = @_;

    return _mapper($self,'cmap',$proc,@args);
}

sub cmap_sem {
    my($self,$proc,@args) = @_;

    return _mapper($self,'cmap_sem',$proc,@args);
}

sub _crewrite {
    my($self,$rewr,$proc,@args) = @_;

    my(@nunits) = map {$_->{_unit}->$rewr($proc,$_->{_symtab},@args)}
                     @{$self->{_units}};
    my(@sts) = $self->contexts();

    my($rv) = {_units =>
		   [ map
		       {_redo_context($nunits[$_],$sts[$_])}
		     (0 .. $#nunits)] };
    bless $rv,ref($self);
    return $rv;
}

sub crewrite {
    my($self,$proc,@args) = @_;

    return _crewrite($self,'crewrite',$proc,@args);
}

sub crewrite_sem {
    my($self,$proc,@args) = @_;

    return _crewrite($self,'crewrite_sem',$proc,@args);
}

sub add_markers {
    my($ff,$st) = @_;
    my($last);

    foreach $l (@{$ff->{_lines}}){
	next if $l->is_comment();
	if (is_decl($l,$st)){
	    $last = $l;
	    next;
	}
	$l->putprop('_first_exec',1);
	last;
    }
    $last->putprop('_last_decl',1);
}

1;
