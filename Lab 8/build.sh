lex lab8.l
yacc lab8.y -Wnone
gcc y.tab.c -ll -ly -w
./a.out < input > output
# cleanup
rm a.out lex.yy.c y.tab.c
