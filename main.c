/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:53:21 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/03/18 17:03:19 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_option	*create_option(void)
{
	t_option *option;

	if ((option = (t_option *)ft_memalloc(sizeof(t_option))) == NULL)
		ft_putendl("malloc fail in create_option");
	option->l = 0;
	option->re = 0;
	option->a = 0;
	option->r = 0;
	option->t = 0;
	option->error = 0;
	return (option);
}

void		illegal_opt(char opt)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(opt);
	ft_putchar('\n');
	ft_putendl("usage: ./ft_ls [-Ralrt] [file ...]");
	exit(0);
}

void		set_option(int argc, char **argv, t_option *option)
{
	int i;
	int j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] != '-' || argv[i][1] == '-')
			return ;
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] == 'l')
				option->l = 1;
			else if (argv[i][j] == 'R')
				option->re = 1;
			else if (argv[i][j] == 'a')
				option->a = 1;
			else if (argv[i][j] == 'r')
				option->r = 1;
			else if (argv[i][j] == 't')
				option->t = 1;
			else if(argv[i][j] != '-')
				illegal_opt(argv[i][j]);
		}
	}
}

void		print_path(char *path, char *name)
{
	ft_putchar('\n');
	ft_putstr(path);
	ft_putstr(name);
	ft_putendl(":");
}

int			main(int argc, char **argv)
{
	t_option	*option;

	option = create_option();
	set_option(argc, argv, option);
	if (argc == 1)
		print_dir(".", option);
	else
		read_arg(argc, argv, option);
	return (0);
}
