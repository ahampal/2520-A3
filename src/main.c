#include "HashTableAPI.h"

/**
 * Function that takes a string and returns an equivalent integer value (hash)
 * @param size of table as type size_t
 * @param pointer of char type that points to string that is to be hashed
 * @return integer value
 */
int hashFunc(size_t size, char *key);

/**
 * Function that deletes the data within a node
 * @param pointer of type void that points to data that is to be deleted
 */
void deleteWord(void *data);

/**
 * Function to print the data within a node
 * @param pointer of type void that points to data that is to be printed
 */
void printNode(void *toBePrinted);

/**
 * Function that checks if input string is a word (ie. does not contain spaces
 * or invalid characters)
 * @return returns integer value 1 if input string is invalid, or returns
 * integer value 0 if valid
 */
int checkInput(char *file);

/**
 * Function that removes the newline character at the end of input string and
 * replaces it with a null terminator
 * @param pointer of type char that points to input string
 * @return pointer of type char that points to input string with newline replaced
 */
char *removeNewLine(char *file);

/**
 * Main function implementation that runs the command loop and calls the necessary
 * functions based on user input
 * @param integer value that represents the command line arguement count
 * @param pointer to pointer of type char that contains the command line arguements
 * @return 0
 */
int main(int argc, char ** argv) {
	HTable *dictionaryTable;
	FILE *fp;
	int count;
	char *file;
	char character;
	int i;
	int quit;
	int usrIn;
	int flag;
	char *input;
	FILE *sCF;
	void *ptr;
	int wrongWordCount;
	int rightWordCount;
	file = malloc(sizeof(char) * 45);
	printf("File is: %s\n", argv[argc - 1]);
	if(argc > 1)
	{
		fp = fopen( argv[argc - 1], "r" );
	}
	else
	{
		return 0;
	}
	if(fp == NULL) 
	{
		printf("Cannot find file. Exiting program.\n");
		return 0;
	}
	count = 0;
	while(!feof(fp))
	{
	  character = fgetc(fp);
	  if(character == '\n')
	  {
		count++;
	  }
	}
	rewind(fp);
	dictionaryTable = createTable(count, &hashFunc, &deleteWord, &printNode);
	i = 0;
	while( !feof(fp) ) 
	{
		fgets(file, 45, fp);
		file = removeNewLine(file);
		if(strcmp(file, "") != 0) {
			insertDataInMap(dictionaryTable, file);
		}
		file += 1;
		file = malloc(sizeof(char) * 45);
		i++;
	}
	file += 1;
	file = malloc(sizeof(char) * 2);
	quit = 0;
	while(quit == 0) {
		flag = -1;
		printf("1) Add a word to Dictionary\n");
		printf("2) Remove a word from Dictionary\n");
		printf("3) Spell Check a file\n");
		printf("4) Show Dictionary Words\n");
		printf("5) Quit\n");
		printf("Select Option Number: ");
		fgets(file, 2, stdin);
		printf("\n");
		usrIn = atoi(file);
		switch(usrIn) {
			case 1:
				input += 1;
				input = malloc(sizeof(char) * 45);
				printf("Enter word to add to dictionary: ");
				fgets(input, 45, stdin);
				fgets(input, 45, stdin);
				input = removeNewLine(input);
				flag = checkInput(input);
				if(flag == 0) {
					insertDataInMap(dictionaryTable, input);
					printf("Added %s.\n", input);
				}
				else {
					printf("Could not add %s, check to ensure %s does not contain any invalid characters or spaces\n", input, input);
				}
				break;
			case 2:
				input += 1;
				input = malloc(sizeof(char) * 45);
				printf("Enter word to remove from dictionary: ");
				fgets(input, 45, stdin);
				fgets(input, 45, stdin);
				input = removeNewLine(input);
				flag = checkInput(input);
				if(flag == 0) {
					printf("Successfully removed any instances of %s in dictionary\n", input);
					removeData(dictionaryTable, input);
				}
				else {
					printf("Could not remove %s, check to ensure %s does not contain any invalid characters or spaces\n", input, input);
				}
				break;
			case 3:
				wrongWordCount = 0;
				rightWordCount = 0;
				input += 1;
				input = malloc(sizeof(char) * 45);
				printf("Enter file path: ");
				fgets(input, 45, stdin);
				fgets(input, 45, stdin);
				input = removeNewLine(input);
				sCF = fopen( input, "r" );
				if(sCF == NULL) 
				{
					printf("Cannot find file %s. Retry.\n", input);
				}
				else {
					printf("File processed by Spell Check %s\n", input);
					printf("\n");
					while( !feof(sCF) ) {
						file += 1;
						file = malloc(sizeof(char) * 45);
						fgets(file, 45, sCF);
						file = removeNewLine(file);
						ptr = lookupData(dictionaryTable, file);
						if(ptr == NULL) {
							printf("%s was not found in the dictionary\n", file);
							wrongWordCount++;
						}
						else {
							rightWordCount++;
						}
						ptr = NULL;
					}
					printf("\n");
					printf("Summary:\n");
					printf("Correctly spelt words: %d\n", rightWordCount);
					printf("Incorrectly spelt words: %d\n", wrongWordCount);
					printf("\n\nPress enter key to return to main menu\n\n");
					fgets(file, 2, stdin);	
				}	
				break;
			case 4:
				printf("<Index>:<Key>:<Word>\n");
				Node *row;
				for(int g = 0; g < dictionaryTable->size; g++){
					row = dictionaryTable->table[g];
					while(row != NULL) {
						printf("%d:%s:", dictionaryTable->hashFunction(dictionaryTable->size, row->key), row->key);
						dictionaryTable->printNode(row->data);
						row = row->next;
					}
				}
				fgets(file, 2, stdin);
				break;
			case 5:
				quit = 1;
				printf("Exiting program. Good Bye.\n");
				break;
			default:
				printf("Invalid input. Retry.\n");
				break;
		}
		printf("\n");
	}		
	return 0;
}

