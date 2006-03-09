        subroutine template()

!$TEMPLATE_PRAGMA_DECLARATIONS

!$PLACEHOLDER_PRAGMA$ id=1
        call show('id 1')
!$PLACEHOLDER_PRAGMA$ id=2
        call show('id 2')
!$PLACEHOLDER_PRAGMA$ id=3
        call show('id 3')
        end subroutine template

