#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/inetdevice.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter_ipv6.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/skbuff.h>
#include <linux/inet.h>

#define MODULE_NAME "advanced_net_module"

static struct nf_hook_ops nfho_in; // Netfilter hook option struct

// Netfilter hook function for incoming packets
static unsigned int incoming_packet_hook(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    struct iphdr *ip_header = ip_hdr(skb);

    if (ip_header->protocol == IPPROTO_TCP) {
        struct tcphdr *tcp_header = tcp_hdr(skb);
        printk(KERN_INFO "Received TCP packet from %pI4:%d to %pI4:%d\n",
               &ip_header->saddr, ntohs(tcp_header->source),
               &ip_header->daddr, ntohs(tcp_header->dest));
    } else if (ip_header->protocol == IPPROTO_UDP) {
        struct udphdr *udp_header = udp_hdr(skb);
        printk(KERN_INFO "Received UDP packet from %pI4:%d to %pI4:%d\n",
               &ip_header->saddr, ntohs(udp_header->source),
               &ip_header->daddr, ntohs(udp_header->dest));
    }

    return NF_ACCEPT; // Accept all packets
}

// Module initialization function
static int __init net_module_init(void) {
    printk(KERN_INFO "Initializing advanced networking module\n");

    // Register Netfilter hook for incoming packets
    nfho_in.hook = incoming_packet_hook;
    nfho_in.pf = PF_INET; // IPv4
    nfho_in.hooknum = NF_INET_PRE_ROUTING; // Hook in PRE_ROUTING stage
    nfho_in.priority = NF_IP_PRI_FIRST; // Highest priority
    nf_register_net_hook(&init_net, &nfho_in);

    printk(KERN_INFO "Advanced networking module initialized\n");
    return 0; // Success
}

// Module cleanup function
static void __exit net_module_exit(void) {
    printk(KERN_INFO "Exiting advanced networking module\n");

    // Unregister Netfilter hook
    nf_unregister_net_hook(&init_net, &nfho_in);

    printk(KERN_INFO "Advanced networking module exited\n");
}

module_init(net_module_init);
module_exit(net_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Advanced Networking Module");
