/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 02:14:25 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/21 17:36:07 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <uuid/uuid.h>
#include "ft_ls.h"
#include "libft.h"
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

static void		print_size(t_stat_name entry, t_dir_info dir_info)
{
	if ((entry.buf.st_mode & S_IFMT) == S_IFCHR
		|| (entry.buf.st_mode & S_IFMT) == S_IFBLK)
	{
		ft_printf(" %*d, ", dir_info.mx_sz_maj, major(entry.buf.st_rdev));
		ft_printf("%*d ", dir_info.mx_sz_min, minor(entry.buf.st_rdev));
	}
	else	
		ft_printf("%*lld ", (int)dir_info.max_size, entry.buf.st_size);
	
}

static void		print_date(t_stat_name entry)
{
	char	*stime;
	time_t	tim;

	stime = ctime(&entry.buf.st_mtimespec.tv_sec);
	ft_printf("%.7s", stime + 4);
	tim = time(NULL);
	if (tim - entry.buf.st_mtimespec.tv_sec > 15552000
		|| entry.buf.st_mtimespec.tv_sec - tim < -15552000)
		ft_printf(" %.4s ", stime + 20);
	else
		ft_printf("%.5s ", stime + 11);
}

static void		print_link(t_stat_name entry)
{
	char	buf[256];
	ssize_t	n;
	
	if ((entry.buf.st_mode & S_IFMT) == S_IFLNK)
	{
		n = readlink(entry.full_name, buf, 256);
		ft_printf(" -> %.*s", n, buf);
	}
}

void			print_list(t_stat_name *arr, unsigned int options, int len,
						 int total)
{
	t_dir_info	dir_info;
	char		perm[12];
	int			i;

	dir_info = get_dir_info(arr, len);
	if (total)
		ft_printf("total %lld\n", dir_info.total);
	i = 0;
	while (i < len)
	{
		get_perm(perm, arr[i]);
		ft_printf("%s ", perm);
		ft_printf("%*d ", dir_info.max_links, arr[i].buf.st_nlink);
		ft_printf("%-*s  ", dir_info.mx_ln_us, get_name(arr[i]));
		ft_printf("%-*s  ", dir_info.mx_ln_gr, get_group(arr[i]));
		print_size(arr[i], dir_info);
		print_date(arr[i]);
		print_name(arr[i], options);
		print_link(arr[i]);
		ft_putchar('\n');
		++i;
	}
}
