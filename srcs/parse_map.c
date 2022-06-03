/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:42:07 by flee              #+#    #+#             */
/*   Updated: 2022/05/05 15:42:29 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	set_background(int bck, t_game *game, char **RGB)
{
	if (ft_size(RGB) == 3 && str_is_digit(RGB))
	{
		if (bck == 0)
		{
			game->texture.floor[0] = ft_atoi(RGB[0]);
			game->texture.floor[1] = ft_atoi(RGB[1]);
			game->texture.floor[2] = ft_atoi(RGB[2]);
		}
		if (bck == 1)
		{
			game->texture.sky[0] = ft_atoi(RGB[0]);
			game->texture.sky[1] = ft_atoi(RGB[1]);
			game->texture.sky[2] = ft_atoi(RGB[2]);
		}
	}
}

int search_bck(t_game *game, char *str)
{
	char **line;
	char **RGB;

	str = whitespace(str);
	line = ft_split(str, ' ');
	if (ft_size(line) != 2)
		return (ft_free_tab(line),(0));
	RGB = ft_split(line[1], ',');
	if (ft_size(RGB) != 3)
		return (ft_free_tab(line), ft_free_tab(RGB), (0));
	else if (ft_strncmp(line[0], "F", ft_strlen(line[0])) == 0)
		set_background(0, game, RGB);
	else if (ft_strncmp(line[0], "C", ft_strlen(line[0])) == 0)
		set_background(1, game, RGB);
	else 
		return (ft_free_tab(line), ft_free_tab(RGB), (0));
	return (ft_free_tab(line), ft_free_tab(RGB), (1));
}

int search_id(t_game *game, char *str)
{
	char **line;
	
	str = whitespace(str);
	line = ft_split(str, ' ');
	if ((ft_size(line)) != 2)
		return ((ft_free_tab(line)), (0));
	if (ft_strncmp(line[0], "N", ft_strlen(line[0])) == 0
			|| ft_strncmp(line[0], "NO", ft_strlen(line[0])) == 0)
		game->texture.NO = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "S", ft_strlen(line[0])) == 0
			|| ft_strncmp(line[0], "SO", ft_strlen(line[0])) == 0)
		game->texture.SO = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "W", ft_strlen(line[0])) == 0
			|| ft_strncmp(line[0], "WE", ft_strlen(line[0])) == 0)
		game->texture.WE = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "E", ft_strlen(line[0])) == 0
			|| ft_strncmp(line[0], "EA", ft_strlen(line[0])) == 0)
		game->texture.EA = ft_strdup(line[1]);
	else	
		return ((ft_free_tab(line)), (0));
	return ((ft_free_tab(line)), (1));
}


bool	parse_texture(t_game *game)
{
	int i;
	int ctrl;

	i = 0;
	ctrl = 1;
	while(game->map.map[i] && ctrl < 7)
	{
		if (search_id(game, game->map.map[i]))
			ctrl++;
		if (search_bck(game, game->map.map[i]))
			ctrl++;
		i++;
	}
	if(ctrl != 7 || i == ft_size(game->map.map))
		return (0);
	while (line_is_empty(game->map.map[i]) && (i + 1) < ft_size(game->map.map))
		i++;
	if ((ft_size(game->map.map) != i))
	{
		game->map.map = ft_popTab(game->map.map, i);
		return (1);
	}
	return (0);
}

void	parse_map(t_game *game)
{
	game->texture.floor[0] = -1;
	game->texture.floor[1] = -1;
	game->texture.floor[2] = -1;
	game->texture.sky[0] = -1;
	game->texture.sky[1] = -1;
	game->texture.sky[2] = -1;
	game->player.posX = -1;
	game->player.posY = -1;
	game->texture.EA = NULL;
	game->texture.SO = NULL;
	game->texture.NO = NULL;
	game->texture.WE = NULL;
	if (!parse_texture(game) || !check_info(game))
	{
		free_parse(game);
		return (printf("Problem in description\n"), exit (0));
	}
}
