use FindBin qw($RealBin);
use lib "$RealBin/..";
use Test::More qw(no_plan);
use FTcontext;

setup();
my(@u)= $ctx->units();
is(@u+0,1,'context has 1 unit');
($f,$s) = ($u[0]->{_unit},$u[0]->{_symtab});
is($s->lookup_type_str('xx'),'character*70','type str for character var xx');
is($s->lookup_dims('xx')+0,1,'# dims xx is 1');
is($s->lookup_type_str('yy'),'character*70','type str for character var yy');
is($s->lookup_dims('yy')+0,0,'# dims yy is 0');
is($s->lookup_type_str('zz'),'character*1','default len 1 type str for character var zz');
is($s->lookup_dims('zz')+0,1,'# dims yy is 1');
foreach (qw(xx yy zz)){
    is($s->lookup_type_cls($_),'character',"type class for $_ is 'character'");
}
isnt($f2->to_string(),'','f2 read');
@u = $f2->units();
is(@u+0,2,'f2 has 2 units');

$st = ($f2->contexts())[1];
is($st->unit_name(),'eeparams_mod','2nd unit of f2 is eeparams_mod');
is($st->lookup_type_str('FORWARD_SIMULATION'),'integer',
   'type of FORWARD_SIMULATION is integer');
is($st->lookup_type_str('sNx'),'integer',
   'type of sNx from size_mod is integer');
is($st->lookup_dims('myByLo')+0,1,'myByLo is 1 dim vec');

isnt($f3->to_string(),'','f3 read');
@u = $f3->units();
is(@u+0,3,'f3 has 3 units');

$st = ($f3->contexts())[2];
is($st->lookup_dims('myByLo')+0,1,'dims myByLo (from module) = 1');
is($st->dims_str_of('myByLo'),
	'(max_no_threads)',
	'myByLo actual dimension expr');
is($st->unit_name(),'foo','3rd unit of f3 is foo');
is($st->lookup_type_str('FORWARD_SIMULATION'),'integer',
   'type of FORWARD_SIMULATION is integer');
is($st->lookup_type_str('sNx'),'integer',
   'type of sNx from size_mod is integer');
is($st->lookup_vclass('myByLo'),'module:eeparams_mod','myByLo from a module');
is($st->lookup_dims('FORWARD_SIMULATION')+0,0,
   'FORWARD_SIMULATION is a scalar');
is($st->lookup_type_str('x'),'double precision','type arg x is dbl');
is($st->lookup_dims('y')+0,0,'arg y is a scalar');

sub setup{

    $f2  = FTcontext->file('FortranFiles/tmod.f');
    $f3  = FTcontext->file('FortranFiles/tmods.3.f');

    $ctx = FTcontext->here(<<'F');
      SUBROUTINE ttt(XX,YY,ZZ)
      IMPLICIT NONE
      character*70 xx(10),yy
      character zz(13)
      END
F
}
sub teardown {
}
