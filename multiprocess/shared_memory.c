#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_MEM 1000000

struct mem_area {
	int length;
	char buf[MAX_MEM];
};

const char* SHARED_MEM_NAME = "/shared_mem_name";
const int SHARED_SLEEP_TIME = 2;
const int LOOP_MAX = 5000;

void cleanup() {
	if (shm_unlink(SHARED_MEM_NAME) == -1) {
		// one of the processes will run into this
		fprintf(stderr, "has already been cleaned up!\n");
	} else {
		fprintf(stdout, "cleaning up!\n");
	}
}

void fork_method(char * proc_name) {
	fprintf(stdout, "%s says hi.\n", proc_name);

	struct mem_area *mem_pointer;

	int file_descriptor = shm_open(SHARED_MEM_NAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (file_descriptor == -1) {
		fprintf(stderr, "%s couldn't open shared memory.\n", proc_name);
	}

	if (ftruncate(file_descriptor, sizeof(struct mem_area)) == -1) {
		fprintf(stderr, "%s couldn't truncate memory store\n", proc_name);
	}

	mem_pointer = mmap(NULL, sizeof(struct mem_area), PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);
	if (mem_pointer == MAP_FAILED) {
		fprintf(stderr, "%s couldn't map memory area.\n", proc_name);
	}

	for (int i = 0; i < LOOP_MAX; i++) {
		fprintf(stdout, "%s reads memory, it looks like: %s\n", proc_name, mem_pointer->buf);

		char* bufp = &mem_pointer->buf[mem_pointer->length];

		// add to char array
		strcat(bufp, proc_name);
		strcat(bufp, " ");
	}

	cleanup();
}

void split_processes() {
	if (fork() == 0) {
		fork_method("child");
	} else {
		fork_method("parent");
	}
}

int main() {
	split_processes();
}

