#!/usr/bin/perl

while(<>) {
    s/\b[a]+\b/argh/i;
    print;
}
