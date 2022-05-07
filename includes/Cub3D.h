/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:06:09 by flee              #+#    #+#             */
/*   Updated: 2022/05/04 11:06:26 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft.h"
# include "mlx.h"

# define IMG_SIZE 100

typedef struct s_map
{
	char **map;
}	t_map;

typedef struct s_texture
{
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	int floor[3];
	int sky[3];
}	t_texture;

typedef struct s_player
{
	float posX;
	float posY;
	int	dirX;
	int dirY;
	float planeX;
	float planeY;
	int mapX;
	int mapY;
}	t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*windows;
	size_t	w_x;
	size_t	w_y;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		byte_p;
	int		line_l;
	int		end;
}	t_img;

typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_texture	texture;
	t_player	player;
	t_img		NO;
	t_img		SO;
	t_img		WE;
	t_img		EA;
}	t_game;

void	get_file(char *map, t_game *game);
void 	parse_map(t_game *game);
void	square_map(t_game *game);
void	game_init(t_game *game);

#endif
