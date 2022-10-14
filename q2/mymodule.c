/* kern_mod.c -- a very simple kernel module */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonathan Cameron <jacc@bu.edu>");
MODULE_DESCRIPTION("A simple /proc kernel module.");
MODULE_VERSION("1.0");

#define NODE_DATA_SIZE 32 
#define PROCFS_NAME "Canonical_kernel_module"

static struct proc_dir_entry *mymodule;
static int bytes_written = 0;

struct node{
    struct node *next;
    char data[NODE_DATA_SIZE];
    int num;
};

static struct node* head_node = NULL;

void delete (struct node** head_node){
    struct node* tmp1 = *head_node;
    struct node* tmp2;
    if(tmp1 == NULL){
        kfree(tmp1);
    }else if(tmp1->next == NULL){
        kfree(tmp1);
    }else{
        while(tmp1->next != NULL){
            tmp2 = tmp1;
            tmp1 = tmp1->next;
            kfree(tmp2);
        }
        kfree(tmp1);
    }
};

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

void assemble_buffer(char* buffer){
    struct node* tmp = head_node;
    // memset(buffer, '\0', (bytes_written * sizeof(char)));
    // tmp->data[tmp->num - 1] = '\0';
    // pr_info("tmp->data on its own: %s\n", tmp->data);
    strncpy(buffer, tmp->data, tmp->num);
    tmp = tmp->next;
    if(tmp == NULL){
        return;
    }else{
        do{
            // tmp->data[tmp->num - 1] = '\0';
            // pr_info("tmp->data on its own: %s\n", tmp->data);
            strncat(buffer, tmp->data, tmp->num);
            tmp = tmp->next;
        }while(tmp != NULL);
    }
    // bytes_written += 6;
    // pr_info("Break before strcat(). Bytes written: %d\n", bytes_written);
    // strcat(buffer, s);
    pr_info("the whole string: %s\n", buffer);
    return;
}

static ssize_t file_read(struct file *file_pointer, char __user *buffer, size_t len, loff_t *offset){
    

    char s[13] = "HelloWorld!\n"; 
    int length = sizeof(s); 
    ssize_t ret = length; 
    char* outbuffer = (char*)kmalloc(bytes_written * sizeof(char), GFP_KERNEL);
    // memset(outbuffer, '\0', (bytes_written * sizeof(char)));
    if(head_node == NULL){
        pr_info("Empty node\n");
        kfree(outbuffer);
        return 0;
    }
    assemble_buffer(outbuffer);
    length = sizeof(outbuffer);
    // print_list(&head_node);
    // pr_info("left assemble_buffer()\n");
    // pr_info("printing outbuffer to dmesg: %s\n", outbuffer);
    if (*offset >= length || copy_to_user(buffer, outbuffer, bytes_written)) { 
        pr_info("copy_to_user failed\n"); 
        ret = 0; 
    } else { 
        pr_info("procfile read %s\n", file_pointer->f_path.dentry->d_name.name); 
        *offset += length; 
    } 
    kfree(outbuffer);
    //ret = length;
    return ret; 
}

static ssize_t file_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset){
    struct node* tmp = (struct node*)kmalloc(sizeof(struct node), GFP_KERNEL);
    struct node* last = head_node;

    if(len > NODE_DATA_SIZE){
        len = NODE_DATA_SIZE;
    }

    if(copy_from_user(tmp->data, buffer, len)){
        return -EFAULT;
    }

    tmp->data[len-1] = '\0';
    tmp->next = NULL;
    tmp->num = len;

    if(head_node == NULL){
        head_node = tmp;
    }else{
        while(last->next != NULL){
            last = last->next;
        }
        last->next = tmp;
    }

    bytes_written = bytes_written + len;
    *offset += bytes_written;
    pr_info("Bytes written: %d\n", bytes_written);

    return len;
}

static const struct proc_ops file_ops = {
    .proc_read = file_read,
    .proc_write = file_write,
};

static int __init kern_mod_init(void)
{
	printk(KERN_INFO "Hello, kernel world!\n");
		
	mymodule = proc_create(PROCFS_NAME, 0666, NULL, &file_ops);
	if(!mymodule){
		proc_remove(mymodule);
		return -1;
	}
	else{
		printk(KERN_INFO "Created new /proc file successfully\n");
	}
	return 0;
}

static void __exit kern_mod_exit(void)
{
	delete(&head_node);
	remove_proc_entry(PROCFS_NAME, NULL);
	printk(KERN_INFO "Goodbye, kernel world!\n");
};

module_init(kern_mod_init);
module_exit(kern_mod_exit);