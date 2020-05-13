/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:28:49 by schene            #+#    #+#             */
/*   Updated: 2020/05/07 12:47:59 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
//# include "../get_next_line/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <signal.h>

# define MAX_PATH 4096

int		is_builtin(char *cmd);
void	exec_builtin(char **cmd, t_list *env);
void	builtin_cd(char *path);
void	builtin_pwd(void);
t_list	*create_env(char	**env);
void	print_env(t_list *env);
void	builtin_export(char **cmd, t_list *env);
void	builtin_unset(char	**cmd, t_list *env);
void	builtin_exit(void);
void	builtin_echo(t_list *env, char **cmd);

#endif 