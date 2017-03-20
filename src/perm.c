/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:55:20 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/20 16:15:30 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/xattr.h>

static char		get_type(struct stat buf)
{
	if ((buf.st_mode & S_IFMT) == S_IFREG)
		return ('-');
	if ((buf.st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	if ((buf.st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	if ((buf.st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	if ((buf.st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	if ((buf.st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	return ('-');
}

static void	get_read_write(char *perm, struct stat buf)
{
	perm[1] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
	perm[2] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
	perm[4] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
	perm[5] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
	perm[7] = (buf.st_mode & S_IROTH) ? 'r' : '-';
	perm[8] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
}

static void	get_execute(char *perm, struct stat buf)
{
	if (buf.st_mode & IXUSR)
		perm[3] = (st_mode & S_ISUID) ? 's' : 'x';
	else
		perm[3] = (st_mode & S_ISUID) ? 'S' : '-';
	if (buf.st_mode & IXGRP)
		perm[3] = (st_mode & S_ISGID) ? 's' : 'x';
	else
		perm[3] = (st_mode & S_ISGID) ? 'S' : '-';
	if (buf.st_mode & IXOTH)
		perm[3] = (st_mode & S_ISVTX) ? 't' : 'x';
	else
		perm[3] = (st_mode & S_ISVTX) ? 'T' : '-';
}

void		get_perm(char *perm, t_stat_name entry)
{
	perm[11] = '\0';
	perm[0] = get_type(entry.buf);
	get_read_write(perm, entry.buf);
	get_execute(perm, entry.buf);
	
}
