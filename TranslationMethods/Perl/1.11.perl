#!/usr/bin/perl

while(<>) {
    print if /^(0|11|1001|1(01*0)*1)*$/;
}
