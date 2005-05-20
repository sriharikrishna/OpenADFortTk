package FTcontext;
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
    return bless _common(Ffile->new($_[1])),$_[0];
}

#
# the 'new' operation from a string (ie a 'here' document)
#
sub here {
    return bless _common(Ffile->new_from_heredoc($_[1])),$_[0];
}

#
# The common ops to perform for either creation
#
sub _common {
    my($u) = FTUnit->new($_[0]);

    return {_units => [ map {_add_context($_)} $u->units() ]};
}

sub _add_context {
    my($ctx);
    my($st) = Symtab->new($_[0]);
    add_markers($_[0],$st);
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

sub cmap {
    my($self,$proc,@args) = @_;

    return map {$_->{_unit}->cmap($proc,$_->{_symtab},@args)}
               @{$self->{_units}}
}

sub cmap_sem {
    my($self,$proc,@args) = @_;

    return map {$_->{_unit}->cmap_sem($proc,$_->{_symtab},@args)}
               @{$self->{_units}}
}

sub crewrite {
    my($self,$proc,@args) = @_;

    my(@nunits) = map {$_->{_unit}->crewrite($proc,$_->{_symtab},@args)}
                     @{$self->{_units}};
    my(@sts) = $self->contexts();

    my($rv) = {_units => [ map {_redo_context($nunits[$_],$sts[$_])}
			   (0 .. $#nunits)] };
    bless $rv,ref($self);
    return $rv;
}

sub crewrite_sem {
    my($self,$proc,@args) = @_;

    my(@nunits) = map {$_->{_unit}->crewrite_sem($proc,$_->{_symtab},@args)}
                     @{$self->{_units}};

    my(@sts) = $self->contexts();

    my($rv) = {_units => [ map {_redo_context($nunits[$_],$sts[$_])}
			   (0 .. $#nunits)] };
    bless $rv,ref($self);
    return $rv;
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
