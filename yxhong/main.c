#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include <time.h>


int for_data_segment = 48763;
int for_bss_segment;
int *for_heap_segment;
void *for_libraries_segment = &printf;
void for_text_segment() {}


void process_function(void) {
    int for_stack_stgment = 357;

	unsigned long input_arr[arr_size];
	unsigned long output_arr[arr_size];

	input_arr[0] = &for_text_segment;
	input_arr[1] = &for_data_segment;
	input_arr[2] = &for_bss_segment;
	input_arr[3] = for_heap_segment;
	input_arr[4] = for_libraries_segment;
	input_arr[5] = &for_stack_segment;

	printf("input:\n");
	printf("%p\n", input_arr[0]);
	printf("%p\n", input_arr[1]);
	printf("%p\n", input_arr[2]);
	printf("%p\n", input_arr[3]);
	printf("%p\n", input_arr[4]);
	printf("%p\n", input_arr[5]);

	int temp = syscall(351, input_arr, arr_size, output_arr);

	printf("output:\n");
	printf("%p\n", output_arr[0]);
	printf("%p\n", output_arr[1]);
	printf("%p\n", output_arr[2]);
	printf("%p\n", output_arr[3]);
	printf("%p\n", output_arr[4]);
	printf("%p\n", output_arr[5]);
}


int main(void) {
    int pid = fork();

    if(pid > 0) {
        printf("This is parent process!\n");
        process_function();
    }
    else if(pid == 0) {
        sleep(3);
        printf("This is child process!\n");
        process_function()
    }

    return 0;
}