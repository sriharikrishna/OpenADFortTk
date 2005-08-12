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
   'elsif');

is($f2->crewrite_sem($fn2sub)
      ->crewrite_sem(\&add_fun_repl_decls)->to_string(),
   $f2_ok->to_string(),
   'character variables are not functions');

teardown();

sub setup {
    $f1 = FTcontext->file("$RealBin/Tfiles/t.elsif.f");
    $f1_ok = FTcontext->file("$RealBin/Ok/t.elsif.f");

    $f2 = FTcontext->file("$RealBin/Tfiles/t.char.f");
    $f2_ok = FTcontext->file("$RealBin/Ok/t.char.f");
}

sub teardown {
}
