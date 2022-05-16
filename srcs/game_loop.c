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

void	draw(t_game *game);

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->byte_p / 8));
	*(unsigned int*)dst = color;
}

void	move_up(t_game *game)
{
	game->player.posX += game->player.dirX * 0.01;
	game->player.posY += game->player.dirY * 0.01;
	draw(game);
}

/*void	move_left(t_game *game)
{
}*/

/*void move_right(t_game *game)
{
}*/

void move_down(t_game *game)
{
	game->player.posX -= game->player.dirX * 0.01;
	game->player.posY -= game->player.dirY * 0.01;
	draw(game);
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
	draw(game);
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
	draw(game);
}


int	input(int key, t_game *game)
{
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

void 	verline(int x, int drawStart, int drawEnd, int color, t_game *game)
{
	int ground;

	ground = 0;
	while(ground < drawStart)
	{
		my_mlx_pixel_put(&game->windows, x, ground, 0x008000);
		ground++;
	}
	while (drawStart != drawEnd)
	{
		my_mlx_pixel_put(&game->windows, x, drawStart, color);
		drawStart++;
	}
	while (drawStart < 1280)
	{
		my_mlx_pixel_put(&game->windows, x, drawStart, 0x00FF00);
		drawStart++;
	}
}

void	draw(t_game *game)
{
	double w = 1920;
		for(int x = 0; x < w; x+=2)
    	{
      		double cameraX = 2 * x / w - 1;
      		double rayDirX = game->player.dirX + game->player.planeX * cameraX;
      		double rayDirY = game->player.dirY + game->player.planeY * cameraX;

			int mapX = (int)game->player.posX;
      		int mapY = (int)game->player.posY;
			
			double sideDistX;
      		double sideDistY;

      		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
      		double perpWallDist;

      		int stepX;
      		int stepY;
			int hit = 0;
      		int side; 

     		if (rayDirX < 0)
      		{
        		stepX = -1;
        		sideDistX = (game->player.posX - mapX) * deltaDistX;
      		}
      		else
      		{
      			stepX = 1;
    			sideDistX = (mapX + 1.0 - game->player.posX) * deltaDistX;
     		}
      		if (rayDirY < 0)
      		{
       			stepY = -1;
        		sideDistY = (game->player.posY - mapY) * deltaDistY;
      		}
      		else
      		{
        		stepY = 1;
        		sideDistY = (mapY + 1.0 - game->player.posY) * deltaDistY;
    		}
			while (hit == 0)
      		{
        		if (sideDistX < sideDistY)
        		{
        		  sideDistX += deltaDistX;
        		  mapX += stepX;
        		  side = 0;
        		}
        		else
        		{
        		  sideDistY += deltaDistY;
        		  mapY += stepY;
        		  side = 1;
        		}
        		if (game->map.map[mapX][mapY] == '1')
					hit = 1;
			}
			if(side == 0) 
				perpWallDist = (sideDistX - deltaDistX);
   	   		else        
			  	perpWallDist = (sideDistY - deltaDistY);

			int h = 1280;

			int lineHeight = (int)(h / perpWallDist);

    		int drawStart = -lineHeight / 2 + h / 2;
      		if(drawStart < 0)
			  	drawStart = 0;
      		int drawEnd = lineHeight / 2 + h / 2;
      		if (drawEnd >= h || drawEnd < 0)
			  	drawEnd = h;
			if(side == 1)
				verline(x, drawStart, drawEnd, 0xCD5C5C, game);
			else
				verline(x , drawStart, drawEnd, 0xF08080, game);
		}
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.windows, game->windows.img , 0, 0);
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
	draw(game);

	mlx_hook(game->mlx.windows, 2, 1L<<0, input, game);
	mlx_hook(game->mlx.windows, 33, 1l << 5,0 , game);
	mlx_loop(game->mlx.mlx);

}