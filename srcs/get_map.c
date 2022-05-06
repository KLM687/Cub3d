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

char	*cpy(char *dest, char *src)
{
	int i;

	i = 0;
	while(src[i])
	{
		if (src[i] == '\n')
			return(dest);
		if (src[i] == '\t')
			src[i] = ' ';
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

int  longest_str(char **map)
{
    int i;
    int size;
    int longest;

	i = 0;
	size = 0;
	longest = ft_strlen(map[i]);
	while(map[i])
	{
		size = ft_strlen(map[i]);
		if (size > longest)
			longest = size;
		i++;
	}
    return (longest);
}

char **square_map(char **map)
{
    int 	longest;
	int 	i;
	char 	*str;

    longest = longest_str(map);
	i = 0;
	while (map[i])
	{
		str = malloc(sizeof(char) * longest);
		ft_memset(str, ' ', longest);
		str = cpy(str, map[i]);
		free(map[i]);
		map[i] = str;
		i++;
	}
	return (map);
}


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

void	get_map(char *map, t_game *game)
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
	map_ret = square_map(map_ret);
	game->map.map = map_ret;
}