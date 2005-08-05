use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use FTcontext;
use Canonicalizer;

setup();

is($f1->crewrite_sem($fn2sub)
      ->crewrite_sem(\&add_fun_repl_decls)->to_string(),
   $f1_ok->to_string(),
   'intrinsics and if stmts');

teardown();

sub setup {
    $f1 = FTcontext->file("$RealBin/Tfiles/t.gcm.1.f");
    $f1_ok = FTcontext->file("$RealBin/Ok/t.gcm.1.f");

}

sub teardown {
}
