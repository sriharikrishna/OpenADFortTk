package ADtemplate;

use Ffile;
use FTscan;
use FTpat;
use FTUnit;

sub new {
    my($class,$ff) = @_;

    bless {ff => $ff},$class;
}

sub module {
    my($scan) = FTscan->new($_[0]);

    return $scan->match(qr/^ module $TB/ix);
}

sub is_module {
    my($in) = @_;
    my($ff) = $in->filter(\&module);
    
    return ($ff->lines()+0);
}
sub instantiate {
    my($self,$src) = @_;

# !! HACK !! to find out if unit is a module  :-] :-]
# (no rewrite of modules
#
    return $src if (is_module($src));
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
    my(%info) = (unitnm => '',
		 name => '',
		 args => '',
		 decls => [],
		 frags => [],
		 );

    sub _init {
	($seek_decls,$seek_frag,$frag) = (0,0,-1);
	%info = (unitnm => '',
		 name => '',
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
	if ( my($unitnm,$name,$args) = 
	       $scn->match(qr/^(program|subroutine) $TB (\w+)
			   (?: $TB \( $TB (.*) $TB \))?/ix)){
	    $info{unitnm} = $unitnm->str();
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
       if (my($t_args) = ($line =~ /^ \s+ subroutine \s+ template \s*
			          \( \s* ([^\)]*) \s* \)/ix)) {
	   
	   my($comma) = $info{args} =~ /\w+/ && $t_args =~ /\w+/ ? ',' : '';
	   my($arglist) = $info{args} . $comma . $t_args;
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
