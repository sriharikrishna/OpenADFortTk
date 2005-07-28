      subroutine t1(x,y)
      real x,y(5),z
      real ad_ctmp_0
      real ad_ctmp_1
      real ad_ctmp_2
      real ad_ctmp_3
      real ad_ctmp_4
      real ad_ctmp_5
      real ad_ctmp_6
      real ad_ctmp_7
      integer ad_ctmp_8
      integer ad_ctmp_9
      integer ad_ctmp_10
      integer ad_ctmp_11
      real ad_ctmp_12
      integer ad_ctmp_13
      real ad_ctmp_14
      integer ad_ctmp_15
      dimension z(20,10)

      call foo(x)

      call s_hh(y(1),ad_ctmp_0)
      call foo2(z(1,5),ad_ctmp_0)

      call foo(z(ii,jj))

      call foo(y(4))

      call s_bar(y,ad_ctmp_1)
      y = x+ad_ctmp_1
      call s_baz(x,ad_ctmp_2)
      y(2) = y(3)+ad_ctmp_2

      call s_hh(y(2),ad_ctmp_3)
      call s_rrr(z(20,10),ad_ctmp_4)
 10   call foo3(ad_ctmp_3,ad_ctmp_4)

      call s_mmm(z(2,2),ad_ctmp_8)
      call s_hh(x,ad_ctmp_8,ad_ctmp_5)
      call s_rrr(x,ad_ctmp_6)
      call s_nnn(x,y(1),ad_ctmp_10)
      call s_mmm(ad_ctmp_10,3.2,ad_ctmp_9)
      call s_rrr(ad_ctmp_9,ad_ctmp_7)
 25   call foo4(ad_ctmp_5,ad_ctmp_6,ad_ctmp_7)

      call s_idx(y,3.3,ad_ctmp_11)
      y(2) = y(ad_ctmp_11)*z(3,4)

      call s_nnn(y(1)*5.,ad_ctmp_15)
      call s_rrr(x+3.,ad_ctmp_15,ad_ctmp_14)
      call s_mm(z(2,2),ad_ctmp_14,ad_ctmp_13)
      call s_hh(x,ad_ctmp_13,3.2,ad_ctmp_12)
      z(3,4) = ad_ctmp_12*y(4)

      x = y(4) * 10.

      end
