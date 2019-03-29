#include <stdio.h>
#define MAXLEN 1024

int main(int argc, char*argv){
	char str[MAXLEN];
	// fgets(str, MAXLEN, stdin);
	FILE* fptr = fopen("inter", "r");
	int end=0;
	while(fread(&str[end], 1, 1, fptr)){
		++end;
	}
	
	// printf("%d\n", end);

	char* rgx_in = "key_whl cond_opn token comp_op number cond_cls\nkey_bgn\n";
	char* statmt = "\tStatement";
	char* rgx_of = "key_end";
	int j;
	for(j=0; j<55; ++j){
		if(str[j]!=rgx_in[j]){
			printf("Error_1\n");
			return 1;
		}
		// else {
		// 	printf("%c %c", str[j], rgx_in[j]);
		// }
	}
	while(str[j]=='\t'){
		// printf("%d %d", str[j], statmt[0]);
		// ++j;
		for(int k=0;k<10;){
			if(str[j]==statmt[k]){
				++j;
				++k;
				// printf("%d %d\n", j, k);
				// printf("%c %c\n", statmt[k], str[j]);
			}
			else{
				printf("Error_2\n");
				return 1;
			}
		}
		// printf("%d\n", str[j]);
		++j;
	}
	for(int k=0;k<7;){
		if(rgx_of[k]==str[j]){
			++j;
			++k;
		}
		else{
			printf("Error_3\n");
			return 1;
		}
	}
	printf("While loop is valid\n");
	return 0;
}