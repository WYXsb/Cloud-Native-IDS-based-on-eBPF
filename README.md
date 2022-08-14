## 各目录

```text
/mining                  #针对挖矿病毒的系统调用序列检测
/HIDS-eBPF               #监测容器行为与rootkit检测模块
/container               #容器进程创建与shell命令信息收集
/dss                     #生成系统调用序列bpftrace脚本的工具
/log                     #记录检测系统的输出

```

### 各文件详解

```text
run.sh                         #安装hids运行所需环境并运行整个系统的脚本
runbpf.sh                      #运行hids所有模块的脚本
installbpf.sh                  #检查并安装bpftrace的脚本
close.sh                       #关闭hids所有模块
/mining/cont_openfiles.bt      #对于容器打开文件的检测
/mining/hash.txt               #文件检测SHA1特征库
/mining/cmp.c                  #SHA1特征匹配源码
/mining/hash1.1.c              #计算文件SHA1值源码
/mining/syscalls_seq.bt        #系统调用检测
/HIDS-eBPF/examples/hids       #容器行为检测与rootkit检测源码
/container/container_monitor.bt     #容器进程创建与shell命令信息收集
/network/sliver-implant-detect.bt   #检测sliver病毒并过滤流量
```

### 快速运行该系统指令

./run.sh

### 快速关闭该IDS指令

./close.sh

#有可能会误伤到其他bpftrace进程

### 自定义恶意系统调用序列

一个系统调用序列的定义方式如下：



   ```

   #sequence

       read->read->

       sys_enter_newfstatat->sys_enter_newfstatat->sys_enter_getcwd+->sys_enter_newfstatat->

       sys_enter_openat->sys_enter_epoll_ctl->sys_enter_getdents64->

       (sys_enter_newfstatat)*->

       sys_enter_getdents64->sys_enter_close->

       write->write->

       epoll_pwait->epoll_pwait;

   #do

       time("%H:%M:%S  ");

       printf("%-20s %-10d %-10d %-20s\n",comm,pid,tid,"ls");

   #end

   ```



   * 第一行的`#sequence`是定义系统调用序列的开始，它需要独立一行



   * 从第二行开始到`#do`之间的内容是由检测节点组成的检测序列，在这里，你既可以使用自己定义的，带有额外触发条件和触发动作的检测节点（例如上面的`read`，`write`，`epoll_pwait`），也可以使用默认的系统调用探针作为检测节点（只需要把系统调用名前面加上`sys_enter_`或者`sys_exit_`即可）



   * 使用`->`运算符把两个序列连接在一起，也可以使用`*`表示匹配该序列零次或多次，使用`+`表示匹配该序列零次或一次，使用`|`表示两个序列只需要匹配其中一个即可。它们的运算符优先级如下：



     `*`==`+`>`|`>`->`



   * `#do`到`#end`之间的内容是当匹配上该序列之后会执行的动作



   你可以定义多个系统调用序列，同时检测它们

按照上面的书写规则，将序列写入一个文本文件，然后使用dss编译器将其翻译成bt脚本文件，就可以将bt脚本文件作为检测规则加入IDS中。

具体的系统调用序列检测规则书写方式见[__https://github.com/csc010228/detect_syscall_sequence/blob/main/README.md__](https://github.com/csc010228/detect_syscall_sequence/blob/main/README.md)




