/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 21:37:24 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/27 04:31:13 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_ls.h"

static void	print_list(t_stat_name *arr, unsigned int options, int len)
{
	(void)arr;
	(void)options;
	(void)len;
}

static void	print_colored_name(t_stat_name name)
{
	if ((name.buf.st_mode & S_IFMT) == S_IFDIR)
		print_col_dir(name);
	else if ((name.buf.st_mode & S_IFMT) == S_IFLNK)
		print_col_link(name);
	else if ((name.buf.st_mode & S_IFMT) == S_IFSOCK)
		print_col_sock(name);
	else if ((name.buf.st_mode & S_IFMT) == S_IFIFO)
		print_col_fifo(name);
	else if ((name.buf.st_mode & S_IFMT) == S_IFCHR)
		print_col_char_spec(name);
	else if ((name.buf.st_mode & S_IFMT) == S_IFBLK)
		print_col_block_char(name);
	else if ((name.buf.st_mode & S_IFMT) ==  S_IFREG)
	{
		if (name.buf.st_mode & S_IXUSR || name.buf.st_mode & S_IXGRP
			|| name.buf.st_mode & S_IXOTH)
			print_col_exe(name);
		else
			ft_putstr(name.name);
	}
	else
		ft_putstr(name.name);

}

void		print_type(t_stat_name name)
{
	if ((name.buf.st_mode & S_IFMT) == S_IFDIR)
		ft_putchar('/');
	else if ((name.buf.st_mode & S_IFMT) == S_IFLNK)
		ft_putchar('@');
	else if ((name.buf.st_mode & S_IFMT) == S_IFSOCK)
		ft_putchar('=');
	else if ((name.buf.st_mode & S_IFMT) == S_IFWHT)
		ft_putchar('%');
	else if ((name.buf.st_mode & S_IFMT) == S_IFIFO)
		ft_putchar('|');
	else if ((name.buf.st_mode & S_IFMT) ==  S_IFREG)
	{
		if (name.buf.st_mode & S_IXUSR || name.buf.st_mode & S_IXGRP
			|| name.buf.st_mode & S_IXOTH)
			ft_putchar('*');
	}
}

static void	print_default(t_stat_name *arr, unsigned int options, int len)
{
	int		i;

	i = 0;
	if (options & LS_COLORS)
		while (i < len)
		{
			print_colored_name(arr[i]);
			if (options & LS_TYPE)
				print_type(arr[i]);
			ft_putchar('\n');
			++i;
		}
	else
		while (i < len)
		{
			ft_putstr(arr[i].name);
			if (options & LS_TYPE)
				print_type(arr[i]);
			ft_putchar('\n');
			++i;
		}
}

void		print_arr(t_stat_name *arr, unsigned int options, int len)
{
	if (options & LS_LIST)
		print_list(arr, options, len);
	else
		print_default(arr, options, len);
}
