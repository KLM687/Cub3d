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

bool	str_is_digit(char **str)
{
	int i;
	int a;

	i = 0;
	while (str[i])
	{
		a = 0;
		while(str[i][a])
		{
			if (!ft_isdigit(str[i][a]))
				return (0);
			a++;
		}
		i++;
	}
	return (1);
}

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

char *whitespace(char *str)
{
	int i; 
	
	i = 0;
	while (str[i])
	{
		if (str[i] >= 9 && str[i] <= 13)
			str[i] = 32;
		i++;
	}
	return (str);
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

bool	line_is_empty(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
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


void	parse_texture(t_game *game)
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
	if(ctrl == 7)
	{
		while (line_is_empty(game->map.map[i]))
			i++;
		if (ft_size(game->map.map) != i)
			game->map.map = ft_popTab(game->map.map, i);
	}
}

void	parse_map(t_game *game)
{
	game->texture.floor[0] = -1;
	game->texture.floor[1] = -1;
	game->texture.floor[2] = -1;
	game->texture.sky[0] = -1;
	game->texture.sky[1] = -1;
	game->texture.sky[2] = -1;
	parse_texture(game);
	printf("NO = %s\n", game->texture.NO);
	printf("SO = %s\n", game->texture.SO);
	printf("WE = %s\n", game->texture.WE);
	printf("EA = %s\n", game->texture.EA);
	printf("sky %d,%d,%d\n", game->texture.sky[0], game->texture.sky[1], game->texture.sky[2]);
	printf("floor %d,%d,%d\n", game->texture.floor[0], game->texture.floor[1], game->texture.floor[2]);
}
