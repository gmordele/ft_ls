/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 00:22:00 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/22 00:35:31 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/stat.h"
#include "ft_ls.h"

int		comp_size(t_stat_name p1, t_stat_name p2)
{
	return (p1.buf.st_size - p2.buf.st_size);
}

int		comp_last_modif(t_stat_name p1, t_stat_name p2)
{
	return (p2.buf.st_mtimespec.tv_sec - p1.buf.st_mtimespec.tv_sec);
}
