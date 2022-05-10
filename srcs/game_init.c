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

void	undraw_player(t_game *game)
{
	int x;
	int y;

	x = game->player.posX - 10;
	while (x < (game->player.posX + 10))
	{
		y = game->player.posY - 10;
		while (y < (game->player.posY + 10))
		{
			my_mlx_pixel_put(&game->windows, x, y, game->texture.s_rgb);
			y++;
		}
		x++;
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
			my_mlx_pixel_put(&game->windows, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
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
			if ((x % game->map.grid_size) == 0 || (y % game->map.grid_size) == 0)
				my_mlx_pixel_put(&game->windows, x, y, 0xFFFF00);
			//if else (y < (1024 / 2))
				//my_mlx_pixel_put(&game->windows, x, y, game->texture.f_rgb);
			else
				my_mlx_pixel_put(&game->windows, x, y, game->texture.s_rgb);
			y++;
		}
		x++;
	}	
}

void	move_up(t_game *game)
{
	undraw_player(game);
	game->player.posY -= 4;
	draw_background(game);
	draw_player(game);
}

void	move_left(t_game *game)
{
	undraw_player(game);
	game->player.posX -= 4;
	draw_player(game);
}

void move_right(t_game *game)
{
	undraw_player(game);
	game->player.posX += 4;
	draw_background(game);
	draw_player(game);
}

void move_down(t_game *game)
{
	undraw_player(game);
	game->player.posY += 4;
	draw_background(game);
	draw_player(game);
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
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.windows, game->windows.img , 0, 0);
	return (0);
}

void	game_init(t_game *game)
{


	game->mlx.mlx = mlx_init();
	game->mlx.w_x = 1280;
	game->mlx.w_y = 1024;
	game->mlx.windows = mlx_new_window(game->mlx.mlx,
			game->mlx.w_x, game->mlx.w_y, "CUB3333333333D");

	game->player.posX = (1280 / 2);
	game->player.posY = (1024 / 2);
	
	game = open_img(game);
	
	game->windows.img = mlx_new_image(game->mlx.mlx, 1280, 1024);
	game->windows.addr = mlx_get_data_addr(game->windows.img, &game->windows.byte_p, &game->windows.line_l, &game->windows.end);

	game->texture.f_rgb = create_rgb(game->texture.floor[0], game->texture.floor[1], game->texture.floor[2]);
	game->texture.s_rgb = create_rgb(game->texture.sky[0], game->texture.sky[1], game->texture.sky[2]);

	draw_background(game);
	draw_player(game);

	mlx_put_image_to_window(game->mlx.mlx, game->mlx.windows, game->windows.img , 0, 0);
 
	mlx_hook(game->mlx.windows, 2, 1L<<0, input, game);
	mlx_hook(game->mlx.windows, 33, 1l << 5,0 , game);
	mlx_loop(game->mlx.mlx);
}