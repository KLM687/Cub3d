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

/*int	img_pix_get(t_img *img, int x, int y)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_l + x * (img->byte_p / 8));
	
	return (ft_atoi(pixel));
}*/

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->byte_p / 8));
	*(unsigned int*)dst = color;
}

void 	verline(int x, int raycastingStart, int raycastingEnd, int side, t_game *game)
{
	int sky;
	//static int x;
	//int	y;

	side *= 1;
	sky = 0;
	while(sky < raycastingStart)
	{
		my_mlx_pixel_put(&game->windows, x, sky, game->texture.s_rgb);
		sky++;
	}
	/*if (x == 64)
		x = 0;
	y = 0;
	while (y < 64)
	{
		my_mlx_pixel_put(&game->windows, x, raycastingStart, my_mlx_pixel_get(game->NO,x , y ));
		y++;
	}*/
	while (raycastingEnd < 1280)
	{
		my_mlx_pixel_put(&game->windows, x, raycastingStart, game->texture.f_rgb);
		raycastingEnd++;
	}
}