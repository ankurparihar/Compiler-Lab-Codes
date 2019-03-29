%{ 
%} 

%% 

(while) 		{printf("key_whl ");}
(begin) 		{printf("key_bgn\n");}
(end)			{printf("key_end\n");}
(\() 			{printf("cond_opn ");}
(\)) 			{printf("cond_cls\n");}
[\n \t]+ 		{}
(==|<=|>=|>|<)	{printf("comp_op ");}
[0-9]+			{printf("number ");}
[A-Za-z][A-Za-z0-9]* {printf("token ");}
([A-Za-z][A-Za-z0-9]*.(==|<=|>=|<|>).[A-Za-z][A-Za-z0-9]*) {printf("condition\n");}
([A-Za-z][A-Za-z0-9]*=[A-Za-z0-9]+[+-/*][A-Za-z0-9]+;) {printf("\tStatement\n");}

%% 

/*** User code section***/
int yywrap(){} 
int main(int argc, char **argv) 
{ 

yylex(); 

return 0; 
} 
