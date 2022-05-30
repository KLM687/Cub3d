/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 09:28:37 by flee              #+#    #+#             */
/*   Updated: 2022/05/16 09:28:40 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

void	raycasting(t_game *game)
{
	double w = windows_x;
		for(int x = 0; x < w; x++)
    	{
      		game->ray.cameraX = 2 * x / w - 1;
      		game->ray.rayDirX = game->player.dirX + game->player.planeX * game->ray.cameraX;
      		game->ray.rayDirY = game->player.dirY + game->player.planeY * game->ray.cameraX;

			game->ray.mapX = (int)game->player.posX;
      		game->ray.mapY = (int)game->player.posY;
			

      		game->ray.deltaDistX = (game->ray.rayDirX == 0) ? 1e30 : fabs(1 / game->ray.rayDirX);
      		game->ray.deltaDistY = (game->ray.rayDirY == 0) ? 1e30 : fabs(1 / game->ray.rayDirY);

			game->ray.hit = 0;

     		if (game->ray.rayDirX < 0)
      		{
        		game->ray.stepX = -1;
        		game->ray.sideDistX = (game->player.posX - game->ray.mapX) * game->ray.deltaDistX;
      		}
      		else
      		{
      			game->ray.stepX = 1;
    			game->ray.sideDistX = (game->ray.mapX + 1.0 - game->player.posX) * game->ray.deltaDistX;
     		}
      		if (game->ray.rayDirY < 0)
      		{
       			game->ray.stepY = -1;
        		game->ray.sideDistY = (game->player.posY - game->ray.mapY) * game->ray.deltaDistY;
      		}
      		else
      		{
        		game->ray.stepY = 1;
        		game->ray.sideDistY = (game->ray.mapY + 1.0 - game->player.posY) * game->ray.deltaDistY;
    		}
			while (game->ray.hit == 0)
      		{
        		if (game->ray.sideDistX < game->ray.sideDistY)
        		{
        		  game->ray.sideDistX += game->ray.deltaDistX;
        		  game->ray.mapX += game->ray.stepX;
        		  game->ray.side = 0;
        		}
        		else
        		{
        		  game->ray.sideDistY += game->ray.deltaDistY;
        		  game->ray.mapY += game->ray.stepY;
        		  game->ray.side = 1;
        		}
        		if (game->map.map[game->ray.mapX][game->ray.mapY] == '1')
					game->ray.hit = 1;
			}
			if(game->ray.side == 0) 
				game->ray.perpWallDist = (game->ray.sideDistX - game->ray.deltaDistX);
   	   		else        
			  	game->ray.perpWallDist = (game->ray.sideDistY - game->ray.deltaDistY);

			int h = windows_y;

			game->ray.lineHeight = (int)(h / game->ray.perpWallDist);

    		game->ray.drawStart = -game->ray.lineHeight / 2 + h / 2;
      		if(game->ray.drawStart < 0)
			  	game->ray.drawStart = 0;
      		game->ray.drawEnd = game->ray.lineHeight / 2 + h / 2;
      		if (game->ray.drawEnd >= h || game->ray.drawEnd < 0)
			  	game->ray.drawEnd = h;
			

      		if (game->ray.side == 0) 
				game->ray.wallX = game->player.posY + game->ray.perpWallDist * game->ray.rayDirY;
      		else           
			  	game->ray.wallX = game->player.posX + game->ray.perpWallDist * game->ray.rayDirX;
      		game->ray.wallX -= floor((game->ray.wallX));

      		game->ray.texX = (int)(game->ray.wallX * (double)tex_size);
      		if(game->ray.side == 0 && game->ray.rayDirX > 0) 
				game->ray.texX = tex_size - game->ray.texX - 1;
      		if(game->ray.side == 1 && game->ray.rayDirY < 0) 
				game->ray.texX = tex_size - game->ray.texX - 1;
			
			game->ray.step = 1.0 * tex_size / game->ray.lineHeight;
    		game->ray.texPos = (game->ray.drawStart - h / 2 + game->ray.lineHeight / 2) * game->ray.step;
			int sky;

			sky = 0;
			while(sky < game->ray.drawStart)
			{
				my_mlx_pixel_put(&game->windows, x, sky, game->texture.s_rgb);
				sky++;
			}
			for(int y = game->ray.drawStart; y<game->ray.drawEnd; y++)
    		{
        		game->ray.texY = (int)game->ray.texPos & (tex_size - 1);
        		game->ray.texPos += game->ray.step;

				if (game->ray.side == 0 && game->ray.mapX >= game->player.posX)
					my_mlx_pixel_put(&game->windows, x, y, img_pix_get(&game->NO, game->ray.texX, game->ray.texY));
				else if (game->ray.side == 0 && game->ray.mapX <= game->player.posX)
					my_mlx_pixel_put(&game->windows, x, y, img_pix_get(&game->SO, game->ray.texX, game->ray.texY));
				else if(game->ray.side == 1 && game->ray.mapY <= game->player.posY)
					my_mlx_pixel_put(&game->windows, x, y, img_pix_get(&game->WE, game->ray.texX, game->ray.texY));
				else if (game->ray.side == 1 && game->ray.mapY >= game->player.posY)
					my_mlx_pixel_put(&game->windows, x, y, img_pix_get(&game->EA, game->ray.texX, game->ray.texY));
      		}
			while (game->ray.drawEnd < 1280)
			{
				my_mlx_pixel_put(&game->windows, x, game->ray.drawEnd, game->texture.f_rgb);
				game->ray.drawEnd++;
			}
		}
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.windows, game->windows.img , 0, 0);
}