# How to run

- compile `gcc main.c`
- run `./a.out < input.txt > output.txt`. Result will be saved in [output.txt](./output.txt)
- input format (file:[input.txt](./input.txt))
	- The first line of input contains number of rules n.
	- Then next n lines contains rules property lhs(left hand side symbol) and rhs(no of symbols in rhs). Eg. `A->Aa` becomes `A 2`
	- Next line no of terminal symbols
	- Next line no of non-terminal symbols
	- Next line no of states generated for LR table
	- Next line non-terminal symbols space separated
	- Next line terminal symbols space separated
	- Next line Table rules (action) in matrix form: 00=blank, si=shift i, ri=reduce i, a0=accept
	- Next line Table rules (goto) in matrix form: -1=blank
	- Final line expression to evaluate

# Tools
- Use [LR1 machine](http://jsmachines.sourceforge.net/machines/lr1.html) to create tables and verify programs.
- Tool's indexing starts from 0 and my program's from 1. so if tools has reduce instruction `r3` my program's input will be `r4`. shift instructions are as it is.
