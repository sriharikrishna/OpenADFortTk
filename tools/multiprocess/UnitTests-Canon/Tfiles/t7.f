      subroutine t(x)

      implicit double precision(a-h,o-z)
      double precision x
      dimension y(10),z(10,20)
      logical lll,lll2
      external lll
      
      y(1) = ff(z(1,1),x) * z(3,4)

      lll2 = lll(x,z(4,3)) .or. (x .lt. 3)

      if (lll(x,z(2,2)) .and. (x .ge. 2.7d0)) then

         y(3) = z(1,1) - ff(z(2,2))

      endif

      end
