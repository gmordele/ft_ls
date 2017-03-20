/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_dir_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 07:07:45 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/20 01:53:52 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

static void	print_reg_arg(t_stat_name *arr, int len, unsigned int options,
						int *first_dir)
{
	int i;

	i = 0;
	while (i < len)
	{
		if ((arr[i].buf.st_mode & S_IFMT) != S_IFDIR)
		{
			print_arr(arr + i, options, 1);
			*first_dir = 1;
		}
		++i;
	}
	i = 0;
}

static void	print_list_arg(t_stat_name *arr, int len, unsigned int options)
{
	int		i;
	int		first_dir;

	first_dir = 0;
	print_reg_arg(arr, len, options, &first_dir);
	i = 0;
	while (i < len)
	{
		if ((arr[i].buf.st_mode & S_IFMT) == S_IFDIR)
		{
			if (first_dir == 1)
				printf("\n");
			first_dir = 1;
			printf("%s:\n", arr[i].name);
			list_dir(arr[i].name, options);
		}
		++i;
	}
}

void		list_dir_arg(int argc, char *argv[], unsigned int options)
{
	int			len;
	t_stat_name	*arr;

	if (argc == 2)
	{
		arr = make_arr_arg(argv, argc, &len);
		if ((arr[0].buf.st_mode & S_IFMT) == S_IFDIR)
			list_dir(arr[0].name, options);
		else
			print_arr(arr, options, 1);
	}
	else
	{
		arr = make_arr_arg(argv, argc, &len);
		sort_arr(arr, options, len);
		print_list_arg(arr, len, options);
		free_arr(arr, len);
	}
}
