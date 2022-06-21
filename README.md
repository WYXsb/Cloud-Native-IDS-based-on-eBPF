## 各目录

```text
/wyx                     #针对挖矿病毒的系统调用序列检测
/dhz                     #监测容器行为和rootkit检测
/dss                     #生成系统调用序列bpftrace脚本的工具
/log                     #记录检测系统的输出

```

### 各文件详解

```text
run.sh                  #运行整个系统的脚本
runbpf.sh               #运行所有bpftrace的编写程序的脚本
installbpf.sh           #检查并安装bpftrace的脚本
close.sh                #关闭所有bpftrace进程
/wyx/cont_openfiles.bt  #对于容器打开文件的检测
/wyx/hash.txt           #文件检测SHA1特征库
/wyx/cmp.c              #SHA1特征匹配源码
/wyx/hash1.1.c          #计算文件SHA1值源码
/wyx/syscalls_seq.bt    #系统调用检测
/dhz/rootkit.bt         #Rootkit检测
/dhz/container_mount.bt #容器异常挂载检测
/dhz/container_exec.bt  #容器进程创建信息收集
/dhz/container_shell.bt #容器shell操作信息收集
/network/sliver-implant-detect.bt   #检测sliver病毒并过滤流量
```

### 快速运行该系统指令

./run.sh

### 快速关闭该IDS指令

./close.sh

#有可能会误伤到其他bpftrace进程

