/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 05:06:11 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/17 05:10:22 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ft_ls.h"

int			sorted(unsigned int options)
{
	return (options & LS_REV || options & LS_TIME);
}

void	sort_arr(t_stat_name *arr, unsigned int options, off_t len)
{
	(void)arr;
	(void)options;
	(void)len;
}
