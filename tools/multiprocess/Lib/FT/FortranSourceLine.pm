package FortranSourceLine;
use FTscan;
use Exporter;

@ISA = qw(Exporter);
@EXPORT = qw(flow);

$continuation = qr/^\s{5}\S/;
$comment = qr/^[^\d\s]/;
$blank = qr/^ \s* $/x;

sub new
{
    my($class,$line,$rawline,$linenum) = @_;
    my($obj) = {_line =>$line, _rawline => $rawline, _linenum => $linenum};
    $obj->{_scan} = FTscan->new($line);
    bless $obj,$class;
    commentq($obj);

    return $obj;
}
#
# given a wide variety of inputs, return a FortranSourceLine
# object
#
sub gen {
    return $_[0] if (ref($_[0]) eq "FortranSourceLine");
    my($obj) = {_line => '', 
		_rawline => '',
		_linenum => 0,
		};
    bless $obj, 'FortranSourceLine';
    if (ref($_[0]) eq "FTscan"){
	$obj->{_scan} = $_[0];
	adjust2scan($obj);
    } else {   # scalar case
	$obj->{_line} = $_[0];
	adjust2text($obj);
    }
    return $obj;
}
sub putprop {
    $_[0]->{$_[1]} = $_[2];
    return $_[0];
}
sub getprop {
    return $_[0]->{$_[1]};
}
sub clearprop {
    delete $_[0]->{$_[1]};
    return $_[0];
}
sub same_level {
    return gen($_[1])->set_indent($_[0]->indent());
}
sub same_leading {
    return gen($_[1])->set_leading($_[0]->leading())
}
sub plus_indent {
    $_[0]->{_scan}->plus_indent($_[1]);
    return $_[0]->adjust2scan();
}
sub concatd {
    my($s) = shift;
    $s->{_scan}->concatd(@_);
    return $s->adjust2scan();
}
#
# Note: This does NOT handle embedded comments
#
sub new_from_lines
{
    local($/);
    $/ = "\n";
    my($class,@lines) = @_;
    my($rawline,@rawline,@fslines,$line,$linenum) = ();

    while (@lines)
    {
        $line = shift @lines;
	chomp($line);
	@rawline = ($line);

	unless ($line =~ /$comment/io)
	{
	    $line = substr($line,0,72);
	    while ($lines[0] =~ /$continuation/)
	    {
	        my($cont) = shift @lines;
	        chomp($cont);
		push @rawline,$cont;
		$cont = substr($cont,6,66);
		$line .= $cont;
	    }
	}
	$line .= "\n";
	$rawline = join("\n",@rawline) . "\n";
	push @fslines,
              FortranSourceLine->new($line,$rawline,$linenum++);
    }
    return @fslines;
}

sub line
{
    my($self) = @_;

    return $self->{_line};
}

sub rawline
{
    my($self) = @_;

    return $self->{_rawline};
}

sub rawline_list
{
    local($/);
    $/ = "\n";
    my($self) = @_;
    my($tmp) = $self->rawline();
    
    chomp($tmp);

    return map {$_ . "\n"} split("\n",$tmp);
}

sub linenum
{
    my($self) = @_;

    return $self->{_linenum};
}
sub setlinenum
{
    my($self,$linenum) = @_;

    $self->{_linenum} = $linenum;
}
sub setraw
{
    my($self,$line) = @_;

    $self->{_rawline} = $line;
}
sub setline
{
    my($self,$line) = @_;

    $self->{_line} = $line;
}
sub scan {
    return $_[0]->{_scan};
}
sub flow
{
    local($/);
    $/ = "\n";
    my($unflowed) = @_;
    my($flowed, $tmp);

    return $unflowed if ($unflowed =~ /^[^\d\s]/);
    chomp($unflowed);
    $flowed = substr($unflowed,0,72);
    $unflowed = substr($unflowed,72);
    while(length($unflowed))
    {
        $tmp = substr($unflowed,0,66);
        $flowed .= "\n" . " " x 5 . "+" . $tmp;
	$unflowed = substr($unflowed,66);
    }
    $flowed .= "\n";

    return ($flowed);
}
sub adjust2scan {
    $_[0]->{_line} = $_[0]->{_scan}->lstring();
    $_[0]->{_rawline} = flow($_[0]->{_line});
    commentq($_[0]);
    return $_[0];
}
sub adjust2text {
    $_[0]->{_rawline} = flow($_[0]->{_line});
    $_[0]->{_scan} = FTscan->new($_[0]->{_line});
    commentq($_[0]);
    return $_[0];
}
sub commentq {
    $_[0]->{_comm} = ($_[0]->{_line} =~ /$comment | $blank /xo);
}
sub is_comment {
    return $_[0]->{_comm};
}
sub set_indent {
    $_[0]->{_scan}->set_indent($_[1]);
    return $_[0]->adjust2scan();
}
sub indent {
    return $_[0]->{_scan}->indent();
}
sub ln {
    return $_[0]->{_scan}->ln();
}
sub leading {
    return $_[0]->{_scan}->leading();
}
sub tl {
    return $_[0]->{_scan}->tl();
}
sub set_ln {
    $_[0]->{_scan}->set_ln($_[1]);
    return adjust2scan($_[0]);
}
sub set_leading {
    $_[0]->{_scan}->set_leading($_[1]);
    return adjust2scan($_[0]);
}
sub set_tl {
    $_[0]->{_scan}->set_tl(@_[1 .. $#_]);
    return adjust2scan($_[0]);
}
sub match {
    return $_[0]->{_scan}->match($_[1]);
}
sub gmatch {
    return $_[0]->{_scan}->gmatch($_[1]);
}
sub lmatch {
    my($self) = shift @_;
    return $self->{_scan}->lmatch(@_);
}
sub subst {
    my($rv) = $_[0]->{_scan}->subst($_[1]);
    adjust2scan($_[0]);
    return $rv;
}
sub smap {
    return $_[0]->{_scan}->map($_[1]);
}
sub mterm {
    return $_[0]->{_scan}->mterm($_[1]);
}
sub gmterm {
    return $_[0]->{_scan}->gmterm($_[1]);
}
sub rterm {
    $_[0]->{_scan} = $_[0]->{_scan}->rterm($_[1],$_[2]);
    adjust2scan($_[0]);
    return $_[0];
}
sub grterm {
    $_[0]->{_scan} = $_[0]->{_scan}->grterm($_[1],$_[2]);
    adjust2scan($_[0]);
    return $_[0];
}

sub ignore {
    my($l) = $_[0]->{_line};
    my($postf) = $_[1];
    my($leading) = ($l =~ /^(\s+)/);

    chomp($l);
    $l =~ s/\'/\'\'/og;
    $l =~ s/^\s+//;
    $l = "${leading}call ignore$postf('$l')\n";
    return gen($l);
}

sub comment {
    my($postf) = $_[1];
    my($l) = $_[0]->{_rawline};

    my(@raw) = ($l =~ /^(.*\n)/omg);
    return map {gen("c$postf $_")} @raw;
}

1;
