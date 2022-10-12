#Dummy kmod
A loadable module to load into the kernel.

1. Create a kernel module that can be loaded and unloaded with insmod/rmmod. [X]

2. The kernel module will create a proc entry and register a read/write file_op. [ ]
a. We create a /proc entry. [X]
b. We monitor our new /proc file for when it is read from and written to. [X]

3. On each write to the proc, a copy of the buffer will be stored in a linked list data structure. [ ]
a. We store the things written to this new file in a linked list data structure.
	- Each new write is a new entry to the linked list. [ ]
	- The linked list does not need to be fancy. From the spec, we need to be able to append to the linked list, and print it out on a read of the /proc file. [ ]
	- For simplicities sake, we will write all of our linked list functionality in kern_mod.c

4. Each read from the proc will fill the read buffer with list entries up to the read length (buffer size). [ ]
a. I assume this means that we print the list to stdout? Or we can do other things with the read buffer, like pipe to another process or write to another file.

5. List memory and proc entry will get properly cleaned up when module is unloaded. [ ]
a. We free up memory used for our linked list and we delete the new file we create.

Assumptions:
- We do not need to handle command line arguments, unless we wanted to take an argument that determines the name of the new /proc file, which we might do if time allows.


