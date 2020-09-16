#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int retCode = 0;

int echo(int argc, char* argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
	}
	return argc - 1;
}

int retcode(int argc, char* argv[])
{
	printf("%d\n", retCode);
	return 0;
}

void parse(int argc, char* argv[], char* input)
{
	char* nextCommand;
	char* nextWord;
	char* parsedInput = strtok_r(input, ";\n", &nextCommand);
	while (parsedInput != NULL)
	{
		char* words = strtok_r(parsedInput, " ", &nextWord);
		argc = 0;
		while (words != NULL)
		{
			argv[argc] = words;
			argc++;
			words = strtok_r(NULL, " ", &nextWord);
		}

		if (strcmp(argv[0], "echo") == 0)
			retCode = echo(argc, argv);
		else if (strcmp(argv[0], "retcode") == 0)
			retcode(argc, argv);
		else
			printf("Unknown command.\n");

		parsedInput = strtok_r(NULL, ";\n", &nextCommand);
	}
}

int main(int argc, char* argv[])
{
	char* input[256];
	
	while (fgets(input, 256, stdin) != NULL)
		parse(argc, argv, input);
	
	return 0;
}