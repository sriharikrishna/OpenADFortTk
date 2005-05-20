package FSrcLine;

=head1 FSrcLine Class

=pod

mline takes a multiline (ie with embedded newlines) and
joins it into a single long line

=cut

$c_re = qr/^[^\d\s]/;
$cont_re = qr/^\s{5}\S/;

sub mline {
    local($_) = $_[1];
    local($/) = "\n";
    my($v);
    $v->{_rawline} = $_;
    bless $v,$_[0];

    chomp;
    if (/\A[^\d\s]/o){   # comments are unchanged
	$v->{_tline} = $_;
	return $v;
    }
    foreach (split(/\n/)){
	if (/^[^\d\s]/o) {
	    push @{$v->{_comments}},$_;
	    next;
	}
	if (//)
    }
}

=pod
The join routine extracts the continuations + whitespace (including newlines),
joining a multiline true lines into 1 true line. The embedded comments
are also factored out of the joined line. The 72 char limit is
also factored in here.
=cut

sub join {
    local($_) = $_[0];
    local($/) = "\n";

    chomp;
    return $_ if (/\A[^\d\s]/o); # comments returned unchanged
    foreach (split(/n/)){
	if ()
    }
}

1;
