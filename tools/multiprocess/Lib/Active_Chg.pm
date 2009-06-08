use Ffile;

use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(active_chg);

sub active_chg {
    my($line) = @_;

    my($scn) = FTscan->new($line);
    if ( $scn->token_scan('active') ){
	return $scn->g_repl_token(['active'],['active1'])->lstring();
    }
    if ( $scn->token_scan('OAD_active') ){
	return $scn->g_repl_token(['OAD_active'],['OAD_active1'])
	           ->lstring();
    }
    return ($UNCHANGED);
}

