#
# Roll-your-own Fortran Tokenizer
#
# given a fortran line (w continuation already joined)
#  return a list of tokens. 
# ignore the "whitespace" problem f the moment
#   i d = 2 5   *is the same as*  id=25 in real fortran
#   That is not the case for this tokenizer
#

package FTList;
use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(ftlist nlftlist);
@EXPORT_OK = qw($comment $q_str $bl $qq_str
		$word $int $conc $symb $dot
		$flonum $realRE $dblRE);
$EXPORT_TAGS{REs} = [qw($comment $q_str $bl $qq_str
			$word $int $conc $symb $dot
			$flonum)];
$EXPORT_TAGS{SKIP} = [qw($bl $comment)];
$EXPORT_TAGS{FPNUM} = [qw($flonum $dot)];
$EXPORT_TAGS{NUMRE} = [qw($realRE $dblRE)];

# various re's

$_RETAIN_CASE = 0;

$comment = qr/^[^\d\s]/; # note: extended from f77 std

$bl = qr/^\s*(?:!.*)?$/;

$q_str = qr/'             # single quote opening
            (?:           # body of quote is collection of chars
              [^'\\] |    #  a NON special character OR
              ''     |    #  specifically a repeated quote OR
              \\.    |    #  a backslashed anything (including quote)
             )*           # zero or more occurences
            '/x;          # followed by a trailing quote

# analogous to single quoted strings
#  non std fortran, but account for it.

$qq_str = qr/"            # double quote opening
            (?:           # body of quote is collection of chars
              [^"\\] |    #  a NON special character OR
              ''     |    #  specifically a repeated quote OR
              \\.    |    #  a backslashed anything (including quote)
             )*           # zero or more occurences
            "/x;          # followed by a trailing dbl quote

$word = qr/[a-z_\$][\w\$]*/i; # fortran wd starts w letter++

$int = qr/\d+/; # no sign, work out sign later if need be
$ddot = qr/::/; # :: token in F90
$conc = qr@//@;
$symb = qr@[-+*/()=,;%:]@;
$dot = qr/\.          # fortran "dotted" key words
          (?:
             eq         |
             ne         |
             [gl][te]   |
             and        |
             or         |
             not        |
             true       |
             false
          )
          \./ix;
$floexp = qr/
              [de]   # exponent marker
              [-+]?  # optional sign
              \d+    # exponent
            /ix;

$flonum = qr/      # [-+]? # optional sign, dropped, let be symb token
            (?:   # EITHER
             (?:
               \d+       # some digits 
               (?!$dot)  # NOT followed by a dot kw, but are followed by
               (?:       # EITHER
             	 (?:   
             	    \.              # decimal point
             	    \d*             # 0 or more digits after decimal
             	    (?:$floexp)?    # optional exp
             	 ) |     # OR
             	 $floexp            # definite exp
               )
              ) | # OR
              (?:   # no leading digits
            	\.              # decimal point
                \d+             # some digits after decimal
                (?:$floexp)?    # optional exp
               )
              )
            /ix;

$realExp = qr/
              e      # exponent marker
              [-+]?  # optional sign
              \d+    # exponent
            /ix;

$dblExp = qr/
              d      # exponent marker
              [-+]?  # optional sign
              \d+    # exponent
            /ix;
$realRE = qr/     # [-+]? # optional sign, dropped, let be symb token
            (?:   # EITHER
             (?:
               \d+       # some digits 
               (?!$dot)  # NOT followed by a dot kw, but are followed by
               (?:       # EITHER
             	 (?:   
             	    \.              # decimal point
             	    \d*             # 0 or more digits after decimal
             	    (?:$realExp)?   # optional exp
             	 ) |     # OR
             	 $realExp           # definite exp
               )
              ) | # OR
              (?:   # no leading digits
            	\.              # decimal point
                \d+             # some digits after decimal
                (?:$realExp)?   # optional exp
               )
              )
            /ix;
$dblRE =  qr/     # [-+]? # optional sign, dropped, let be symb token
            (?:   # EITHER
             (?:
               \d+       # some digits 
               (?!$dot)  # NOT followed by a dot kw, but are followed by
               (?:       # EITHER
             	 (?:   
             	    \.              # decimal point
             	    \d*             # 0 or more digits after decimal
             	    $dblExp         # double exp
             	 ) |                # OR
             	 $dblExp            # just a double exp
               )
              ) | # OR
              (?:   # no leading digits
            	\.              # decimal point
                \d+             # some digits after decimal
                $dblExp         # double exp
               )
              )
            /ix;

#
# order of choices important
#  $conc before $symb so that '//' found before '/'
#  $dot before $flonum so that 1.le.2 finds 1, then .le. then 2
#  $flonum before int, so that 543.11 is 1 token, not 3(543,.,11)
$fttok = qr/$word   |
            $conc   |
            $ddot   |
            $symb   |
            $dot    | 
            $q_str  |
            $qq_str |
            $flonum |
            $int
           /x;

sub ftlist {
    local($_) = shift;
    my(@list) = /($fttok)/g;
    my($ln) = ($list[0] =~ /^\d+$/) ? shift @list : '';

    return map {/^['"]/? $_ : lc $_}($ln,@list) unless ($_RETAIN_CASE);
    return ($ln,@list);
}
sub nlftlist {
    my($dc,@tl) = ftlist ($_[0]);
    return @tl;
}

#
# notes on pretty join
#   spaces ok, except for ( and ,
# want no spaces for common block name
#   common /a/ x,y not common / a / x,y
# want no spaces on implicit ranges:
#   implicit (x-z) NOT implicit (x - z)
# want space for if test, but not for array or fn invoke
#    if (...) not if(...)
#

1;
