# Vulnerability Research

## CVE-2016-0741

### Identify what software this issue affects

### What is the commit or commits to fix it, if any are available

### Describe how you would go about determining whether any Ubuntu releases are affected and which ones

### Describe how you would address the vulnerability

### Describe how you would verify that your fix does address the issue and does not introduce any regressions

# Design Review

# Code Audit

### What are the errors in this code?

Using gets() and strcpy() in getinput can cause a buffer overflow if the input from the user is too large.

Despite ASLR and PIE mitigating the possiblility of a stack buffer overflow, it is still possible to achieve privilege escalation from this code, by bypassing these two. This can be done by leaking the offset between something like libc and our process in GDB

`$ gdb greetings`

`$ break main`

`$ run`

`$ info proc mappings`

`$ cat payload.bin - | ./greetings`

There are calls to malloc() but no calls to free() to free the memory allocated on the heap for the buffers the program handles.

### What threat model is appropriate for this code?

### What threat model would you consider if this program was exposed to the internet?

### What test cases would you use to test this program?

### Bonus: Rewrite this code to address the issues you've identified. What choices need to be addressed with the rewrite? What changes in your choices if this program is a simple tool for yourself versus if this is part of a larger product you're distributing to others? 


Plan of action.
- Do steps 1 and 2, the vulnerability research and the design review.
- Review code and rewrite it so it is safer. 
- If it is possible, exploit the code.