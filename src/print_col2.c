/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_col2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:58:35 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/23 03:59:12 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

void		print_col_block_char(t_stat_name name)
{
	ft_putstr(COL_BLU);
	ft_putstr(COL_CYA_BG);
	ft_putstr(name.name);
	ft_putstr(COL_RES);
}

void		print_col_exe(t_stat_name name)
{
	if (name.buf.st_mode & S_ISUID)
	{
		ft_putstr(COL_BLA);
		ft_putstr(COL_RED_BG);
	}
	else if (name.buf.st_mode & S_ISGID)
	{
		ft_putstr(COL_BLA);
		ft_putstr(COL_CYA_BG);
	}
	else
		ft_putstr(COL_RED);
	ft_putstr(name.name);
	ft_putstr(COL_RES);
}
