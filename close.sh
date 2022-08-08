ps -aux | grep bpftrace | grep -v grep | awk '{ print$2 }' | xargs kill
ps -aux | grep hids | grep -v grep | awk '{ print$2 }' | xargs kill