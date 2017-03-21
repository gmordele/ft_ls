/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 02:14:25 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/21 16:01:25 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <uuid/uuid.h>
#include "ft_ls.h"
#include "libft.h"
#include <pwd.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>

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

static void		print_size(t_stat_name entry, t_dir_info dir_info)
{
	if ((entry.buf.st_mode & S_IFMT) == S_IFCHR
		|| (entry.buf.st_mode & S_IFMT) == S_IFBLK)
	{
		printf(" %*d, ", dir_info.mx_sz_maj, major(entry.buf.st_rdev));
		printf("%*d ", dir_info.mx_sz_min, minor(entry.buf.st_rdev));
	}
	else	
		printf("%*lld ", (int)dir_info.max_size, entry.buf.st_size);
	
}

static void		print_date(t_stat_name entry)
{
	char	*stime;
	time_t	tim;

	stime = ctime(&entry.buf.st_mtimespec.tv_sec);
	printf("%.7s", stime + 4);
	tim = time(NULL);
	if (tim - entry.buf.st_mtimespec.tv_sec > 15552000
		|| entry.buf.st_mtimespec.tv_sec - tim < -15552000)
		printf(" %.4s ", stime + 20);
	else
		printf("%.5s ", stime + 11);
}

void			print_list(t_stat_name *arr, unsigned int options, int len)
{
	t_dir_info	dir_info;
	char		perm[12];
	int			i;

	dir_info = get_dir_info(arr, len);
	printf("total %lld\n", dir_info.total);
	i = 0;
	while (i < len)
	{
		get_perm(perm, arr[i]);
		printf("%s ", perm);
		printf("%*d ", dir_info.max_links, arr[i].buf.st_nlink);
		printf("%-*s  ", dir_info.mx_ln_us, get_name(arr[i]));
		printf("%-*s  ", dir_info.mx_ln_gr, get_group(arr[i]));
		print_size(arr[i], dir_info);
		print_date(arr[i]);
		print_name(arr[i], options);
		printf("\n");
		++i;
	}
	printf("dir_info.msize = %lld\n" , dir_info.max_size);
}
