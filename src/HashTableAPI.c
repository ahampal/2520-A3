#include "HashTableAPI.h"

/**Function to point the hash table to the appropriate functions. Allocates memory to the struct and table based on the size given.
*@return pointer to the hash table
*@param size size of the hash table
*@param hashFunction function pointer to a function to hash the data
*@param destroyData function pointer to a function to delete a single piece of data from the hash table
*@param printNode function pointer to a function that prints out a data element of the table
**/
HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, char *key),void (*destroyData)(void *data),void (*printNode)(void *toBePrinted)) {
	HTable *t;
	t = malloc(sizeof(HTable));
	t->table = malloc(sizeof(Node *) * size);
	t->size = size;
	t->destroyData = destroyData;
	t->hashFunction = hashFunction;
	t->printNode = printNode;
	return t;
}

/**Function for creating a node for the hash table.
*@pre Node must be cast to void pointer before being added.
*@post Node is valid and able to be added to the hash table
*@param key integer that represents the data (eg 35->"hello")
*@param data is a generic pointer to any data type.
*@return returns a node for the hash table
**/
Node *createNode(char *key, void *data) {
	Node *n;
	n = malloc(sizeof(Node));
	n->key = key;
	n->data = data;
	n->next = NULL;
	return n;
}

/** Deletes the entire hash table and frees memory of every element.
*@pre Hash Table must exist.
*@param hashTable pointer to hash table containing elements of data
**/
void destroyTable(HTable *hashTable) {
	Node *row;
	Node *tmp;
	if(hashTable == NULL) {
		return;
	}
	for(int i = 0; i < hashTable->size; i++) {
		row = hashTable->table[i];
		if(row != NULL) {
			while(row != NULL) {
				tmp = row;
				row = row->next;
				hashTable->destroyData(tmp->data);
				free(tmp);
			}
		}
	}
	free(hashTable->table);
	free(hashTable);
	return;
}

/**Inserts a Node in the hash table.
*@pre hashTable type must exist and have data allocated to it
*@param hashTable pointer to the hash table
*@param key integer that represents the data (eg 35->"hello")
*@param data pointer to generic data that is to be inserted into the list
**/
void insertData(HTable *hashTable, char *key, void *data) {
	Node *newNode;
	int hashKey;
	Node *temp;
	newNode = createNode(key, data);
	if(hashTable == NULL) {
		return;
	}
	hashKey = hashTable->hashFunction(hashTable->size, key);
	if(hashTable->table[hashKey] == NULL) {
		hashTable->table[hashKey] = newNode;
	}
	else {
		temp = hashTable->table[hashKey];
		while(temp->next != NULL && strcmp(temp->key, key) != 0) {
			temp = temp->next;
		}
		if(strcmp(temp->key, key) == 0) {
			temp->data = newNode->data;
		}
		else {
			temp->next = newNode;
		}
	}
	return;
}

/**Function to remove a node from the hash table 
 *@pre Hash table must exist and have memory allocated to it
 *@post Node at key will be removed from the hash table if it exists.
 *@param hashTable pointer to the hash table struct
 *@param key integer that represents a piece of data in the table (eg 35->"hello")
 **/
void removeData(HTable *hashTable, char *key) {
	Node *row;
	Node *temp;
	Node *prev;
	int hashKey;
	if(hashTable == NULL) {
		return;
	}
	hashKey = hashTable->hashFunction(hashTable->size, key);
	if(hashTable->table[hashKey] == NULL) {
		return;
	}
	row = hashTable->table[hashKey];
	if(strcmp(key, row->key) == 0) {
		prev = row;
		row = row->next;
		hashTable->destroyData(prev->data);
		hashTable->table[hashKey] = row;
		free(prev);
	}
	else {
		while(row != NULL && strcmp(row->key, key) != 0) {
			prev = row;
			row = row->next;
		}
		if(row != NULL) {
			temp = row;
			prev->next = row->next;
			hashTable->destroyData(temp->data);
			free(temp);
		}
	}
	return;
}

/**Function to return the data from the key given.
 *@pre The hash table exists and has memory allocated to it
 *@param hashTable pointer to the hash table containing data nodes
 *@param key integer that represents a piece of data in the table (eg 35->"hello")
 *@return returns a pointer to the data in the hash table. Returns NULL if no match is found.
 **/
void *lookupData(HTable *hashTable, char *key) {
	Node *row;
	char *tmpOne;
	char *tmpTwo;
	if(hashTable == NULL) {
		return NULL;
	}
	int hashKey = hashTable->hashFunction(hashTable->size, key);
	if(hashTable->table[hashKey] == NULL) {
		return NULL;
	}
	row = hashTable->table[hashKey];
	tmpOne = malloc(sizeof(char) * strlen(row->key));
	tmpTwo = malloc(sizeof(char) * strlen(key));
	strcpy(tmpOne, row->key);
	strcpy(tmpTwo, key);
	tmpOne = toLowerCase(tmpOne);
	tmpTwo = toLowerCase(tmpTwo);
	if(strcmp(tmpOne, tmpTwo) == 0) {
		return row->data;
	}
	while(row != NULL && strcmp(tmpOne, tmpTwo) != 0) {
		row = row->next;
		if(row != NULL) {
			strcpy(tmpOne, row->key);
			tmpOne = toLowerCase(tmpOne);
		}
	}
	if(row != NULL) {
		return row->data;
	}
	free(tmpOne);
	free(tmpTwo);
	return NULL;
}

/** THIS FUNCTION IS NOT MANDATORY, users call this function to insert a Node in the hash table.
* It's meant as a wrapper for insertData so the users don't need to generate the key when adding.
*@pre hashTable type must exist and have data allocated to it
*@param hashTable pointer to the hash table
*@param data pointer to generic data that is to be inserted into the list
**/
void insertDataInMap(HTable *hashTable, void *data) {
	insertData(hashTable, (char *)data, data);
}

/**
 * Function to print data of every node in the table
 * @param pointer of type HTable
 */	 
void printTable(HTable *hashTable) {
	Node *row;
	for(int i = 0; i < hashTable->size; i++){
		row = hashTable->table[i];
		while(row != NULL) {
			hashTable->printNode(row->data);
			row = row->next;
		}
	}
	return;
}

/**
 * Funcion that takes string and transforms it to a lower case type
 * @param pointer of type char
 * @return pointer of type char that points to the lower case version of input string
 */
char *toLowerCase(char *input) {
	for(int i = 0; i < strlen(input); i++) {
		*(input + i) = tolower(*(input +i));
	}
	return input;
}	
		
	
