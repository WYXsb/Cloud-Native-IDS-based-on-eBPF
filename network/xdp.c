#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <stdio.h>
#include <linux/tcp.h>
#include <string.h>

#include <linux/types.h>
#define SEC(NAME) __attribute__((section(NAME), used))
 
SEC("mysection")
int filter(struct xdp_md *ctx) {
    int ipsize = 0;
    void *data = (void *)(long)ctx->data;
    void *data_end = (void *)(long)ctx->data_end;
    struct ethhdr *eth = data;
    struct iphdr *ip;
    unsigned int tmp = 0;
    char *ip_src;//ip发送地址
 
    
    char black_ip1[] ="192.168.1.1";
    //char *black_ip2 ;
    //char *black_ip3 ;
    ipsize = sizeof(*eth);
    ip = data + ipsize;
    ip_src = (char *)(ip->saddr);
    
    
    
    
    ipsize += sizeof(struct iphdr);
    if (data + ipsize > data_end) {
        return XDP_DROP;
    }
 
    if (ip->protocol == IPPROTO_TCP) {

       if ((ip->saddr)==(unsigned long long)black_ip1)
       return XDP_DROP;
       

       
        else
        //printf("good!");
        return XDP_PASS;
    }
 
    return XDP_PASS;
}
 