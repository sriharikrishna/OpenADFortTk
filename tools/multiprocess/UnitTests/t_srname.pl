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

$inl = ADinline->new(Ffile->new('srname.inl.f'));
$template = ADtemplate->new(Ffile->new('srname.template.f'));

$ff = Ffile->new('srname.src.f');

$ffi = $ff->rewrite_sem(\&xaifpp)->rewrite($inl->inline());

$ffit = fconcat( map {$template->instantiate($_)} FTUnit->new($ffi)->units() );

is($ffit->to_string(),Ffile->new('srname.ok.f')->to_string(),'srname');

teardown();

sub setup {
}
sub teardown {
}
