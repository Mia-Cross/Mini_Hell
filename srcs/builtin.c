/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:21:34 by schene            #+#    #+#             */
/*   Updated: 2020/05/07 02:36:30 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	return (0);
}

void	exec_builtin(char **cmd, t_list *env)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		builtin_cd(cmd[1]);
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		builtin_pwd();
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		print_env(env);
	if (ft_strncmp(cmd[0], "export", 6) == 0)
		builtin_export(cmd, env);
	if (ft_strncmp(cmd[0], "unset", 5) == 0)
		builtin_unset(cmd, env);
	if (ft_strncmp(cmd[0], "exit", 4) == 0)
		builtin_exit();
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		builtin_echo(env, cmd);
}

void	builtin_cd(char *path)
{
	if (chdir(path) == -1)
		ft_putendl_fd(strerror(errno), 2);
}

void	builtin_pwd(void)
{
	char	cwd[MAX_PATH];

	if (getcwd(cwd, MAX_PATH) != NULL)
		ft_putendl_fd(cwd, 1);
	else
		ft_putendl_fd(strerror(errno), 2);
}

void	builtin_exit(void)
{
	exit(EXIT_SUCCESS);
}