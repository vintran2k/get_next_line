/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 15:55:40 by vintran           #+#    #+#             */
/*   Updated: 2021/03/26 15:56:56 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		main(int ac, char **av)
{
	int		fd;
	int		ret;
	char	*line;

	fd = 0;
	if (ac <= 2)
	{
		if (ac == 2)
		{
			if ((fd = open(av[1], O_RDONLY)) == -1)
			{
				printf("open() failled\n");
				return (0);
			}
		}
		ret = 1;
		while (ret)
		{
			ret = get_next_line(fd, &line);
			if (ret == -1)
			{
				printf("error in GNL\n");
				return (0);
			}
			printf("ret = %d pour line = |%s|\n", ret, line);
			free(line);
		}
		close(fd);
	}
	return (0);
}
