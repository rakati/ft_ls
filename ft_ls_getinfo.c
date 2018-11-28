/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_getinfo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@protonmail>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:26:09 by abiri             #+#    #+#             */
/*   Updated: 2018/11/26 00:37:19 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char *ft_ls_gettime(time_t *sec)
{
	char *date;

	date = ctime(sec);
	while (*(date++))
		if (*(date - 1) == ' ')
			break ;
	date[12] = 0;
	return (ft_strdup(date));
}

char **ft_ls_getusergrp(struct stat info)
{
	char **result;
	struct passwd	*udata;
	struct group	*gdata;

	result = malloc(sizeof(char*) * 2);
	udata = getpwuid(info.st_uid);
	result[0] = udata->pw_name;
	gdata = getgrgid(info.st_gid);
	result[1] = gdata->gr_name;
	return (result);
}

char ft_ls_gettype(struct stat info)
{
	mode_t mode;

	mode = info.st_mode;
	mode = mode & S_IFMT;
	if (mode == S_IFLNK)
		return ('l');
	if (mode ==  S_IFBLK)
		return ('b');
	if (mode == S_IFCHR)
		return ('c');
	if (mode == S_IFDIR)
		return ('d');
	if (mode == S_IFSOCK)
		return ('s');
	if (mode == S_IFIFO)
		return ('p');
	if (mode == S_IFREG)
		return ('-');
	return (' ');
}

char *ft_ls_getperm(struct stat info)
{
	mode_t mode;
	char *result;

	result = ft_memalloc(10);
	mode = info.st_mode;
	result[0] = (mode & S_IRUSR) ? 'r':'-';
	result[1] = (mode & S_IWUSR) ? 'w':'-';
	result[2] = (mode & S_IXUSR) ? 'x':'-';
	result[3] = (mode & S_IRGRP) ? 'r':'-';
	result[4] = (mode & S_IWGRP) ? 'w':'-';
	result[5] = (mode & S_IXGRP) ? 'x':'-';
	result[6] = (mode & S_IROTH) ? 'r':'-';
	result[7] = (mode & S_IWOTH) ? 'w':'-';
	result[8] = (mode & S_IXOTH) ? 'x':'-';
	return (result);
}

char *ft_ls_getfilename(char *dirname, char type)
{	
	char text[1024];
	char *temp;

	if (type == 'l' )
	{
		readlink(dirname, text, 1024);
		temp = ft_strjoin(" -> ",text);
		dirname = ft_strjoin(dirname,temp);
		free(temp);
	}
	return (dirname);
}

t_file	*ft_ls_getinfo(char *dirname)
{
	char **uidgid;
	char text[1024];
	mode_t filemode;
	t_file *result;
	struct stat buffer;

	lstat(dirname, &buffer);
	result = ft_filenew();
	uidgid = ft_ls_getusergrp(buffer);
	filemode = buffer.st_mode;
	result->links = buffer.st_nlink;
	result->user = uidgid[0];
	result->group = uidgid[1];
	result->size = buffer.st_size;
	result->time = ft_ls_gettime(&(buffer.st_mtimespec.tv_sec));
	result->attrb = (listxattr(dirname, text, 1024, 0) != 0) ? '@':' ';
	result->type = ft_ls_gettype(buffer);
	result->perm = ft_ls_getperm(buffer);
	result->name = ft_ls_getfilename(dirname, result->type);
	(result->secn)[0] = buffer.st_mtimespec.tv_sec;
	(result->secn)[1] = buffer.st_mtimespec.tv_nsec;
	return (result);
}
