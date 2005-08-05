use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use FTcontext;
use Canonicalizer;

setup();

is($ff->crewrite_sem(\&Canonicalizer::mark_fn2sub)->to_string(),
   $ff_ok->to_string(),
   'detect function call');

is($f2->crewrite_sem(\&Canonicalizer::mark_fn2sub)->to_string(),
   $f2_ok->to_string(),
   'detect function call 2');

is($f3->crewrite_sem($fn2sub)->to_string(),
   $f3_ok->to_string(),
   'replace fn calls w tmp');

is($f4->crewrite_sem($fn2sub)->to_string(),
   $f4_ok->to_string(),
   'replace fn calls w tmp in multi defn file');

is($f5->crewrite_sem($fn2sub)
      ->crewrite_sem(\&add_fun_repl_decls)->to_string(),
   $f5_ok->to_string(),
   'replace fn calls w tmp, plus add tmp decls');

is($f6->crewrite_sem($fn2sub)
      ->crewrite_sem(\&add_fun_repl_decls)->to_string(),
   $f6_ok->to_string(),
   'replace fn calls w tmp, plus add tmp decls for multi defn file');

is($f7->crewrite_sem($fn2sub)
      ->crewrite_sem(\&add_fun_repl_decls)->to_string(),
   $f7_ok->to_string(),
   'double precision vars');

teardown();

sub setup {
    $ff = FTcontext->file("$RealBin/Tfiles/t1.f");
    $ff_ok = FTcontext->file("$RealBin/Ok/t1.f");

    $f2 = FTcontext->file("$RealBin/Tfiles/t2.f");
    $f2_ok = FTcontext->file("$RealBin/Ok/t2.f");

    $f3 = FTcontext->file("$RealBin/Tfiles/t3.f");
    $f3_ok = FTcontext->file("$RealBin/Ok/t3.f");

    $f4 = FTcontext->file("$RealBin/Tfiles/t4.f");
    $f4_ok = FTcontext->file("$RealBin/Ok/t4.f");

    $f5 = FTcontext->file("$RealBin/Tfiles/t5.f");
    $f5_ok = FTcontext->file("$RealBin/Ok/t5.f");

    $f6 = FTcontext->file("$RealBin/Tfiles/t6.f");
    $f6_ok = FTcontext->file("$RealBin/Ok/t6.f");

    $f7 = FTcontext->file("$RealBin/Tfiles/t7.f");
    $f7_ok = FTcontext->file("$RealBin/Ok/t7.f");
}

sub teardown {
}
