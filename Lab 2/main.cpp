// Desk calculator using operator precedence parsing

// E -> E + T | T
// T -> T * F | F
// F-> ( E ) | id

#include <iostream>
#include <stdio.h>



int eval(char *, int, int);
int eval_bracket(char *, int, int);
int getClosingBracket(char*, int, int);

int getClosingBracket(char *input, int start, int end){
	int k = start + 1;
	int stack = 1;
	while (k < end && stack > 0)
	{
		if (input[k] == '(')
			++stack;
		else if (input[k] == ')')
			--stack;
		++k;
	}
	return k;
}

int eval_bracket(char *input, int start, int end)
{
	// int k ;
	int stack = 1;
	int k = getClosingBracket(input, start, end);
	return eval(input, start + 1, k - 1);
}

int eval(char *input, int start, int end)
{
	// if(start)
	int n1 = 0;
	for (int i = start; i < end; ++i)
	{
		// printf("%c ",n1);
		if (input[i] >= '0' && input[i] <= '9')
		{
			n1 = n1 * 10 + (input[i] - '0');
		}
		else if (input[i] == '*' || input[i] == '/')
		{
			int j = i + 1;
			bool bracket_exists = false;
			int bracket_start = 0;
			int bracket_end = 0;
			while (j < end && (input[j] != '+' && input[j] != '-'))
			{
				if(input[j]=='(' && !bracket_exists){
					j = getClosingBracket(input, j, end);
					bracket_end = j;
					bracket_exists = true;
					bracket_start = j;
				}
				++j;
			}
			if (j == end)
			{
				if(bracket_exists){
					if(input[i]=='*'){
						if(input[bracket_start-1]=='*'){
							if(input[bracket_end+1]=='*'){
								return n1 * eval(input, i+1, bracket_start-2) * eval(input, bracket_start+1, bracket_end-1) * eval(input, bracket_end+2, end);
							}
							else {
								return n1 * eval(input, i+1, bracket_start-2) * eval(input, bracket_start+1, bracket_end-1) / eval(input, bracket_end+2, end);
							}
						}
						else {
							if(input[bracket_end+1]=='*'){
								return n1 * eval(input, i+1, bracket_start-2) / eval(input, bracket_start+1, bracket_end-1) * eval(input, bracket_end+2, end);
							}
							else{
								return n1 * eval(input, i+1, bracket_start-2) / eval(input, bracket_start+1, bracket_end-1) / eval(input, bracket_end+2, end);
							}
						}
					}
					else {
						if(input[bracket_start-1]=='*'){
							if(input[bracket_end+1]=='*'){
								return n1 / eval(input, i+1, bracket_start-2) * eval(input, bracket_start+1, bracket_end-1) * eval(input, bracket_end+2, end);
							}
							else {
								return n1 / eval(input, i+1, bracket_start-2) * eval(input, bracket_start+1, bracket_end-1) / eval(input, bracket_end+2, end);
							}
						}
						else {
							if(input[bracket_end+1]=='*'){
								return n1 / eval(input, i+1, bracket_start-2) / eval(input, bracket_start+1, bracket_end-1) * eval(input, bracket_end+2, end);
							}
							else{
								return n1 / eval(input, i+1, bracket_start-2) / eval(input, bracket_start+1, bracket_end-1) / eval(input, bracket_end+2, end);
							}
						}
					}
				}
				return (input[i] == '*') ? n1 * eval(input, i + 1, end) : n1 / eval(input, i + 1, end);
			}
			else
			{
				return (input[i] == '*') ? (n1 * eval(input, i + 1, j) + ((input[j] == '-') ? -1 : 1) * eval(input, j + 1, end)) : (n1 / eval(input, i + 1, j) + ((input[j] == '-') ? -1 : 1) * eval(input, j + 1, end));
			}
		}
		else if (input[i] == '+')
		{
			return n1 + eval(input, i + 1, end);
		}
		else if (input[i] == '-')
		{
			return n1 - eval(input, i + 1, end);
		}
		else if (input[i] == '(')
		{
			// int k=i+1;
			return eval_bracket(input, i, end);
		}
		else {
			printf("Error!");
			return 0;
		}
	}
	return n1;
}

int checkForinvalidOp(char *input, int len){
	for(int i=0; i<len; ++i){
		if(input[i]=='+'||input[i]=='-'||input[i]=='*'||input[i]=='/'){
			if(i==len-1 || input[i+1]=='+'|| input[i+1]=='-'|| input[i+1]=='*'|| input[i+1]=='/'){
				printf("Bad operator!!\n");
				return 0;
			}
		}
	}
	return 1;
}

int main()
{
	char input[256] = "6*9*3";
	scanf("\n%s", input);
	int end = 0;
	while (input[end] != '\0')
	{
		// printf("%c", input[end]);
		++end;
	}
	// printf("%d\n",end);
	if(checkForinvalidOp(input, end)==0){
		return 1;
	}
	printf("%d\n", eval(input, 0, end));
	return 0;
}