#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void thehelper(char *haha)
{
        char *hey;

        hey = haha;
        printf("%s\n", hey);
        free(hey);
}

int main(void)
{
	char *string = NULL, *something = "something something";

	string = malloc(sizeof(char) * (strlen(something) + 1));
	strcpy(string, something);
	thehelper(string);
	string = something;
	something = NULL;
	printf("%s\n", string);
	return (0);
}
