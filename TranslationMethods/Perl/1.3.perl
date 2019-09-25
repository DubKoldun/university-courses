#!/usr/bin/perl

while(<>) {
    print if /^.*(cat|Cat|cAt|caT|CAt|CaT|cAT|CAT).*$/;
}
