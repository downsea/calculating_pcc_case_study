#perl -w
use strict;
use warnings;

my @files=glob("*.cor");

foreach my $file(@files){
    print "$file\n";
    my ($first)=split(/\./,$file);
    open (IN,"$file");
    open (OUT,">$first.pcc");
    my $title=<IN>;
    chomp($title);
    $title=~s/\r//;
    my @titles=split(/\s/,$title);
    for(my $i=0;$i<@titles;$i++){
        $titles[$i]=~s/\"//g;
    }
    while(<IN>){
        chomp;
        my ($temp)=split(/\r/,$_);
        my ($genea,@value)=split(/\s/,$temp);
        $genea=~s/\"//g;
        for(my $j=0;$j<@titles;$j++){
            if($genea lt $titles[$j]){
                print OUT "$genea\t$titles[$j]\t$value[$j]\n";
            }
        }
    }
    close(IN);
    close(OUT);
}

