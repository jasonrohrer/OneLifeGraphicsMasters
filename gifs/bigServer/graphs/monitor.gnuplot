set output "serverMonitor.eps"

set terminal post enhanced color size 8.3in,9.7in

# set terminal wxt size 600,700


set multiplot layout 3,1 rowsfirst

plot "serverMonitorBefore2.txt" using ($1):($2) title "Old Player Count" with lines, "serverMonitorAfter.txt" using ($1):($2) title "New Player Count" with lines  lc rgb '#00FF00'lt 1

plot "serverMonitorBefore2_avg.txt" using ($1):($5) title "Old CPU usage" with lines, "serverMonitorAfter_avg.txt" using ($1):($5) title "New CPU usage" with lines   lc rgb '#00FF00'lt 1

plot "serverMonitorBefore2_avg.txt" using ($1):($5/$2) title "Old CPU per Player" with lines, "serverMonitorAfter_avg.txt" using ($1):($5/$2) title "New CPU Per Player" with lines   lc rgb '#00FF00'lt 1

unset multiplot

