#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
int* readDataFromFile(const char* filename, int* count);
void saveResultToFile_fixed(const char* filename, int arr[], int count);
int isSorted(int arr[], int count);
void merge(int arr[], int left, int mid, int right);
void mergeSortSerial(int arr[], int left, int right);
void mergeSortParallel(int arr[], int left, int right);

int* readDataFromFile(const char* filename, int* count) {
        printf("open %s\n", filename);
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
	printf("number %d\n", *count);
	int* arr = (int*)malloc(*count * sizeof(int));
	if (arr == NULL) {
		printf("no\n");
		fclose(file);
		return NULL;
}
	for (int i = 0; i < *count; i++ ) {
		if (fscanf(file, "%d", &arr[i]) != 1) {
			printf("no %d\n", i);
			free(arr);
			fclose(file);
			return NULL;
}
}

	fclose(file);
	printf("over\n");
	return arr;
}

void saveResultToFile_fixed(const char* filename, int arr[], int count) {
        printf("start save\n");
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("now %s\n", cwd);
}
        printf("create %s\n", filename);
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
                perror("no");
                char local_file[1024];
                snprintf(local_file, sizeof (local_file), ",/%s", filename);
                printf("try %s\n", local_file);
                file = fopen(local_file, "w");
                if (file == NULL) {
                        perror("no again");
                        return;
}
                printf("local  yes\n");
}
        else {
                printf("yes\n");
}
      printf("%d\n", count);
      fprintf(file, "%d\n", count);
      fflush(file);
      printf("write in\n");
      int written = 0;
      for (int i = 0; i < count; i++) {
              fprintf(file, "%d\n", arr[i]);
              written++;
              if ((i + 1) % 20000 == 0) {
                      printf("%d/%d\n", i + 1, count);
                      fflush(file);
}
}
      fclose(file);
      printf("over %d\n", written);
      FILE* verify = fopen(filename, "r");
      if (verify) {
              int verify_count;
              fscanf(verify, "%d", &verify_count);
              fclose(verify);
              printf("verify  %d\n", verify_count);
}
      else {
              printf("warn no\n");
}
}
int isSorted(int arr[], int count) {
        printf("verify\n");
        if (arr == NULL || count <= 0) {
                printf("no \n");
                return 0;
}
	for (int i = 1; i < count; i++) {
		if(arr[i] < arr[i - 1]) {
			return 0;
}
}
        printf("pass\n");
	return 1;
}

void merge(int arr[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	
	int* leftArr = (int*)malloc(n1 * sizeof(int));
	int* rightArr = (int*)malloc(n2 * sizeof(int));
	if (leftArr == NULL || rightArr == NULL) {
		printf("no\n");
		if (leftArr) free(leftArr);
		if (rightArr) free(rightArr);
		return;
}
	for (int i = 0; i < n1; i++) {
		leftArr[i] = arr[left + i];
}
	for (int j = 0; j < n2; j++) {
		rightArr[j] = arr[mid + 1 + j];
}
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (leftArr[i] <= rightArr[j]) {
			arr[k] = leftArr[i];
			i++;
}
		else {
			arr[k] = rightArr[j];
			j++;
}
		k++;
}
	while (i < n1) {
		arr[k] = leftArr[i];
		i++;
		k++;
}
	while (j < n2) {
		arr[k] = rightArr[j];
		j++;
		k++;
}
	free(leftArr);
	free(rightArr);
}

void mergeSortSerial(int arr[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSortSerial(arr, left, mid);
		mergeSortSerial(arr, mid + 1, right);
		merge(arr, left, mid, right);
}
}

void mergeSortParallel(int arr[], int left, int right) {
	const int PARALLEL_THRESHOLD = 10000;
	if (left < right) {
		int mid = left + (right - left) / 2;
		if (right - left > PARALLEL_THRESHOLD) {
			#pragma opm parallel sections
			{
				#pragma opm section
				{
					mergeSortParallel(arr, left, mid);
}
				#pragma opm section
				{
					mergeSortParallel(arr, mid + 1, right);
}
}
}
		else {
			mergeSortSerial(arr, left, mid);
			mergeSortSerial(arr, mid + 1, right);
}
		merge(arr, left, mid, right);
}
}

int main() {
	const char* inputFile = "int_data.txt";
	const char* outputFile = "parallel_sorted_data.txt";
	printf("=== start ===\n");
        int count;
        int* data = readDataFromFile(inputFile, &count);
        if (data == NULL) {
                printf("no \n");
                return 1;
}
        printf("success %d\n", count);
        
	printf("\n start \n");
	double start_time = omp_get_wtime();
	mergeSortParallel(data, 0, count - 1);
	double end_time = omp_get_wtime();
	printf("over  use  %.3f second\n",end_time - start_time);
	
	if (isSorted(data, count)) {
		printf("yes\n");
	}
	else {
		printf("no\n");
		free(data);
		return 1;
}
	printf("\n save \n");
	saveResultToFile_fixed(outputFile, data, count);
	printf("clean\n");
	free(data);
	printf("\n === over === \n");
	return 0;
}
	
	
	

		
		
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			

	

