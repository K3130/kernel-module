#pragma once

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/inetdevice.h>

#define IP_TO_HEX(a,b,c,d) ((d << 24) | (c << 16) | (b << 8) | a)
#define DEV_NAME "vnetint0"

static struct net_device* vnet_dev;
static __be32 vnet_ip_addr;
static struct proc_dir_entry* vnet_proc_file;

static int ip_a;
static int ip_b;
static int ip_c;
static int ip_d;

module_param(ip_a, int, 0644);
module_param(ip_b, int, 0644);
module_param(ip_c, int, 0644);
module_param(ip_d, int, 0644);

static int __init vnetint_init(void);
static void __exit vnetint_exit(void);
static bool vnetint_flush(void);
static int vnetint_update_interface_ip(__be32 new_ip, __be32 mask, int prefixlen);

static netdev_tx_t vnet_xmit(struct sk_buff* skb, struct net_device* dev);
static void vnet_setup(struct net_device* dev);
static int vnet_proc_show(struct seq_file* m, void* v);
static ssize_t vnet_proc_write(struct file* file, const char __user* buffer, size_t count, loff_t* pos);
static int vnet_proc_open(struct inode* inode, struct file* file);


