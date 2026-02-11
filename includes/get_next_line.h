/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:21:36 by selevray          #+#    #+#             */
/*   Updated: 2025/11/27 11:56:14 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	char	*str_static;
	char	*buffer;
	char	*temp;
	int		bytes_read;
	int		fd;
}			t_gnl;

/* get_next_line.c */
char		*get_next_line(int fd);

/* get_next_line_utils.c */
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *string, int searchedChar);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif