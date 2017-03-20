/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 02:14:25 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/20 16:13:57 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

static t_dir_info	get_dir_info(t_stat_name *arr, int len)
{
	int 	i;
	t_dir_info dir_info;
	
	dir_info.total = 0;
	dir_info.max_size = 0;
	dir_info.max_links = 0;
	i = 0;
	while (i < len)
	{
		dir_info.max_size = dir_info.max_size > arr[i].buf.st_size ?
			dir_info.max_size : arr[i].buf.st_size;
		dir_info.max_links = dir_info.max_links > arr[i].buf.st_nlink ?
			dir_info.max_links : arr[i].buf.st_nlink;
		dir_info.total+= arr[i].buf.st_blocks;
		++i;
	}
	return (dir_info);
}

void			print_list(t_stat_name *arr, unsigned int options, int len)
{
	t_dir_info	dir_info;
	char		perm[12];
	char		*print_string;
	char		date[12];
	int			i;

	(void)options;
	(void)date;
	print_string = "%s %*d %s %s %*d *s";
	dir_info = get_dir_info(arr, len);
	i = 0;
	while (i < len)
	{
		get_perm(perm, arr[i]);
	}


}
