/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:54:15 by flee              #+#    #+#             */
/*   Updated: 2022/05/07 16:54:18 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->byte_p / 8));
	*(unsigned int*)dst = color;
}

void	move_up(t_game *game)
{
	game->player.posX += game->player.dirX * 0.1;
	game->player.posY += game->player.dirY * 0.1;
}

/*void	move_left(t_game *game)
{
}*/

/*void move_right(t_game *game)
{
}*/

void move_down(t_game *game)
{
	game->player.posX -= game->player.dirX * 0.1;
	game->player.posY -= game->player.dirY * 0.1;
}

void rotate_right(t_game *game)
{
	float rotSpeed = 0.01;
	double oldDirX = game->player.dirX;
	game->player.dirX = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
    game->player.dirY = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);
    double oldPlaneX = game->player.planeX;
    game->player.planeX = game->player.planeX * cos(-rotSpeed) - game->player.planeY * sin(-rotSpeed);
    game->player.planeY = oldPlaneX * sin(-rotSpeed) + game->player.planeY * cos(-rotSpeed);
}

void rotate_left(t_game *game)
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
	usleep(500);
	if (key == 65307)
		printf("FREEEEE on PROOOOOGREEESS\n");
	//else if (key == 97)
	//	move_left(game);
	else if (key == 119)
		move_up(game);
	else if (key == 115)
		move_down(game);
	//else if (key == 100)
	//	move_right(game);
	else if (key == 65361)
		rotate_left(game);
	else if (key == 65363)
		rotate_right(game);
	return (0);
}

void 	verline(int x, int raycastingStart, int raycastingEnd, int color, t_game *game)
{
	int ground;

	ground = 0;
	while(ground < raycastingStart)
	{
		my_mlx_pixel_put(&game->windows, x, ground, 0x008000);
		ground++;
	}
	while (raycastingStart != raycastingEnd)
	{
		my_mlx_pixel_put(&game->windows, x, raycastingStart, color);
		raycastingStart++;
	}
	while (raycastingStart < 1280)
	{
		my_mlx_pixel_put(&game->windows, x, raycastingStart, 0x00FF00);
		raycastingStart++;
	}
}

void	get_player(t_game *game)
{
	int z;
	int s;
	
	z = 0;
	while(game->map.map[z])
	{
		s = 0;
		while(game->map.map[z][s]) 
		{
			if (game->map.map[z][s] == 'P')
			{
				game->player.posX = z;
				game->player.posY = s;
			}
			s++;
		}
		z++;
	}
	game->player.planeX = 0;
	game->player.planeY = 0.66;
}

int test_render(t_game *game)
{
	raycasting(game);
	return (1);
}

void	game_loop(t_game *game)
{
	game->mlx.mlx = mlx_init();
	game->mlx.windows = mlx_new_window(game->mlx.mlx,
			windows_x, windows_y, "CUB3333333333D");
 
	get_player(game);
	game->player.dirX = -1;
	game->player.dirY = 0;
	game->player.pa = 0;
	
	open_img(game);
	raycasting(game);
	mlx_loop_hook(game->mlx.mlx, &test_render , game);
	mlx_hook(game->mlx.windows, 2, 1L<<0 , input, game);
	mlx_hook(game->mlx.windows, 33, 1l << 5,0 , game);
	mlx_loop(game->mlx.mlx);


}