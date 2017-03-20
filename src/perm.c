/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:55:20 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/21 00:07:26 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/xattr.h>
#include <sys/acl.h>
#include <stdio.h>

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
	if (buf.st_mode & S_IXUSR)
		perm[3] = (buf.st_mode & S_ISUID) ? 's' : 'x';
	else
		perm[3] = (buf.st_mode & S_ISUID) ? 'S' : '-';
	if (buf.st_mode & S_IXGRP)
		perm[6] = (buf.st_mode & S_ISGID) ? 's' : 'x';
	else
		perm[6] = (buf.st_mode & S_ISGID) ? 'S' : '-';
	if (buf.st_mode & S_IXOTH)
		perm[9] = (buf.st_mode & S_ISVTX) ? 't' : 'x';
	else
		perm[9] = (buf.st_mode & S_ISVTX) ? 'T' : '-';
}

static char	get_attr(t_stat_name entry)
{
	ssize_t		xattr;
	acl_t		acl;
	acl_entry_t tmp;

	xattr = listxattr(entry.full_name, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		return ('@');
	acl = acl_get_link_np(entry.full_name, ACL_TYPE_EXTENDED);
	if (acl != NULL)
		if (acl_get_entry(acl, ACL_FIRST_ENTRY, &tmp) == -1)
		{
			acl_free(acl);
			acl = NULL;
		}
	if (acl != NULL)
		return ('+');
	return (' ');
}

void		get_perm(char *perm, t_stat_name entry)
{
	perm[11] = '\0';
	perm[0] = get_type(entry.buf);
	get_read_write(perm, entry.buf);
	get_execute(perm, entry.buf);
	perm[10] = get_attr(entry);
}
