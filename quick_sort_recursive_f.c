#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
float* readDataFromFile(const char* filename, int* count);
void saveResultFToFile(const char* filename, float arr[], int count);
int isSorted(float arr[], int count);
void quickSortRecursive(float arr[], int left, int right);
int partition(float arr[], int left, int right);
int medianOfThree(float arr[], int left, int right);

float* readDataFromFile(const char* filename, int* count) {
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
	float* arr = (float*)malloc(*count * sizeof(float));
	if (arr == NULL) {
		printf("no \n");
		fclose(file);
		return NULL;
}

	for (int i = 0; i < *count; i++) {
		if (fscanf(file, "%f", &arr[i]) != 1) {
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

void saveResultToFile(const char* filename, float arr[], int count) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("no %s\n", filename);
		return;
}

	fprintf(file, "%d\n", count);
	for (int i = 0; i < count; i++) {
		fprintf(file, "%f\n", arr[i]);
}
	fclose(file);
	printf("over %s\n", filename);
}

int isSorted(float arr[], int count) {
	for (int i = 1; i < count; i++) {
		if (arr[i] < arr[i - 1]) {
			printf("no %d (%f) > %d (%f)\n", i - 1, arr[i - 1], i, arr[i]);
			return 0;
}
}
	return 1;
}

int medianOfThree(float arr[], int left, int right) {
	int mid = left + (right - left) / 2;
	if (arr[left] > arr[mid]) {
		float temp = arr[left];
		arr[left] = arr[mid];
		arr[mid] = temp;
}
	if (arr[left] > arr[right]) {
		float temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
}
	if (arr[mid] > arr[right]) {
		float temp = arr[mid];
		arr[mid] = arr[right];
		arr[right] = temp;
}
	return mid;
}

int partition(float arr[], int left, int right) {
	int pivotIndex = medianOfThree(arr, left, right);
	float pivot = arr[pivotIndex];
	float temp = arr[pivotIndex];
	arr[pivotIndex] = arr[right];
	arr[right] = temp;
	int i = left - 1;
	for (int j = left; j < right; j++) {
	if (arr[j] <= pivot) {
		i++;
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
}
}
	temp = arr[i + 1];
	arr[i + 1] = arr[right];
	arr[right] = temp;
	return i + 1;
}

void quickSortRecursive(float arr[], int left, int right) {
	if (left < right) {
		int pivotIndex = partition(arr, left, right);
		quickSortRecursive(arr, left, pivotIndex - 1);
		quickSortRecursive(arr, pivotIndex + 1, right);
}
}

int main() {
	const char* inputFile = "float_data.txt";
	const char* outputFile = "sorted_data.txt";
	printf("start\n");
	printf("in %s\n", inputFile);
	printf("out %s\n", outputFile);
	int count;
	float* data = readDataFromFile(inputFile, &count);
	if (data == NULL) {
		printf("no\n");
		return 1;
}
	printf("\n 10 \n");
	for (int i = 0; i < 10 && i < count; i++) {
		printf("%f", data[i]);
}
	printf("\n");
	printf("\n start \n");
	clock_t start_time = clock();
	quickSortRecursive(data, 0, count - 1);
	clock_t end_time = clock();
	double time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	printf("over %.6f second\n", time_used);
	printf("\n verify \n");
	if (isSorted(data, count)) {
		printf("yes \n");
}
	else {
	printf("no \n");
}
	printf("\n 10 \n");
	for (int i = 0; i < 10 && i < count; i++) {
		printf("%f", data[i]);
}
	printf("\n");
	printf("\n save \n");
	saveResultToFile(outputFile, data, count);
	free(data);
	printf("\n  ----over----  \n");
	return 0;
}
