// <whileStatement>	::= while ( <expression> ) { [<statement>] }
// <expression>		::= <id> <CompOp> <id>
// <statement>		::= <id> = <id> <arithOp> <id> ;
// <CompOp>			::= < | > | <= | >= | ==
// <arithOp>		::= + | - | * | /
// <id>				::= [a-zA-Z0-9]
//

// code transformation:
// while	-> W
// {}();=	-> {}();=
// <id>		-> I
// +-*/		-> A
// ><		-> C
// >= <= ==	-> C

// Z -> W(E)B
// E -> ICI
// B -> {}
// B -> {S}
// S -> SS
// S -> I=IAI;

#include <stdio.h>
#include <stdlib.h>
#define MaxCodeSize 1024
#define GrammerStr 100
#define MaxStackSize MaxCodeSize

struct GrammerRule
{
	// S -> P
	char S;
	char *P;
	int rule_len;
};

/** Stack implementation as array : start */
struct Stack
{
	int size;
	char c[MaxStackSize];
};

int pushStack(struct Stack *stack, char c)
{
	if (stack->size == MaxStackSize)
	{
		printf("Error: stack full");
		return 0;
	}
	stack->c[stack->size] = c;
	++(stack->size);
	stack->c[stack->size] = '\0';
	return 1;
}

void replaceStack(struct Stack *stack, int start, int end, char c)
{
	stack->c[start] = c;
	for (++end, ++start; end < stack->size; ++end, ++start)
	{
		stack->c[start] = stack->c[end];
	}
	stack->c[start] = '\0';
	stack->size = start;
}

void popStack(struct Stack *stack)
{
	stack->c[stack->size] = '\0';
	--(stack->size);
}

/** Stack implementation as array :  end  */

