      subroutine template(call_nr,version)
!          implicit none
!$TEMPLATE_PRAGMA_DECLARATIONS
          integer, intent(in) :: call_nr

          print *,'in subroutine __SRNAME__'
!$PLACEHOLDER_PRAGMA$ id=1
      end subroutine template
