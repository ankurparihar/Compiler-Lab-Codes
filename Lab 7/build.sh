yacc -d lab7.y -v
lex lab7.l
gcc y.tab.c lex.yy.c
./a.out input
