/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:14:15 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/03/20 14:53:53 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	empty_arg(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
		{
			ft_putendl("ft_ls: fts_open: No such file or directory");
			exit(0);
		}
		i++;
	}
}

void	print_error(char *str)
{
	ft_putstr("ft_ls: ");
	perror(str);
}

t_data	*del_node(t_data *start, char *name, t_option *opt)
{
	t_data *tmp1;
	t_data *tmp2;

	tmp1 = start;
	tmp2 = NULL;
	while (tmp1 != NULL && ft_strcmp(tmp1->name, name) != 0)
	{
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
	if (tmp2 == NULL)
	{
		tmp2 = start;
		start = start->next;
		free_data(&tmp2, 0, opt);
	}
	else
	{
		tmp2->next = tmp1->next;
		free_data(&tmp1, 0, opt);
	}
	return (start);
}

t_data	*check_error(t_data *start, t_option **opt)
{
	t_stat	buf;
	t_data	*tmp;

	tmp = start;
	while (tmp != NULL)
	{
		if (lstat(tmp->name, &buf) == -1)
		{
			(*opt)->error = 1;
			print_error(tmp->name);
			start = del_node(start, tmp->name, *opt);
		}
		tmp = tmp->next;
	}
	return (start);
}
