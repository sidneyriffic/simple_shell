#include "shell.h"
/**
 *
 *
 */
char *_strtok(char *str, const char *delim)
{
	static int pos = 0;
	int i = 0;
	char *tmp_str;

	if (str == NULL)
		return ();
	if (pos != 0 || str[pos] == *delim) // if initial spot is delim, move
		pos++; //increment to get off delim from previous call//
	tmp_str = str + pos; // increment str to spot left off at//
	while (*tmp_str)
	{
		if (*tmp_str != *delim)
		{
			buffer[i] = *tmp_str; //copy tmp string to buffer//
			i++; //increment everythin one place//
			tmp_str++;
			pos++;
		}
		else //if match is found//
		{
			break;
		}
	}
	return (tmp_str);
}

int main(void)
{
	char a[] = "; apple ; pie  ; tastes good";
	char *delim = ";";
	char *test1;
	char *test2;

	printf("testing\n");

	test2 = _strtok(a, delim);
	while (*test2)
	{
	   printf("mine: %s\n",test2);
        test2 = _strtok(a, delim);
	}

	return(0);
}
