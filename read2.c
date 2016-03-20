/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 15:40:47 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/03/20 12:59:46 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_older(t_data *tmp1, t_data *tmp2) /*tmp1 older than tmp2 return 1*/
{
	if ((tmp1->sec_epoch).tv_sec == (tmp2->sec_epoch).tv_sec)
	{
		if ((tmp1->sec_epoch).tv_nsec > (tmp2->sec_epoch).tv_nsec)
			return (1);
		if ((tmp1->sec_epoch).tv_nsec < (tmp2->sec_epoch).tv_nsec)
			return (0);
		if (ft_strcmp(tmp1->name, tmp2->name) < 0)
			return (1);
		return(0);
	}
	if ((tmp1->sec_epoch).tv_sec > (tmp2->sec_epoch).tv_sec)
		return (1);
	return (0);
}

t_data	*fill_t_arg(int i, int argc, char **argv, t_option **opt)
{
	t_data	*start;
	t_data	*tmp;
	t_data	*new;

	start = get_data(argv[i], argv[i], *opt);
	tmp = start;
	while (i < argc - 1)
	{
		i++;
		new = get_data(argv[i], argv[i], *opt);
		if (is_older(new, start) == 1)
		{
			ft_putendl("retrun");
		start = insert_start(start, new);
		}
		else
		{
			while (tmp->next != NULL && is_older(new, tmp->next) == 0)
				tmp = tmp->next;
			insert_middle(tmp, tmp->next, new);
		}
		tmp = start;
	}
	start = check_error(start, opt);
	return (start);
}


t_data *get_data2(t_data *data, t_option *opt, t_stat tmp)
{
	if((data->type == 'c' || data->type == 'b') && opt->l == 1)
	{
		data->major = major(tmp.st_rdev);
		data->minor = minor(tmp.st_rdev);
	}
	return (data);
}
