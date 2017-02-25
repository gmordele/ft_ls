/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 01:00:34 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/25 05:50:01 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>

static void	list_dir_rec(t_stat_name *arr, int len, unsigned int options)
{
	int i;

	i = 0;
	while (len--)
	{
		if (!ft_strequ(".", arr[i].name) && !ft_strequ("..", arr[i].name))
		{		
			if ((arr[i].buf.st_mode & S_IFMT) == S_IFDIR)
			{
				printf("\n%s:\n", arr[i].full_name);
				list_dir(arr[i].full_name, options);
			}
		}
		++i;
	}
}

void		list_dir(char *dir, unsigned int options)
{
	DIR 		*dirp;
	t_stat_name	*arr;
	int			len;
	t_max		max;

	if ((dirp = opendir(dir)) == NULL)
	{
		printf("ft_ls: %s: %s\n", dir, strerror(errno));
		return ;
	}
	arr = make_arr(dir, &len, &max, options);
	sort_arr(arr, options, len);
	print_arr(arr, options, len);
	closedir(dirp);
	if (options & LS_REC)
		list_dir_rec(arr, len, options);
	free_arr(arr, len);
}
