/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 23:28:24 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/21 16:21:44 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_ls.h"

static int			valid_option(int c)
{
	char *valid_options;

	valid_options = "lRartGF";
	return (ft_strchr(valid_options, c) != NULL ? 1 : 0);
}

static unsigned int	get_options(int c)
{
	if (c == 'l')
		return (LS_LIST);
	else if (c == 'R')
		return (LS_REC);
	else if (c == 'a')
		return (LS_ALL);
	else if (c == 'r')
		return (LS_REV);
	else if (c == 't')
		return (LS_TIME);
	else if (c == 'G')
		return (LS_COLORS);
	else if (c == 'F')
		return (LS_TYPE);
	return (0);
}

static unsigned int	parse_options(int argc, char **argv, int *first_arg)
{
	unsigned int	options;
	int				c;

	*first_arg = 1;
	options = 0;
	while (--argc > 0 && *(argv[*first_arg]) == '-')
	{
		while ((c = *(++(argv[*first_arg]))) != '\0')
		{
			if (valid_option(c))
				options |= get_options(c);
			else
			{
				ft_printf("ls: illegal option -- %c\n", c);
				ft_printf("usage : ls [-lRartGF] [file ...]\n");
				exit(EXIT_FAILURE);
			}
		}
		++(*first_arg);
	}
	return (options);
}

int 				main(int argc, char *argv[])
{
	unsigned int	options;
	int				first_arg;

	options = parse_options(argc, argv, &first_arg);
	if (first_arg  == argc)
		list_dir(".", options);
	else
		list_dir_arg(argc - first_arg + 1, argv + first_arg - 1, options);
	exit(EXIT_SUCCESS);
}
