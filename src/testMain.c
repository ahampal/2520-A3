#include "HashTableAPI.h"

/**
 * Function that takes a string and returns an equivalent integer value (hash)
 * @param size of table as type size_t
 * @param pointer of char type that points to string that is to be hashed
 * @return integer value
 */
int hashingFunction(size_t size, char *key);

/**
 * Function that deletes the data within a node
 * @param pointer of type void that points to data that is to be deleted
 */
void delete(void *data);

/**
 * Function to print the data within a node
 * @param pointer of type void that points to data that is to be printed
 */
void print(void *toBePrinted);

/**
 * Main function implementation that tests the implementation of the Hash API
 * @param integer value that represents the command line arguement count
 * @param pointer to pointer of type char that contains the command line arguements
 * @return 0
 */
int main(int argc, char ** argv) {
	HTable *testTable;
	Node *newNode;
	char **input = malloc(sizeof(char *) * 10);
	void *ptr;
	for(int i = 0; i < 10; i++) {
		*(input + i) = malloc(sizeof(char) * 10);
	}
	printf("TESTING: createTable\n");
	printf("creating table of size 10 to store country names\n");
	testTable = createTable(10, &hashingFunction, &delete, &print);
	printf("Passed\n\n");
	printf("TESTING: createNode\n");
	printf("creating Node named newNode\n");
	*input = malloc(sizeof(char) * 10);
	strcpy(*input, "key");
	newNode = createNode(*input, *input);
	testTable->destroyData(newNode->data);
	free(newNode);
	printf("Passed\n\n");
	printf("TESTING: insertDataInMap\n");
	printf("inserting following names into table using insertDataInMap\n");
	printf("Canada\n");
	strcpy(*(input + 1), "Canada");
	insertDataInMap(testTable, *(input + 1));
	printf("USA\n");
	strcpy(*(input + 2), "USA");
	insertDataInMap(testTable, *(input + 2));
	printf("Brazil\n");
	strcpy(*(input + 3), "Brazil");
	insertDataInMap(testTable, *(input + 3));
	printf("Belgium\n");
	strcpy(*(input + 4), "Belgium");
	insertDataInMap(testTable, *(input + 4));
	printf("China\n");
	strcpy(*(input + 5), "China");
	insertDataInMap(testTable, *(input + 5));
	printf("Passed\n\n");
	printf("TESTING: insertData\n");
	printf("inserting following names into table using insertData\n");
	printf("Germany\n");
	strcpy(*(input + 6), "Germany");
	insertData(testTable, *(input + 6), *(input + 6));
	printf("India\n");
	strcpy(*(input + 7), "India");
	insertData(testTable, *(input + 7), *(input + 7));
	printf("Passed\n\n");
	printf("TESTING: printTable\n");
	printf("EXPECTED:\n");
	printf("Brazil\nUSA\nChina\nGermany\nIndia\nCanada\nBelgium\n");
	printf("OUTPUT:\n");
	printTable(testTable);
	printf("Passed\n\n");
	printf("TESTING: lookupData\n");
	printf("EXPECTED:\n");
	printf("Belgium\n");
	printf("OUTPUT:\n");
	ptr = lookupData(testTable, *(input + 4));
	testTable->printNode(ptr);
	printf("Passed\n\n");
	printf("TESTING: removeData\n");
	printf("removing: %s\n", *(input + 2));
	printf("EXPECTED:\n");
	printf("Brazil\nChina\nGermany\nIndia\nCanada\nBelgium\n");
	printf("OUTPUT:\n");
	removeData(testTable, *(input + 2));
	printTable(testTable);
	printf("Passed\n\n");
	return 0;
}

/**
 * Function that takes a string and returns an equivalent integer value (hash)
 * @param size of table as type size_t
 * @param pointer of char type that points to string that is to be hashed
 * @return integer value
 */
int hashingFunction(size_t size, char *key) {
	int val;
	int i;
	i = 0;
	val = 0;
	while(val < INT_MAX && i < strlen(key)) {
		val += *(key + i);
		i++;
	}
	return val % size;
}

/**
 * Function that deletes the data within a node
 * @param pointer of type void that points to data that is to be deleted
 */
void delete(void *data) {
	free(data);
	return;
}

/**
 * Function to print the data within a node
 * @param pointer of type void that points to data that is to be printed
 */
void print(void *toBePrinted) {
	printf("%s\n", (char *)toBePrinted);
	return;
}
	
