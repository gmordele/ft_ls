/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arr_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 06:08:42 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/25 07:05:26 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "ft_ls.h"
#include <stdio.h>

static int			valid_file(char *file)
{
	struct stat	tmp;
	if (!lstat(file, &tmp))
		return (1);
	else
	{
		printf("ft_ls: %s: %s\n", file, strerror(errno));
		return (0);
	}
}

static t_stat_name	add_arr_entry(char *file)
{
	t_stat_name ret;

	ret.name = ft_strdup(file);
	ret.full_name = ft_strdup(file);
	lstat(ret.full_name, &ret.buf);
	return (ret);
}

t_stat_name			*make_arr_arg(char *argv[], int len, t_max *max, int *n)
{
	int			i;
	t_stat_name *arr;

	max->size = 0;
	max->links = 0;
	arr = (t_stat_name *)malloc(sizeof(t_stat_name) * len);
	i = 0;
	*n = 0;
	while (i < len)
	{
		if (valid_file(argv[i]))
		{
			arr[*n] = add_arr_entry(argv[i]);
			max->size = max->size > arr[*n].buf.st_size ?
				max->size : arr[*n].buf.st_size;
			max->links = max->links > arr[*n].buf.st_nlink ?
				max->links : arr[*n].buf.st_nlink;
			++(*n);
		}
		++i;
	}
	
	return (arr);
}