int isalphanumeric(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

int isarithop(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int isimmutable(char c)
{
	return (c == '(' || c == ')' || c == '{' || c == '}' || c == '=' || c == ';');
}

int iswhile(char *s, int len)
{
	return (len == 5 && (s[0] == 'w' && s[1] == 'h' && s[2] == 'i' && s[3] == 'l' && s[4] == 'e'));
}

/** Nice print function */
void printNice(char *c, int i, int space)
{
	for (int k = i; c[k] != '\0'; ++k, --space)
	{
	}
	while (space-- > 0)
	{
		printf(" ");
	}
	for (; c[i] != '\0'; ++i)
	{
		printf("%c", c[i]);
	}
}

/** Substring function */
// return first string match index or -1
int SubStr(char *s, char *c)
{
	for (int i = 0, j = 0; s[i] != '\0'; ++i)
	{
		if (c[0] == s[i])
		{
			for (j = 1; c[j] != '\0' && s[j + i] != '\0' && c[j] == s[i + j]; ++j)
			{
			}
			if (c[j] == '\0')
				return i;
		}
	}
	return -1;
}

int main()
{
	FILE *fptr = fopen("program.c.txt", "r");
	if (!fptr)
	{
		printf("Error reading program\n");
		return 1;
	}

	// code input in one line
	char code[MaxCodeSize];
	char c;
	int i = 0;
	while (i < MaxCodeSize && fread(&c, 1, 1, fptr))
	{
		if (c != ' ' && c != '\n' && c != '\t' && c != '\0')
		{
			code[i] = c;
			++i;
		}
	}
	code[i] = '\0';
	printf("Linear code: %s\n", code);

	// transform code to terminal and nonterminal symbols
	char token[1024];
	int tn = 0;
	char tcode[1024];
	int tc = 0;
	for (int j = 0; j < i; ++j)
	{
		c = code[j];

		if (isalphanumeric(c))
		{
			token[tn] = c;
			++tn;
		}
		else if (isarithop(c))
		{
			// token[tn] = 0;
			if (iswhile(token, tn))
			{
				tcode[tc] = 'W';
				++tc;
			}
			else if (tn > 0)
			{
				tcode[tc] = 'I';
				++tc;
			}
			tn = 0;
			tcode[tc] = 'A';
			++tc;
		}
		else if (c == '<' || c == '>')
		{
			if (code[j + 1] == '=')
				++j;
			if (iswhile(token, tn))
			{
				tcode[tc] = 'W';
				++tc;
			}
			else if (tn > 0)
			{
				tcode[tc] = 'I';
				++tc;
			}
			tn = 0;
			tcode[tc] = 'C';
			++tc;
		}
		else if (c == '=')
		{
			if (iswhile(token, tn))
			{
				tcode[tc] = 'W';
				++tc;
			}
			else if (tn > 0)
			{
				tcode[tc] = 'I';
				++tc;
			}
			tn = 0;
			if (code[j + 1] == '=')
			{
				++j;
				tcode[tc] = 'C';
			}
			else
			{
				tcode[tc] = '=';
			}
			++tc;
		}
		else if (isimmutable(c))
		{
			if (iswhile(token, tn))
			{
				tcode[tc] = 'W';
				++tc;
			}
			else if (tn > 0)
			{
				tcode[tc] = 'I';
				++tc;
			}
			tn = 0;
			tcode[tc] = c;
			++tc;
		}
		else
		{
			tcode[tc] = c;
			++tc;
		}
	}
	tcode[tc] = '\0';
	++tc;

	printf("Transformed code: %s\n", tcode);

	// scan grammer
	fclose(fptr);
	fptr = fopen("grammer.txt", "r");
	if (!fptr)
	{
		printf("Error reading grammer rules\n");
		return 1;
	}
	char grammer_str[GrammerStr];
	int num_rules = 0;
	i = 0;
	while (fread(&code[i], 1, 1, fptr))
	{
		if (code[i] == '\n')
		{
			++num_rules;
		}
		++i;
	}
	code[i] = '\0';
	if (i > 0)
	{
		++num_rules;
	}
	if (num_rules == 0)
	{
		printf("No rule found\n");
		return 1;
	}
	// printf("Rules:\n%s\n", code);
	// parse and store rules
	// printf("No of grammer rules: %d\n", num_rules);
	struct GrammerRule GrammerList[num_rules];
	int k, p;
	for (i = 0, k = 0; i < num_rules; ++i)
	{
		GrammerList[i].S = code[k];
		k += 2;
		for (p = k; p < MaxCodeSize && (code[p] != '\n' && code[p] != ' ' && code[p] != '\0'); ++p)
		{
		}
		char *prod = (char *)malloc(p - k + 2);
		for (p = k; p < MaxCodeSize && (code[p] != '\n' && code[p] != ' ' && code[p] != '\0'); ++p)
		{
			prod[p - k] = code[p];
		}
		code[p] = '\0';
		GrammerList[i].P = prod;
		GrammerList[i].rule_len = p - k;
		k = p;
		while (code[k] == ' ' || code[k] == '\n' || code[k] == '\0')
			++k;
	}
	// print all rules
	printf("Grammer Rules: (Total %d)\n", num_rules);
	for (i = 0; i < num_rules; ++i)
	{
		printf("%2d. %c -> %10s : %d\n", i + 1, GrammerList[i].S, GrammerList[i].P, GrammerList[i].rule_len);
	}

	// ab stack wali bakchodi

	struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
	char push = 1;
	int reduce_by_rule;
	for (tc = 0; tcode[tc] != '\0'; ++tc)
	{
		if (push)
		{
			pushStack(stack, tcode[tc]);
			printf("%-20s |", stack->c);
			printNice(tcode, tc + 1, 70);
			for (i = 0; i < num_rules; ++i)
			{
				reduce_by_rule = SubStr(stack->c, GrammerList[i].P);
				if (reduce_by_rule >= 0)
				{
					push = 0;
					printf(" | Reduce by %c -> %s\n", GrammerList[i].S, GrammerList[i].P);
					break;
				}
			}
			if (push)
			{
				printf(" | Shift\n");
			}
		}
		else
		{
			// printf("Reduce by %c -> %s\n", GrammerList[i].S, GrammerList[i].P);
			replaceStack(stack, reduce_by_rule, reduce_by_rule + GrammerList[i].rule_len - 1, GrammerList[i].S);
			push = 1;
			tc--;
			printf("%-20s |", stack->c);
			printNice(tcode, tc + 1, 70);
			printf(" | Shift\n");
		}
	}
	c = 1;
	while (c)
	{
		if (reduce_by_rule >= 0)
		{
			replaceStack(stack, reduce_by_rule, reduce_by_rule + GrammerList[i].rule_len - 1, GrammerList[i].S);
			printf("%-20s |", stack->c);
			printNice("", 0, 70);
			for (i = 0; i < num_rules; ++i)
			{
				reduce_by_rule = SubStr(stack->c, GrammerList[i].P);
				if (reduce_by_rule >= 0)
				{
					printf(" | Reduce by %c -> %s\n", GrammerList[i].S, GrammerList[i].P);
					break;
				}
			}
		}
		else
		{
			c = 0;
			printf(" | End\n");
		}
	}
	if (stack->c[0] == 'Z')
	{
		printf("Correct!\n");
	}
	else
	{
		printf("Incorrect!\n");
	}
	// printf("%d\n", stack->size);
	return 0;
}