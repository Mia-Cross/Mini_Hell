/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schene <schene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 14:45:45 by schene            #+#    #+#             */
/*   Updated: 2020/06/14 16:40:41 by schene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static void		print_elem_export(void *str)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putendl_fd((char *)str, 1);
}

void			print_export(t_data *data)
{
	data->status = 0;
	ft_lstiter(data->env, &print_elem_export);
}

// void ft_swap_list(t_list **a, t_list **b)
// {
// 	t_list tmp;
// 	l_list 
// 	tmp = a->next);
// 	*a->next = *b->next;
// 	*b->next = tmp;
// }

// void	sort_ascii(t_list **list)
// {
// 	t_list *elem;
// 	t_list *next;
// //	t_list *tmp;
// 	char *a;
// 	char *b;
// 	int size;
// 	int i;

// 	elem = *list;
// 	size = ft_lstsize(*list);
// 	i = 0;
// 	while (i < size - 1)
// 	{
// 		next = elem->next;
// 		a = (char *)elem->content;
// 		b = (char *)next->content;
// 		printf("|%c| vs |%c|\n", *a, *b);
// 		if (*a > *b)
// 		{
// 			ft_swap_list(&elem, &next);
// 			sort_ascii(&elem);
// 		}
// 		i++;
// 	}
// }