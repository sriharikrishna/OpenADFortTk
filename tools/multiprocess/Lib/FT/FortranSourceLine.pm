package FortranSourceLine;
use Exporter;

@ISA = qw(Exporter);
@EXPORT = qw(flow);

$continuation = qr/^\s{5}\S/;
$comment = qr/^[^\d\s]/;

sub new
{
    my($class,$line,$rawline,$linenum) = @_;
    my($obj) = {_line =>$line, _rawline => $rawline, _linenum => $linenum};

    bless $obj,$class;
}

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
sub flow
{
    local($/);
    $/ = "\n";
    my($unflowed) = @_;
    my($flowed, $tmp);

    return $unflowed if ($unflowed =~ /^[Cc!]/);
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

1;
