/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_group.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 16:59:34 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/21 17:00:27 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <grp.h>
#include <uuid/uuid.h>
#include "ft_ls.h"
#include <pwd.h>
#include <sys/types.h>

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
