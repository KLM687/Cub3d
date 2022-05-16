/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:02:15 by flee              #+#    #+#             */
/*   Updated: 2022/05/16 14:02:16 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	move_up(t_game *game)
{
	game->player.posX += game->player.dirX * 0.1;
	game->player.posY += game->player.dirY * 0.1;
}

void	move_right(t_game *game)
{
    game->player.posX += game->player.dirY * 0.1;
    game->player.posY -= game->player.dirX * 0.1;
}

void    move_left(t_game *game)
{
    game->player.posX -= game->player.dirY * 0.1;
    game->player.posY += game->player.dirX * 0.1;
}

void    move_down(t_game *game)
{
	game->player.posX -= game->player.dirX * 0.1;
	game->player.posY -= game->player.dirY * 0.1;
}

void    rotate_right(t_game *game)
{
	float rotSpeed = 0.05;
	double oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
    game->player.dirY = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);
    double oldPlaneX = game->player.planeX;
    game->player.planeX = game->player.planeX * cos(-rotSpeed) - game->player.planeY * sin(-rotSpeed);
    game->player.planeY = oldPlaneX * sin(-rotSpeed) + game->player.planeY * cos(-rotSpeed);
}

void    rotate_left(t_game *game)
{
	float rotSpeed = 0.05;
	double oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
    game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
    double oldPlaneX = game->player.planeX;
    game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
    game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
}

int	input(int key, t_game *game)
{
	usleep(500);
	if (key == 65307)
		printf("FREEEEE on PROOOOOGREEESS\n");
	else if (key == 97)
		move_left(game);
	else if (key == 119)
		move_up(game);
	else if (key == 115)
		move_down(game);
	else if (key == 100)
		move_right(game);
	else if (key == 65361)
		rotate_left(game);
	else if (key == 65363)
		rotate_right(game);
	return (0);
}

