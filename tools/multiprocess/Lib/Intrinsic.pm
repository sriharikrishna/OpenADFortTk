package Intrinsic;

@table = qw (
	     sqrt
	     exp
	     sin
	     cos
	     tan
	     tanh
	     atan
	     atan2
	     mod
	     abs
	     sign
	     int
	     nint
	     float
	     open
	     read
	     write
	     close
         );

%table = map { $_=> 1 } @table;


1;
