#include "common.h"
#include "table.c"
#define explen 100

int* append_int(int n, int *arr, int *p);
int getReduction(int k);
char getRedChar(int k);
void printStack(int* stack, int n);

int main(){
	
	struct lr_table* lrt = CreateTable();
	// PrintTable(lrt);
	PrintTableNice(lrt);
	
	// Scan expression
	char expr[explen];
	scanf("%s", expr);
	printf("Expression: %s\n", expr);

	char c;
	int i,j;
	int state = 0;
	struct action act;
	int* stack = (int*)malloc(5*sizeof(int));
	int stack_ptr = 1;
	int red;
	stack[0] = state;
	printf("stack: ");
	printStack(stack, stack_ptr);
	for(i=0; expr[i]!='\0'; ++i){
		c = expr[i];
		j = char_to_col(c, lrt->at.symbols, lrt->num_term);
		act = lrt->at.table[state][j];
		switch (act.type)
		{
			case t_accept:
				printf("Accepted\n");
				// if(expr[i+1]=='\0') printf("Entire");
				// else printf("Partial (%d)", i);
				return 0;
				break;
			case t_shift:
				printf("shift: s%d\n", act.value);
				state = act.value;
				stack = append_int(c, stack, &stack_ptr);
				stack = append_int(state, stack, &stack_ptr);
				printf("stack: ");
				printStack(stack, stack_ptr);
				break;
			case t_reduce:
				printf("Rduce: r%d\n", act.value);
				red = getReduction(act.value);
				c = getRedChar(act.value);
				stack_ptr -= red*2;
				if(stack_ptr<0){
					printf("Error!\n");
					return 0;
				}
				stack = append_int(c, stack, &stack_ptr);
				j = char_to_col(c, lrt->gt.symbols, lrt->num_nonterm);
				state = stack[stack_ptr-2];
				state = lrt->gt.table[state][j];
				stack = append_int(state, stack, &stack_ptr);
				printf("stack: ");
				printStack(stack, stack_ptr);
				i--;
				break;
			default:
				printf("Error!\n");
				return 0;
				break;
		}
	}
	return 0;
}

int* append_int(int n, int *arr, int *p){
	if(*p>0 && *p%5==0){
		int* a = (int*)malloc((*p+5)*sizeof(int));
		for(int i=0; i<*p; ++i){
			a[i] = arr[i];
		}
		a[*p] = n;
		free(arr);
		*p = *p + 1;
		return a;
	}
	arr[*p] = n;
	*p = *p + 1;
	return arr;
}

int getReduction(int k){
	int a[] = {2,2,1};
	return a[k-1];
}

char getRedChar(int k){
	char a[] = {'S','A','A'};
	return a[k-1];
}

void printStack(int* stack, int n){
	for(int i=0; i<n; ++i){
		if((i&1)==0){
			printf("%d ", stack[i]);
		}
		else printf("%c ", stack[i]);
	}
	printf("\n");
}