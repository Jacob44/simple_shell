#include "shell.h"
char *addis_read_line(void);
char **addis_tokenize_line(char *line);
void addis_execute(char **parsed);
/**
 * main - the main program to run the whole shell.
 * @ac: number of commands.
 * @av: commands.
 *
 * Return: 1 for success and 0 otherwise.
 */
int main(int ac, char **av)
{
	char *buffer = NULL;
	char **command = NULL;
	size_t buf_size = 0;
	int i = 0;
	int int_mode;
	int status;

	while (1)
	{
		int_mode = isatty(STDIN_FILENO);
		if (int_mode == 1)
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		buffer = addis_read_line();
		command = addis_tokenize_line(buffer);
		/*
		 * if (strcmp(command[0], "exit") == 0)
		 * addis_exit(command);
		*/
		addis_execute(command);
		free(buffer);
		free(command);
	}
	return (EXIT_SUCCESS);
}
/**
 * addis_read_line - read the input.
 *
 * Return: the written buffer room
 */
char *addis_read_line(void)
{
	char *line = NULL;
	size_t buf_size = 0;
	ssize_t textread = 0;

	textread = getline(&line, &buf_size, stdin);

	if (textread == EOF)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(line);
		exit(EXIT_SUCCESS);
	}
	if (textread == -1)
	{
		perror("readline problem");
		exit(EXIT_FAILURE);
	}
	return (line);
}

/**
 * addis_tokenize_line - parse the input text as per the delimiter.
 * @line: input line.
 *
 * Return: the parsed the input text.
 */
char **addis_tokenize_line(char *line)
{
	int counter = 0, bufsize = ADDIS_TOK_BUFSIZE;
	char **toks = malloc(bufsize * sizeof(char *));
	char *delim = " \t\r\n\a";
	char *tok;

	if (toks == NULL)
	{
		exit(EXIT_FAILURE);
	}
	tok = strtok(line, delim);
	while (tok != NULL)
	{
		toks[counter] = strdup(tok);
		counter++;
		tok = strtok(NULL, delim);
	}
	toks[counter] = NULL;
	return (toks);
}
/**
 * addis_execute - execute the commands.
 * @parsed: parse the command
 *
 * Return: nothing
 */
void addis_execute(char **parsed)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("\nForking failed..");
		return;
	}
	else if (!pid)
	{
		/*if (execvp(parsed[0], parsed) < 0)*/
		printf("./shell: No such file or directory\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		return;
	}
}
