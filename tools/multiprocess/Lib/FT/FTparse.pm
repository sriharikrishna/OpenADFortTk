#
# parse Fortran term lists
#
package FTparse;
use Exporter;
use FTTerm;

@ISA = qw(Exporter);
@EXPORT = qw(parse_type_noun
	     parse_unit
	     parse_type
	     parse_var_dims
	     parse_implicit
	     parse_common
	     parse_rw
	     parse_if
	     parse_include
	     parse_io_elt
	     parse_iolst
	     parse_external
	     is_simple_elt
	     is_impl_do
	     impl_do_control
	     impl_elts
	     io_elt_to_string
	     iol_to_tl
	     impl_do_string
	     io_elt_map
	     io_vars_of
	     base_vars_of
	     typestr
	     iestr
	     insert_index);
my(%single_type) = (logical => 1,
		    complex => 1,);
my(%pr_type) = (    real    => 1,
		    integer => 1,);
my(%rw) = (read    => 1,
	   write   => 1,);
sub parse_type_noun {
    return ( shift, @_) if ($single_type{$_[0]});
    return ( join(' ',(shift,shift)),@_) if ($_[0] eq 'double');
#
# only handle *4 or *8 for precision of real
#   complex*16 = dbl complex?
#
    if ($pr_type{$_[0]}){
	return (shift, @_) unless ($_[1] eq '*');
	my($t) = shift;
	shift;
	my ($p) = shift;
	return ($t, @_) unless ($p eq '8');
	return ('double precision', @_);
    }
#
# might have to parse this different
#
    if ($_[0] eq 'character') {
	my(@t) = shift;
	if ($_[0] eq '*') {
	    push @t,shift;
	    if ($_[0] eq '('){
		(my($p),@_) = pt(@_);
		push @t,@$p;
	    }
	    else {
		push @t,shift;
	    }
	}
	else {     # default character length = 1
	    push @t,'*','1';
	}
	return ( [ @t ], @_);
    }
    return ([],@_);
}
sub parse_unit {
    if ($_[0] eq 'subroutine'){
	my($u) = shift;
	my($n) = shift;
	my(@v) = ();
	if ($_[0] eq '('){
	    my($pt) = pt(@_);
	    @v = map {$_->[0]} tlcsv(@$pt[1 .. $#$pt-1]);
	}
	return @{[ $u,$n,[],@v ]};
    }
    if (grep {$_ eq 'function'} @_) {
	(my($t),@_) = parse_type_noun(@_);
	my($u) = shift;
	my($n) = shift;
	my(@v) = ();
	if ($_[0] eq '('){
	    my($pt) = pt(@_);
	    @v = map {$_->[0]} tlcsv(@$pt[1 .. $#$pt-1]);
	}
	return @{[ $u,$n,$t,@v]};
    }
    if ($_[0] eq 'program') {
	my($u) = shift;
	my($n) = shift;
	return @{[ $u,$n,[] ]};
    }
    if (($_[0] eq 'block') && ($_[1] eq 'data')){
	return @{['block',$_[2],[] ]};
    }
    if ($_[0] eq 'module'){
	my($u) = shift;
	my($n) = shift;
	return @{[ $u,$n,[],()]};
    }
    return ();
}
sub parse_type {
    (my($t),@_) = parse_type_noun(@_);
    return @{[ $t,tlcsv(@_)]} unless ((ref($t) eq 'ARRAY') && (! @$t));
    return ();
}
sub typestr {
    return join('',@{$_[0]}) if (ref($_[0]) eq 'ARRAY');
    return $_[0];
}
sub __vdt {
    return [ shift @{$_[0]}, [ ptl(@{$_[0]}) ] ];
}
sub parse_var_dims {
    map {__vdt($_)} @_;
}
sub iestr{
    return $_[0] unless (ref($_[0]) eq 'ARRAY');
    return join('-',@{$_[0]});
}
sub __impl_elt {
    return $_[0]->[0] unless ($_[0]->[1] eq '-');
    return [ $_[0]->[0], $_[0]->[2] ];
}
sub __impl_type{
    my($typ,@tl) = parse_type_noun(@_);

    return [ $typ, map {__impl_elt($_)} ptl(@tl) ];
}
sub parse_implicit{
    return map {__impl_type(@$_)} tlcsv(@_);
}
sub parse_external {
    return () unless ($_[0] eq 'external');
    shift;
    return @_;
}
#
# parse single common block name
#   does not handle common xxxx,yyy,zzz/oth/x,y//it
# note scanning weakness: / / is 2 tokens, // is 1
# since it corresponds to concatenation
#
sub parse_common {
    return () unless ($_[0] eq 'common');
    shift;
    my($cb) = ' ';
    if ($_[0] eq '/'){
	shift;
	if ($_[0] eq '/'){
	    shift;
	}
	else {
	    $cb = shift;
	    shift;
	}
    }
    shift if ($_[0] eq '//');

    return @{[$cb,tlcsv(@_)]};
}
#
# parse a read or write statement given a token list
#  (no leading line #)
#  assume read|write FMT,iolist has FMT as a non-paren expr
# returns (read|write token,[ ctl list elt],@iolistptrs)
sub parse_rw {
    return () unless ($rw{$_[0]});
    push my(@rv),shift;
    if ($_[0] eq '('){
	(my($p),@_) = pt(@_);
	push @rv,$p;
    }
    else {
	push @rv,shift;
	shift; # drop next ','
    }
    push @rv,tlcsv(@_);
    return @rv;
}
sub parse_if {
    return () unless ($_[0] eq 'if');
    shift;
    (my($test),@_) = pt(@_);
    return @{[$test,[ @_ ]]};
}
sub parse_include {
    return () unless (shift eq 'include');
    return my($inc) = ($_[0] =~ /^['"](.+)['"]$/);
}
sub implied_do {
    my($idx) = grep {$_[$_]->[1] eq '='} (0 .. $#_);
    my($var,$lo) = ($_[$idx]->[0],[ @{$_[$idx]}[2 .. $#{$_[$idx]}]]);
    my($hi) = $_[$idx+1];
    my($incr) = $_[$idx+2] || [];

    return [ [ $var,$lo,$hi,$incr ],
	     map {parse_io_elt($_)} @_[0 .. $idx-1] ];
}
sub impl_do_control {
    return ($_[0]->[0]->[0],
	    map {join('',@$_)} @{$_[0]->[0]}[1 .. $#{$_[0]->[0]}]);
}
sub impl_elts {
    my(@elts) = @{$_[0]};
    shift @elts;
    return @elts;
}
sub parse_io_elt {
    return $_[0] unless ($_[0]->[0] eq '(');
    my(@ep) = ptl(@{$_[0]});
    return $_[0] unless (@ep > 1);
    return implied_do(@ep);
}
sub parse_iolst {
    return map {parse_io_elt($_)} @_;
}
sub is_simple_elt {
    return $_[0] unless (ref($_[0]->[0]));
    return ();
}
# too simplistic for general progs, but works for many
#  picks 1st word token out token stream
#
sub simple_io_vars {
    return (grep {/\w+/} @{$_[0]})[0];
}
sub simple_base_vars {
    return ($_[0]->[0]) if ((@{$_[0]}+0 == 1) &&
			    $_[0]->[0] =~ /\w+/);
    return ();
}
sub _io_helper {
    my($routine) = shift;
    return &$routine($_[0]) if (is_simple_elt($_[0]));
    return map {_io_helper($routine,$_)} impl_elts($_[0]);
}
sub io_vars_of {
    unshift @_,\&simple_io_vars;
    goto &_io_helper;
}
sub _io_elt_map_helper {
    my($routine) = shift;
    my($aux_args) = shift;
    return &$routine($_[0],$aux_args) if (is_simple_elt($_[0]));
    return 
	[ $_[0]->[0],
	 (map {_io_elt_map_helper($routine,$aux_args,$_)} impl_elts($_[0])) ];
}

sub io_elt_map {
    (my($r,$a),@_) = @_;
    return map {_io_elt_map_helper($r,$a,$_)} @_;
}
sub _ioe_to_tl {
    return @{$_[0]} if (is_simple_elt($_[0]));
    my($ctl,@e) = @{$_[0]};
    my($v,$lo,$hi,$incr) = @$ctl;
    my(@ctl) = ($v,'=',@$lo,',',@$hi);
    push @ctl,',',@$incr if (@$incr);
    return ( '(' ,
	     iol_to_tl(@e),
	     ',',
	     @ctl,
	     ')' );
}
sub iol_to_tl {
    my(@res) = ();
    while (@_) {
	push @res,_ioe_to_tl(shift);
	push @res,',' if (@_);
    }
    return @res;
}
sub impl_do_string {
    my($infp) = shift;
    my($var,$lo,$hi,$incr) = @$infp;
    return '(' .
	join(',',map {io_elt_to_string($_)} @_) .
	    ",$var=" .
		join(',',map {join('',@$_) || ()} ($lo,$hi,$incr)) .
	    ')';
}
sub io_elt_to_string {
    return join('',@{$_[0]}) if (is_simple_elt($_[0]));
    return impl_do_string(@{$_[0]});
}
# base means no subscript
#
sub base_vars_of {
    unshift @_,\&simple_base_vars;
    goto &_io_helper;
}
sub insert_index {
    my($idx) = shift;
    return ('(',$idx,')') unless (@_);
    return ($_[0],$idx,',',@_[1 .. $#_]);
}
#
# for a given io_element that is either a 
#  variable, a variable with subscripts, or
#  an implicit loop on a variable,
#  generate fortran code that loops over all scalars
#   of the element.
#  eg: v          	   =>   $tag(v)           for v scalar
#      v(i,j)     	   =>   $tag(v(i,j))      for v(i,j) scalar
#      v          	   =>   do ii = 1,n       for v array of (n,m)
#                 	        do jj = 1,m     
#                 	           $tag(v(ii,jj))
#                 	        enddo           
#                 	        enddo                                      
#
#      (v(i,j),i=1,3)     =>   do ii = 1,n        for v(i,j) scalar     
#			       do jj = 1,m        implicit loop on i
#			          $tag(v(ii,jj))  j presumably fixed
#			       enddo           
#			       enddo           
#
sub tag_io_elt {
    my($tag,$s,$elt) = @_;
}

1;

