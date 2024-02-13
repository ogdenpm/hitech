my @pat = <STDIN>;
for $l (@pat) {
    if ($l =~ /:(....) \w+.*:\1/) {
        print $l;
    }
}
