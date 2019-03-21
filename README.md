# ScratchPad

a place for me to illustrate some ideas in simple and hopefully informative ways

## Multithread

A simple example of shared memory using the [POSIX](http://man7.org/linux/man-pages/man3/shm_open.3.html) shared memory standard.

### Multithread explanation

this example starts 2 threads, then each thread will open up a shared memory store defined by the struct `mem_area`.

Each thread will then append characters to the end of the character array without caring about synchronization.

When run you will see thet not only does the access never cause a runtime error, but depending on your scheduler
you will see that sometimes the proc_name will get written for both processes before a single space is written.

In real life you would want to use a mutex to ensure access to a shared memory object was protected from this kind of thing.

But I think that it is useful to illustrate how it works without forced order.

And unlike multi-threaded access to the same pointer in memory, this won't cause a segfault in the shared memory.
