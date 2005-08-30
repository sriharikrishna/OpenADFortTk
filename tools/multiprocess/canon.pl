use FindBin qw($RealBin);
use lib "$RealBin/Lib";
use lib "$RealBin/Lib/FT";

use FTcontext;
use Canonicalizer;

die "You must specify exactly 2 files (input, output) on the command line\n"
    unless (@ARGV == 2);

print STDERR "canonicalizing $ARGV[0], creating $ARGV[1]\n";

$ft = FTcontext->file("$ARGV[0]");

Canonicalizer::__set_verbose(1);

print STDERR "File $ARGV[0] read; \nCommencing canonicalization...\n";
$ft->crewrite_sem($fn2sub)
    ->crewrite_sem($add_fun_repl_decls)
    ->write($ARGV[1]);
