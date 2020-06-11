/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:49:51 by schene            #+#    #+#             */
/*   Updated: 2020/06/11 15:08:00 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	g_ctrl_c;
static int	g_ctrl_q;

static void			ctr_c(int num)
{
	(void)num;
	g_ctrl_c = 1;
	ft_putchar_fd('\n', 1);
	if (g_child_pid == 0)
		ft_putstr_fd("minishell>> ", 2);
}

static void			ctr_q(int num)
{
	(void)num;
	if (g_child_pid > 0)
	{
		g_ctrl_q = 1;
		kill(g_child_pid, SIGQUIT);
		ft_putstr_fd("quit (core dumped)\n", 1);
	}
}

static t_data		*init_data(char **main_env)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->env = create_env(main_env);
	data->cmd = NULL;
	data->fd = NULL;
	data->line = NULL;
	data->multi = NULL;
	data->pipe = NULL;
	data->dir = ft_strdup(var_value(data->env, "$PWD"));
	data->status = 0;
	data->input = 0;
	return (data);
}

void print_double_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i] != NULL)
	{
		printf("tab[%d] = {%s}\n", i, tab[i]);
	}
}

static void			exec_shell(t_data *data, char *line)
{
	int		i;
	int		j;
	int		com;
	char	*tmp;

	i = -1;
	if ((com = contains_comment(line)) && com != -1)
	{
		tmp = ft_substr(line, 0, com);
		free(line);
		line = tmp;
	}
	data->multi = split_quotes(line, data, ';');
	free(line);
	line = NULL;
	if (data->multi)
	{
		while (data->multi[++i])
		{
			data->pipe = split_quotes(data->multi[i], data, '|');
			if (data->pipe)
			{
				print_double_tab(data->pipe);
				j = -1;
				while (data->pipe[++j])
				{
					printf("data->pipe[%d] = {%s}\n", j, data->pipe[j]);
					data->line = ft_strtrim(data->pipe[j], " \n\t");
					printf("data->line = {%s}\n", data->line);
					exec_line(data);
				}
				ft_free(data->pipe);
				data->pipe = NULL;
				close_fd(data);
			}
		}
		ft_free(data->multi);
		data->multi = NULL;
	}
}

int					main(int ac, char **av, char **env)
{
	char	*line;
	t_data	*data;

	(void)ac;
	(void)av;
	g_ctrl_c = 0;
	ft_putstr_fd("minishell>> ", 2);
	signal(SIGINT, &ctr_c);
	signal(SIGQUIT, &ctr_q);
	data = init_data(env);
	while (get_next_line(0, &line) > 0)
	{
		if (g_ctrl_c)
			data->status = 130;
		if (g_ctrl_q)
			data->status = 131;
		g_ctrl_c = 0;
		g_ctrl_q = 0;
		exec_shell(data, line);
		ft_putstr_fd("minishell>> ", 2);
	}
	if (line)
		exec_shell(data, line);
	builtin_exit(data, 1);
	return (0);
}

