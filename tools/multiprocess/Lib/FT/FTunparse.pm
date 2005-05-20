package FTunparse;
use Exporter;
@ISA = qw(Exporter);
@EXPORT = (simple_join);
use FTTerm;

my($kw,$pt,$exp);

sub simple_join {
    $kw = shift;

    return "$kw " . join('',@_) if ($_[0] =~ /\w+/);
    if ($_[0] eq '(') {
	($pt,@_) = pt(@_);
	return join('',($kw,@$pt) . ' = ' . join('',@_[1 .. $#_]))
	    if ($_[0] eq '=');
	return "$kw " . join('',@$pt) . ' ' . join('',@_);
    }
    if ($_[0] eq '*') {
	shift;
	if ($_[0] eq '(') {
	    ($pt,@_) = pt(@_);
	    return "$kw*" . join('',@$pt) . ' ' . join('',@_);
	}
	$exp = shift;
	return "$kw*$exp " . join('',@_);
    }
    return join('',@_);
}
1;
