/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 05:06:11 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/22 00:39:41 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	swap(t_stat_name *p1, t_stat_name *p2)
{
	t_stat_name tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

static void	quicksort(t_stat_name *arr, int left, int right, int (*func)())
{
	int	i;
	int	last;
	
	if (left >= right)
		return ;
	swap(&arr[left], &arr[(left +right) / 2]);
	last = left;
	i = left + 1;
	while (i <= right)
	{
		if (func(arr[i], arr[left]) < 0)
			swap(&arr[++last], &arr[i]);
		++i;
	}
	swap(&arr[left], &arr[last]);
	quicksort(arr, left, last - 1, func);
	quicksort(arr, last + 1, right, func);
}

int			sorted(unsigned int options)
{
	return (options & LS_REV || options & LS_TIME);
}

static void	rev_arr(t_stat_name *arr, off_t len)
{
	int	i;
	
	i = 0;
	while (i < len / 2)
	{
		swap(&arr[i], &arr[len - i - 1]);
		++i;
	}
}

void	sort_arr(t_stat_name *arr, unsigned int options, off_t len)
{
	if (options & LS_TIME)
		quicksort(arr, 0, len - 1, comp_last_modif);
	if (options & LS_REV)
		rev_arr(arr, len);
}

