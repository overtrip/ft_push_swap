/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jealonso <jealonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 14:26:32 by jealonso          #+#    #+#             */
/*   Updated: 2015/05/29 12:52:57 by jealonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "push_swap.h"

t_val	*ft_create_elem(char *data)
{
	t_val	*new;

	if (!(new = (t_val *)malloc(sizeof(t_val))))
		return (NULL);
	new->data = ft_atoi(data);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_add_list(t_val **begin, t_val *current)
{
	if (!(*begin))
	{
		*begin = current;
		return ;
	}
	else
	{
		(*begin)->prev = current;
		current->next = (*begin);
		(*begin) = current;
	}
}

t_val	*ft_end_list(t_val **begin)
{
	t_val	*end;

	end = *begin;
	while (end->next)
		end = end->next;
	return (end);
}

void	ft_sort(int option, t_val *begin, t_val *end_list)
{
	t_val	*second;
	t_i		var;
	int		find;
	int		cmp;

	second = NULL;
	cmp = 0;
	ft_init_index(&var);
	while (ft_decresing(begin, &var) == 0)
	{
		find = ft_find(begin, &var);
		if (var.x == 1)
			end_list = push_a(&end_list, &second, &cmp, option);
		else if (var.w == 1 && var.y == 3)
			swap_a(&end_list, &cmp, option);
		else if (find == 1 && var.x == 0)
			end_list = rot_a(&begin, &end_list, &cmp, option);
		else if (find == 0)
			end_list = rrot_a(&begin, &end_list, &cmp, option);
		if (P_V & option)
			ft_aff_stat(begin, second, option);
	}
	(P_T & option) ? ft_reelaff(&begin, &second, &cmp, option) :
		push_b(&second, &cmp, option);
}

void	ft_get_agrs(int ac, int *start, char **av, int option)
{
	t_val	*begin;
	int		i;

	begin = NULL;
	i = ac;
	while (--i > *start)
		ft_add_list(&begin, ft_create_elem(av[i]));
	if (!(begin))
	{
		(option & P_E) ? ft_msg_error("\n\tError: no values set.\n", option) :
			ft_putstr("Error");
		return ;
	}
	ft_sort(option, begin, ft_end_list(&begin));
}
