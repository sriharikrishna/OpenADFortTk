package FTscan;
use FTList qw(:REs :DEFAULT);
use FTpat;
use FTTerm;

sub new {
    my($class,$l) = @_;
    my($ln,@tl) = ftlist($l);
    my($leading) = ($l =~ /^([\s\d]+)/);

    return bless {ln => $ln,
		  leading => $leading,
		  tl => \@tl},$class;
}
#
# internal use only: make a new scan object from token list
#                    NOTE: has no line number or leading
sub _nln {
    return bless {ln => '', leading => '', tl => [ @_ ]},'FTscan';
}
sub copy {
    my($s) = shift;

    return bless {ln => $s->ln(),
	          leading => $s->leading(),
		  tl => [ $s->tl() ]},ref($s);
}
sub str {
    my($self) = shift;
    my($ln,@tl) = ($self->{'ln'},@{$self->{'tl'}});
    my(@jl) = ();
    my($prv) = '';

    foreach (@tl) {
	if (/\(/ && ($prv =~ /if/i )){
	    push @jl,' ';
	}
	if (/^\w+$/ && ($prv =~ /^\w+$/)){
	    push @jl,' ';
	}
	if (/^$dot$/ || ($prv =~ /^$dot$/i)){
	    push @jl,' ';
	}
	if (/^\w+$/ && ($prv eq ')')){
	    push @jl,' ';
	}
	if (($_ eq '=') || ($prv eq '=')){
	    push @jl,' ';
	}
	if (($_ eq '*') && ($prv =~ /print/i)){
	    push @jl,' ';
	}
	push @jl,$_;
	$prv = $_;
    }
    my($tl) = join('',@jl);
    return $tl;
}
sub to_string {
    my($tl) = $_[0]->str();
    my($ln) = $_[0]->ln();
    return ($ln ? sprintf(' %-4s ',"$ln") : '') . $tl;
}
sub lstring {
    my($self) = @_;

    return $self->leading() . $self->str();
}
sub ln {
    return $_[0]->{'ln'};
}
sub leading {
    return $_[0]->{'leading'};
}
sub tl {
    return @{$_[0]->{'tl'}};
}
sub set_ln {
    $_[0]->{'ln'} = $_[1];
    return $_[0];
}
sub set_leading {
    $_[0]->{'leading'} = $_[1];
    return $_[0];
}
sub set_tl {
    my($self) = shift;
    $self->{'tl'} = [ @_ ];
    return $self;
}
sub match {
    my($self,$pat) = @_;

    my($str) = join($FTpat::_TBC,$self->tl());
    my(@res) = ($str =~ /$pat/i);

    return wantarray ? map {_nln(_clean($_))} @res : @res+0;
}
sub _clean {
    my($str) = @_;

    $str =~ s/$FTpat::_TBC$//;
    return split(/$FTpat::_TBC/,$str);
}
sub gmatch {
    my($self,$pat) = @_;

    my($str) = join($FTpat::_TBC,$self->tl());
    my(@res) = ($str =~ /$pat/ig);

    return wantarray ? map {_nln(_clean($_))} @res : @res+0;
}
sub subst {
    my($self,$subst) = @_;

    my($str) = join($FTpat::_TBC,$self->tl());
    my($res);
    eval('$res = ($str =~ ' . "s${subst}i)");
    $self->{'tl'} = [ _clean($str) ];
    return $res;
}
# comma break
sub cbreak {
    my(@tl) = shift()->tl();
    my(@terms) = ();
    my(@current) = ();
    my($nest) = 0;
    my($t);

    return () unless (@tl);
    while(@tl) {
	$t = shift @tl;
	$nest++ if ($t eq '(');
	$nest-- if ($t eq ')');
	if (($t eq ',') && (! $nest)) {
	    push @terms,_nln(@current);
	    @current = ();
	    next;
	}
	push @current,$t;
    }
    push @terms,_nln(@current) if (@current); # trailing empty term discarded
    return @terms;
}
sub map {
    my($self) = shift;
    my($rt) = shift;

    return (map {&$rt($_,@_)} $self->tl());
}
sub mterm {
    my($self,$pat) = @_;

    my($b) = $self->copy();
    my($bp,$tp,$ap) = FTTerm::mterm($pat,$b->tl());
    $b->set_tl(@$bp);
    return ($b,_nln(@$tp),_nln(@$ap));
}

sub rterm {
    my($self,$pat,$fn) = @_;
    my($b,$t,$a) = $self->mterm($pat);
    $b->set_tl($b->tl(),&$fn($t)->tl(),$a->tl());
    return $b;
}

sub grterm {
    my($self,$pat,$fn) = @_;
    my($b,$t,$a) = $self->mterm($pat);
    return $self unless ($t->tl());
    $b->set_tl($b->tl(),&$fn($t)->tl(),$a->grterm($pat,$fn)->tl());
    return $b;
}
sub args {
    my($self) = @_;
    my(@tl) = $self->tl();
    shift(@tl);
    return () unless(@tl);
    
    return map {_nln(@$_)} (tlcsv (@tl[1 .. $#tl-1]));
}
sub term {
    my($self) = @_;
    my(@tl) = $self->tl();
    my($f) = _nln(shift(@tl));
    @tl = map {_nln(@$_)} (tlcsv (@tl[1 .. $#tl-1]));
    return ($f,@tl);
}
1;

