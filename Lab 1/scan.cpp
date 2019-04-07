// Write a program to scan a program and identify tokens (identifiers, keywords, numbers) in it.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sstream>

#define tokenLen 100
#define keywordsCount 10
#define operatorCount 12
// #define digit [0-9]
// #define digits digit+
// #define optDecimal \.digits
// #define optExp [Ee][+-]?digits
// #define NUMBER [+-]?digits.optDecimal.optExp

const char* keywords[keywordsCount] = {"int", "main", "float", "endl", "using", "string", "cout", "fstream", "while", "return"};
const char* operators[operatorCount] = {"<", ">", "<<", ">>", "+", "-", "=", "==", "/", "*", "++", "--"};
// char *test1[3]= {"arrtest","ao", "123"};

bool isKeyword(char*, int);
bool isNumber(char*, int);
bool isIdentifier(char*);
bool isOperator(char*, int);
char* scanWord(FILE*);

using namespace std;

int main(int argc, char* argv[]){
    if(argc!=2){
        printf("Usage: ./scan program.txt\n");
        return 1;
    }
    FILE* fptr = fopen(argv[1], "r");
    if(fptr==NULL){
        printf("Error getting file\n");
        return 1;
    }
    char word[tokenLen];
    char c;
    int i=0;
    while(fread(&c, sizeof(char), 1, fptr)){
        // if(c==' ' || c=='\n' || c=='\0' || c=='(' || c== ')' || c=='{' || c=='}' || c=='[' || c==']' || c==';' || c==',' || c=='.' || c=='=' || c== '<' || c=='>' || c=='"' || c=='\''){
		if(c==' ' || c=='\n' || c=='\0' || c=='(' || c== ')' || c=='{' || c=='}' || c=='[' || c==']' || c==';' || c==',' || c=='.' || c=='"' || c=='\'' || c=='+' || c=='-' || c=='*' || c=='/' || c=='='){
            // check for token
            word[i]='\0';
			if(c=='"'){
				std::stringstream ss;
				ss << "\"";
				while(fread(&c, sizeof(char), 1, fptr) && c!='"'){
					ss << c;
				}
				ss << "\"";
				std::cout << ss.str() << "\tis an identifier\n";
				i=0;
				continue;
			}
			if(c=='\''){
				std::stringstream ss;
				ss << "'";
				while(fread(&c, sizeof(char), 1, fptr) && c!='\''){
					ss << c;
				}
				ss << "'";
				std::cout << ss.str() << "\tis an identifier\n";
				i=0;
				continue;
			}
			if(i>0){
            	// printf("Checking... %s\n", word);
				if(isKeyword(word, i)){
					printf("%20s is a keyword\n", word);
				}
				else if(isOperator(word, i)){
					printf("%20s is a operator\n", word);
				}
				else if(isNumber(word, i)){
					printf("%20s is a number\n", word);
				}
				else{
					printf("%20s is a identifier\n", word);
				}
            	i=0;
			}
			if(c=='+' || c=='-' || c=='*' || c=='/' || c=='='){
				printf("%20c is an operator\n", c);
				i=0;
			}
        }
        else if( (c<='9' && c>='0') || (c <= 'z' || c >= 'a') || (c <= 'Z' && c <= 'A')){
            word[i]=c;
            ++i;
        }
    }
	return 0;
}

char* scanWord(FILE* fptr){
    char *c = (char*)malloc(sizeof(char)*tokenLen);
    char k;
    int i=0;
    while(fread(&k, sizeof(char), 1, fptr)!=EOF){
        if(i<tokenLen && k!=' ' && k!='\n'){
            c[i]=k;
            ++i;
        }
        else{
            c[i]='\0';
            break;
        }
    }
    return c;
}

bool isKeyword(char* word, int len){
	for(int i=0; i<keywordsCount; ++i){
	// printf("%s %s\n", word, keywords[i]);
		bool match = true;
		for(int j=0; j<len; ++j){
			if(word[j]!=keywords[i][j]) match=false;
		}
		if(match) return true;
	}
	return false;
}

bool isOperator(char* word, int len){
	for(int i=0; i<operatorCount; ++i){
	// printf("%s %s\n", word, keywords[i]);
		bool match = true;
		for(int j=0; j<len; ++j){
			if(word[j]!=operators[i][j]) match=false;
		}
		if(match) return true;
	}
	return false;
}

bool isNumber(char* word, int len){
	// int dot=0;
	for(int i=0; i<len; ++i){
		// if(word[i]=='.') ++dot;
		if(word[i]<'0' || word[i]>'9') return false;
	}
	// return (dot>1) ? false : true;
	return true;
}