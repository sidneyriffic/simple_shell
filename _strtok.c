#include "shell.h"
char *_strtok(char *str, char *delim)
{
	static char *saved_string;
	int i;
	int j;
	char *tmp_str;
	char *tmp_delim;

	//if NULL passed in str becomes where saved string left off
	if (str == 0)
		str = saved_string;
	if (str == 0)
		return (0);

	tmp_str = str;
	tmp_delim = delim;
	//skip initial delimiters//
	i = 0;
	while (tmp_str[i] != 0)
	{
		j = 0;
		while (delim[j] != 0)
		{
			if (tmp_str[i] == tmp_delim[j])
				break;
			j++;
		}
		if (tmp_delim[j] == 0)
			break;
		i++;
	}
	str = str + i;
	if (*str == 0)
	{
		saved_string = str;
		return(0);
	}
	//start new token//
	tmp_str = tmp_str + i;

	i = 0;
	while (tmp_str[i] != 0)
	{
		j = 0;
		while (tmp_delim[j] != 0)
		{
			if (tmp_str[i] == tmp_delim[j])
				break;
			j++;
		}
		if (tmp_delim[j] != 0)
			break;
		i++;
	}
	saved_string = tmp_str;
	if (tmp_str[i] != 0)
	{
		//saves string for next call
		saved_string = (saved_string + i + 1);
		tmp_str[i] = '\0';
	}
	else
	{
		saved_string = '\0'; //if end of input string.
	}
	return (tmp_str);
}

int main(void)
{
	char a[] = ";apple ;; pie  - tastes good";
	char b[] = ";apple ;; pie  - tastes good";
	char delim[] = " ;-";
	char *test1;
	char *test2;

	printf("testing strtok\n");
	test1 = strtok(b, delim);
	printf("strtok: %s\n", test1);

	while (test1 != NULL)
	{
		test1 = strtok(NULL, delim);
		printf("strtok: %s\n", test1);
	}

	printf("testing _strtok\n");
	test2 = _strtok(a, delim);
       	printf("_strtok: %s\n", test2);
	while (test2 != NULL)
	{
		test2 = _strtok(NULL , delim);
		printf("_strtok: %s\n", test2);
	}
	return(0);
}
