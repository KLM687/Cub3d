/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:27:39 by flee              #+#    #+#             */
/*   Updated: 2022/05/05 11:27:40 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while(tab[i] != NULL)
			i++;
	}
	return (i); 
}