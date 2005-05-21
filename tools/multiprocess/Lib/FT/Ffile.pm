package Ffile;
use Exporter;
use FortranSourceLine;
use FTscan;
use FTproc;
use FTdecl;

@ISA = qw(Exporter);

$UNCHANGED = bless {},'UN';
$ADDLINES = bless {},'ADL';
$COMMENT_OUT = bless {},'CMO';

@EXPORT = qw($UNCHANGED $ADDLINES $COMMENT_OUT declare_after
              lines_from_heredoc fconcat grep_joined_lines);

$NO_TRIM = 0;

$type = qr/logical |
           real (?: \s* \* \s*\d )?   |
           complex (?: \s* \* \s*\d )? |
           double\s*precision |
           double\s*complex |
           integer |
           character (?: \s* \* \s* \d+)?/xi;
$continuation = qr/^\s{5}\S/;
$comment = qr/(?:^[^\d\s]) | (?:^ \s+ !)/ix;
$blank   = qr/^\s*$/;
$decl    = qr/^[\d\s]+(?:
              common  |
	      logical |
	      data    |
	      implicit|
	      equivalence |
	      parameter|
	      save |
	      external |
	      character |
	      intrinsic |
              include   | # hmmm
	      real |
	      integer |
	      dimension |
              namelist  |
              double\s*precision |
              complex |
              double\s*complex)/xi;

%canonical_type = ('real*4' => 'real',
                   'doubleprecision' => 'double precision',
                   'real*8' => 'double precision',
		   'doublecomplex' => 'double complex',
		   'complex*8' => 'double complex',);

$unit_spec = qr/subroutine |
                entry |
                function/xi;

