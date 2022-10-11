/* kern_mod.c -- a very simple kernel module */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonathan Cameron <jacc@bu.edu>");
MODULE_DESCRIPTION("A simple /proc kernel module.");
MODULE_VERSION("1.0");

#define PROCFS_MAX_SIZE 1024
#define PROCFS_NAME "Canoncical_kernel_module"

static struct proc_dir_entry *kern_mod;

static char procfs_buffer[PROCFS_MAX_SIZE];

static unsigned long procfs_buffer_size = 0;

static ssize_t file_read(struct file *file_pointer, char __user *buffer, size_t buffer_length, loff_t *offset){
	
	int len = sizeof(procfs_buffer);
	ssize_t ret = len; 
	
	strcpy(s, string);
	if (*offset >= len || copy_to_user(buffer, procfs_buffer, sizeof(procfs_buffer))){
		pr_info("copy_to_user failed\n");
		ret = 0;
	}else{
		pr_info("procfile read %s\n", file_pointer->f_path.dentry->d_name.name); 
		*offset += len; 
	} 
	return ret; 
} 

static ssize_t file_write(struct file *file, const char __user *buffer, size_t len, loff_t *off){
	
	procfs_buffer_size = len;

	if(procfs_buffer_size > PROCFS_MAX_SIZE){
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}
	if(copy_from_user(procfs_buffer, buffer, procfs_buffer_size)){
		return -EFAULT;
	}

	procfs_buffer[procfs_buffer_size & (PROCFS_MAX_SIZE - 1)] = '\0';
	*off += procfs_buffer_size;
	pr_info("procfile write %s\n", procfs_buffer);

	return procfs_buffer_size;
}

static const struct proc_ops file_ops = {
	.proc_read = file_read,
	.proc_write = file_write,
};

static int __init kern_mod_init(void)
{
	printk(KERN_INFO "Hello, kernel world!\n");
	
	kern_mod = proc_create(PROCFS_NAME, 0666, NULL, &file_ops);
	if(!kern_mod){
		proc_remove(kern_mod);
		return -1;
	}
	else{
		printk(KERN_INFO "Created new /proc file successfully\n");
	}
	return 0;
}

static void __exit kern_mod_exit(void)
{
	remove_proc_entry(PROCFS_NAME, NULL);
	printk(KERN_INFO "Goodbye, kernel world!\n");
}

module_init(kern_mod_init);
module_exit(kern_mod_exit);
