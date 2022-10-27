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

gets() takes unfiltered input and that leaves it open to taking arguments like `'"put 6 %n in c ", &c'` using the `%n` character. This will put 6 in the variable `c`.

We can even give it things like "%x %x %x %x..." which will cause the program to start printing values from the stack, hence a memory leak vulnerability.

How about `'"%x", &ret'`? This returns the address of `ret`. Can we do something with this? `'"%lx", &ret'` tells us a little more.

How about we find where our stuff is being written on the stack.`"AAAABBBB %<num>$lx"`

Sure enough, `"AAAABBBB %10$lx"` returns to us `"AAAABBBB 4242424241414141"`, or `"AAAABBBB %8$lx"` on a different machine.

We need to remember that the first 6 arguments are passed to functions via registers, the rest are via the stack.

I think we have to overwrite the value of `<system@plt>` or `<exit@plt>` to an address we own.

So I guess the goal is to write some shellcode to an address and then just there when we return from the function?

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