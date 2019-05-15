# run in a lifelog folder

for f in *day.txt;
do
    date=`echo "$f" | sed -e "s/_[A-Za-z]*day.txt//"`

    deaths=`grep "D" $f | wc -l`

    sids=`grep "age=0.0\|age=0.1\|age=0.2" $f | wc -l`

    births=`grep "B" $f | wc -l`

    eves=`grep "noParent" $f | wc -l`

    
    
    echo "$date $births $eves $deaths $sids"

    
done