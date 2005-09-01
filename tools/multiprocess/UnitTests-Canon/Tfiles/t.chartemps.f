      subroutine ttt(aaa,bbb)

      character*10 aaa,bbb(4),ccc

      aaa = f1(bbb(2)) // f2(bbb(3)(2:14))

      ccc = aaa(3:5)

      end
