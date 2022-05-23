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

	if(argc != 2)
		return (0);
	game = malloc(sizeof(t_game));
	get_file(argv[1], game);
	parse_map(game);
	square_map(game);
	parse_wall(game);
	//game_loop(game);
	free(game->texture.EA);
	free(game->texture.NO);
	free(game->texture.SO);
	free(game->texture.WE);
	ft_free_tab(game->map.map);
	free(game);
	return (0);
}