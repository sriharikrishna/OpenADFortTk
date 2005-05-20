      program t1

      use active_module
      
      type active
         double precision :: v
         double precision :: d
      end type active

      type(active) :: x1, x2, x3(30)

      x1%v = 12.2
      x3(1)%d = x3(5)%d - x2%v

      end program t1
