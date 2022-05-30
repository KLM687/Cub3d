/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:28:50 by flee              #+#    #+#             */
/*   Updated: 2022/05/16 09:28:51 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

unsigned int	img_pix_get(t_img *img, int x, int y)
{
	char    *pixel;
	char    *pixel1;
	char    *pixel2;

    pixel = img->addr + (y * img->line_l + x * (img->byte_p / 8));
    pixel1 = img->addr + (y * img->line_l + x * (img->byte_p / 8));
    pixel2 = img->addr + (y * img->line_l + x * (img->byte_p / 8));
	pixel1++;
	pixel += 2;

	return ((*(int *)pixel << 16 | *(int *)pixel1 << 8 | *(int *)pixel2));
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->byte_p / 8));
	*(unsigned int*)dst = color;
}

void 	put_tex(t_game *game, int x)
{
	if (game->ray.side == 0 && game->ray.mapX >= game->player.posX)
		my_mlx_pixel_put(&game->windows, x, game->ray.drawStart, 
			img_pix_get(&game->NO, game->ray.texX, game->ray.texY));
	else if (game->ray.side == 0 && game->ray.mapX <= game->player.posX)
		my_mlx_pixel_put(&game->windows, x, game->ray.drawStart, 
			img_pix_get(&game->SO, game->ray.texX, game->ray.texY));
	else if(game->ray.side == 1 && game->ray.mapY <= game->player.posY)
		my_mlx_pixel_put(&game->windows, x, game->ray.drawStart, 
			img_pix_get(&game->WE, game->ray.texX, game->ray.texY));
	else if (game->ray.side == 1 && game->ray.mapY >= game->player.posY)
		my_mlx_pixel_put(&game->windows, x, game->ray.drawStart, 
			img_pix_get(&game->EA, game->ray.texX, game->ray.texY));
}

void	verline(t_game *game, int x, int sky)
{
	while(sky < game->ray.drawStart)
	{
		my_mlx_pixel_put(&game->windows, x, sky, game->texture.s_rgb);
		sky++;
	}
	while(game->ray.drawStart < game->ray.drawEnd)
    {
    	game->ray.texY = (int)game->ray.texPos & (tex_size - 1);
        game->ray.texPos += game->ray.step;
		put_tex(game, x);
		game->ray.drawStart++;
    }
	while (game->ray.drawEnd < windows_y)
	{
		my_mlx_pixel_put(&game->windows, x, game->ray.drawEnd, game->texture.f_rgb);
		game->ray.drawEnd++;
	}
}