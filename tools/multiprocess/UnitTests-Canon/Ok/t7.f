      subroutine t(x)

      implicit double precision(a-h,o-z)
      double precision x
      dimension y(10),z(10,20)
      logical lll,lll2
      double precision ad_ctmp_0
      logical ad_ctmp_1
      logical ad_ctmp_2
      double precision ad_ctmp_3
      external lll
      
      call s_ff(z(1,1),x,ad_ctmp_0)
      y(1) = ad_ctmp_0*z(3,4)

      call s_lll(x,z(4,3),ad_ctmp_1)
      lll2 = ad_ctmp_1 .or. (x .lt. 3)

      call s_lll(x,z(2,2),ad_ctmp_2)
      if (ad_ctmp_2 .and. (x .ge. 2.7d0)) then

         call s_ff(z(2,2),ad_ctmp_3)
         y(3) = z(1,1)-ad_ctmp_3

      endif

      end
