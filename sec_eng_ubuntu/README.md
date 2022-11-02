# Vulnerability Research

## CVE-2016-0741

### Identify what software this issue affects

slapd/connection.c in 389 Directory Server (formerly Fedora Directory Server) 1.3.4.x before 1.3.4.7 allows remote attackers to cause a denial of service (infinite loop and connection blocking) by leveraging an abnormally closed connection.

### What is the commit or commits to fix it, if any are available

The commit to fix the bug is located here.
https://github.com/389ds/389-ds-base/commit/cd45d032421b0ecf76d8cbb9b1c3aeef7680d9a2

### Describe how you would go about determining whether any Ubuntu releases are affected and which ones

Find which Ubuntu packages are using 389 Directory Server 1.3.4.x up to 1.3.4.7. Using the Ubuntu packages site can help us here. https://packages.ubuntu.com/search?keywords=389-ds

### Describe how you would address the vulnerability

When a connection is abruptly closed due to an error, and there is still some data left to be read(buffer offset vs buffer bytes), connection_threadmain starts to loop. The connection is marked as closed, which prevents the buffer bytes/offset to be updated(e.g. in connection_read_operation()). So the worker thread endlessly tries to read the "data" over and over, but it should just remove the connection from the conn table since it's marked as closed.

While it's looping it's repeatedly taking the factory extension lock which creates a lot of contention with the other worker threads. Ultimately, all the worker threads are trying to read data on closed connections, and the server stops accepting new connections.

So to make sure that the connection is closed properly, we need to make sure that that is returned so the connection table can be updated properly. Also, when attempting to write data from the buffer, check if the connection was closed, and return 0, to indicate that there is no more data to read.

### Describe how you would verify that your fix does address the issue and does not introduce any regressions

To test against regression, we must use the tests that we originally designed the software with. When the software was designed, it would have been designed to a specification so that the designers could write their design requirements and the testers could write their test cases to check its functionality. The bug would have to be fixed against both of these requirements, so that the software still behaves how it should.

# Design Review

Since the client application process is untrusted, the sandbox does not allow it to make requests to the privAPI() of the service process. 

The idea of the sandbox is that it is used to keep the client application separate from the machine the sandbox is running on. However, the service application should be checking whether the request is allowed to be made by the client application, not the sandbox. If the client application is going to be denied of its requests, it should be denied by the service application for not having the correct permissions or by requesting unsafe operations, rather than being denied before the request reach the service application.

Since we can control the trusted service process, we should make sure that this attack surface does not have vulnerabilities and can process the untrusted client application's requests safely.

# Code Audit

### What are the errors in this code?

There are calls to malloc() but no calls to free() for the memory allocated on the heap for the buffers the program handles.

### What threat model is appropriate for this code?

The code is severe because it has the opportunity to have its execution hijacked. This is bad because if it has higher privileges than the user running it, they can use it to gain an escalation in privilege by exploiting the code.

### What threat model would you consider if this program was exposed to the internet?

If this code was exposed to the internet it should be removed immediately, since it would allow an attacker to remotely hijack the host machine of the process.

### What test cases would you use to test this program?

gets() takes unfiltered input and that leaves it open to taking arguments like `'"put 6 %n in c ", &c'` using the `%n` character. This will put 6 in the variable `c`.

We can even give it things like "%x %x %x %x..." which will cause the program to start printing values from the stack, hence a memory leak vulnerability.

How about `'"%x", &ret'`? This returns the address of `ret`. Can we do something with this? `'"%lx", &ret'` tells us a little more.

How about we find where our stuff is being written on the stack.`"AAAABBBB %<num>$lx"`

Sure enough, `"AAAABBBB %10$lx"` returns to us `"AAAABBBB 4242424241414141"`, or `"AAAABBBB %8$lx"` on a different machine.

We need to remember that the first 6 arguments are passed to functions via registers, the rest are via the stack.

I think we have to overwrite the value of `<system@plt>` or `<exit@plt>` to an address we own.

So I guess the goal is to write some shellcode to an address and then just there when we return from the function? Not quite...

We want to overwrite the GOT entry for `exit(0)` which will take us to a function or other process we control. For sake of proving a concept, I will start with hijacking the process with a function I compiled into the program. It will not be called by the normal execution flow and will look like this:

`void hijack(void){`
    `printf("Process hijacked...\n");`
    `system("/bin/sh");`
`}`

We can even start by calling this function in GDB by changing variables in the debugger.

In GDB 
`(gdb) x hijack`
> 0x4012af <hijack>:	0xe5894855

So `hijack()` starts at 0x4012af.

`(gdb) disas main`
...
>0x00000000004013ec <+300>:	call   0x4010a0 <exit@plt>

`(gdb) disas 0x4010a0`
>0x00000000004010a0 <+0>:	jmp    *0x2faa(%rip)        # 0x404050 <exit@got.plt>

`(gdb) x 0x404050`
> 0x404050 <exit@got.plt>:	0x004010a6

And `exit@got.plt` lives at 0x404050.

`(gdb) set {int}0x404050=0x4012af`, and hit continue, we will spawn a shell from hijack within GDB.

Our address for `exit(0)` is at 0x404050 which is `\x50\x40\x40` in little endian, since I'm working on intel architecture. This ends up being `P@@ %8$n` to write to that address. It causes a SEGFAULT which means that somewhere an address is being changed, or that we are trying to access an illegal address. (I suspect the latter). `P@@ %8$lx` shows that what is printed to a register is actually `20404050`, which is not correct. `\x20` is a space character, which means we need to experiment with the padding.

I am time-boxing this exercise since I have spent enough time examining the code with GDB.

### Bonus: Rewrite this code to address the issues you've identified. What choices need to be addressed with the rewrite? What changes in your choices if this program is a simple tool for yourself versus if this is part of a larger product you're distributing to others? 

