#
# add the add last decl operation to an Ffile
#
#  assume 1 subprog / ffile
#  look for last actual declaration, add supplied decls
#   after last 1
#
#  note: should be aware of statement functions
#
use Symtab;
use FTList qw(:DEFAULT);
use FTparse;

package Ffile;

sub add_last_decls {
    my($self,@decls) = @_;

    my($s) = Symtab->new($self);
    my($c) = 0;
    my($st) = 0;
    $self->map_sem(\&_helper::find_last_decl,$s,\$c,\$st);
    $c--;
    $st = 0;
    return $self->rewrite_sem(\&_helper::rwlast,\$c,\$st,@decls);
}

package _helper;
use FTList;
use FTparse;
use Symtab;

%decl_kw = (
	    common       => 1,
	    data         => 1,
	    implicit     => 1,
	    include      => 1, # not sure about this. Ok f stags?
	    equivalence  => 1,
	    parameter    => 1,
	    save         => 1,
	    external     => 1,
	    intrinsic    => 1,
	    dimension    => 1,
	    );

sub find_last_decl {
    my($line,$s,$cp,$sp) = @_;

    goto &null if ($$sp);
    if (is_decl($line,$s)) {
	($$cp)++;
	return ();
    }
#
# after 1st NON decl line, change routine into
#  null action
#
    $$sp = 1;
}
sub is_decl {
    my(@tl) = ftlist(shift);
    my($s) = shift;

    return 0 if ($tl[0] =~ /\d+/);
    shift @tl;
    return 1 if (parse_type(@tl) || parse_unit(@tl) ||
		 $decl_kw{$tl[0]});
    return 1 if (is_stmt_fn($s,@tl));

    return 0;
}
sub is_stmt_fn {
    my($s) = shift;

    return 1 if ((! grep {@$_} $s->lookup_dim($_[0])) &&
		 ($_[1] eq '('));
    return 0;
}
sub rwlast {
    my($line,$cp,$sp,@decls) = @_;

    goto &unch if ($$sp);

    if ($$cp) {
	($$cp)--;
	return $Ffile::UNCHANGED;
    }
    $$sp = 1;
    return ($line,@decls);
    
}
sub unch {
    return $Ffile::UNCHANGED;
}
sub null {
    return ();
}
1;

