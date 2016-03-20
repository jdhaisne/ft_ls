/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdhaisne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 14:53:38 by jdhaisne          #+#    #+#             */
/*   Updated: 2016/03/20 14:54:52 by jdhaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "libft/libft.h"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef	struct			s_option
{
	int					l;
	int					re;
	int					a;
	int					r;
	int					t;
	int					error;
}						t_option;

typedef	struct			s_path
{
	char				*name;
	struct s_path		*next;
}						t_path;

typedef struct			s_data
{
	char				type;
	char				*right;
	char				acl;
	int					nblink;
	char				*link;
	int					size;
	unsigned int		minor;
	unsigned int		major;
	char				*owner;
	char				*grp;
	char				*name;
	struct timespec		sec_epoch;
	char				*last_modif;
	struct s_data		*next;
}						t_data;

void					print_dir(char *name, t_option *option);
void					get_time(t_stat stat, t_data **data);
void					get_type(t_stat stat, t_data **data);
void					get_user(t_stat tmp, t_data **data);
void					get_rigths(t_stat tmp, t_data **data);
t_data					*insert_start(t_data *start, t_data *new);
void					insert_middle(t_data *prev, t_data *next, t_data *new);
void					print_path(char *path, char *name);
void					free_data(t_data **tmp, int mode, t_option *opt);
void					read_arg(int argc, char **argv, t_option *option);
t_option				*create_option();
void					set_option(int argc, char **argv, t_option *option);
t_data					*get_data(char *path, char *filename, t_option *opt);
t_data					*get_data2(t_data *data, t_option *opt, t_stat tmp);
void					print_file(t_data *start, t_option *option, \
		int is_dir);
void					print_dir(char *name, t_option *option);
void					get_link(t_data **data, char *link_path);
t_data					*check_error(t_data *start, t_option **opt);
void					print_error(char *str);
t_data					*reverse(t_data *start);
void					print_total(t_data *data, t_option *opt);
int						get_total(t_data *data, t_option *opt);
int						round_total(float nb);
t_data					*fill_t_arg(int i, int argc, char **argv, \
						t_option **option);
int						is_older(t_data *tmp1, t_data *tmp2);
void					empty_arg(int argc, char **argv);

#endif
