/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 13:42:26 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/03/20 13:34:16 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		round_total(float nb)
{
	int nb_div;

	nb_div = nb / 512;
	if(nb / 512 > nb_div)
		return (nb / 512 + 1);
	return (nb / 512);
}


void	print_total(t_data *data, t_option *opt)
{
	ft_putstr("total ");
	ft_putnbr(get_total(data, opt));
	ft_putchar('\n');
}

void	get_time(t_stat stat, t_data **data)
{
	char	**tab_time;
	char	*time_ok;
	int		i;

	time_ok = (char *)ft_memalloc(sizeof(char) * 1);
	time_ok[0] = '\0';
	tab_time = ft_strsplit(ctime(&stat.st_mtime), ' ');
	time_ok = ft_strjoin(time_ok, tab_time[1]);
	time_ok = ft_strjoin(time_ok, " ");
	time_ok = ft_strjoin(time_ok, tab_time[2]);
	time_ok = ft_strjoin(time_ok, " ");
	if (time(NULL) - stat.st_mtime > 15552000 \
			|| time(NULL) - stat.st_mtime < -15552000)
	{
		time_ok = ft_strjoin(time_ok, tab_time[4]);
		i = ft_strlen(time_ok);
		time_ok[i - 1] = '\0';
	}
	else
	{
		time_ok = ft_strjoin(time_ok, tab_time[3]);
		i = ft_strlen(time_ok);
		time_ok[i - 3] = '\0';
	}
	(*data)->last_modif = ft_strdup(time_ok);
}

void	get_type(t_stat stat, t_data **data)
{
	(*data)->type = (char)ft_memalloc(sizeof(char));
	if (S_ISBLK(stat.st_mode))
		(*data)->type = 'b';
	else if (S_ISCHR(stat.st_mode))
		(*data)->type = 'c';
	else if (S_ISDIR(stat.st_mode))
		(*data)->type = 'd';
	else if (S_ISFIFO(stat.st_mode))
		(*data)->type = 'p';
	else if (S_ISLNK(stat.st_mode))
		(*data)->type = 'l';
	else if (S_ISREG(stat.st_mode))
		(*data)->type = '-';
	else if (S_ISSOCK(stat.st_mode))
		(*data)->type = 's';
	else
		(*data)->type = '?';
}

void	get_link(t_data **data, char *link_path)
{
	t_stat	tmp;
	int		ret;

	if ((*data)->type == 'l')
	{
		lstat(link_path, &tmp);
		(*data)->link = (char *)ft_memalloc(tmp.st_size + 1);
		ret = readlink(link_path, (*data)->link, tmp.st_size + 1);
		ft_putstr(link_path);
		(*data)->link[ret] = '\0';
	}
}
