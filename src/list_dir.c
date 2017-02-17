/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 01:00:34 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/17 04:38:00 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>

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

char		*add_dir(char *dir1, char *dir2)
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

t_stat_name			add_arr_entry(char *dir1, char *file)
{
	t_stat_name	ret;

	ret.name = ft_strdup(file);
	ret.full_name = add_dir(dir1, file);
	stat(ret.full_name, &ret.buf);
	return (ret);
}

static t_stat_name	*make_arr(char *dir, int *len)
{
	DIR				*dirp;
	struct dirent	*direntp;
	int				n_files;
	t_stat_name		*arr;

	n_files = count_files(dir);
	arr = (t_stat_name *)malloc(sizeof(t_stat_name) * (n_files + 1));
	*len = 0;
	dirp = opendir(dir);
	while ((direntp = (readdir(dirp))) != NULL)
	{
		arr[(*len)++] = add_arr_entry(dir, direntp->d_name);
	}
	closedir(dirp);
	return (arr);
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

int			sorted(unsigned int options)
{
	return (options & LS_REV || options & LS_TIME);
}

void		print_arr(t_stat_name *arr, unsigned int options, int len)
{
	int i;

	i = 0;
	while (i < len)
		printf("%s\n", arr[i++].name);
	(void)options;
}

void	sort_arr(t_stat_name *arr, unsigned int options)
{
	(void)arr;
	(void)options;
}

int			is_dir(struct stat buf)
{
	return ((buf.st_mode & S_IFMT) == S_IFDIR);
}

void		list_dir(char *dir, unsigned int options)
{
	DIR 		*dirp;
	t_stat_name	*arr;
	int			i;
	int			len;
	
	if ((dirp = opendir(dir)) == NULL)
	{
		printf("ls: %s: %s\n", dir, strerror(errno));
		return ;
	}
	arr = make_arr(dir, &len);
	if (sorted(options))
		sort_arr(arr, options);
	print_arr(arr, options, len);
	closedir(dirp);
	if (options & LS_REC)
	{
		i = 0;
		while (len--)
		{
			if (!ft_strequ(".", arr[i].name) && !ft_strequ("..", arr[i].name))
			{		
				if (is_dir(arr[i].buf))
				{
					printf("\n%s\n", arr[i].name);
					list_dir(arr[i].full_name, options);
				}
			}
			++i;
		}
	}
	free_arr(arr, len);
}
