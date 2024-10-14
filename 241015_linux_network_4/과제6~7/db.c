#include "db.h"
#include <stdlib.h>

typedef struct _trie {
 	struct _trie* next[128];
	char* value;
} trie;

trie* head;

void dbInit(){
	head = malloc(sizeof(trie));
}

void dbSave(char* key, char* value){
	trie* cur = head;
	while(*key){
		if(cur->next[*key] == NULL)
			cur->next[*key] = malloc(sizeof(trie));
		cur = cur->next[*key];
		++key;
	}
	cur->value = value;
}

char* dbRead(char* key){
	trie* cur = head;
	while(*key){
		if(cur->next[*key] == NULL) 
			return NULL;
		cur = cur->next[*key];
		++key;
	}
	return cur->value;
}

