#!/usr/bin/perl

while(<>) {
    print if /.*\(([^\(\)]*\b\w+\b[^\(\)]*)\).*/;
}
