      subroutine t1(x,y)
      real x,y(5)

      call foo(x)

      y = x + bar(y)
      y(2) = y(3) + baz(x)

      x = y(4) * 10.

      end
