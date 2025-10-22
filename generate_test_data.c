#include <stdio.h>
#include <stdlib.h>
#include <time.h>
	int main() {
		const char* filename = "int_data.txt";
		int count = 100000;
		srand(time(NULL));
		FILE* file = fopen(filename, "w");
		if (file == NULL) {
			printf("no %s\n", filename);
			return 1;
			}
		fprintf(file, "%d\n", count);
		printf("start %d\n", count);
		for (int i = 0; i < count; i++){
		int num = rand() % 1000000;
		fprintf(file, "%d\n", num);
		}
		fclose(file);
		printf("over %s\n", filename);
		return 0;
		}
