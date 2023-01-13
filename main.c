#include<stdio.h>
#include<unistd.h>


#define ADDR_SIZE 7


int data_seg = 123;
int bss_seg = 0;
int *heap_seg;
void *lib_seg = &printf;
void text_seg() {}

int main() {
	heap_seg = malloc(10);
	int stack_seg_bf = 10;
	
	pid_t pid = fork();

	int stack_seg_af = 11;	

	if(pid == 0) {
		printf("child process\n");
	}
	else {
		sleep(2);
		printf("parent process\n");
	}

	int in_addr[ADDR_SIZE] = {
		&data_seg
		, &bss_seg
		, heap_seg
		, lib_seg
		, &text_seg
		, &stack_seg_bf
		, &stack_seg_af
	};
	int out_addr[ADDR_SIZE];
	
	printf("Virtual Address:\n");
	for(int i = 0; i < ADDR_SIZE; i++) {
		printf("%p\n", in_addr[i]);
	}

	syscall(352, in_addr, ADDR_SIZE, out_addr);
	
	printf("Physical Address:\n");
	for(int i = 0; i < ADDR_SIZE; i++) {
		printf("%p\n", out_addr[i]);
	}

	return 0;
}
