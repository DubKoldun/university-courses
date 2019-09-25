#!/usr/bin/perl

my $file = "3.1.txt";

open FILE, $file;

while (my $line = <FILE> !eq "") { #my $line =
     s/(\s)\g1*/$1/g;
    print;
}
