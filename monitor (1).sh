#!/bin/bash
   if [ $# -lt 1 ]; then
       echo "Uso: ./monitor.sh \"comando\" [intervalo]"
       exit 1 
fi

comando="$1"

if [ $# -ge 2 ]; then
    intervalo="$2"
else 
    intervalo=2
fi
bash -c "$comando" &
pid=$!

log="monitor_${pid}.log"
img="monitor_${pid}.png"

inicio=$(date +%s)

echo "SEGUNDOS  CPU% MEM% MEM_RSS_KB" > "$log" 

 finalizar() { 
     kill -TERM "$pid"
     } 
trap finalizar SIGINT 

while ps -p "$pid" > /dev/null
do 
 ahora=$(date +%s)
 segundos=$((ahora - inicio)) 
 linea=$(ps -p "$pid" -o %cpu,%mem,rss --no-headers)

 cpu=$(echo "$linea" | awk '{print $1}')
 mem=$(echo "$linea" | awk '{print $2}')
 rss=$(echo "$linea" | awk '{print $3}')

 echo "$segundos  $cpu $mem $rss" >> "$log"

sleep "$intervalo" 
done 

gnuplot << EOF
set terminal png
set output "$img"
set title "Comando: $comando PID: $pid"
set xlabel "Tiempo (s)"
set ylabel "CPU %"
set y2label "Memoria RSS KB"
set y2tics 
plot "$log" using 1:2 with lines title "CPU %", "$log" using 1:4 axes x1y2 with lines title "MEM RSS KB"
EOF
echo "Log generado: $log"
echo "Grafica generada:$img" 


