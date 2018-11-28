/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@protonmail>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:14:28 by abiri             #+#    #+#             */
/*   Updated: 2018/11/26 00:37:18 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*void	ft_timesortfiles(t_file *files)
{
	t_file *temp;

	if (!files->next)
		return ;
	temp = files->next;
	while (temp->next)
	{
		if ((temp->secn)[0] > (temp->next->secn)[0])
		{
			files->next = temp->next;
			temp->next->next = temp;
		}
		else if ((temp->secn)[0] == (temp->next->secn)[0])
		{
			if ((temp->secn)[1] == (temp->next->secn)[1])
			{
				files->next = temp->next;
				temp->next->next = temp;
			}
		}
		temp = temp->next;
		files = files->next;
	}
}*/

static int	nbrsize(long long nbr)
{
	int i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		i++;
	while (nbr % 10 != 0 || nbr / 10 != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

t_file	*ft_filenew(void)
{
	return (ft_memalloc(sizeof(t_file)));
}	

void	ft_fileadd(t_file *head, t_file* new)
{
	while (head->next)
		head = head->next;
	head->next = new;
}

int		*ft_nfieldw(t_file *files)
{
	int *max;
	int optim;
	unsigned long long *temp;

	max = malloc(sizeof(int *) * 4);
	temp = malloc(sizeof(unsigned long long *) * 2);
	temp[0] = 0;
	temp[1] = 0;
	max[2] = 0;
	max[3] = 0;
	while (files)
	{
		if (files->links > temp[0])
			temp[0] = files->links;
		if (files->size > temp[1])
			temp[1] = files->size;
		if ((optim = ft_strlen(files->user)) > max[2])
			max[2] = optim;
		if ((optim = ft_strlen(files->group)) > max[3])
			max[3] = optim;
		files = files->next;
	}
	max[0] = nbrsize(temp[0]);
	max[1] = nbrsize(temp[1]);
	free(temp);
	return (max);
}

void ft_ls_printl(t_file *files, t_flags *flags)
{
	t_file *temp;
	int *fieldw;

	fieldw = ft_nfieldw(files);
	while (files)
	{
		temp = files;
		if (flags->f[FLAG_a] || (files->name)[0] != '.')
			ft_printf("%c%s%c %*u %*s %*s %*llu %s %s\n",files->type, files->perm, 
		files->attrb, fieldw[0], files->links, fieldw[2], files->user, 
		fieldw[3], files->group, fieldw[1],files->size, files->time, files->name);
		files = files->next;
		free (temp);
	}
}

void ft_ls_printfolder(DIR *cwd, t_flags *flags)
{
	t_file *files;
	struct dirent *dirfiles;
	char *dirname;

	if (flags->f[FLAG_l])
	{
		dirfiles = readdir(cwd);
		dirname = dirfiles->d_name;
		files = ft_ls_getinfo(dirname);
		while ((dirfiles = readdir(cwd)))
		{
			dirname = dirfiles->d_name;
			if (flags->f[FLAG_a] || dirname[0] != '.')
				ft_fileadd(files, ft_ls_getinfo(dirname));
		}
		ft_ls_printl(files, flags);
	}
	else
	{
		while ((dirfiles = readdir(cwd)))
		{
			dirname = dirfiles->d_name;
			if (flags->f[FLAG_a] || dirname[0] != '.')
				ft_printf("%-*s",ft_strlen(dirname) + 4, dirname);
		}
		ft_putchar('\n');
	}
}

int ft_ls_main(char *dirname, t_flags *flags)
{
	struct stat info;
	DIR *cwd;

	if (lstat(dirname, &info) != 0)
	{
		ft_printf("ft_ls: %s: No such file or directory\n",dirname);
		exit(1);
	}
	if (ft_ls_gettype(info) == 'd')
	{
		cwd = opendir(dirname);
		if (cwd == NULL)
		{
			ft_printf("ft_ls: cannot access %s\n",dirname);
			exit(1);
		}
		ft_ls_printfolder(cwd, flags);
	}
	return (0);
}
