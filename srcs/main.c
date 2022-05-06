/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:08:08 by flee              #+#    #+#             */
/*   Updated: 2021/07/20 16:17:39 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int main (int argc, char **argv)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (argc != 2)
		return (0);
	get_map(argv[1], game);
	int i = 0;
	while(game->map.map[i] != 0)
	{
		printf("%s\n", game->map.map[i]);
		i++;
	}
	parse_map(game);
	ft_free_tab(game->map.map);
	free(game);
	return (0);
}
