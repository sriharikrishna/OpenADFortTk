use FindBin qw($RealBin);
use lib "$RealBin/Lib";
use lib "$RealBin/Lib/FT";

use FTcontext;
use Canonicalizer;

die "You must specify exactly 1 file on the command line\n"
    unless (@ARGV == 1);

print STDERR "canonicalizing $ARGV[0], creating $ARGV[0].bak\n";

rename($ARGV[0],"$ARGV[0].bak");

FTcontext->file("$ARGV[0].bak")->crewrite_sem($fn2sub)
    ->crewrite_sem(\&add_fun_repl_decls)
    ->write($ARGV[0]);
