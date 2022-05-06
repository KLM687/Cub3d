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
	printf("---------------------------------------\n");
	int i = 0;
	while(game->map.map[i] != 0)
	{
		printf("%s", game->map.map[i]);
		i++;
	}
	printf("\n---------------------------------------\n\n");
	parse_map(game);
	printf("%s\n",game->texture.EA);
	printf("%s\n",game->texture.NO);
	printf("%s\n",game->texture.SO);
	printf("%s\n",game->texture.WE);
	printf("%d %d %d\n",game->texture.floor[0],game->texture.floor[1],game->texture.floor[2]);
	printf("%d %d %d\n",game->texture.sky[0],game->texture.sky[1],game->texture.sky[2]);
	printf("\n------------------das---------------------\n");
	i = 0;
	while(game->map.map[i] != 0)
	{
		printf("%s", game->map.map[i]);
		i++;
	}
	printf("\n---------------------------------------\n");
	square_map(game);
	printf("\n------------------square---------------------\n");
	i = 0;
	while(game->map.map[i] != 0)
	{
		printf("%s\n", game->map.map[i]);
		i++;
	}
	printf("\n---------------------------------------\n");
	free(game->texture.EA);
	free(game->texture.NO);
	free(game->texture.SO);
	free(game->texture.WE);
	ft_free_tab(game->map.map);
	free(game);
	return (0);
}