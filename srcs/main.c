/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 13:08:08 by flee              #+#    #+#             */
/*   Updated: 2021/07/20 16:17:39 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

int main (int argc, char **argv)
{
	char **map;

	if (argc != 2)
		return (0);
	map = get_map(argv[1]);
	int i = 0;
	while(map[i] != 0)
	{
		printf("%s\n", map[i]);
		i++;
	}
	parse_map(map);
	ft_free_tab(map);
	return (0);
}
