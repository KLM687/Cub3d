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
}

t_game	*open_img(t_game *game)
{
	game->NO.img = mlx_xpm_file_to_image(game->mlx.mlx,
			game->texture.NO, &game->NO.byte_p, &game->NO.line_l);
	img_addr(game);
	return (game);
}

void	put_img(t_game *game, float x, float y)
{
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.windows,
			game->NO.img, y * IMG_SIZE, x * IMG_SIZE);
}

void	game_init(t_game *game)
{
	game->mlx.mlx = mlx_init();
	game->mlx.w_x = 1920;
	game->mlx.w_y = 1080;
	game->mlx.windows = mlx_new_window(game->mlx.mlx,
			game->mlx.w_x, game->mlx.w_y, "CUB3333333333D");
	
	game = open_img(game);
	for (float x = 0 ; x < 10 ; x += 0.1)
	{
		for(float y = 0 ; y < 10 ; y += 0.1)
		{
			put_img(game, x, y);
			usleep(1000);
		}
	}
	//display(game);
	//mlx_key_hook(game->mlx.windows, input, game);
	mlx_hook(game->mlx.windows, 33, 1l << 5,0 , game);
	mlx_loop(game->mlx.mlx);
}