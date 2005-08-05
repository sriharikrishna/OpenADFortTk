      subroutine t1(x,y)
      real x,y(5)

      call foo(x)


c This is the thing

      y = x + bar(y)

c This is the thing

      y(2) = y(3) + baz(x)

      x = y(4) * 10.

      end
