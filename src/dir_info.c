/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 12:58:13 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/21 15:50:58 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"
#include <sys/types.h>
#include <stdio.h>

static int			num_len(unsigned int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		++len;
		n /= 10;
	}
	return (len);
}

/*
static int			size_len(t_stat_name entry)
{
	if ((entry.buf.st_mode & S_IFMT) != S_IFCHR)
		return (num_len(entry.buf.st_size));
	return (4 + num_len(major(entry.buf.st_rdev))
			+ num_len(minor(entry.buf.st_rdev)));
}
*/

static t_dir_info	init_dir_info()
{
	t_dir_info	ret;

	ret.max_size = 0;
	ret.max_links = 0;
	ret.total = 0;
	ret.mx_sz_maj = 0;
	ret.mx_sz_min = 0;
	ret.mx_ln_us = 0;
	ret.mx_ln_gr = 0;
	return (ret);
}

static void			get_values(t_stat_name entry, t_dir_info *dir_info)
{
	int len;

	dir_info->max_size = dir_info->max_size > entry.buf.st_size ?
		dir_info->max_size : entry.buf.st_size;
	dir_info->max_links = dir_info->max_links > entry.buf.st_nlink ?
		dir_info->max_links : entry.buf.st_nlink;
	dir_info->total+= entry.buf.st_blocks;
	len = ft_strlen(get_name(entry));
	dir_info->mx_ln_us = len > dir_info->mx_ln_us ? len : dir_info->mx_ln_us;
	len = ft_strlen(get_group(entry));
	dir_info->mx_ln_gr = len > dir_info->mx_ln_gr ? len : dir_info->mx_ln_gr;
	if ((entry.buf.st_mode & S_IFMT) == S_IFCHR
		|| (entry.buf.st_mode & S_IFMT) == S_IFBLK)
	{
		dir_info->mx_sz_maj = dir_info->mx_sz_maj > major(entry.buf.st_rdev) ?
			dir_info->mx_sz_maj : major(entry.buf.st_rdev);
		dir_info->mx_sz_min = dir_info->mx_sz_min > minor(entry.buf.st_rdev) ?
			dir_info->mx_sz_min : minor(entry.buf.st_rdev);
	}
}

t_dir_info			get_dir_info(t_stat_name *arr, int len)
{
	int 		i;
	t_dir_info	dir_info;
	
	dir_info = init_dir_info();
	i = 0;
	while (i < len)
	{
		get_values(arr[i], &dir_info);
		++i;
	}
	dir_info.max_links = num_len(dir_info.max_links);
	dir_info.max_size = num_len(dir_info.max_size);
	if (dir_info.mx_sz_min != 0)
	{
		dir_info.mx_sz_maj = num_len(dir_info.mx_sz_maj);
		dir_info.mx_sz_min = num_len(dir_info.mx_sz_min);
		if (dir_info.max_size < dir_info.mx_sz_maj + dir_info.mx_sz_min + 3)
			dir_info.max_size = dir_info.mx_sz_maj + dir_info.mx_sz_min + 3;
	}
	return (dir_info);
}