/**
 * Function that takes a string and returns an equivalent integer value (hash)
 * @param size of table as type size_t
 * @param pointer of char type that points to string that is to be hashed
 * @return integer value
 */
int hashFunc(size_t size, char *key) {
	int val;
	int i;
	i = 0;
	val = 0;
	while(val < INT_MAX && i < strlen(key)) {
		val += tolower(*(key + i));
		i++;
	}
	return val % size;
}

/**
 * Function that deletes the data within a node
 * @param pointer of type void that points to data that is to be deleted
 */
void deleteWord(void *data) {
	free(data);
	return;
}

/**
 * Function to print the data within a node
 * @param pointer of type void that points to data that is to be printed
 */
void printNode(void *toBePrinted) {
	printf("%s\n", (char *)toBePrinted);
	return;
}

/**
 * Function that checks if input string is a word (ie. does not contain spaces
 * or invalid characters)
 * @return returns integer value 1 if input string is invalid, or returns
 * integer value 0 if valid
 */
int checkInput(char *file) {
	for(int g = 0; g < strlen(file); g++) {
		switch(*(file + g)) {
			case ' ':
			case ',':
			case '{':
			case '}':
			case '!':
			case '@':
			case '#':
			case '$':
			case '%':
			case '^':
	      	case '&':
			case '*':
			case '(':
			case ')':
			case '-':
			case '+':
			case '=':
			case '[':
			case ']':
			case '\\':
			case '<':
			case '>':
			case '/':
			case '|':
			case '~':
			case '`':
			case '.':
				printf("Invalid input. Retry.\n");
				return 1;
				break;
			default:
				break;
			}
	}
	return 0;
}

/**
 * Function that removes the newline character at the end of input string and
 * replaces it with a null terminator
 * @param pointer of type char that points to input string
 * @return pointer of type char that points to input string with newline replaced
 */
char *removeNewLine(char *file) {
	for(int i = 0; i < strlen(file); i++) {
		if(*(file + i) == '\n') {
			*(file + i) = '\0';
		}
	}
	return file;
}	
