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

void	set_texture(int a, t_game *game, char *str)
{
	int i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if(a == 0)
		game->texture.NO = ft_substr(str, i, (ft_strlen(str) - 4));
	if(a == 1)
		game->texture.SO = ft_substr(str, i, (ft_strlen(str) - 4));
	if(a == 2)
		game->texture.WE = ft_substr(str, i, (ft_strlen(str) - 4));
	if(a == 3)
		game->texture.EA = ft_substr(str, i, (ft_strlen(str) - 4));
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

int search_id(char *str)
{
	int i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i])
	{
		if (str[i] == 'N' || (str[i] == 'N' && str[i + 1] == 'O'))
			return (0);
	}
}


void	parse_texture(t_game *game)
{
	int i;
	int ctrl;

	i = 0;
	ctrl = 1;
	while(game->map.map[i] && ctrl < 7)
	{
		if(search_id(game->map.map[i]) == 0 && ++ctrl)
			set_texture(0, game, game->map.map[i]);
		if(search_id(game->map.map[i]) == 1 && ++ctrl)
			set_texture(1, game, game->map.map[i]);
		if(search_id(game->map.map[i]) == 2 && ++ctrl)
			set_texture(2, game, game->map.map[i]);
		if(search_id(game->map.map[i]) == 3 && ++ctrl)
			set_texture(3, game, game->map.map[i]);
		if(search_id(game->map.map[i]) == 4 && ++ctrl)
			set_background(0, game, game->map.map[i]);
		if(search_id(game->map.map[i]) == 5 && ++ctrl)
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
