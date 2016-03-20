/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 14:42:49 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/03/20 14:39:19 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_user(t_stat tmp, t_data **data)
{
	t_passwd	*user;
	t_group		*grp;

	user = getpwuid(tmp.st_uid);
	grp = getgrgid(tmp.st_gid);
	if (((*data)->owner = (char *)ft_memalloc(sizeof(char) \
					* ft_strlen(user->pw_name) + 1)) == NULL)
		ft_putendl("malloc fail in get_user malloc 1");
	(*data)->owner = ft_strcpy((*data)->owner, user->pw_name);
	if (((*data)->grp = (char *)ft_memalloc(sizeof(char) \
					* ft_strlen(grp->gr_name) + 1)) == NULL)
		ft_putendl("malloc fail in get_user malloc 2");
	(*data)->grp = ft_strcpy((*data)->grp, grp->gr_name);
}

void	get_rigths(t_stat stat, t_data **data)
{
	if (((*data)->right = (char *)ft_memalloc(sizeof(char) * 10)) == NULL)
		ft_putendl("malloc fail in get_rigths malloc 2");
	ft_memset((*data)->right, '-', 9);
	if (stat.st_mode & S_IRUSR)
		(*data)->right[0] = 'r';
	if (stat.st_mode & S_IWUSR)
		(*data)->right[1] = 'w';
	if (stat.st_mode & S_IXUSR)
		(*data)->right[2] = 'x';
	if (stat.st_mode  & S_ISUID && (*data)->right[2] == 'x')
		(*data)->right[2] = 's';
	else if (stat.st_mode & S_ISUID && (*data)->right[2] == '-')
		(*data)->right[2] = 'S';
	if (stat.st_mode & S_IRGRP)
		(*data)->right[3] = 'r';
	if (stat.st_mode & S_IWGRP)
		(*data)->right[4] = 'w';
	if (stat.st_mode & S_IXGRP)
		(*data)->right[5] = 'x';
	if (stat.st_mode  & S_ISGID && (*data)->right[5] == 'x')
		(*data)->right[5] = 's';
	else if (stat.st_mode & S_ISGID && (*data)->right[5] == '-')
		(*data)->right[5] = 'S';
	if (stat.st_mode & S_IROTH)
		(*data)->right[6] = 'r';
	if (stat.st_mode & S_IWOTH)
		(*data)->right[7] = 'w';
	if (stat.st_mode & S_IXOTH)
		(*data)->right[8] = 'x';
	if (stat.st_mode  & S_ISVTX && (*data)->right[8] == 'x')
		(*data)->right[8] = 't';
	else if (stat.st_mode & S_ISVTX && (*data)->right[8] == '-')
		(*data)->right[8] = 'T';
	(*data)->right[9] = '\0';
}

t_data	*get_data(char *path, char *filename, t_option *opt)
{
	t_data	*data;
	t_stat	tmp;

	if ((data = (t_data *)ft_memalloc(sizeof(t_data))) == NULL)
		ft_putendl("malloc failed in get data");
	lstat(path, &tmp);
	get_type(tmp, &data);
	if ((data->name = (char *)ft_memalloc(sizeof(char) \
					* ft_strlen(filename) + 1)) == NULL)
		ft_putendl("malloc failed in get data");
	ft_strcpy(data->name, filename);
	if (opt->l == 1)
	{
		get_user(tmp, &data);
		if (data->type == 'l')
			get_link(&data, path);
		get_rigths(tmp, &data);
		data->nblink = tmp.st_nlink;
		data->size = tmp.st_size;
		get_time(tmp, &data);
	}
	data->sec_epoch = tmp.st_mtimespec;
	data->next = NULL;
	data = get_data2(data, opt, tmp);
	return (data);
}
