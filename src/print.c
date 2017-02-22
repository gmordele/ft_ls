/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 21:37:24 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/22 21:39:41 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

void		print_arr(t_stat_name *arr, unsigned int options, int len)
{
	int i;

	i = 0;
	while (i < len)
		printf("%s\n", arr[i++].name);
	(void)options;
}
