use FindBin qw($RealBin);
use lib "$RealBin";
use lib "$RealBin/..";
use lib "$RealBin/../Lib";
# use lib "/home/mfagan/Perllib/FT";
use Test::More qw(no_plan);

use FortranSourceLine;
use FTscan;
use FTpat;

setup();

is(FortranSourceLine::gen($l1)->
                      same_level(FTscan->new('if (adunit(16)) then'))
                      ->rawline(),
   "      if (adunit(16)) then\n",'same level');
					   
is(FortranSourceLine::gen($l1)->scan()->str(),
   'dimension x(ppp+5,15,10),yyy(3)',
   'line 1 scan');

is(@l2+0,8,'split the heredoc lines');
is($l2[1],"c Internal comment\n",'line 1 of heredoc ok');
is(@{[ FortranSourceLine->new_from_lines(@l3) ]}+0,1,'src lines ok');
is((FortranSourceLine->new_from_lines(@l3))[0]->scan()->str(),
   'double precision foo,bar(3,2,1),baz,v3(xxx*yyy,int(sin(foo))),' .
   'v4(xxx*yyy,int(sin(foo))),v5,v6,v7',
   'continued line l3 ok');
($f1) = FortranSourceLine->new_from_lines(@l3);
ok($f1->match(qr/^double $TB precision/ix),'match boolean l3 works');
($m1) = $f1->match(qr/^double $TB precision $TB (.+) $/ix);
is($m1->str(),
   'foo,bar(3,2,1),baz,v3(xxx*yyy,int(sin(foo))),' .
   'v4(xxx*yyy,int(sin(foo))),v5,v6,v7',
   'match extract works');
is(($m1->cbreak())[3]->str(),
   'v3(xxx*yyy,int(sin(foo)))',
   'cbreak of match l3 works');

is(FortranSourceLine::gen($f1),$f1,'gen of source line object');
is(FortranSourceLine::gen($l4)->rawline(),<<'L4','gen text line ok');
          v1 = 'This is an' // 'Extreeeeeemely long line that is continu
     +ed past its natural length'
L4

$ll1 = FortranSourceLine::gen(FTscan->new('cccc = 25.0 * exp(44)'));
$ll1->set_indent(' ' x 8);
ok(! $ll1->is_comment(),'generated scan not comment');
is($ll1->rawline(),<<'LL1','ll1 generated scan');
        cccc = 25.0*exp(44)
LL1

ok(! $ll1->getprop('foo'),'ll1 has no foo property');
$ll1->putprop('foo','bar');
is($ll1->getprop('foo'),'bar','ll1 has foo property = bar');
ok( ! $ll1->clearprop('foo')->getprop('foo'),'ll1 cleared foo property');

ok(FortranSourceLine::gen($l5)->is_comment(),'comment detected');
ok(! FortranSourceLine::gen($l4)->is_comment(),'non-comment detected');

teardown();

sub setup {
    $l1 = <<'L1';
      dimension x(PPP+5,15,10),yyy(3)
L1
    $l2 = <<'L2';
      double precision foo,bar(3,2,1),baz
c Internal comment
C  continued past here
c  even more stuff
     +,v3(xxx*yyy,int(sin(foo)))
     +,v4(xxx*yyy,int(sin(foo))),v5,
     +v6,
     +v7                  ! embedded shout comment
L2

    @l2 = ($l2 =~ /^(.*\n)/gmxo);
    $l3 = <<'L3';
      double precision foo,bar(3,2,1),baz
     +,v3(xxx*yyy,int(sin(foo)))
     +,v4(xxx*yyy,int(sin(foo))),v5,
     +v6,
     +v7
L3

    @l3 = ($l3 =~ /^(.*\n)/gmxo);
    $l4 = <<'L4';
          v1 = 'This is an' // 'Extreeeeeemely long line that is continued past its natural length'
L4

    $l5 = <<'C1';
c This is a comment line
C1

}

sub teardown {
}
