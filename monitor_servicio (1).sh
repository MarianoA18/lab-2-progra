#!/bin/bash
LOGFILE="/var/log/monitor.log"

while true
do 
   echo "===== $(date '+%Y-%m-%d %H:%M:%s') ====" >> "$LOGFILE"
   ps aux --sort=-%cpu | head -n 6 >> "$LOGFILE"
   echo "" >> "$LOGFILE"
   sleep 5
done  
 
