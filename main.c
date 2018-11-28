/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@protonmail>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 14:58:12 by abiri             #+#    #+#             */
/*   Updated: 2018/11/26 00:37:17 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"

int ft_ls_addflags(char *str, t_flags *flags)
{
	char index;

	while (*str)
	{
		if ((index = ft_charindex(VALIDFLAGS,*str)) != -1)
			flags->f[(int)index] = 1;
		else
		{
			ft_printf("ft_ls: illegal option -- %c\n",*str);
			exit(1);
		}
		str++;
	}
	return (0);
}

int ft_ls_parse(int ac, char **av, t_flags *flags)
{
	int counter;

	counter = 1;
	while (counter < ac)
	{
		if (av[counter][0] == '-' && av[counter][1] != '\0')
		{
			ft_ls_addflags(av[counter] + 1, flags);
			counter++;
		}
		else
			break ;
	}
	return (counter);
}

void ft_ls_init(t_flags **flags)
{
	*flags = malloc(sizeof(flags));
}

int main(int argc, char **argv)
{
	int dirindex;
	t_flags *flags;


	ft_ls_init(&flags);
	dirindex = ft_ls_parse(argc, argv, flags);
	if (dirindex == argc)
		argv[--dirindex] = ".";
	while (dirindex < argc)
		ft_ls_main(argv[dirindex++], flags);
	return (0);
}
