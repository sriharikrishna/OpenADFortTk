#
# instead of strings, use list of fortran
#  tokens. Should work with FTList
#
package FTTerm;
use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(pt tlcsv ptl mterm);

# from token list, extract balanced paren element
#  return 1 ref, 1 list: list 1 = paren list, list 2 = remaining
sub pt {
    my(@remain) = @_;
    my(@pt) = ();
    my($cnt) = 0;

    while(@remain) {
	my($e) = shift @remain;
	push @pt, $e;
	$cnt++ if ($e eq '(');
	$cnt-- if ($e eq ')');
	last unless ($cnt);
    }
    return (\@pt,@remain);
}

# tlcsv = term list of comma-separated values.
# Like commabreak in old adifor
#
# given a token list, with some embedded ',',
# return a list of lists(refs), each list ref
# being a collection of tokens that corre
sub tlcsv {
    my(@tl) = @_;
    my(@terms) = ();
    my(@current) = ();

    return ([]) unless (@tl);
    while(@tl) {
	my($t) = $tl[0];
	if ($t eq ',') {
	    push @terms,[ @current ];
	    @current = ();
	    shift @tl;
	    next;
	}
	if ($t eq '(') {
	    (my($p),@tl) = pt(@tl);
	    push @current,@$p;
	    next;
	}
	shift @tl;
	push @current,$t;
    }
    push @terms,[ @current ] if (@current);
    return @terms;
}
sub ptl {
    my($pt,@dc) = pt(@_);
    return tlcsv(@$pt[1 .. $#$pt -1]);
}
#
# from token list, extract term whose head matches
# a given pattern
#
sub mterm {
    my($pat) = shift;
    my(@remain) = @_;
    my(@before,@term,@after) = ();
    
    while (@remain){
	$_ = shift @remain;
	if (/$pat/i){
	    push @term,$_;
	    @after = @remain;
	    last;
	}
	push @before,$_;
    }
    return (\@before,\@term,\@after) unless ($after[0] eq '(');
    my($cnt) = 0;
    while (@after) {
	$_ = shift @after;
	push @term, $_;
	$cnt++ if ($_ eq '(');
	$cnt-- if ($_ eq ')');
	last unless ($cnt);
    }
    return (\@before,\@term,\@after);
}

1;
