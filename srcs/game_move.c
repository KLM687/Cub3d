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
	float tmpX;
	float tmpY;

	tmpX = game->player.posX;
	tmpY = game->player.posY;
	game->player.posX += game->player.dirX * 0.05;
	game->player.posY += game->player.dirY * 0.05;
	if (!check_move(game))
	{
		game->player.posX = tmpX;
		game->player.posY = tmpY;
	}
}

void	move_right(t_game *game)
{
	float tmpX;
	float tmpY;

	tmpX = game->player.posX;
	tmpY = game->player.posY;
    game->player.posX += game->player.dirY * 0.02;
    game->player.posY -= game->player.dirX * 0.02;
	if (!check_move(game))
	{
		game->player.posX = tmpX;
		game->player.posY = tmpY;
	}
}	

void    move_left(t_game *game)
{
	float tmpX;
	float tmpY;

	tmpX = game->player.posX;
	tmpY = game->player.posY;
    game->player.posX -= game->player.dirY * 0.02;
    game->player.posY += game->player.dirX * 0.02;
	if (!check_move(game))
	{
		game->player.posX = tmpX;
		game->player.posY = tmpY;
	}
}

void    move_down(t_game *game)
{
	float tmpX;
	float tmpY;

	tmpX = game->player.posX;
	tmpY = game->player.posY;
	game->player.posX -= game->player.dirX * 0.05;
	game->player.posY -= game->player.dirY * 0.05;
	if (!check_move(game))
	{
		game->player.posX = tmpX;
		game->player.posY = tmpY;
	}
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
	float rotSpeed = 0.01;
	double oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
    game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
    double oldPlaneX = game->player.planeX;
    game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
    game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
}

int	input(int key, t_game *game)
{
	if (key == 65307)
		free_and_destroy(game);
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

