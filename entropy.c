#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void calcEntropy(char el[], int sz){
	int *chars = calloc(256, sizeof(int));
	double entropy; 
	int i;
	for(i = 0; i < (sz - 1); i++){
		chars[(int)el[i]]++;
	}
	
	for(i = 0; i < 256; i++){
		double frequency = chars[i]/(double)(sz - 1);
		
		if(frequency){
			entropy -= frequency*(log2(frequency));
		}
	}

	free(chars);	
	printf("Entropy: %f\n", entropy);
}

int main(int argc, char *argv[]){
	FILE *fp;
	
	if(argc != 2){
		printf("Accepting only one argument, file name");
		return 1;
	}

	fp = fopen(argv[1], "r");  
	
	if( !fp ){
		perror(argv[1]);
		return 1;
	}
	
	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	rewind(fp);
		
	char *buffer;
	buffer = malloc(sz);
	fread(buffer, 1, sz, fp);
	fclose(fp);
	 
	calcEntropy(buffer, sz);

	free(buffer);	
	return 0;
}	
	
