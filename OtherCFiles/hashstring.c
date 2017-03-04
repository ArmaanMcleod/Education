#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMCHAR 256

char *remove_dups(char *string);

int main(void) {
	char string[NUMCHAR], temp;
	char *result;
	size_t len, i;
	int ch;

	printf("Enter char array size of string(counting with backslash 0): \n");
	if (scanf("%zu", &len) != 1) {
		printf("invalid length entered\n");
		exit(EXIT_FAILURE);
	}
	
	ch = getchar();
	while (ch != '\n' && ch != EOF);

	if (len >= NUMCHAR) {
		printf("Length specified is longer than buffer size of %d\n", NUMCHAR);
		exit(EXIT_FAILURE);
	}

	printf("Enter string you wish to remove duplicates from: \n");
	for (i = 0; i < len; i++) {
		if (scanf("%c", &temp) != 1) {
			printf("invalid character entered\n");
			exit(EXIT_FAILURE);
		}
		if (isspace(temp)) {
			break;
		}
		string[i] = temp;
	}
	string[i] = '\0';

	printf("Original string: %s Length: %zu\n", string, strlen(string));

	result = remove_dups(string);

	printf("Duplicates removed: %s Length: %zu\n", result, strlen(result));

	return 0;
}

char *remove_dups(char *str) {
  int hash[NUMCHAR] = {0};
  size_t count = 0, i;
  char temp;

  for (i = 0; str[i]; i++) {
  	temp = str[i];
  	if (hash[(unsigned char)temp] == 0) {
  		hash[(unsigned char)temp] = 1;
  		str[count++] = str[i];
  	}
  }

  str[count] = '\0';

  return str;
}