      subroutine t1(x,y)
      real x,y(5),z
      dimension z(20,10)

      call foo(x)

      call foo2(z(1,5),hh(y(1)))

      call foo(z(ii,jj))

      call foo(y(4))

      y = x + bar(y)
      y(2) = y(3) + baz(x)

 10   call foo3(hh(y(2)),rrr(z(20,10)))

 25   call foo4(hh(x,mmm(z(2,2))),rrr(x),rrr(mmm(nnn(x,y(1)),3.2)))

      y(2) = y(idx(y,3.3)) * z(3,4)

      z(3,4) = hh(x,mm(z(2,2),rrr(x+3.,nnn(y(1)*5.))),3.2)*y(4)

      x = y(4) * 10.

      end
