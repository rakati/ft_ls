/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addtolibft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@protonmail>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 18:45:31 by abiri             #+#    #+#             */
/*   Updated: 2018/11/25 22:05:38 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charindex(char *str, char c)
{
	unsigned int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

void *ft_realloc(void *mem, size_t oldsize, size_t newsize)
{
	void *result;

	result = malloc(newsize);
	ft_memmove(result, mem, oldsize);
	return (result);
}
