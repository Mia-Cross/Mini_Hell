#include "../include/minishell.h"

void	print_struct(t_data *data)
{
	if (data->line)
		printf("data->line = {%s}\n", data->line);
	if (data->multi)
		print_multi(data);
	if (data->cmd)
		print_cmd(data);
	if (data->fd)
		print_fd_list(data->fd);
}

void print_multi(t_data *data)
{
	int i;

	i = -1;
	while (data->multi[++i])
		printf("data->multi[%d] = {%s}\n", i, data->multi[i]);
}

void print_cmd(t_data *data)
{
	int i;

	i = -1;
	while (data->cmd[++i])
		printf("data->cmd[%d] = {%s}\n", i, data->cmd[i]);
}

void print_fd_list(t_list *fd)
{
	int i;
	t_list *head;

	i = 0;
	head = fd;
//	printf("tentative de print_list_fd\n");
	while (head)
	{
		printf("fd[%d] = {%d}\n", i++, *(int *)head->content);
		head = head->next;
	}
}

int is_pipe(char *str, int i)
{
	return (str[i] == '|' && (i == 0 || str[i - 1] != '\\') && 
	!between_quotes(str, i));
}