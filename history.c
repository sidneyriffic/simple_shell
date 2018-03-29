#include "shell.h"
#include "history.h"
/**
 * gethistory - gets the history list
 * Return: 0 uposon success
 */
HistList **gethistory()
{
	static HistList *hlist;
	return (&hlist);
}
/**
 * sethist - set hist and value
 * @cmd: command
 * Return: 0 upon success
 */
int sethist(char *cmd)
{
	HistList **hlistroot = gethistory();
	HistList *hlist = *hlistroot;
	HistList *ptr = hlist, *new;

	if (hlist == NULL)
	{
		new = malloc(sizeof(HistList));
		if (new == NULL)
			return (-1);

		new->cmd = _strdup(cmd);
		new->next = NULL;
		*hlistroot = new;
		return (0);
	}
	while (ptr->next != NULL)
		ptr = ptr->next;

	new = malloc(sizeof(HistList));
	if (new == NULL)
		return (-1);
	new->cmd = _strdup(cmd);
	new->next = NULL;
	ptr->next = new;
	return (0);
}
/**
 * print_listint - prints all elements of listint
 * @h: pointer to first node of list
 * Return: num of elements
 */
int print_hist()
{
	HistList **hlistroot = gethistory();
	HistList *h = *hlistroot;
	int i;
	int len, numlen;
	char *s, *num;

	i = 0;
	while (h != NULL)
	{
		len = _strlen(h->cmd);
		s = h->cmd;
		num = itos(i);
		numlen = _strlen(num);
		write(1, num, numlen);
		write(1, s, len);
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * init_hist - initialize history
 * Return
 */
int init_hist()
{
	HistList **hlistroot = gethistory();
	HistList *hlist = *hlistroot;
	HistList *ptr = hlist, *new;
	char *line;
	int len;
	int fd;
	char *file = "/home/gjdame/.simple_shell_history";

	fd = open(file, O_RDWR);
		if (fd == -1)
			return (-1);
	line = malloc(100);
	while((len = _getline(&line, fd)) != 0)
	{
		if (hlist == NULL)
		{
			new = malloc(sizeof(HistList));
			if (new == NULL)
				return (-1);

			new->cmd = _strdup(line);
			new->next = NULL;
			*hlistroot = new;
		}

		while (ptr->next != NULL)
			ptr = ptr->next;

		new = malloc(sizeof(HistList));
		if (new == NULL)
			return (-1);
		new->cmd = _strdup(line);
		new->next = NULL;
		ptr->next = new;
	}
	return (0);
}

/**
 * exit_hist - exit history and write to file
 * Return: 1 on success
 */
int exit_hist()
{
	int fd;
	char *file = ".simple_shell_history";
	int i, len, w;
	char *str;

	HistList **hlistroot = gethistory();
	HistList *hlist = *hlistroot;
	HistList *ptr = hlist;

	/*file = tildeexpand(file);*/
	fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0600);
	if (fd == -1)
		return (-1);
	while (ptr != NULL)
	{
		len = _strlen(ptr->cmd);
		printf("copying\n");
		str = ptr->cmd;
		write(fd, str , len);
		ptr = ptr->next;
	}

	close(fd);
	ptr = hlist;

	while (hlist != NULL)
	{
		ptr = hlist->next;
		free(hlist->cmd);
		free(hlist);
		hlist = ptr;
	}

	return(1);
}
