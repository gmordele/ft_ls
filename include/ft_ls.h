/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 00:34:09 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/23 04:31:33 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define LS_LIST	0x1
# define LS_REC		0x2
# define LS_ALL		0x4
# define LS_REV		0x8
# define LS_TIME	0x10
# define LS_COLORS	0x20
# define LS_TYPE	0x40

# define COL_RES	"\033[0m"

# define COL_BLA	"\033[30m"
# define COL_RED	"\033[31m"
# define COL_GRE	"\033[32m"
# define COL_YEL	"\033[33m"
# define COL_BLU	"\033[34m"
# define COL_MAG	"\033[35m"
# define COL_CYA	"\033[36m"
# define COL_WHI	"\033[37m"

# define COL_BLA_BG	"\033[40m"
# define COL_RED_BG	"\033[41m"
# define COL_GRE_BG	"\033[42m"
# define COL_YEL_BG	"\033[43m"
# define COL_BLU_BG	"\033[44m"
# define COL_MAG_BG	"\033[45m"
# define COL_CYA_BG	"\033[46m"
# define COL_WHI_BG	"\033[47m"

#include <sys/stat.h>
#include <stdlib.h>

typedef struct		s_stat_name
{
	char		*name;
	char		*full_name;
	struct stat	buf;
}					t_stat_name;

typedef struct		s_max
{
	off_t		size;
	nlink_t		links;
}					t_max;

void		list_dir(char *dir, unsigned int options);
void		free_arr(t_stat_name *arr, int len);
t_stat_name	*make_arr(char *dir, int *len, t_max *max, unsigned options);
int			sorted(unsigned int options);
void		sort_arr(t_stat_name *arr, unsigned int options, off_t len);
int			comp_size(t_stat_name p1, t_stat_name p2);
int			comp_last_modif(t_stat_name p1, t_stat_name p2);
void		print_arr(t_stat_name *arr, unsigned int options, int len);
int			comp_name(t_stat_name p1, t_stat_name p2);
void		print_col_dir(t_stat_name name);
void		print_col_link(t_stat_name name);
void		print_col_sock(t_stat_name name);
void		print_col_fifo(t_stat_name name);
void		print_col_char_spec(t_stat_name name);
void		print_col_block_char(t_stat_name name);
void		print_col_exe(t_stat_name name);


#endif
