for (<*.rh>){
    my $n = $_;
    s/\.rh$//;
    rename $n,$_;
}
for (<*.urh>){
    my $n = $_;
    s/\.urh$//;
    rename $n,$_;
}
