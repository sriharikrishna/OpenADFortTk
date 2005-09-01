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
   'character function replacements and temp vars');

is($f2->crewrite_sem($fn2sub)
      ->crewrite_sem(\&add_fun_repl_decls)->to_string(),
   $f2_ok->to_string(),
   'substrings of character vars');

is($f3->crewrite_sem($fn2sub)
      ->crewrite_sem(\&add_fun_repl_decls)->to_string(),
   $f3_ok->to_string(),
   'modules and substrings');

teardown();

sub setup {
    $f1 = FTcontext->file("$RealBin/Tfiles/t.chartemps.f");
    $f1_ok = FTcontext->file("$RealBin/Ok/t.chartemps.f");

    $f2 = FTcontext->file("$RealBin/Tfiles/t.char.f");
    $f2_ok = FTcontext->file("$RealBin/Ok/t.char.f");

    $f3 = FTcontext->file("$RealBin/Tfiles/t.mods.f");
    $f3_ok = FTcontext->file("$RealBin/Ok/t.mods.f");

}

sub teardown {
}
