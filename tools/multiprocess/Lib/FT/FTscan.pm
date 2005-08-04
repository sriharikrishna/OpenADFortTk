package FTscan;
use FTList qw(:REs :DEFAULT);
use FTpat;
use FTTerm;
use FTscanUtils;

sub new {
    my($class,$l) = @_;
    my($ln,@tl) = ftlist($l);
    my($leading) = ($l =~ /^([\s\d]+)/);

    return bless {ln => $ln,
		  leading => $leading,
		  tl => \@tl},$class;
}
sub empty {
    return bless {ln => '',
		  leading => '',
		  tl => []},$_[0];
}
sub set_indent {
    $_[0]->{leading} = $_[1];
    return $_[0];
}
sub indent {
    local($_) = $_[0]->{leading};
    s/\d/ /g;
    return $_;
}
sub plus_indent {
    $_[0]->set_indent($_[0]->indent() . $_[1]);
    return $_[0];
}
sub make_term {
    my($class,$f,@args) = @_;
    my($term) = FTscan->empty()
	        ->set_tl($f,'(', sl_join(',',@args)->tl(),')');
    return $term;
}
#
# convert an array of termlist(refs) to array of FTscans
#
sub conv {
    my($class) = shift;
    return (map {_nln(@$_)} @_);
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
	if (/^\w+$/ && ($prv =~ /\A double \s* precision \z/xms)){
	    push @jl,' ';
	}
	if (/^[\'\"]/ && ($prv =~ /^\w+$/)){
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
	if ($_ eq '//' || $prv eq '//') {
	    push @jl,' ';
	}
	if ($_ eq '::' || $prv eq '::') {
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
sub is_nil {
    return (! ($_[0]->tl()));
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
sub gmterm {
    my($self,$pat) = @_;

    my($bp,$tp,$ap) = $self->mterm($pat);
    return () if $tp->is_nil();
    push my(@t),$tp,$ap->gmterm($pat);
    return (@t);
}
sub gmterm_r {
    my($self,$pat) = @_;

    my($bp,$tp,$ap) = $self->mterm($pat);

    return () if $tp->is_nil();

    my @rec = map {$_->gmterm_r($pat)} $tp->args();
    return (
       $tp,
       @rec,
       $ap->gmterm_r($pat),
    );
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
sub term_split {
    my($term) = @_;

    my($head) = ( $term->tl() )[0];
    return ($head,$term->args());
}
sub args_p {
    my(@tl) = $_[0]->tl();
    shift @tl; pop @tl;
    return (FTscan->empty()->set_tl(@tl)->cbreak());
}
sub args_as_scan {
    my(@tl) = $_[0]->tl();
    shift @tl;  # grab head
    shift @tl;  # grab '('
    pop @tl;    # remove ')'

    return (FTscan->empty()->set_tl(@tl));
}
sub term {
    my($self) = @_;
    my(@tl) = $self->tl();
    my($f) = _nln(shift(@tl));
    @tl = map {_nln(@$_)} (tlcsv (@tl[1 .. $#tl-1]));
    return ($f,@tl);
}
sub csv {
    my(@tl) = $_[0]->tl();
    return map {_nln(@$_)} tlcsv(@tl);
}
sub concatd {
    my($self) = shift @_;
    $self->set_tl($self->tl(),map {_concat_helper($_)} @_);
    return $self;
}
sub _concat_helper {
    return ($_[0]) unless (ref($_[0]) eq 'FTscan');
    return ($_[0]->tl());
}
sub lmatch {
    my($s) = shift @_;
    my(@tl) = $s->tl();
    my($i);

    for $i (0 .. $#_){
	return () unless ($tl[$i] eq $_[$i]);
    }
    return ($s);
}
sub checkit (@@) {
    my($l1,$l2) = @_;
    my(@l1) = @$l1;
    my(@l2) = @$l2;

    return () if (@l1 != @l2);
    for my $i (0 .. $#l2){
	return () unless ($l1[$i] eq $l2[$i]);
    }
    return ($l1);

}
sub token_scan {
    my($s) = shift @_;
    my($tl) = [ $s->tl() ];

    while ( (@$tl + 0) >= @_ + 0){
	return ($s) if checkit([ @$tl[0 .. $#_] ],[ @_ ]);
	shift @$tl;
    }
    return ();
}
sub scan_index (@@) {
    my($l1,$l2) = @_;

    return () if ( @$l1 == 0 || @$l2 == 0);
    foreach my $i (0 .. (@$l1+0) - (@$l2+0)){
	return ($i) if checkit([ @$l1[$i .. $i + @$l2 -1] ], $l2);
    }
    return ();
}
sub g_repl_token {
    my($s) = shift @_;
    my(@pat) = @{ shift @_ };
    my(@repl) = @{ shift @_ };

    my(@tl) = $s->tl();
    my(@tl1) = @tl;
    while (my($i) = scan_index([ @tl1 ],[ @pat ])){
	splice @tl, $i, @pat+0, @repl;
	@tl1 = @tl1[$i + @repl .. $#tl];
    }
    return $s->set_tl(@tl);
}

1;

