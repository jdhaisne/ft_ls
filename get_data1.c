/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:35:45 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/03/20 14:56:33 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_file_l(t_data *start)
{
	ft_putchar(start->type);
	ft_putstr(start->right);
	ft_putstr("  ");
	ft_putnbr(start->nblink);
	ft_putchar(' ');
	ft_putstr(start->owner);
	ft_putstr("  ");
	ft_putstr(start->grp);
	ft_putstr("  ");
	if (start->type == 'c' || start->type == 'd')
	{
		ft_putnbr(start->major);
		ft_putstr(", ");
		ft_putnbr(start->minor);
	}
	else
		ft_putnbr(start->size);
	ft_putchar(' ');
	ft_putstr(start->last_modif);
	ft_putchar(' ');
	ft_putstr(start->name);
	if (start->type == 'l')
	{
		ft_putstr(" -> ");
		ft_putendl(start->link);
	}
	else
		ft_putchar('\n');
}

void			print_file(t_data *start, t_option *option,int is_dir)
{
	if (option->l == 1 && is_dir == 1 && start->next != NULL)
		print_total(start, option);
	while (start != NULL)
	{
		if (!(option->a == 0 && start->name[0] == '.') && option->l == 1)
		{
			print_file_l(start);
		}
		else if (!(option->a == 0 && start->name[0] == '.'))
			ft_putendl(start->name);
		start = start->next;
	}
}

t_data			*sort_data(t_data *start, t_data *tmp, t_data *new, \
		t_option *opt)
{
	if(opt->t == 1)
	{
		if (is_older(new, tmp) == 1)
			start = insert_start(tmp, new);
		else
		{
			while (tmp->next != NULL && is_older(new, tmp->next) == 0)
				tmp = tmp->next;
			insert_middle(tmp, tmp->next, new);
		}
		return (start);
	}
	if (ft_strcmp(new->name, tmp->name) <= 0)
		start = insert_start(tmp, new);
	else
	{
		while (tmp->next != NULL && \
				ft_strcmp(new->name, (tmp->next)->name) >= 0)
			tmp = tmp->next;
		insert_middle(tmp, tmp->next, new);
	}
	return (start);
}

static t_data	*create_dir_list(char *dir_name, t_option *opt)
{
	DIR			*dir;
	t_dirent	*file;
	t_data		*start;
	t_data		*new;

	if ((dir = opendir(dir_name)) == NULL)
	{
		print_error(dir_name);
		return (NULL);
	}
	dir_name = ft_strjoin(dir_name, "/");
	file = readdir(dir);
	start = get_data(ft_strjoin(dir_name, file->d_name), file->d_name, opt);
	while ((file = readdir(dir)) != NULL)
	{
		new = get_data(ft_strjoin(dir_name, file->d_name), file->d_name, opt);
		start = sort_data(start, start, new, opt);
	}
	closedir(dir);
	return (start);
}

void			print_dir(char *name, t_option *option)
{
	t_data			*start;
	t_data			*tmp;

	if ((start = create_dir_list(name, option)) == NULL)
		return;
	if (option->r == 1)
		start = reverse(start);
	print_file(start, option, 1);
	tmp = start;
	name = ft_strjoin(name, "/");
	while (tmp != NULL)
	{
		if (tmp->type == 'd' && ft_strcmp(tmp->name, "..") != 0 \
				&& ft_strcmp(tmp->name, ".") != 0 && option->re == 1)
		{
			if (!(tmp->name[0] == '.' && option->a == 0))
			{
				print_path(name, tmp->name);
				print_dir(ft_strjoin(name, tmp->name), option);
			}
		}
		tmp = tmp->next;
	}
	free_data(&start, 1, option);
}
