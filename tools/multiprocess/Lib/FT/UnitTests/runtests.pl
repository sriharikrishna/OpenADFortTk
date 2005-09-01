#! /bin/env perl
#
foreach (@ARGV) {
    print "-----running test $_----\n";
    system('perl',$_);
    print("-------------\n");
}
