use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use Ffile;
use FTscan;
use FTpat;

use PPsetup;

setup();

is($ff->rewrite_sem(\&sax)->to_string(),$sax_pp,'saxpy pp ok');

teardown();

sub setup {
    $sax = <<'SAX';
      subroutine ttt

      BLENGTH(2)%v = 1.0D00
      BLENGTH(3)%v = BLENGTH(1)%v
      CALL sax_a_a(1.0D00,BLENGTH(1)%v,BLENGTH(3)%v)

      SymbolTable_0x81ed9a0_274%v = SymbolTable_0x81ed9a0_0%v
      SymbolTable_0x81ed9a0_276%v = SymbolTable_0x81ed9a0_1%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_274%v,SymbolTable_0x81ed9a0_275
     +%v,BHEIGHT(2)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_276%v,SymbolTable_0x81ed9a0_2
     +77%v,BHEIGHT(2)%v)
      end subroutine
SAX
    $sax_pp = <<'SAX_PP';
      subroutine ttt

      BLENGTH(2)%v = 1.0D00
      BLENGTH(3)%v = BLENGTH(1)%v
      CALL sax_a_a(1.0D00,BLENGTH(1),BLENGTH(3))

      SymbolTable_0x81ed9a0_274%v = SymbolTable_0x81ed9a0_0%v
      SymbolTable_0x81ed9a0_276%v = SymbolTable_0x81ed9a0_1%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_274%v,SymbolTable_0x81ed9a0_275
     +,BHEIGHT(2))
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_276%v,SymbolTable_0x81ed9a0_2
     +77,BHEIGHT(2))
      end subroutine
SAX_PP
    $ff = Ffile->new_from_heredoc($sax);
}

sub teardown {
}

sub sax {
    my($line) = @_;
    my($scn) = FTscan->new($line);
    if($scn->match(qr/sax(?:py)?_a_a $TB /x)){
	return ($scn->grterm(qr/sax(?:py)?_a_a/,\&fixsax)->lstring());
    }
    return($UNCHANGED);
}

sub fixsax {
    my($f,@args) = $_[0]->term();
    $f = $f->str();
    my(@newargs) = map {$_->subst('/% $TB v $//x');$_->str()} @args[1..$#args];
    unshift @newargs,$args[0]->str();
    return FTscan->new($f . '(' . join(',',@newargs) . ')');
}