#
# new means "new from file", since that is the most common
#
sub new
{
    my($class,$filename) = @_;
    local(*F);

    open(F,$filename);
    my(@lines) = <F>;
    close(F);

    $class->new_from_lines(@lines);
}
$VERBOSE = 0;
sub new_from_lines
{
    local($/);
    $/ = "\n";
    my($class,@lines) = @_;
    my($line,$linenum) = ();
    my($ffile);
    my($rawline,@rawline) = ();

    while (@lines)
    {
        $line = shift @lines;
	chomp($line);
	if ($line =~ /\r$/) {
	    print STDERR "Warning, carriage return encounterd!\n"
		if ($VERBOSE);
	    $line =~ s/\r+$//;
	}
	@rawline = ($line);
	$line = &kill_bang_comments($line);

#
# !! hack to fix comments between continuations
#   if find a continuation when expecting a statment,
#   go back an fix previous lines
#
	if ($line =~ /$continuation/)
	{
	    my($cont) = $line;
	    my($ll,$lll,$lp);

	    $lp = $ffile->{_lines};
	    for($ll = $linenum - 1; $l >= 0; $ll--)
	    {
	        $lll = $lp->[$ll]->line();
	        last unless (($lll =~ /$comment/) ||
			     ($lll =~ /$blank/));
	    }
	    $cont .= "\n";
	    my(@rawline) = map {$_->rawline()} @{$lp}[$ll .. $#{$lp}];
	    push @rawline,$cont;
	    my($rawline) = join('',@rawline);

	    chomp($lll);

	    $cont = &kill_bang_comments(substr($cont,6,66));
            $lll .= $cont;
	    $#{$lp} = $ll-1;
	    push @{$lp},FortranSourceLine->new($lll,$rawline,$ll);
	    $linenum = $ll+1;
	    next;
	}
	unless ($line =~ /$comment/io)
	{
	    $line = substr($line,0,72) unless $NO_TRIM;
	    while ($lines[0] =~ /$continuation/)
	    {
	        my($cont) = shift @lines;
	        chomp($cont);
		if ($cont =~ /\r$/) {
		    print STDERR "Warning, carriage return encounterd!\n"
			if ($VERBOSE);
		    $cont =~ s/\r+$//;
		}
		push @rawline,$cont;
		$cont = &kill_bang_comments(substr($cont,6,66));
		$line .= $cont;
	    }
	}
	$line .= "\n";
	$rawline = join("\n",@rawline) . "\n";
	push @{$ffile->{_lines}},
              FortranSourceLine->new($line,$rawline,$linenum++);
    }
    $ffile->{_nextline} = $linenum;

    bless $ffile,$class;

    return $ffile;
}

#
# Create a new ffile from a list of (possibly) joined lines
#   ie flow the list of lines in the here doc
#
sub new_flow_from_heredoc
{
    my($class,$heredoc) = @_;

    $heredoc =~ s/\n/\n\003/g;
    return $class->empty()->add_lines(
	  map {FortranSourceLine->new($_,flow($_),0)}
  	     split(/\003/,$heredoc));
}
sub new_from_heredoc
{
    my($class,$heredoc) = @_;

#    $heredoc =~ s/\n/\n\003/g;
#    return $class->new_from_lines(split(/\003/,$heredoc));
    return $class->new_from_lines($heredoc =~ /^(.*\n)/mg);
}
#
# kill from ! to end of line, unless ! inside a quoted string
#  NOTE: if string STARTS on a line, but does not finish,
#   ! comments still killed:
#
#     print *,'foo is ! this is killed  ==> kills from the ! to the end of line
#    +  the end of the quote'
#
#     print *,'foo is !the end',in      ==> retains the !(and rest of quote)
#    +var
#
# simple idea: use negative lookahead for ' or "
#   fails if quoted string appears in comment to be killed,
#    but might be good enough
#
sub kill_bang_comments
{
    local($_) = @_;

    return $_ if (/^\s*!/); # is a comment line

    s/!(?!.*[\'\"]).*$//;

    return $_; 
}
sub empty
{
    my($class) = @_;

    bless {_nextline => 0,_lines => []},$class
}
sub add_lines
{
    my($self,@lines) = @_;
    my($n) = $self->{_nextline};

    foreach(@lines){$_->setlinenum($n++)};
    push @{$self->{_lines}},@lines;

    $self->{_nextline} = $n;
    return $self;
}
sub add_text_lines {
    my($self,@lines) = @_;
    $self->add_lines(
		     map {FortranSourceLine->new($_,flow($_),0)}
		     @lines);
    return $self;
}
sub fconcat {
    my($f) = Ffile->empty();
    foreach (@_){
	$f->add_lines($_->lines());
    }
    return $f;
} 
sub lines
{
    my($self) = @_;

    return @{$self->{_lines}};
}
sub rewrite
{
    my($self,$proc,@rest) = @_;
    my($rw) = Ffile->empty();
    my(@lines) = $self->lines();
    my(@chglines) = ();
    my($tmp);

    foreach(@lines)
    {
        @chglines = &$proc($_->line(),@rest);
	if (ref($chglines[0]) eq 'CMO')
	{   $rw->add_lines(map {FortranSourceLine->new($_,flow($_),0)}
			       map {'c ' . $_} $_->rawline_list());
	    shift @chglines;
	}
	if (ref($chglines[0]) eq 'ADL')
	{
	    $rw->add_lines($_);
	    shift @chglines;
	}
	$tmp = $_;
        $rw->add_lines(
	      map {ref($_) eq 'UN' ? $tmp :
		   FortranSourceLine->new($_,flow($_),0)}
		       @chglines);
#        $rw->add_lines(
#           ref($chglines[0]) eq 'UN' ? ($_) :
#	      map {FortranSourceLine->new($_,flow($_),0)} @chglines);
    }
    return $rw;
}
sub rewrite_sem
{
    my($self,$proc,@rest) = @_;
    my($rw) = Ffile->empty();
    my(@lines) = $self->lines();
    my(@chglines) = ();

    foreach(@lines)
    {   my($l) = $_->line();
        if (($l =~ /$comment/) || ($l =~ /$blank/))
	{
	    $rw->add_lines($_);
	    next;
	}
        @chglines = &$proc($_->line(),@rest);
	if (ref($chglines[0]) eq 'CMO')
	{   $rw->add_lines(map {FortranSourceLine->new($_,flow($_),0)}
			       map {'c ' . $_} $_->rawline_list());
	    shift @chglines;
	}
	if (ref($chglines[0]) eq 'ADL')
	{
	    $rw->add_lines($_);
	    shift @chglines;
	}
	$tmp = $_;
        $rw->add_lines(
	      map {ref($_) eq 'UN' ? $tmp :
		   FortranSourceLine->new($_,flow($_),0)}
		       @chglines);
#        $rw->add_lines(
#           ref($chglines[0]) eq 'UN' ? ($_) :
#	      map {FortranSourceLine->new($_,flow($_),0)} @chglines);
    }
    return $rw;
}
#
# convenience function
#
sub mkSrcLine {
    return map {FortranSourceLine::gen($_)} @_;
}
#
# context rewrite -- use line object instead of 
# line text
#
sub crewrite {
    my($self,$proc,@rest) = @_;
    my($rw) = Ffile->empty();
    my(@lines) = $self->lines();

    if (ref($proc) eq 'FTproc') {
	$proc->[0]->(@rest);
    }
    my($p) = ref($proc) eq 'FTproc' ? $proc->[1] : $proc;
    $rw->add_lines(map {mkSrcLine(&$p($_,@rest))} @lines);
    if ((ref($proc) eq 'FTproc') && $proc->[2]){
	$proc->[2]->(@rest);
    }
    return $rw;
}
sub crewrite_sem {
    my($self,$proc,@rest) = @_;
    my($rw) = Ffile->empty();
    my(@lines) = $self->lines();

    if (ref($proc) eq 'FTproc') {
	$proc->[0]->(@rest);
    }
    my($p) = ref($proc) eq 'FTproc' ? $proc->[1] : $proc;
    $rw->add_lines(map {$_->is_comment() ? ($_) : mkSrcLine(&$p($_,@rest))}
		   @lines);
    if ((ref($proc) eq 'FTproc') && $proc->[2]){
	$proc->[2]->(@rest);
    }
    return $rw;
}
sub raw_rewrite
{
    my($self,$proc) = @_;
    my($rw) = Ffile->empty();
    my(@lines) = $self->lines();

    foreach(@lines)
    {
        my($rawline) = $_->rawline();
	$rawline =~ s/\n/\n\003/g;
        $rw->add_lines(
          FortranSourceLine->new_from_lines(
            &$proc(split("\003",$rawline))));
    }
    return $rw;
}
sub filter
{
    my($self,$proc,@args) = @_;
    my($filtered) = Ffile->empty();
    my(@lines) = $self->lines();

    $filtered->add_lines(grep {&$proc($_->line(),@args)} @lines);
    return $filtered;
}
*grep = \&filter;
sub map
{
    my($self,$proc,@args) = @_;

    return map {&$proc($_->line(),@args)} $self->lines();
}
sub map_sem
{
    my($self,$proc,@args) = @_;

    return map {my($l) = $_->line();
		(($l =~ /$comment/) || ($l =~ /$blank/))?
		    () : &$proc($l,@args)} $self->lines();
}
sub cmap {
    my($self,$proc,@args) = @_;

    return map {&$proc($_,@args)} $self->lines();
}
sub cmap_sem {
    my($self,$proc,@args) = @_;

    return map {my($l) = $_->line();
		(($l =~ /$comment/) || ($l =~ /$blank/))?
		    () : &$proc($_,@args)} $self->lines();
}
sub grep_joined_lines
{
    my($self,$proc,@args) = @_;

    return map {$_->line()}
     (grep {&$proc($_->line(),@args)} $self->lines());
}
sub grep_rawlines
{
    my($self,$proc,@args) = @_;

    my(@tmpres) = (grep {&$proc($_->line(),@args)} $self->lines());

    $nc = 0;
    return map {$_->rawline()} @tmpres;
#     (grep {&$proc($_->line(),@args)} $self->lines());
}
sub move_lines
{
    my($self,$indp,$loc) = @_;
    my(@ind) = @$indp;

    return $self unless (@ind);

    my($rv) = Ffile->empty();
    my(@srclines) = $self->lines();
    $rv->add_lines(@srclines[ map {my(%ii) = map {($_=>1)} @ind;
                                   ($ii{$_} ? () : $_,($_ == $loc) ? @ind : ())}
				   (0 .. $#srclines) ]);
    return $rv;
}
sub write
{
    my($self,$filename) = @_;
    local(*F);

    open(F,">$filename") || die("cannot write $filename from Ffile!!:$!");
    print F map {$_->rawline()} $self->lines();
    close(F);
}
sub declare_after
{
    my($line) = @_;

    local($_) = $line;

    return (! /$comment/) && (/$unit_spec/i);
}
sub comment_with
{
    my($tag,$line) = @_;

    $line =~ s/^\t/        /;
    return "c$tag" . $line;
}
#
# expects 2 function pointers (one to start the inclusion, one to end it)
#
#  returns a list of 3 $ff objects:
#    ($ffb,$ffi,$ffa)
#
# 
sub partition
{
    my($self,$f1,$f2,$a1,$a2) = @_;
    my($ffb,$ffi,$ffa) = map {Ffile->empty()} (0 .. 2);
    my(@lines) = $self->lines();
    my($state) = 0;

    foreach (@lines)
    {
        if ($state == 0)
	{
	    if (&$f1($_->line(),@$a1))
	    {
	        $ffi->add_lines($_);
		$state = 1;
		next;
	    }
	    $ffb->add_lines($_);
	    next;
	}
	if ($state == 1)
	{
	    $ffi->add_lines($_);
	    if (&$f2($_->line(),@$a2))
	    {
	        $state = 2;
	    }
	    next;
	}
	$ffa->add_lines($_);
    }
    return ($ffb,$ffi,$ffa);
}
sub print
{
    my($self) = @_;

    print map {$_->rawline()} $self->lines();
}
sub to_string
{
    my($self) = @_;

    return join('',map {$_->rawline()} $self->lines());
}
sub lines_from_heredoc {
    local($_) = shift;
    return /^(.*\n)/mg;
}
sub linearr {
    my($self) = @_;

    return (map {$_->line()} $self->lines());
}

1;
