#! /usr/bin/perl -w

use strict;
use Data::Dumper;


if(@ARGV!=2){
	die "usage: perl pcc.pl <rawdata> <result>\n";
}

my ($fin, $fout)=@ARGV;
my $missing = 0;

open(IN, "$fin") or die "Cannot open file:[$fin]\n";

# first loop for assembling property of rawdata.
my @data;
my (%idMap,%grpMap);

while(<IN>){
	chomp;chomp;	
	s/^\s+//; s/\s+$//;
	my ($id,$grp,$value) = split(/\s+/);	
#	print "$id, $grp, $value\n";
	$idMap{$id} = 1;	
	$grpMap{$grp} = 1;	
}
close(IN);

my (@ids, @grps);
@ids = sort{$a cmp $b} keys(%idMap);
@grps = sort{$a cmp $b} keys(%grpMap);

for(my $i=0;$i<@ids;$i++){
	$idMap{$ids[$i]}=$i;
}
for(my $i=0;$i<@grps;$i++){
	$grpMap{$grps[$i]}=$i;
}

#print Dumper(\@grps);
#print "%grpMap\n\n";
print "Data Info obtained successfully.\n";
#die;

# second loop for creating ordered matrix.
my @mtx;
my $idCnt = scalar(keys(%idMap));
my $grpCnt = scalar(keys(%grpMap));

open(IN, "$fin") or die "Cannot open file:[$fin]\n";
while(<IN>){
	chomp;chomp;
	s/^\s+//; s/\s+$//;
        my ($id,$grp,$value) = split(/\s+/);

	my $idx = $idMap{$id}*$grpCnt+$grpMap{$grp};
	$mtx[$idx] = $value * 1;
	
#	print "$idMap{$id},$grpMap{$grp},$idx,$value\n" if(!defined($mtx[$idx]) || !$mtx[$idx]);
}
close(IN);

# handle missing data
for(my $i=0;$i<@mtx;$i++){
         $mtx[$i] = $missing if (!defined($mtx[$i]));
}
print "Data Matrix assembled successfully.\n";
#print Dumper(\@mtx);
#die;

my $tim = 0;
#my (@sumX,@sumXX,@sumXY);
my (@sumX,@sumXX);
my ($ftmpX, $ftmpXX, $ftmpXY) = ('tmpX.dat','tmpXX.dat','tmpXY.dat');
#open (OUTX, ">$ftmpX");
#open (OUTXX, ">$ftmpXX");
open (OUTXY, ">$ftmpXY");

for(my $i = 0; $i < $idCnt; $i++){
	for (my $k = 0; $k < $grpCnt; $k++){
		$sumX[$i] += $mtx[$i*$grpCnt+$k];
		$sumXX[$i] += $mtx[$i*$grpCnt+$k] * $mtx[$i*$grpCnt+$k];
	}
#	die "$ids[$i] sumX=$sumX[$i].\n" if(!$sumX[$i]);

	for(my $j = $i+1; $j < $idCnt; $j++){
		my $sumxy = 0;
		for (my $k = 0; $k < $grpCnt; $k++){
			#$sumXY[$i][$j] += $mtx[$i*$grpCnt+$k] * $mtx[$j*$grpCnt+$k];
			next	if(!$mtx[$i*$grpCnt+$k] || !$mtx[$j*$grpCnt+$k]);
			$sumxy += $mtx[$i*$grpCnt+$k] * $mtx[$j*$grpCnt+$k];
		}
		print OUTXY "$sumxy\n";
	}
	my $p = ($i+1)*100/$idCnt;
	$p = int($p);	
	if ($p > $tim){
		print "$p %\n";
		$tim = $p;
	}	
}
#close (OUTX);
#close (OUTXX);
close (OUTXY);

print "\nprinting... \n";

open(INXY, $ftmpXY);
open(OUT, ">$fout") or die "Cannot open file:[$fout]\n";
for(my $i = 0; $i < $idCnt; $i++){
	for(my $j = $i+1; $j < $idCnt; $j++){

		my $sumxy = <INXY>;	chomp($sumxy);
		my $pcc = -2;
	#	print "sumX:$sumX[$i], sumY:$sumX[$j], sumXX:$sumXX[$i], sumYY:$sumXX[$j], sumXY:$sumxy\n";
		if($sumX[$i] && $sumX[$j] && $sumxy){
			$pcc = ($sumxy - $sumX[$i] * $sumX[$j] / $grpCnt) 
				/ sqrt(($sumXX[$i]-$sumX[$i] * $sumX[$i] / $grpCnt) * ($sumXX[$j] - $sumX[$j] * $sumX[$j] / $grpCnt));
		}
#		print OUT "$ids[$i],$ids[$j],$pcc\n";
#		print OUT "$ids[$i]\t$ids[$j]\t$pcc\n";
		printf OUT "%s\t%s\t%6.4f\n", $ids[$i], $ids[$j], $pcc;
	}
}
close(OUT);
close(INXY);
print "\nFinished!\n";
