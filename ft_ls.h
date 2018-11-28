/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@protonmail>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:26:23 by abiri             #+#    #+#             */
/*   Updated: 2018/11/26 00:37:18 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include "libft.h"
# define FLAGNUM 5
# define VALIDFLAGS "lRart"

enum
{
	FLAG_l, FLAG_R, FLAG_a, FLAG_r, FLAG_t
};

typedef	struct		s_flags
{
	unsigned char	f[FLAGNUM];
}					t_flags;

typedef struct			s_file
{
	unsigned long long	size;
	unsigned int		links;
	char				*name;
	char				*user;
	char				*group;
	char				*time;
	char				*perm;
	struct s_file		*next;
	unsigned long		secn[2];
	char				type;
	char				attrb;
}						t_file;

int					ft_charindex(char *str, char c);
void				*ft_realloc(void *mem, size_t oldsize, size_t newsize);
int					ft_ls_main(char *dirname, t_flags *flags);
t_file				*ft_ls_getinfo(char *dirname);
char				ft_ls_gettype(struct stat info);
t_file				*ft_filenew(void);
#endif
