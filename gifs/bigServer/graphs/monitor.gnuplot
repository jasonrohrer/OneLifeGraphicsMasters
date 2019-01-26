

set multiplot layout 3,1 rowsfirst

plot "serverMonitorBefore2.txt" using ($1):($2) title "Old Player Count" with lines, "serverMonitorAfter.txt" using ($1):($2) title "New Player Count" with lines

plot "serverMonitorBefore2_avg.txt" using ($1):($5) title "Old CPU usage" with lines, "serverMonitorAfter_avg.txt" using ($1):($5) title "New CPU usage" with lines

plot "serverMonitorBefore2.txt" using ($1):($4) title "Old CPU per Player" with lines, "serverMonitorAfter.txt" using ($1):($4) title "New CPU Per Player" with lines

unset multiplot

pause -1