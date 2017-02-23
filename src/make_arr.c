/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 04:55:02 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/23 01:10:38 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

static char	*add_dir(char *dir1, char *dir2)
{
	int size;
	char *ret;
	int i;

	size = ft_strlen(dir1) + ft_strlen(dir2) + 1;
	ret = malloc(size + 1);
	i = 0;
	while (*dir1)
		ret[i++] = *(dir1++);
	ret[i++] = '/';
	while (*dir2)
		ret[i++] = *(dir2++);
	ret[i++] = '\0';
	return (ret);
}

static int	count_files(char *dir)
{
	DIR				*dirp;
	struct dirent	*direntp;
	int				n_files;

	n_files = 0;
	dirp = opendir(dir);
	while ((direntp = readdir(dirp)) != NULL)
		++n_files;
	closedir(dirp);
	return (n_files);
}

static t_stat_name			add_arr_entry(char *dir1, char *file)
{
	t_stat_name	ret;

	ret.name = ft_strdup(file);
	ret.full_name = add_dir(dir1, file);
	lstat(ret.full_name, &ret.buf);
	return (ret);
}

void		free_arr(t_stat_name *arr, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(arr[i].name);
		free(arr[i].full_name);
		++i;
	}
	free(arr);
}

t_stat_name	*make_arr(char *dir, int *len, off_t *max_size, unsigned options)
{
	DIR				*dirp;
	struct dirent	*direntp;
	int				n_files;
	t_stat_name		*arr;

	*max_size = 0;
	n_files = count_files(dir);
	arr = (t_stat_name *)malloc(sizeof(t_stat_name) * (n_files + 1));
	*len = 0;
	dirp = opendir(dir);
	while ((direntp = (readdir(dirp))) != NULL)
	{
		if ((direntp->d_name)[0] != '.' || options & LS_ALL)
		{
			arr[*len] = add_arr_entry(dir, direntp->d_name);
			*max_size = *max_size > arr[*len].buf.st_size ?
				*max_size : arr[*len].buf.st_size;
			(*len)++;
		}
	}
	closedir(dirp);
	return (arr);
}
