/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 16:49:51 by schene            #+#    #+#             */
/*   Updated: 2020/05/06 19:29:52 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free(char **cmd, char *line)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
	}
	free(cmd);
	cmd = NULL;
	free(line);
	line = NULL;
}

char	*ft_getenv(char **env, char *elem)
{
	char *ret;
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], elem, ft_strlen(elem)))
		{
			ret = ft_strchr(env[i], '=');
			return(ret + 1);
		}
	}
	return (NULL);
}

void	get_path(char **env, char **cmd)
{
	struct stat	*buf;
	char		*path;
	char		**path_tab;
	char		*bin;
	int			i;
	
	path = ft_strdup(ft_getenv(env, "PATH"));
	bin = NULL;
	if (cmd[0][0] != '/' && (ft_strncmp(cmd[0], "./", 2) != 0))
	{
		path_tab = ft_split(path, ':');
		buf = malloc(sizeof(struct stat));
		i = -1;
		while(path_tab[++i])
		{
			if (!(bin = malloc(sizeof(char *)*(ft_strlen(path_tab[i]) + 
					ft_strlen(cmd[0]) + 2))))
					break;
			ft_strlcat(bin, path_tab[i], ft_strlen(path_tab[i]) + 1);
			ft_strlcat(bin, "/", ft_strlen(path_tab[i]) + 2);
			ft_strlcat(bin, cmd[0], ft_strlen(path_tab[i]) + ft_strlen(cmd[0]) + 2);
			if (stat(bin, buf) == 0)
				break;
			free(bin);
			bin = NULL;
		}
		ft_free(path_tab, path);
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
}

void	exec_cmd(char **cmd)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = 0;
	pid = fork();
	if (pid == -1)
		ft_putstr_fd(strerror(errno), 2);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			ft_putstr_fd(strerror(errno), 2);
		exit (EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
//	(void)env;
	char	*line;
	char	**cmd;
	t_list	*my_env;

	ft_putstr("minishell>> ");
	
	my_env = create_env(env);
	while (get_next_line(0, &line) > 0)
	{
		cmd = ft_split(line, ' ');
		if (cmd[0] && is_builtin(cmd[0]))
			exec_builtin(cmd, my_env);
		else if (cmd[0])
		{
			get_path(env, cmd);
			if (cmd[0] != NULL)
				exec_cmd(cmd);
			else
				ft_putstr("Command not found\n");
		}
		ft_putstr("minishell>> ");
		ft_free(cmd, line);
	}
	ft_putendl_fd("Bye !", 1);
	exit(EXIT_SUCCESS);
	return(0);
}
