#!perl

my @fc = qw(60 150 250 350 450 570 700 840 1000 1170 1370 1600 1850 2150 2500 2900 3400);
my @bw = qw(80 100 100 100 110 120 140 150 160 190 210 240 280 320 380 450 550);

while (@fc > 0)
{
	$fc = shift @fc;
	$bw = shift @bw;
	print "mkfilter -Bu -Bp -o 2 -a " . ($fc-$bw/2)/8000 . " " . ($fc+$bw/2)/8000 . " -l\n";
	# print qx("mkfilter -Bu -Bp -o 2 -a ");
}
# parse output of mkfilter
