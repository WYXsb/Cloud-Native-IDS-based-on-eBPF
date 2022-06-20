# Cloud-Native-IDS-based-on-eBPF
## 各目录
    /wyx                     #针对挖矿病毒的系统调用序列检测
    /dhz                     #监测容器行为和rootkit检测
    /dss                     #生成系统调用序列bpftrace脚本的工具
    /log                     #记录检测系统的输出
### 各文件详解
    run.sh                  #运行整个系统的脚本
    runbpf.sh               #运行所有bpftrace的编写程序的脚本
    installbpf.sh           #检查并安装bpftrace的脚本
    close.sh                #关闭所有bpftrace进程
    /wyx/cont_openfiles.bt  #对于容器打开文件的检测
    /wyx/hash.txt           #文件检测SHA1特征库
    /wyx/cmp.c              #SHA1特征匹配源码
    /wyx/hash1.1.c          #计算文件SHA1值源码
    /wyx/syscalls_seq.bt    #系统调用检测
    

### 快速运行该系统指令
<p>./run.sh</p>    

### 快速关闭该IDS指令
<p>./close.sh</p>
<p>#有可能会误伤到其他bpftrace进程</p>
