package ADinline;

use Ffile;
use FTscan;
use FTpat;
use FTUnit;

sub gendef;

sub new {
    my($class,$ff) = @_;

    my(@defns) = map {gendef($_)} FTUnit->new($ff)->units();
    my(%defns) = map {$_->[0] => {args => $_->[1],
			      src => $_->[2],
			      scans => $_->[3]}} @defns;

    bless \%defns,$class;
}

#
# binding = [ [tok,...] ...  ] = array of token arrays, in order
# of inlinable function arguments
#

# return a function reference to do the inlining via
# a Ffile rewrite method

sub inline {
    my($inlobj) = @_;
    my($inl_next) = 0;
    my($directive_re) = qr/^[^\d\s] \s+ 
                           \$OpenAD\$ \s+ INLINE \s+
			   (\w+)\((.*)\)/ix;
    my($fn,$info) = ();

    return sub {
	my($line) = @_;
	if ($inl_next) {
	    $inl_next = 0;
	    my($scn) = FTscan->new($line);
	    my($name,$args) = $scn->match(qr/^call $TB (\w+) $TB
					     \( $TB (.*) $TB \)/ix);
	    $name = lc $name->str();
	    my(@args) = $args->cbreak();
	    @args = map {$_->str()} @args;
	    return ("C!! requested inline of $name has no defn\n",
		    $UNCHANGED,) unless ($inlobj->{$name});
	    my(@lns) = $inlobj->mksubs($name,[ @args ]);
	    @lns = map {$_ . "\n"} @lns;
	    return (@lns);
#	    return ("C - inline: $line");
	}
	if (($fn,$info) = ($line =~ /$directive_re/)) {
	    $inl_next = 1;
	    return ();
	}
	return ($UNCHANGED);
    }
}

sub mksubs {
    my($self,$fn,$bind) = @_;

    my($argsp) = $self->{$fn}->{args};
    my($scnsp) = $self->{$fn}->{scans};

    my(@strings) = ();
    my(%bind) = map { $argsp->[$_] => $bind->[$_] } (0 .. $#$argsp);
    foreach $l (@$scnsp){
	my($tmp) = $l->copy();
	my(@lst) = ();
	foreach $t ($l->tl()) {
	    push @lst, $bind{lc $t} || $t;
	}
	push @strings,$tmp->set_tl(@lst)->lstring();
    }
    return @strings;
}

sub mkbind {
    my($self,$fn,$bind) = @_;

    my($argsp) = $self->{$fn}->{args};
    my(%bind) = map { $argsp->[$_] => $bind->[$_] } (0 .. $#$argsp);
    return %bind;
}

sub gendef {
    my($ff) = @_;

    getdef_init();
    my ($name,$argp,@lns) = $ff->map(\&getdef);
    return [ $name,$argp,[ @lns ],[map {FTscan->new($_)} @lns] ];
}

{
    my($in) = 0;
    my($skip_til_sub) = 1; 
    my($start_re) = qr/^[^\d\s] \s+ \$OpenAD\$ \s+ INLINE \s+ DECLS/ix;
    my($end_re) = qr/^[^\d\s] \s+ \$OpenAD\$ \s+ END \s+ DECLS/ix;


    sub getdef_init {
	$in = 0;
	$skip_til_sub = 1;
	$start_re = qr/^[^\d\s] \s+ \$OpenAD\$ \s+ INLINE \s+ DECLS/ix;
	$end_re = qr/^[^\d\s] \s+ \$OpenAD\$ \s+ END \s+ DECLS/ix;
    }

    sub getdef {

	my($line) = @_;

	if ($in) {
	    $in = 0 if ($line =~ /$end_re/);
	    return ();
	}
	if ($line =~ /$start_re/) {
	    $in = 1;
	    return ();
	}
	my($scn) = FTscan->new($line);
	my($name,$args) = $scn->match(qr/^subroutine $TB (\w+)
				      (?:
				       $TB \( $TB (.*) $TB \)
				       )?$/ix);
	if ($name){
	    $skip_til_sub = 0;
	    return (lc $name->str(),[map {lc ($_->str())} $args->cbreak()]); 
	}
	return () if ($scn->match(qr/^end $TB subroutine/ix));
	return $skip_til_sub ? () : ($line);
    }
}
1;
