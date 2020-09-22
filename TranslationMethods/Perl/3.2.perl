#!/usr/bin/perl

my $file = "3.2.txt";
open FILE, $file;

my $flag = 0;
my $flag2 = 0;

while (<>) {
    s/(\<[^\>]*\>)//g;
    if ($flag2 == 1) {
        if (/^\s*$/) {
            $flag = 1;
        } else {
            if ($flag == 1) {
                print "\n";
            }
            $flag = 0;
            s/^(\ +)(.*)/$2/;
            s/(\ )(\ +)/$1/g;
            s/(\ +)$//;
            print;
        }
    } else {
        if (/^\s*$/) {

        } else {
            $flag2 = 1;
            s/^(\ +)(.*)/$2/;
            s/(\ )(\ +)/$1/g;
            s/(\ +)$//;
            print;
        }
    }
}
