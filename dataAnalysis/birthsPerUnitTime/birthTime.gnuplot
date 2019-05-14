# extract data from lineage server on my sql thus, for a given eveID
#
# select date_sub( death_time, interval floor( age * 60 ) second ) as birth_time, eve_life_id from lineageServer_lives where server_id=17 and eve_life_id = 3789121 order by birth_time INTO OUTFILE '/var/lib/mysql-files/birthTimes3.txt';

# figure out which eveIDs are worth looking at (wide, deep trees) with this:
#
# select count(*), eve_life_id  from lineageServer_lives group by eve_life_id order by count(*);


set timefmt '%Y-%m-%d %H:%M:%S'

binwidth = 1800

bin(x,width) = width*floor(x/width)

#set format x "%Y"

set xdata time
set format x "%d\n%H:%M"


plot "birthTimeData3.txt" using (bin(timecolumn(1),binwidth)):(1.0) smooth frequency with boxes fs solid 

pause -1