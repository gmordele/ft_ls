/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 02:14:25 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/21 00:28:00 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <uuid/uuid.h>
#include "ft_ls.h"
#include "libft.h"
#include <pwd.h>
#include <sys/types.h>
#include <grp.h>
#include <stdio.h>

int					num_len(unsigned int n)
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

int					size_len(t_stat_name entry)
{
	if ((entry.buf.st_mode & S_IFMT) != S_IFCHR)
		return (num_len(entry.buf.st_size));
	return (4 + num_len(major(entry.buf.st_rdev))
			+ num_len(minor(entry.buf.st_rdev)));
}

static t_dir_info	init_dir_info()
{
	t_dir_info	ret;

	ret.max_size = 0;
	ret.max_links = 0;
	ret.total = 0;
	return (ret);
}

char				*get_name(t_stat_name entry)
{
	struct passwd *pwd;

	pwd = getpwuid(entry.buf.st_uid);
	return (pwd->pw_name);
}

char				*get_group(t_stat_name entry)
{
	struct group	*grp;

	grp = getgrgid(entry.buf.st_gid);
	return (grp->gr_name);
}

static t_dir_info	get_dir_info(t_stat_name *arr, int len)
{
	int 		i;
	t_dir_info	dir_info;
	int			ln;
	
	dir_info = init_dir_info();
	i = 0;
	while (i < len)
	{
		dir_info.max_size = dir_info.max_size > arr[i].buf.st_size ?
			dir_info.max_size : arr[i].buf.st_size;
		dir_info.max_links = dir_info.max_links > arr[i].buf.st_nlink ?
			dir_info.max_links : arr[i].buf.st_nlink;
		dir_info.total+= arr[i].buf.st_blocks;
		ln = ft_strlen(get_name(arr[i]));
		dir_info.mx_ln_us = len > dir_info.mx_ln_us ? ln : dir_info.mx_ln_us;
		ln = ft_strlen((get_group(arr[i])));
		dir_info.mx_ln_gr = len > dir_info.mx_ln_gr ? ln : dir_info.mx_ln_gr;
		++i;
	}
	dir_info.max_links = num_len(dir_info.max_links);
	dir_info.max_size = num_len(dir_info.max_size);
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
	print_string = "%s %*d %-*s, %-*s\n";
	dir_info = get_dir_info(arr, len);
	printf("total %lld\n", dir_info.total);
	i = 0;
	while (i < len)
	{
		get_perm(perm, arr[i]);
		printf("%s ", perm);
		printf("%*d ", dir_info.max_links, arr[i].buf.st_nlink);
		printf();
		printf("\n");
		++i;
	}
}
