/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 00:34:09 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/23 01:09:38 by gmordele         ###   ########.fr       */
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

#include <sys/stat.h>

typedef struct		s_stat_name
{
	char		*name;
	char		*full_name;
	struct stat	buf;
}					t_stat_name;

void		list_dir(char *dir, unsigned int options);
void		free_arr(t_stat_name *arr, int len);
t_stat_name	*make_arr(char *dir, int *len, off_t *max_size, unsigned options);
int			sorted(unsigned int options);
void		sort_arr(t_stat_name *arr, unsigned int options, off_t len);
int			comp_size(t_stat_name p1, t_stat_name p2);
int			comp_last_modif(t_stat_name p1, t_stat_name p2);
void		print_arr(t_stat_name *arr, unsigned int options, int len);

#endif
