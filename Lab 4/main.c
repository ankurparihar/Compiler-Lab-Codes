// <whileStatement>	::= while ( <expression> ) { [<statement>] }
// <expression>		::= <id> <CompOp> <id>
// <statement>		::= <id> = <id> <arithOp> <id> ;
// <CompOp>			::= < | > | <= | >= | ==
// <arithOp>		::= + | - | * | /
// <id>				::= [a-zA-Z0-9]
//

// Z -> W(E){S}
// E -> ICI
// S -> I=IAI;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define StackCapacity 1024

struct stack
{
	int top;
	char *array[StackCapacity];
};

int pushStack(struct stack *stk, char *str)
{
	if (stk->top == StackCapacity - 1)
	{
		return 0;
	}
	++(stk->top);
	stk->array[stk->top] = str;
}

char* popStack(struct stack *stk){
	return stk->array[stk->top];
	--(stk->top);
}

void printStack(struct stack *stk){
	for(int i=0; i<=stk->top; ++i){
		printf("%s\n", stk->array[i]);
	}
}

int compStr(char* str1, char* str2){
	for(int i=0; str1[i]!='\0' && str2[i]!='\0'; ++i){
		if(str1[i]!=str2[i]) return 0;
	}
	return 1;
}

int isArithOp(char c){
	return (c=='+'||c=='-'||c=='*'||c=='/');
}

int isBrackt(char c){
	return (c=='('||c==')'||c=='{'||c=='}');
}

int main(int argc, char *argv)
{
	FILE *fptr = fopen("program.c.txt", "r");
	if (!fptr)
	{
		printf("Error opening file\n");
		return 1;
	}
	// sanitize code
	char c;
	char code[1024];
	int i = 0;
	while (fread(&c, 1, 1, fptr))
	{
		if (c != '\n' && c != '\0' && c != ' ' && c != '\t')
		{
			code[i] = c;
			++i;
		}
	}
	code[i] = '\0';
	printf("%s\n", code);

	// Transform code
	char codeT[1024]; int ct = 0;
	char token[1024]; int t = 0;
	for(int j=0; j<i; ++j){
		c = code[j];
		if(isArithOp(c)){
			token[t]='\0';
			if(strcmp(token, "while")==0){
				codeT[ct]='W';
				++ct;
			}else{
				if(t>0){
					codeT[ct] = 'I';
					++ct;
				}
			}
			codeT[ct]='A';
			++ct;
			t=0;
		}
		else if(isBrackt(c)){
			token[t]=0;
			if(strcmp(token, "while")==0){
				codeT[ct]='W';
				++ct;
			}
			else{
				if(t>0){
					codeT[ct] = 'I';
					++ct;
				}
			}
			t=0;
			codeT[ct]=c;
			++ct;
		}
		else if(c=='=' && code[j+1]!='='){
			token[t]='\0';
			if(strcmp(token, "while")==0){
				codeT[ct]='W';
				++ct;
			}else{
				if(t>0){
					codeT[ct] = 'I';
					++ct;
				}
			}
			t=0;
			codeT[ct]='=';
			++ct;
		}
		else if(c=='<' || c=='>' || c=='='){
			if(code[j+1]=='=')++j;
			token[t]='\0';
			if(strcmp(token, "while")==0){
				codeT[ct]='W';
				++ct;
			}else{
				if(t>0){
					codeT[ct] = 'I';
					++ct;
				}
			}
			t=0;
			codeT[ct]='C';
			++ct;
		}
		else if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')){
			token[t] = c;
			++t;
		}
		else if(c==';'){
			token[t]='\0';
			if(strcmp(token, "while")==0){
				codeT[ct]='W';
				++ct;
			}else{
				if(t>0){
					codeT[ct] = 'I';
					++ct;
				}
			}
			t=0;
			codeT[ct]=';';
			++ct;
		}
		// else{
		// 	codeT[ct]=c;
		// 	++ct;
		// 	t=0;
		// }
	}
	codeT[ct]='\0';
	// struct stack *stk = (struct stack *)calloc(1, sizeof(struct stack));
	// stk->top = -1;
	printf("%s\n", codeT);
	
}