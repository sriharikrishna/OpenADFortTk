package ADtemplate;

use Ffile;
use FTscan;
use FTpat;
use FTUnit;

sub new {
    my($class,$ff) = @_;

    bless {ff => $ff},$class;
}

sub instantiate {
    my($self,$src) = @_;

    _init();
    $src->map(\&readit);
    my($retn) = $self->{ff};
    $retn = $retn->rewrite(\&fill_in);
    return $retn;
}

sub get_template_info {
    my($src) = @_;

    _init();
    $src->map(\&readit);
    return getinfo();
}

#
# extract info from a source file:
#  routine name
#  routine formal parameters
#  declarations
#  labeled fragments (as many as there are)
#
{
    my($seek_decls,$seek_frag,$frag) = (0,0,-1);
    my(%info) = (name => '',
		 args => '',
		 decls => [],
		 frags => [],
		 );

    sub _init {
	($seek_decls,$seek_frag,$frag) = (0,0,-1);
	%info = (name => '',
		 args => '',
		 decls => [],
		 frags => [],
		 );
    }

    sub getinfo {
	return %info;
    }

    sub readit {
	my($line) = @_;

	if ($seek_decls) {
	    push @{$info{decls}},$line;
	    if ($line =~ /^c \s+ \*\*\*\* \s statements \s \*\*\*\*/ix){
		push @{$info{decls}},"C\n";
		$seek_decls = 0;
	    }
	    return ();
	}
	if ($seek_frag) {
	    if ($line =~ /^C \s+ \$OpenAD\$ \s+ END \s+ REPLACEMENT/ix) {
		$seek_frag = 0;
	    } else {
		push @{$info{frags}->[$frag]},$line;
	    }
	    return ();
	}
	if (($frag) = ($line =~ /^C \s+ \$OpenAD\$ \s+
			          BEGIN \s+ REPLACEMENT \s+ (\d+)/ix)){
	    $seek_frag = 1;
	    $frag--;
	    return ();
	}
	my($scn) = FTscan->new($line);
	if ( my($name,$args) = $scn->match(qr/^subroutine $TB (\w+) 
					   (?: $TB \( $TB (.*) $TB \))?/ix)){
	    $info{name} = $name->str();
	    $info{args} = $args->str();
	    $seek_decls = 1;
	    return ();
	}
	return ();
    }

   sub fill_in {
       my($line) = @_;

       if ($line =~
	     /^!\$TEMPLATE_DECLARARTION_PRAGMA\$ id="template"/){
	   return ();
       }
       if ($line =~ /^ \s+ subroutine \s+ template/ix) {
	   my($arglist) = $info{args} ? $info{args} . "," . "call_nr,version"
                        	      : "call_nr,version";
	   return(<<HEAD);
       subroutine $info{name}($arglist)
HEAD
       }
       if ($line =~ /^!\$TEMPLATE_PRAGMA_DECLARATIONS/) {
	   return (@{$info{decls}});
       }
       if (my($frag) = ($line =~ /^!\$PLACEHOLDER_PRAGMA\$ \s+
                                     id \s* = \s* (\d+)/ix)) {
	   $frag--;
	   return (@{$info{frags}->[$frag]});
       }
       if ($line =~ /^ \s+ end \s+ subroutine \s+ template/ix) {
	   $line =~ s/template/$info{name}/;
	   return ($line);
       }

       return ($UNCHANGED);
   }
}

1;
