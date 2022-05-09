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

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->byte_p / 8));
	*(unsigned int*)dst = color;
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_background(t_game *game)
{
	int x = 0;
	int y = 0;
	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			//if (y < (1080 / 2))
			//	my_mlx_pixel_put(&game->windows, x, y, game->texture.f_rgb);
			//else
			my_mlx_pixel_put(&game->windows, x, y, game->texture.s_rgb);
			y++;
		}
		x++;
	}	
}

float square(float a)
{
	return (a * a);
}

float sq_dist(float x1, float y1, float x2, float y2)
{
	float dist_x;
	float dist_y;

	dist_x = square(x1 - x2);
	dist_y = square(y1 - y2);
	return (dist_x + dist_y);
}

int is_in_circle(float x, float y, float circleX, float circleY)
{
	float	distance;
	float	distance_sqrt;

	distance_sqrt = sqrtf(sq_dist(x, y, circleX, circleY));
	distance = distance_sqrt - 5;
	if (distance <= 0.00000000)
		return (1);
	return (0);
}

void	draw_player(t_game *game)
{
	int x;
	int y;

	x = 0;
	while (x < 1980)
	{
		y = 0;
		while (y < 1080)
		{
			if(!is_in_circle(x, y, game->player.posX, game->player.posY))
				my_mlx_pixel_put(&game->windows, x, y, game->texture.f_rgb);
			y++;
		}
		x++;
	}
}

void	game_init(t_game *game)
{


	game->mlx.mlx = mlx_init();
	game->mlx.w_x = 1920;
	game->mlx.w_y = 1080;
	game->mlx.windows = mlx_new_window(game->mlx.mlx,
			game->mlx.w_x, game->mlx.w_y, "CUB3333333333D");

	game->player.posX = (1980 / 2);
	game->player.posY = (1080 / 2);
	
	game = open_img(game);
	
	game->windows.img = mlx_new_image(game->mlx.mlx, 1920, 1080);
	game->windows.addr = mlx_get_data_addr(game->windows.img, &game->windows.byte_p, &game->windows.line_l, &game->windows.end);

	game->texture.f_rgb = create_rgb(game->texture.floor[0], game->texture.floor[1], game->texture.floor[2]);
	game->texture.s_rgb = create_rgb(game->texture.sky[0], game->texture.sky[1], game->texture.sky[2]);

	draw_background(game);
	draw_player(game);



	mlx_put_image_to_window(game->mlx.mlx, game->mlx.windows, game->windows.img , 0, 0);
 
	mlx_key_hook(game->mlx.windows, input, game);
	mlx_hook(game->mlx.windows, 33, 1l << 5,0 , game);
	mlx_loop(game->mlx.mlx);
}