#include "common.h"
#include "table.c"

int main(){
	struct lr_table* lrt = CreateTable();
	PrintTable(lrt);
	return 0;
}