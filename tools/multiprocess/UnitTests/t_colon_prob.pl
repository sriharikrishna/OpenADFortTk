use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use Ffile;
use FTscan;
use FTpat;
use FTUnit;

use ADxaif;
use ADinline;
use ADtemplate;

use PPsetup;

setup();

ADxaif::set_old();

$inl = ADinline->new(Ffile->new('colon_prob_inl.f'));

$ff = Ffile->new('colon_prob.f');

$ffi = $ff->rewrite_sem(\&xaifpp)->rewrite($inl->inline());

is($ffi->to_string(),Ffile->new('colon_prob_ok.f')->to_string(),
   'colon problem');

teardown();

sub setup {
}

sub teardown {
}
