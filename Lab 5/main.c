#include "common.h"
#include "table.c"

int main(){
	struct lr_table* lrt = CreateTable();
	// PrintTable(lrt);
	PrintTableNice(lrt);
	return 0;
}