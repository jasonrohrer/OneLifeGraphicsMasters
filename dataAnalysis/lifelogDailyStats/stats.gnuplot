set timefmt '%Y_%m%B_%d'

binwidth = 1800

bin(x,width) = width*floor(x/width)

#set format x "%Y"

set xdata time
set format x "%Y\n%B\n%d"


plot "stats.txt" using 1:2 with lines, "stats.txt" using 1:3 with lines, "stats.txt" using 1:5 with lines, "stats.txt" using 1:(20000*$5/$4) with lines, "stats.txt" using 1:(40000*$3/$2) with lines

pause -1