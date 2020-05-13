/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 02:26:00 by schene            #+#    #+#             */
/*   Updated: 2020/05/07 13:57:34 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*variable_value(t_list *env, char *var)
{
	char	*name;

	name = &var[1];
	while (env->next)
	{
		if (ft_strncmp(env->content, name, ft_strlen(name)) == 0)
			return (ft_strrchr(env->content, '=') + 1);
		env = env->next;
	}
	return(NULL);
}

void	builtin_echo(t_list *env, char **cmd)
{
	(void)env;

	if (ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])) == 0)
	{
		if (cmd[2][0] == '$')
			ft_putstr(variable_value(env, cmd[2]));
		else
			ft_putstr(cmd[2]);
	}
	else
	{
		if (cmd[1][0] == '$')
			ft_putendl_fd(variable_value(env, cmd[1]), 1);
		else
			ft_putendl_fd(cmd[1], 1);
	}
}