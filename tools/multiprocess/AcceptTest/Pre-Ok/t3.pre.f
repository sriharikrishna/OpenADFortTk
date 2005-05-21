      program t1

        ! active needs to be a sequence type 

      use active1_module
      
      type active1
         double precision :: v
         double precision :: d
      end type active1

      type(active1) :: x1,x2,x3(30)

      x1%v = 12.2
      x3(1)%d = x3(5)%d - x2%v

      end program t1
