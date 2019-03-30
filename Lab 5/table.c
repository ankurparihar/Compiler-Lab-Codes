#include "common.h"
#define t_shift 0
#define t_reduce 1
#define t_accept 2
#define t_blank 3

struct action{
	int type;
	int value;
};

struct goto_table{
	char *symbols;
	int **table;
};

struct action_table{
	char *symbols;
	struct action **table;
};

struct lr_table{
	int num_states;
	int num_nonterm;
	int num_term;
	struct action_table at;
	struct goto_table gt;
};

int char_to_col(char c, char* ca, int len){
	for(int i=0; i<len; ++i){
		if(ca[i]==c) return i;
	}
	return -1;
}

void PrintTable(struct lr_table* lrt){
	printf("action table:\n");
	for(int i=0; i<lrt->num_term; ++i){
		printf(" %c ", lrt->at.symbols[i]);
	}
	printf("\n");
	for(int i=0; i<lrt->num_states; ++i){
		for(int j=0; j<lrt->num_term; ++j){
			int type = lrt->at.table[i][j].type;
			if(type==t_shift) printf("s%d ", lrt->at.table[i][j].value);
			else if(type == t_reduce) printf("r%d ", lrt->at.table[i][j].value);
			else if(type == t_accept) printf(" a");
			else printf("   ");
		}
		printf("\n");
	}
	printf("goto table:\n");
	for(int i=0; i<lrt->num_nonterm; ++i){
		printf("%c ", lrt->gt.symbols[i]);
	}
	printf("\n");
	for(int i=0; i<lrt->num_states; ++i){
		for(int j=0; j<lrt->num_nonterm; ++j){
			int val = lrt->gt.table[i][j];
			if(val==-1) printf("  ");
			else printf("%d ", val);
		}
		printf("\n");
	}
}

void PrintTableNice(struct lr_table* lrt){
	printf("\nTable:\n");
	printf("|       |");
	for(int i=0; i<lrt->num_term; ++i){
		printf("%c\t", lrt->at.symbols[i]);
	}
	printf("|");
	for(int i=0; i<lrt->num_nonterm; ++i){
		printf(" %c\t", lrt->gt.symbols[i]);
	}
	printf("|\n");
	int type;
	for(int i=0; i<lrt->num_states; ++i){
		printf("|   %2d  |", i);
		for(int j=0; j<lrt->num_term; ++j){
			type = lrt->at.table[i][j].type;
			if(type==t_shift) printf("s%d\t", lrt->at.table[i][j].value);
			else if(type == t_reduce) printf("r%d\t", lrt->at.table[i][j].value);
			else if(type == t_accept) printf(" a\t");
			else printf("\t");
		}
		printf("|");
		for(int j=0; j<lrt->num_nonterm; ++j){
			int val = lrt->gt.table[i][j];
			if(val==-1) printf("  \t");
			else printf("%2d\t", val);
		}
		printf("|\n");
	}
	printf("\n");
}

char* appendToCharArray(char c, char* array, int len){
	if(array==NULL){
		char *cp = (char*)malloc(sizeof(char));
		*cp = c;
		return cp;
	}
	char *cp = (char *)malloc(len+1);
	for(int i=0; i<len; ++i){
		*(cp+i) + *(array+i);
	}
	*(cp+len) = c;
	free(array);
	return cp;
}

int discardable(char c){
	if(c=='\t' || c=='\n' || c==' ') return 1;
	return 0;
}

struct lr_table* CreateTable(){
	int k;
	struct lr_table* lrt = (struct lr_table*)malloc(sizeof(struct lr_table));
	printf("How many non-terms are there ?: ");
	scanf("\n%d", &lrt->num_nonterm);
	printf("How many terminals are there ?: ");
	scanf("\n%d", &lrt->num_term);
	printf("How many states are there ?: ");
	scanf("\n%d", &lrt->num_states);

	// Enter non terminals
	lrt->gt.symbols = (char*)malloc(lrt->num_nonterm * sizeof(char));
	printf("Enter non terminals: ");
	char c;
	for(int i=0; i<lrt->num_nonterm; ++i){
		scanf("%c", &c);
		if(discardable(c)){
			i--;
			continue;
		}
		lrt->gt.symbols[i] = c;
	}

	// Enter terminals
	lrt->at.symbols = (char*)malloc(lrt->num_term * sizeof(char));
	printf("Enter terminals: ");
	for(int i=0; i<lrt->num_term; ++i){
		scanf("%c", &c);
		if(discardable(c)){
			i--;
			continue;
		}
		lrt->at.symbols[i] = c;
	}

	// Enter action table
	printf("Enter action table in matrix form: 00=blank, si=shift i, ri=reduce i, a0=accept\n");
	lrt->at.table = (struct action**)malloc(lrt->num_states * sizeof(struct action*));
	int type;
	for(int i=0; i<lrt->num_states; ++i){
		lrt->at.table[i] = (struct action*)malloc(lrt->num_term * sizeof(struct action));
		for(int j=0; j<lrt->num_term; ++j){
			scanf(" %c%d", &c, &k);
			if(c=='s') type = t_shift;
			else if(c=='r') type = t_reduce;
			else if(c=='a') type = t_accept;
			else type = t_blank;
			lrt->at.table[i][j].type = type;
			lrt->at.table[i][j].value = k;
		}
	}

	// Enter goto table
	printf("Enter goto table in matrix form: -1=blank\n");
	lrt->gt.table = (int **)malloc(lrt->num_states * sizeof(int *));
	for(int i=0; i<lrt->num_states; ++i){
		lrt->gt.table[i] = (int*)malloc(lrt->num_nonterm * sizeof(int));
		for(int j=0; j<lrt->num_nonterm; ++j){
			scanf(" %d", &k);
			lrt->gt.table[i][j] = k;
		}
	}

	return lrt;
}