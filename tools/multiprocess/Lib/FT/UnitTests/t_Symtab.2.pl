use FindBin qw($RealBin);
use lib "$RealBin/..";
use Test::More qw(no_plan);
use FTcontext;

my($ctx) = setup();
my(@u)= $ctx->units();
is(@u+0,1,'context has 1 unit');
($f,$s) = ($u[0]->{_unit},$u[0]->{_symtab});
is($s->lookup_type('a1'),'double precision','type a1 is real*8');
is($s->lookup_dims('a1')+0,1,'# dims a1 is 1');

sub setup{

    my($f) = FTcontext->here(<<'F');
      subroutine foo(x,yyy,zxz)

      implicit none

      integer l_a1
      parameter(l_a1=10)

      real*8 a1(l_a1),b(l_a1),c(l_a1+5,5+ix)
      data a1 /1. , 1. , 1., 1./
      data b /2. , 2. , 2., 2./
      data c / 3., 3. , 3. /

      a1(3) = x * yyy

      end
F

    return $f;

}
sub teardown {
}
