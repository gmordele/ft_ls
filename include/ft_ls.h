/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 00:34:09 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/17 05:07:27 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define LS_LIST	0x1
# define LS_REC		0x2
# define LS_ALL		0x4
# define LS_REV		0x8
# define LS_TIME	0x10

#include <sys/stat.h>

typedef struct		s_stat_name
{
	char		*name;
	char		*full_name;
	struct stat	buf;
}					t_stat_name;

void		list_dir(char *dir, unsigned int options);
void		free_arr(t_stat_name *arr, int len);
t_stat_name	*make_arr(char *dir, int *len, off_t *max_size);
int			sorted(unsigned int options);
void		sort_arr(t_stat_name *arr, unsigned int options, off_t len);

#endif
