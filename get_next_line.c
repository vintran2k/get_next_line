/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:04:34 by vintran           #+#    #+#             */
/*   Updated: 2021/03/26 15:55:31 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_buf(char *s1, char *s2)
{
	char	*res;
	int		reslen;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	reslen = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(res = malloc(reslen)))
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}

char	*maj_file(char *file, int newline)
{
	char	*res;
	int		restlen;

	restlen = ft_strlen(file + newline);
	if (!(res = ft_strndup(file + newline, restlen)))
		return (NULL);
	free(file);
	return (res);
}

char	*get_line(char **file)
{
	char	*res;
	int		i;

	i = 0;
	while ((*file)[i] && (*file)[i] != '\n')
		i++;
	if (!(res = ft_strndup(*file, i)))
		return (NULL);
	if ((*file)[i] != '\n')
		i--;
	if (!(*file = maj_file(*file, i + 1)))
		return (NULL);
	return (res);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	static char	*file;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	ret = 1;
	while (ret && !is_newline(file))
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) == -1)
			return (-1);
		buf[ret] = '\0';
		if (!(file = join_buf(file, buf)))
			return (-1);
	}
	if (!(*line = get_line(&file)))
		return (-1);
	if (ret == 0)
	{
		free(file);
		return (ret);
	}
	return (1);
}
