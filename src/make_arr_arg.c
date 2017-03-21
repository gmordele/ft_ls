/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arr_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 06:08:42 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/21 16:22:55 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "ft_ls.h"

static int			valid_file(char *file)
{
	struct stat	tmp;
	if (!lstat(file, &tmp))
		return (1);
	else
	{
		ft_printf("ft_ls: %s: %s\n", file, strerror(errno));
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

t_stat_name			*make_arr_arg(char *argv[], int len, int *n)
{
	int			i;
	t_stat_name *arr;

	arr = (t_stat_name *)malloc(sizeof(t_stat_name) * len);
	i = 1;
	*n = 0;
	while (i < len)
	{
		if (valid_file(argv[i]))
		{
			arr[*n] = add_arr_entry(argv[i]);
			++(*n);
		}
		++i;
	}
	return (arr);
}
