/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:49:08 by flee              #+#    #+#             */
/*   Updated: 2022/05/30 11:49:10 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	free_parse(t_game *game)
{
	if (game->texture.EA != NULL)
		free(game->texture.EA);
	if (game->texture.NO != NULL)
		free(game->texture.NO);
	if (game->texture.SO != NULL)
		free(game->texture.SO);
	if (game->texture.WE != NULL)
		free(game->texture.WE);
	ft_free_tab(game->map.map);
	free(game);
}

int	free_and_destroy(t_game *game)
{
	mlx_destroy_image(game->mlx.mlx, game->NO.img);
	mlx_destroy_image(game->mlx.mlx, game->SO.img);
	mlx_destroy_image(game->mlx.mlx, game->WE.img);
	mlx_destroy_image(game->mlx.mlx, game->EA.img);
    mlx_destroy_image(game->mlx.mlx, game->windows.img);
	mlx_destroy_window(game->mlx.mlx, game->mlx.windows);
	mlx_destroy_display(game->mlx.mlx);
    free(game->texture.EA);
	free(game->texture.NO);
	free(game->texture.SO);
	free(game->texture.WE);
	ft_free_tab(game->map.map);
	free(game->mlx.mlx);
    free(game);
	exit (EXIT_SUCCESS);
}