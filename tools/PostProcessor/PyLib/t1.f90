! -*- Mode: f90 -*-
!*********************************************************************
! $Id: Vector.F,v 1.10 2002/12/03 04:55:05 turner Exp $
! 
! Vector routines.
!
!*********************************************************************
module Vector_module
  use types_module
  implicit none
  private
  public :: &
       Ubik_Dot_Product, &
       Ubik_MaxVal, &
       Norm, &
       Ubik_Sum, &
       Dump, &
       Load, &
       Swap, &
       Spew
contains
  10  xxx = 35.0
