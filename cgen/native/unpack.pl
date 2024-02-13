#!/usr/bin/perl
open my $in, "<:raw", "../cgen.c" or die "$!";

my @code = <$in>;
close $in;
my $curFile = "";
my $start = 0;
my $hasInclude = 0;

sub chkFile {
    my $end = $_[0];
    return if $curFile eq "";
    my $file = "";
    while ($start <= $end && $code[$start] !~ /\*\//) {
        $file .= $code[$start++];
    }
    $file .= $code[$start++];
    $file .= "#include \"cgen.h\"\r\n\r\n" if ($hasInclude == 0);
    $file .= join("",@code[$start..$end]);
    if (open my $in, "<:raw", $curFile) {
        local $/;
        my $ofile = <$in>;
        close $in;
        return if ($file eq $ofile);
    }
    print "Updating $curFile\n";
    open my $out, ">:raw", $curFile or die "$!";
    print $out $file;
    close $out;
}


for (my $i = 0; $i <= $#code; $i++) {
    if ($code[$i] =~ /File.*? (\S+\.cx?)/) {
        my $newfile = $1;
        my $j = $i;
        1 while ($code[--$j] !~ /^\//);
        chkFile($j - 1);
        $start = $j;
        $curFile = $newfile;
        if ($curFile =~ /^sub_([\dA-Za-z]+)\.c/) {
            $curFile = sprintf "sub_%04X.c", hex($1);
        }
        $hasInclude = 0;
    } elsif ($code[$i] =~ /^#include "cgen.h"/) {
        $hasInclude = 1;
    }
}
chkFile($#code);
if ($^O eq "MSWin32") {
    system("COPY /y ..\\cgen.h .");
} else {
    system("cp -p ../cgen.h .");
}
