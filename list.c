/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:18:03 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/03/19 14:34:06 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int get_total(t_data *data, t_option *opt)
{
	int total;

	total = 0;
	while(data != NULL)
	{
		if(!(opt->a == 0 && data->name[0] == '.'))
			total += round_total(data->size);
		data = data->next;
	}
	return (total);
}
t_data	*insert_start(t_data *start, t_data *new)
{
	new->next = start;
	start = new;
	return (start);
}

void	free_data(t_data **tmp, int mode, t_option *opt)
{
	free((*tmp)->name);
	if (opt->l == 1)
	{
		free((*tmp)->right);
		if ((*tmp)->type == 'l')
			free((*tmp)->link);
		free((*tmp)->owner);
		free((*tmp)->grp);
	}
	if ((*tmp)->next != NULL && mode == 1)
		free_data(&(*tmp)->next, 1, opt);
	free(*tmp);
	*tmp = NULL;
}

t_data	*reverse(t_data *start)
{
	t_data *new;
	t_data *tmp1;
	t_data *tmp2;

	tmp1 = start;
	tmp2 = start;
	new = NULL;
	while (tmp1)
	{
		tmp1 = tmp1->next;
		tmp2->next = new;
		new = tmp2;
		tmp2 = tmp1;
	}
	return (new);
}

void	insert_middle(t_data *prev, t_data *next, t_data *new)
{
	if (new == NULL)
		ft_putendl("errorr in insert middle");
	prev->next = new;
	if (next != NULL)
		new->next = next;
}
