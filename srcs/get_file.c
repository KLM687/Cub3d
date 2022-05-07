/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:04:17 by flee              #+#    #+#             */
/*   Updated: 2022/05/05 14:04:19 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int	count_line(char *file)
{
	int		fd;
	int		read_ret;
	char	c;
	int		x;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("error fd\n");
		exit (EXIT_FAILURE);
	}
	x = 1;
	while (1)
	{
		read_ret = read(fd, &c, 1);
		if (read_ret == 0)
			break ;
		if (read_ret < 0)
			return (-1);
		if (c == '\n')
			x++;
	}
	close(fd);
	return (x);
}

void	get_file(char *map, t_game *game)
{
    int fd;
	char *line;
    char **map_ret;
    int i;

	i = count_line(map);
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
    map_ret = malloc(sizeof(char *) * (i + 1));
    i = 0;
	while (line)
	{
        map_ret[i] = ft_strdup(line); 
		free(line);
		line = get_next_line(fd);
        i++;
	}
    map_ret[i] = 0;
	game->map.map = map_ret;
}