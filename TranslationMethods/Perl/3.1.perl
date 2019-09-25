#!/usr/bin/perl

my $file = "3.1.txt";
open FILE, $file;

my flag = 0;

while (<FILE>) { #my $line =
    if (flag == 0) {
        if (/$\s+^/) {

        } else {
            flag = 1;
            s/(\s)\g1*/$1/g;
            print;
        }
    } else {

    }
    print s/(\s)\g1*/$1/g;
    print;
}
