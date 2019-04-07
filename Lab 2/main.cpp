// Desk calculator using operator precedence parsing

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "table.cpp"
// status definition
using namespace std;

enum states{
	S_START, S_OPRTR, S_NUMRL, S_BRCKT_OPN, S_BRCKT_CLS
};

bool isNumeric(char c){
	return (c=='.' || (c>='0' && c<='9'));
}
bool isOperator(char c){
	return (c=='+' || c=='-' || c=='*' || c=='/');
}
bool isAllowed(states prevStat, states nextStat){
	return (((prevStat==S_START) && (nextStat==S_NUMRL || nextStat==S_BRCKT_OPN)) || ((prevStat==S_OPRTR) && (nextStat==S_NUMRL || nextStat==S_BRCKT_OPN)) || (prevStat==S_NUMRL && (nextStat==S_OPRTR || nextStat==S_BRCKT_OPN || nextStat==S_BRCKT_CLS)) || (prevStat==S_BRCKT_OPN && (nextStat==S_NUMRL || nextStat==S_BRCKT_OPN)) || (prevStat==S_BRCKT_CLS && (nextStat==S_OPRTR || nextStat==S_BRCKT_CLS)));
}

double char_to_double(char* str){
	double d = 0;
	int n;
	bool afterDecimal = false;
	int pow = 1;
	int level;
	char c = str[0];
	for(int i=0; c!='\0'; ++i, c=str[i]){
		if(c=='.'){
			if(!afterDecimal){
				afterDecimal = true;
				continue;
			}
			else{
				return 0;
			}
		}
		else{
			n = str[i] - '0';
			if(afterDecimal){
				pow *= 10;
				d += (double)n/pow;
			}else{
				d *= 10;
				d += n;
			}
		}
	}
	return d;
}

int getClosingBracket(char* str, int start, int end){
	int stack = 1;
	int i;
	for(i=start; i<=end; ++i){
		if(str[i]=='(') stack++;
		else if(str[i]==')') stack--;
		if(stack==0) break;
	}
	if(i<=end){
		return i;
	}
	return -1;
}

template <typename T>
T* append(T c, T* arr, int p){
	if(p>0 && p%5==0){
		T* arr2 = (T*)malloc((p+5)*sizeof(T));
		for(int i=0; i<p; ++i){
			arr2[i] = arr[i];
		}
		arr2[p] = c;
		free(arr);
		return arr2;
	}
	arr[p] = c;
	return arr;
}

template <typename T>
T* appendUnit(T c, T* arr, int p){
	if(p==0){
		arr[p] = c;
		return arr;
	}
	T* arr2 = (T*)malloc((p+1)*sizeof(T));
	for(int i=0; i<p; ++i){
		arr2[i] = arr[i];
	}
	arr2[p] = c;
	free(arr);
	return arr2;
}

template <typename T>
void printStack(T* arr, int p){
	for(int i=0; i<=p; ++i){
		cout << arr[i] << " ";
	}
	cout << endl;
}

void reduceStack(double* values, int p, char op, int& p_end){
	switch (op)
	{
		case '+':
			values[p] = values[p] + values[p+1];
			break;
		case '-':
			values[p] = values[p] - values[p+1];
			break;
		case '*':
			values[p] = values[p] * values[p+1];
			break;
		case '/':
			if(values[p+1]==0){
				printf("Error: Divide by zero\n");
				std::exit(1);
			}
			values[p] = values[p] / values[p+1];
			break;
	
		default:
			break;
	}
	for(int j=p+1; j<p_end; ++j){
		values[j] = values[j+1];
	}
	p_end--;
}

double parseExp(char* expr, double* values, int p_ops, int p_val){
	operator_table optab;
	char c1, c2, c3;
	char* stack = (char*)malloc(sizeof(char));
	stack = append('$', stack, 0);
	int p_stk = 0;
	int p_exp = 0;
	int p_val2 = -1;
	while(p_val>0){
		c1 = stack[p_stk];
		c2 = expr[p_exp];
		c3 = optab[c1][c2];
		if(c3=='<'){
			// push
			p_stk++;
			p_exp++;
			stack = append(c2, stack, p_stk);
		}
		else if(c3=='>'){
			// pop
			if(c1=='i'){
				p_val2++;
			}
			else{
				reduceStack(values, p_val2-1, c1, p_val);
				p_val2--;
			}
			p_stk--;
		}
		else{
			// return
			if(c1=='$' && c2=='$') return values[0];
		}
	}
	return values[0];
}

double eval(char* str, int start, int end){
	double *values = (double*)malloc(5*sizeof(double));
	char *ops = (char*)malloc(5*sizeof(char));
	int p_val = -1, p_ops = -1;
	int status;
	char c;
	states state = S_START;
	for(int i=start; i<=end; ++i){
		c = str[i];
		if(str[i]=='('){
			if(!isAllowed(state, S_BRCKT_OPN)){
				printf("Error:%4d\tInvalid '('\n", i);
				std::exit(1);
			}
			int j = getClosingBracket(str, i+1, end);
			if(j==-1){
				printf("Error:%4d\tBracket Mismatch\n", i);
				std::exit(1);
			}
			p_val++;
			p_ops++;
			values = append(eval(str, i+1, j-1), values, p_val);
			ops = append('i', ops, p_ops);
			i=j;
			state = S_BRCKT_CLS;
		}
		else if(str[i]==')'){
			printf("Error:%4d\tInvalid ')'\n", i);
			std::exit(1);
		}
		else if(isOperator(c)){
			if(!isAllowed(state, S_OPRTR)){
				printf("Error:%4d\tInvalid operator positioning\n", i);
				std::exit(1);
			}
			++p_ops;
			ops = append(c, ops, p_ops);
			state = S_OPRTR;
		}
		else if(isNumeric(c)){
			if(!isAllowed(state, S_NUMRL)){
				printf("Error:%4d\tImproper number positioning\n", i);
				std::exit(1);
			}
			int j;
			char* token = (char*)malloc(sizeof(char));
			for(j=i; j<=end; ++j){
				c = str[j];
				if(isNumeric(c)) token = appendUnit(c, token, j-i);
				else{
					token = appendUnit('\0', token, j-i);
					break;
				}
			}
			i=j-1;
			p_val++;
			p_ops++;
			values = append(char_to_double(token), values, p_val);
			ops = append('i', ops, p_ops);
			state = S_NUMRL;
		}
	}
	if(state!=S_BRCKT_CLS && state!=S_NUMRL){
		printf("Error: Invalid expression ending\n");
		std::exit(1);
	}
	p_ops++;
	ops = append('$', ops, p_ops);
	printStack(ops, p_ops);
	printStack(values, p_val);
	if(p_val==0){
		return values[0];
	}
	else{
		return parseExp(ops, values, p_ops, p_val);
	}
}

int main(){
	// cout << optab['*']['+'] << endl;
	// cout << char_to_double((char*)"5.67") << endl;
	// cout << getClosingBracket((char*)"1+(5)))", 0, 7) << endl;
	// cout << append('\0', append('!', (char*)"I am ankur", 10), 11) << endl;
	char* expr = (char*)"((1*2*3)+5/8*((5)-9))+5.6*5-9.7";
	int len = 0;
	while(expr[len]!='\0') len++;
	cout << "Evaluation: " << eval(expr, 0, len) << endl;
	char expr_arr[1024];
	while(true){
		scanf("%s", expr_arr);
		int len = 0;
		while(expr_arr[len]!='\0') len++;
		cout << "Evaluation: " << eval((char*)expr_arr, 0, len) << endl;
	}
	return 0;
}