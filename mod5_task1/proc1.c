
 
#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/proc_fs.h> 
#include <linux/uaccess.h> 
#include <linux/version.h>
#include <linux/ktime.h>  
#include <linux/time.h> 
#include <linux/rtc.h>  
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/file.h>


#define procfs_name "module5_task1" 

static struct proc_dir_entry *our_proc_file; 
struct rtc_time t;

 
static ssize_t procfile_read(struct file *filePointer, char __user *buffer, 
                             size_t buffer_length, loff_t *offset) 
{  
    char dat[20];
    sprintf(dat,"%ptRs",&t);
    int len = sizeof(dat); 
    ssize_t ret = len; 
  
    if (*offset >= len || copy_to_user(buffer, dat, len)) { 
        ret = 0; 
    } else { 
        pr_info("procfile read %s\n", filePointer->f_path.dentry->d_name.name); 
        *offset += len; 
    } 
    return ret; 
} 
 
static const struct proc_ops proc_file_fops = { 
    .proc_read = procfile_read, 
}; 

 
static int __init procfs1_init(void) 
{ 
     
    our_proc_file = proc_create(procfs_name, 0644, NULL, &proc_file_fops); 
    if (NULL == our_proc_file) { 
        proc_remove(our_proc_file); 
        pr_alert("Error:Could not initialize /proc/%s\n", procfs_name); 
        return -ENOMEM; 
    } 
 
    pr_info("/proc/%s created\n", procfs_name); 
    t = rtc_ktime_to_tm(ktime_get_real());

    return 0; 
} 
 
static void __exit procfs1_exit(void) 
{ 
 
    //proc_remove(our_proc_file); 
    //pr_info("/proc/%s removed\n", procfs_name); 
} 
 
module_init(procfs1_init); 
module_exit(procfs1_exit); 
 
MODULE_LICENSE("GPL");