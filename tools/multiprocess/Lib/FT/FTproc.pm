#
# FTproc packages routines for use with rewriters and mappers
# of Ffiles
#

package FTproc;

sub new {
    my($class) = shift; 
    return bless [ @_ ], $class;
}

1;
