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

void	set_background(int a, t_game *game, char *l)
{
	char **str;
	char *tmp;

	tmp = ft_substr(l, 2, (ft_strlen(l) - 3));
	str = ft_split(tmp, ',');
	if (ft_size(str) == 3 && str_is_digit(str))
	{
		if (a == 0)
		{
			game->texture.floor[0] = ft_atoi(str[0]);
			game->texture.floor[1] = ft_atoi(str[1]);
			game->texture.floor[2] = ft_atoi(str[2]);
		}
		if (a == 1)
		{
			game->texture.sky[0] = ft_atoi(str[0]);
			game->texture.sky[1] = ft_atoi(str[1]);
			game->texture.sky[2] = ft_atoi(str[2]);
		}
	}
	ft_free_tab(str);
	free(tmp);
}

void	set_texture(int a, t_game *game, char *l)
{
	if(a == 0)
		game->texture.NO = ft_substr(l, 3, (ft_strlen(l) - 4));
	if(a == 1)
		game->texture.SO = ft_substr(l, 3, (ft_strlen(l) - 4));
	if(a == 2)
		game->texture.WE = ft_substr(l, 3, (ft_strlen(l) - 4));
	if(a == 3)
		game->texture.EA = ft_substr(l, 3, (ft_strlen(l) - 4));
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

void	parse_texture(t_game *game)
{
	int i;
	int ctrl;

	i = 0;
	ctrl = 1;
	while(game->map.map[i] && ctrl < 7)
	{
		if(ft_strncmp(game->map.map[i], "NO",  2) == 0 && ++ctrl)
			set_texture(0, game, game->map.map[i]);
		if(ft_strncmp(game->map.map[i], "SO",  2) == 0 && ++ctrl)
			set_texture(1, game, game->map.map[i]);
		if(ft_strncmp(game->map.map[i], "WE",  2) == 0 && ++ctrl)
			set_texture(2, game, game->map.map[i]);
		if(ft_strncmp(game->map.map[i], "EA",  2) == 0 && ++ctrl)
			set_texture(3, game, game->map.map[i]);
		if(ft_strncmp(game->map.map[i], "F",  1) == 0 && ++ctrl)
			set_background(0, game, game->map.map[i]);
		if(ft_strncmp(game->map.map[i], "C",  1) == 0 && ++ctrl)
			set_background(1, game, game->map.map[i]);
		i++;
	}
	if(ctrl == 7)
	{
		while (line_is_empty(game->map.map[i]))
			i++;
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
}
