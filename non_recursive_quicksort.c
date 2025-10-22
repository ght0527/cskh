#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* my_malloc(size_t size) {
	void* ptr = malloc(size);
	if (ptr == NULL) {
		printf("no\n");
		exit(1);
}
	return ptr;
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
	
typedef struct {
	int* data;
	int top;
	int capacity;
} Stack;

Stack* create_stack(int capacity) {
	Stack* stack = (Stack*)my_malloc(sizeof(Stack));
	stack->data = (int*)my_malloc(capacity * sizeof(int));
	stack->top = -1;
	stack->capacity = capacity;
	return stack;
}

void push(Stack* stack, int value) {
	if (stack->top >= stack->capacity - 1) {
		int new_capacity = stack->capacity * 2;
		int* new_data = (int*)my_malloc(new_capacity * sizeof(int));
		for (int i = 0; i <= stack->top; i++) {
			new_data[i] = stack->data[i];
}
	free(stack->data);
	stack->data = new_data;
	stack->capacity = new_capacity;
}
	stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
	if (stack->top < 0) {
		printf("empty\n");
		exit(1);
}
	return stack->data[stack->top--];
}

int is_empty(Stack* stack) {
	return stack->top == -1;
}

void free_stack(Stack* stack) {
	if (stack) {
		if (stack->data) free(stack->data);
		free(stack); 
}
}

int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (arr[j] <= pivot) {
		i++;
		swap(&arr[i], &arr[j]);
}
}
	swap(&arr[i + 1], &arr[high]);
	return i + 1;
}

void quick_sort_iterative(int arr[], int low, int high) {
	if (low >= high) return;
	Stack* stack = create_stack(1000);
	push(stack, low);
	push(stack, high);
	while (!is_empty(stack)) {
		int h = pop(stack);
		int l = pop(stack);
		if (l < h) {
			int p = partition(arr, l, h);
			if (p - 1 > l) {
				push(stack, l);
				push(stack, p - 1);
}
			if (p + 1 < h) {
				push(stack, p + 1);
				push(stack, h);
}
}
}
	free_stack(stack);
}

int* read_data(const char* filename, int* count) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("no %s\n", filename);
		return NULL;
}

	if (fscanf(file, "%d", count) != 1) {
		printf("no\n");
		fclose(file);
		return NULL;
}

	printf("start %d \n", *count);
	int* arr = (int*)malloc(*count * sizeof(int));
	if (arr == NULL) {
		printf("no \n");
		fclose(file);
		return NULL;
}

	for (int i = 0; i < *count; i++) {
		if (fscanf(file, "%d", &arr[i]) != 1) {
		printf("no %d\n", i);
		free (arr);
		fclose(file);
		return NULL;
}
}

	fclose(file);
	printf("over\n");
	return arr;
}

void write_data(const char* filename, int arr[], int count) {
	remove(filename);
	FILE* file = fopen(filename, "w");
	if (!file) {
		printf("no %s\n", filename);
		return;
}
	fprintf(file, "%d\n", count);
	for (int i = 0; i < count; i++) {
		fprintf(file, "%d\n", arr[i]);
}
	fflush(file);
	fclose(file);
	printf("ok %s\n", filename);
}

int verify_sorted(int arr[], int count) {
	for (int i = 1; i < count; i++) {
		if(arr[i] < arr[i - 1]) {
			printf("wrong arr[%d] = %d > arr[%d] = %d", i-1, arr[i-1], i, arr[i]);
			return 0;
}
}
	return 1;
}

int main() {
	const char* input_file = "int_data.txt";
	const char* output_file = "sorted_result.txt";
	printf("=== non_recursive_quicksort.exe ===\n");
	int count;
	int* data = read_data(input_file, &count);
	printf("5\n");
	for (int i = 0; i < 5 && i < count; i++) {
		printf("%d\n", data[i]);
}
	printf("\n");
	printf("start\n");
	clock_t start_time = clock();
	quick_sort_iterative(data, 0, count - 1);
	clock_t end_time = clock();
	double sort_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("over  %.6f second\n", sort_time);
	printf("verify\n");
	if (verify_sorted(data, count)) {
		printf("yes\n");
} 
	 else {
	 	printf("wrong\n");
	 	free(data);
	 	return 1;
}
	write_data(output_file, data, count);
	printf("5\n");
	for (int i = 0; i < 5 && i < count; i++) {
		printf("%d\n", data[i]);
}
	printf("\n");
	free(data);
	printf("=== over ===");
	return 0;
}
		
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
