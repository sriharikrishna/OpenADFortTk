use FindBin qw($RealBin);
use lib "$RealBin/..";
use Test::More qw(no_plan);
use FTcontext;

my($ctx) = setup();
my(@u)= $ctx->units();
is(@u+0,1,'context has 1 unit');
($f,$s) = ($u[0]->{_unit},$u[0]->{_symtab});

is($s->unit_type(),'subroutine','unit is subr');
is($s->unit_name(),'foo','subr foo');
is(join('|',$s->unit_args()),'x|yyy|zxz','args x|yyy|zxz');
is($s->implicit_type('dejj'),'double complex','implicit z');
is($s->implicit_type('kkk'),'integer','implicit integer');

foreach (qw(kkxkf anoth qqqq aaa bbb iafi jafi kafi)){
    is($s->lookup_type($_),'double precision'," dbl for $_");
}
foreach (qw(kkykf aanoth afi)){
    is($s->lookup_type($_),'double complex'," dbl cplx for $_");
}
foreach (qw(zxz moo ngng plrb file afile)){
    is($s->lookup_type($_),'integer',"int for $_");
}
foreach (qw(hhh iii jjj)){
    is($s->lookup_type($_),'real',"real for $_");
}
is(ref($s->lookup_type('charv1')),'ARRAY','character variable');
is(ref($s->lookup_type('aaa')),'','non char variable');
my(@d) = $s->lookup_dims('AAA');
is(@d+0,0,'dim array 0');
is(join('|',map {join('',@$_)} $s->lookup_dim('AAA')),
   '','aaa scalar');
is($s->dims_str_of('AAA'),'','empty dims str for AAA');
is(join('|',map {join('',@$_)} $s->lookup_dim('hhh')),
   'szhx|szhy','2 var dim hhh');
is($s->dims_str_of('hhh'),'(szhx,szhy)','dim str of hhh');
is(join('|',map {join('',@$_)} $s->lookup_dim('Gloob')),
   'int(cos(flr*pi))','1 complicated dim gloob');
is($s->dims_str_of('gloob'),'(int(cos(flr*pi)))','dim str of gloob');
is(join('|',map {join('',@$_)} $s->lookup_dim('kkykf')),
   '*|4','* dim kkykf');
is(join('|',map {join('',@$_)} $s->lookup_dim('iafi')),
   '2|4','* dim included iafi');
is(join('|',map {join('',@$_)} $s->lookup_dim('lafi')),
   '22','dim include lafi');

is('|' . join('|',sort $s->common_blocks()) . '|',
   '| |cm|fileh|','both common blocks');

is(join('|',sort $s->vars_in_common_block(' ')),
   'hhh|iii|jjj','blank common vars');

is(join('|',sort $s->vars_in_common_block('cm')),
   'aaa|bbb|gloob','cm common vars');

is(join('|',sort $s->vars_in_common_block('fileh')),
   'afile|file','fileh common vars');

foreach (qw(anoth flerb kkxkf afi iafi jafi kafi)) {
    is($s->lookup_vclass($_),'local',"local var $_");
    is($s->raw_vclass_of($_),'local',"raw local vclass $_");
}
foreach (qw(hhh iii jjj)){
    is($s->lookup_vclass($_),'common: ',"blank common var $_");
    is($s->raw_vclass_of($_),'common',"raw vclass blank common var $_");
}
foreach (qw(x yyy zxz)) {
    is($s->lookup_vclass($_),'arg',"arg $_ is still arg");
    is($s->raw_vclass_of($_),'arg',"raw vclass arg $_ is still arg");
}
foreach (qw(aaa bbb gloob)){
    is($s->raw_vclass_of($_),'common',"raw vclass for $_ is common");
}
foreach (qw(x yyy zxz kkykf aaa bbb afi afile file iafi jafi kafi)) {
    ok($s->lookup_decl($_),"$_ has explicit type decl");
}
foreach (qw(gloob fff lllm lafi)) {
    ok(! $s->lookup_decl($_),"$_ has implicit type decl");
}

teardown();

sub setup{
    local(*FFF);

    open(FFF,">AFILE");
    print FFF <<'AFILE';
       include 'iAFILE'
       double complex afi(2,4)
AFILE
    close(FFF);

    open(FFF,">iAFILE");
    print FFF <<'IAFILE';
       real*8 iafi(2,4),jafi,kafi(6)
       dimension lafi(22)
IAFILE
    close(FFF);

    open(FFF,">file.h");
    print FFF <<'FILE_H';
       integer file(1),afile
       common /fileh/ file,afile
FILE_H
    close(FFF);

    my($f) = FTcontext->here(<<'F');
      subroutine foo(x,yyy,zxz)

      implicit double complex (a-h,l),
     +                              double precision(q-s,w-z),
     +         integer(m-p)
      real x,yyy(*)
      integer zxz
      double precision kkxkf(44,2,6),   anoth(4, 1, 3)
      include 'AFILE'
      real * 4 hhh,iii,jjj
      real*8 aaa,bbb
      Double   CompleX kkykf  (*,4)
      include 'file.h'
      dimension zxz(XXX*XSZ,2),gloob(INT(COS(FLR*PI)))
      common hhh(SZHX,SZHY),iii(SZI),jjj
      common /CM/ aaa,bbb(SZHX+SZI),gloob
      character*15 charv1
      character*(isome) charv2
      character*(*) charv_arg

      x = real(fff + kkxkf(21,1,4) + lllm)
      end
F

    return $f;

}
sub teardown {
    unlink('AFILE');
    unlink('file.h');
    unlink('iAFILE');
}
