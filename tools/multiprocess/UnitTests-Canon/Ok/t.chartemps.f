      subroutine ttt(aaa,bbb)

      real ad_ctmp_0
      real ad_ctmp_1
      character*10 aaa,bbb(4),ccc

      call s_f1(bbb(2),ad_ctmp_0)
      call s_f2(bbb(3)(2:14),ad_ctmp_1)
      aaa = ad_ctmp_0 // ad_ctmp_1

      ccc = aaa(3:5)

      end
