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
#define NODE_DATA_SIZE 32 
#define PROCFS_NAME "Canonical_kernel_module"

static struct proc_dir_entry *kern_mod;
static char procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;
static int list_length = 0;
static char* out_buf;

struct node{
	struct node *next;
	char data[NODE_DATA_SIZE];
};

static struct node *head_node = NULL;

/* Initialise linked list. Will be called once per module loading */
void initialise(char data[NODE_DATA_SIZE]);

/* Append new buffer to list in new node. */
void append(struct node** head_node, char data[NODE_DATA_SIZE]);

/* Delete entire list on module cleanup */
void delete(struct node** head_node){
	struct node* tmp1 = *head_node;
	struct node* tmp2;
//	printk(KERN_INFO "You are in delete()\n");
	if(tmp1 == NULL){
//		printk(KERN_INFO "if statement\n");
		kfree(tmp1);
	}else if(tmp1->next == NULL){
//		printk(KERN_INFO "else if\n");
		kfree(tmp1);
	}else{
		while(tmp1->next != NULL){
//			printk(KERN_INFO "else statement\n");
			tmp2 = tmp1;
			tmp1 = tmp1->next;
			kfree(tmp2);
		}
		kfree(tmp1);
	}
};

/* Add each element to a read buffer that can be printed, piped etc. */
void print_list(struct node** head_node){
	struct node* tmp = *head_node;
	
	char tmpbuff[NODE_DATA_SIZE];
	if(tmp == NULL){
		printk(KERN_INFO "Empty list lol\n");
		return;
	}
	do{
		memset(tmpbuff, '\0', NODE_DATA_SIZE);
		strncpy(tmpbuff, tmp->data, NODE_DATA_SIZE);
		pr_info("%s ", tmpbuff);
		tmp = tmp->next; 
	}while(tmp != NULL);
};

void assemble_buffer(void){
	printk(KERN_INFO "this has been fun\n");
	out_buf = (char*)kmalloc(sizeof(NODE_DATA_SIZE * list_length), GFP_KERNEL);
	printk(KERN_INFO "it did not break\n");
}

static ssize_t file_read(struct file *file_pointer, char __user *buffer, size_t len, loff_t *offset){
	ssize_t bytes; 
	struct node* tmp;
	
	tmp = head_node;
//	print_list(&head_node);
//	printk(KERN_INFO "in file_read\n");
	
	assemble_buffer();

	if(len < (NODE_DATA_SIZE-(*offset))){
		len = (NODE_DATA_SIZE-(*offset));
	}
	bytes = len;
	if(tmp == NULL){
		printk(KERN_INFO "Empty list\n");
		return 0;
	}
	do{
		printk(KERN_INFO "do loop\n");
//		memset(buffer,0,len);
		if (/**offset >= len || */ copy_to_user(buffer, tmp->data, sizeof(tmp->data))){
			pr_info("copy_to_user failed\n");
			return -EFAULT;
		}else{
			pr_info("procfile read %s from %s\n", tmp->data, file_pointer->f_path.dentry->d_name.name); 
			*offset += bytes; 
		}
		tmp = tmp->next;
//		printk(KERN_INFO "tmp next\n");
		
	}while(tmp != NULL);
//	printk(KERN_INFO "left the loop\n");
	return bytes; 
} 

static ssize_t file_write(struct file *file, const char __user *buffer, size_t len, loff_t *off){
	struct node* tmp = (struct node*)kmalloc(sizeof(struct node), GFP_KERNEL);
	struct node* last;
	last = head_node;
	memset(procfs_buffer, '\0', NODE_DATA_SIZE);

	procfs_buffer_size = len;

	if(procfs_buffer_size > NODE_DATA_SIZE){
		procfs_buffer_size = NODE_DATA_SIZE;
	}
	if(copy_from_user(tmp->data, buffer, len)){
		return -EFAULT;
	}

//	strncpy(tmp->data, procfs_buffer, NODE_DATA_SIZE);
	tmp->data[NODE_DATA_SIZE - 1] = '\n';
	tmp->next = NULL;

	/* If linked list is empty */
	if(head_node == NULL){
		head_node = tmp;
	}else{
		while(last->next != NULL){
			last = last->next;
		}
		last->next = tmp;
	}

	procfs_buffer[procfs_buffer_size & (NODE_DATA_SIZE - 1)] = '\0';
	*off += procfs_buffer_size;
//	pr_info("procfile write %s and %s\n", procfs_buffer, head_node->data);
	
	list_length++;
	pr_info("THE LENGTH OF THIS LIST IS: %d\n", list_length);
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
	printk(KERN_INFO "You are in kern_mod_exit\n");
	delete(&head_node);
	remove_proc_entry(PROCFS_NAME, NULL);
	printk(KERN_INFO "Goodbye, kernel world!\n");
}

module_init(kern_mod_init);
module_exit(kern_mod_exit);
