/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 13:52:56 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/03/20 14:55:26 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		init_file(t_data *arg, t_option *option, \
		int *nb_file, int *nb_dir)
{
	t_data	*tmp;
	while (arg != NULL)
	{
		if (arg->type != 'd')
		{
			*nb_file += 1;
			if (option->l == 1)
			{
				tmp = arg->next;
				arg->next = NULL;
				print_file(arg, option, 0);
				arg->next = tmp;
			}
			else
				ft_putendl(arg->name);
			}
		else
			*nb_dir += 1;
				arg = arg->next;
	}
}

static void		init_dir(t_data *arg, t_option *option, int nb_file, int nb_dir)
{
	int		i;
	t_data	*tmp;

	i = 0;
	tmp = arg;
	while (tmp != NULL)
	{
		if (tmp->type == 'd')
		{
			if (nb_file > 0 || nb_dir > 1 || option->error == 1)
			{
				if (nb_file > 0 || i > 0)
					ft_putchar('\n');
				ft_putstr(tmp->name);
				ft_putendl(":");
			}
			print_dir(tmp->name, option);
			i++;
		}
		tmp = tmp->next;
	}
}

static t_data	*fill_arg(int i, int argc, char **argv, t_option **opt)
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
		if (ft_strcmp(new->name, tmp->name) <= 0)
			start = insert_start(start, new);
		else
		{
			while (tmp->next != NULL && \
					ft_strcmp(new->name, (tmp->next)->name) >= 0)
				tmp = tmp->next;
			insert_middle(tmp, tmp->next, new);
		}
		tmp = start;
	}
	start = check_error(start, opt);
	return (start);
}

static void		print_arg(t_data *arg, t_option *option)
{
	int	nb_file;
	int	nb_dir;

	nb_file = 0;
	nb_dir = 0;
	init_file(arg, option, &nb_file, &nb_dir);
	init_dir(arg, option, nb_file, nb_dir);
}

void			read_arg(int argc, char **argv, t_option *option)
{
	int i;

	i = 1;
	empty_arg(argc, argv);
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '-')
		i++;
	if(i < argc && ft_strcmp(argv[i], "--") == 0)
		i++;
	if (i == argc)
	{
		print_dir(".", option);
		return ;
	}
	if(option->t == 1)
		print_arg(fill_t_arg(i, argc, argv, &option), option);
	else
		print_arg(fill_arg(i, argc, argv, &option), option);
}
