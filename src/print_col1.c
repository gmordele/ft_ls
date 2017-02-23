/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_col1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:55:45 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/23 03:56:15 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ls.h"

void		print_col_dir(t_stat_name name)
{
	if (name.buf.st_mode & S_IWOTH)
	{
		ft_putstr(COL_BLA);
		if (name.buf.st_mode & S_ISVTX)
			ft_putstr(COL_GRE_BG);
		else
			ft_putstr(COL_YEL_BG);
	}
	else
		ft_putstr(COL_BLU);
	ft_putstr(name.name);
	ft_putstr(COL_RES);
}

void		print_col_link(t_stat_name name)
{
	ft_putstr(COL_MAG);
	ft_putstr(name.name);
	ft_putstr(COL_RES);
}

void		print_col_sock(t_stat_name name)
{
	ft_putstr(COL_GRE);
	ft_putstr(name.name);
	ft_putstr(COL_RES);
}

void		print_col_fifo(t_stat_name name)
{
	ft_putstr(COL_YEL);
	ft_putstr(name.name);
	ft_putstr(COL_RES);
}

void		print_col_char_spec(t_stat_name name)
{
	ft_putstr(COL_BLU);
	ft_putstr(COL_YEL_BG);
	ft_putstr(name.name);
	ft_putstr(COL_RES);
}
