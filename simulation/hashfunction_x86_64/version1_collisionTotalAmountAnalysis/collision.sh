#!/bin/sh
filename=output_shake_32.dat
result=collision_shake32.txt

awk 'END{print "total data: " NR}' ${filename} > ${result} 
sort -r ${filename} | uniq -c |sort -n | awk -v limit=1 '$1 > limit {print $1,$2}' > collision_temp1
awk '{a+=$1}END{print "total collision: " a}'  collision_temp1 > collision_temp2

cat collision_temp2 >> ${result}
cat collision_temp1 >> ${result}
rm collision_temp*


