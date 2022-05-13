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

void 	draw_vector(t_game *game)
{
	int i;
	int x;
	int y;

	i = 0;
	x = game->player.posX;
	y = game->player.posY;
	while (i < 50)
	{
		x += game->player.dirX;
		y += game->player.dirY;
		if ((x < 1280 && y < 1000) && (x > 0 && y > 0))	
			my_mlx_pixel_put(&game->windows, x, y, 0xFFFFFF);
		i++;
	}
}

void 	draw_player(t_game *game)
{
	int x;
	int y;

	x = game->player.posX - 10;
	while (x < (game->player.posX + 10))
	{
		y = game->player.posY - 10;
		while (y < (game->player.posY + 10))
		{
			if (x < 1280 && y < 1000 && x > 0 && y > 0)
				my_mlx_pixel_put(&game->windows, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
	//-----------------------draw direction--------------------------//

}

void	img_addr(t_game *game)
{
	game->NO.addr = mlx_get_data_addr(game->NO.img,
			&game->NO.byte_p, &game->NO.line_l, &game->NO.end);
	game->EA.addr = mlx_get_data_addr(game->EA.img,
			&game->EA.byte_p, &game->EA.line_l, &game->EA.end);
	game->SO.addr = mlx_get_data_addr(game->SO.img,
			&game->SO.byte_p, &game->SO.line_l, &game->SO.end);
	game->WE.addr = mlx_get_data_addr(game->WE.img,
			&game->WE.byte_p, &game->WE.line_l, &game->WE.end);
}

t_game	*open_img(t_game *game)
{
	game->NO.img = mlx_xpm_file_to_image(game->mlx.mlx,
			game->texture.NO, &game->NO.byte_p, &game->NO.line_l);
	game->EA.img = mlx_xpm_file_to_image(game->mlx.mlx,
			game->texture.EA, &game->EA.byte_p, &game->EA.line_l);
	game->SO.img = mlx_xpm_file_to_image(game->mlx.mlx,
			game->texture.SO, &game->SO.byte_p, &game->SO.line_l);
	game->WE.img = mlx_xpm_file_to_image(game->mlx.mlx,
			game->texture.WE, &game->WE.byte_p, &game->WE.line_l);
	img_addr(game);
	return (game);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_background(t_game *game)
{
	int x = 0;
	int y = 0;
	while (x < 1280)
	{
		y = 0;
		while (y < 1024)
		{
			if (y < (1024 / 2))
				my_mlx_pixel_put(&game->windows, x, y, game->texture.f_rgb);
			else
				my_mlx_pixel_put(&game->windows, x, y, game->texture.s_rgb);
			y++;
		}
		x++;
	}
}

void	move_up(t_game *game)
{
	game->player.posX += game->player.dirX;
	game->player.posY += game->player.dirY;

	draw_background(game);
	draw_player(game);
	draw_vector(game);
}

void	move_left(t_game *game)
{
	double tmp_pa = game->player.pa - (pi / 2);
	if (tmp_pa < 0)
		tmp_pa += 2*pi;
	double dirX = cos(tmp_pa) * 5;
	double dirY = sin(tmp_pa) * 5;
	game->player.posX += dirX;
	game->player.posY += dirY;
	draw_background(game);
	draw_player(game);
	draw_vector(game);
}

void move_right(t_game *game)
{
	double tmp_pa = game->player.pa + (pi / 2);
	if (tmp_pa < 2*pi)
		tmp_pa -= 2*pi;
	double dirX = cos(tmp_pa) * 5;
	double dirY = sin(tmp_pa) * 5;
	game->player.posX += dirX;
	game->player.posY += dirY;
	draw_background(game);
	draw_player(game);
	draw_vector(game);
}

void move_down(t_game *game)
{
	game->player.posX -= game->player.dirX;
	game->player.posY -= game->player.dirY;
	draw_background(game);
	draw_player(game);
	draw_vector(game);	
}

void rotate_left(t_game *game)
{
	game->player.pa -= 0.1;
	if (game->player.pa < 0)
		game->player.pa += 2*pi;
	game->player.dirX = cos(game->player.pa) * 5;
	game->player.dirY = sin(game->player.pa) * 5;
	draw_background(game);
	draw_player(game);
	draw_vector(game);
}

void rotate_right(t_game *game)
{
	game->player.pa += 0.1;
	if (game->player.pa > 2*pi)
		game->player.pa -= 2*pi;
	game->player.dirX = cos(game->player.pa) * 5;
	game->player.dirY = sin(game->player.pa) * 5;
	draw_background(game);
	draw_player(game);
	draw_vector(game);

}


int	input(int key, t_game *game)
{
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
	printf("x = %f y = %f\n", game->player.posX, game->player.posY);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.windows, game->windows.img , 0, 0);
	return (0);
}

void 	verline(int x, int drawStart, int drawEnd, int color, t_game *game)
{
	while (drawStart != drawEnd)
	{
		my_mlx_pixel_put(&game->windows, x, drawStart, color);
		drawStart++;
	}
}

void	game_init(t_game *game)
{


	game->mlx.mlx = mlx_init();
	game->mlx.w_x = 1920;
	game->mlx.w_y = 1280;
	game->mlx.windows = mlx_new_window(game->mlx.mlx,
			game->mlx.w_x, game->mlx.w_y, "CUB3333333333D");

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
	game->player.dirX = -1;
	game->player.dirY = 0;
	game->player.pa = 0;
	
	game = open_img(game);
	
	game->windows.img = mlx_new_image(game->mlx.mlx, 1920, 1280);
	game->windows.addr = mlx_get_data_addr(game->windows.img, &game->windows.byte_p, &game->windows.line_l, &game->windows.end);

	game->texture.f_rgb = create_rgb(game->texture.floor[0], game->texture.floor[1], game->texture.floor[2]);
	game->texture.s_rgb = create_rgb(game->texture.sky[0], game->texture.sky[1], game->texture.sky[2]);

	//draw_background(game);
	//draw_player(game);
	//draw_vector(game);
	
	//mlx_put_image_to_window(game->mlx.mlx, game->mlx.windows, game->windows.img , 0, 0);

	game->player.planeX = 0;
	game->player.planeY = 0.66;

	double w = 1920;
	while (1)
	{
		//draw_background(game);
		for(int x = 0; x < w; x++)
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
      		if(drawStart < 0)drawStart = 0;
      			int drawEnd = lineHeight / 2 + h / 2;
      		if(drawEnd >= h)drawEnd = h - 1;
			
			if(side == 1)
				verline(x, drawStart, drawEnd, 0xCD5C5C, game);
			else
				verline(x , drawStart, drawEnd, 0xF08080, game);
		}
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.windows, game->windows.img , 0, 0);
	}


 
	mlx_hook(game->mlx.windows, 2, 1L<<0, input, game);
	mlx_hook(game->mlx.windows, 33, 1l << 5,0 , game);
	mlx_loop(game->mlx.mlx);
}