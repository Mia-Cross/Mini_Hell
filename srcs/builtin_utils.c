/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 17:27:33 by schene            #+#    #+#             */
/*   Updated: 2020/06/11 14:58:58 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lst(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	close_fd(t_data *data)
{
	t_list *tmp;

	while (data->fd)
	{
		tmp = data->fd;
		data->fd = data->fd->next;
		printf("trying to close fd{%d}\t", *(int *)tmp->content);
		close(*(int *)tmp->content);
		printf("OK !\n");
		printf("trying to free tmp->content %p\t", tmp->content);
		free(tmp->content);
		printf("OK !\n");
		tmp->content = NULL;
		printf("trying to free tmp %p\t", tmp);
		free(tmp);
		printf("OK !\n");
		tmp = NULL;
	}
	data->fd = NULL;
}

int		is_quotes(char *str, int i)
{
	return (str[i] && (str[i] == '\"' || str[i] == '\'') && is_meta(str, i));
}
