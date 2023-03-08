die "Usage: rbase.pl file newloc oldloc\n" if $#ARGV  != 2;
my $file = shift @ARGV;
my $delta = hex(shift @ARGV);
$delta -= hex(shift @ARGV);
my $intext = 1;
open my $fh, "<$file" or die $!;
while (<$fh>) {
    if (/psect\s+text/) {
        $intext = 1;
    } elsif (/psect *data/) {
        $intext = 0;
    }
    s/(....)'/sprintf("%04X'", hex($1)+$delta)/e if $intext;
    print $_;
}
close $fh;
