#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 int main() {
 	const char* filename = "float_data.txt";
 	int count = 100000;
 	srand(time(NULL));
 	FILE* file = fopen(filename, "w");
 	if (file == NULL) {
 		printf("no %s\n", filename);
 		return 1;
}
	fprintf(file, "%d\n", count);
	printf("start %d\n", count);
	for (int i = 0; i < count; i++) {
		float num = (float)(rand() % 1000000) / 1000.0f;
		fprintf(file, "%.3f\n", num);
}
	fclose(file);
	printf("over %s\n", filename);
	return 0;
}
	
 	
