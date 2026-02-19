/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selevray <selevray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:52:11 by selevray          #+#    #+#             */
/*   Updated: 2026/02/19 12:42:20 by selevray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strchr(const char *string, int searchedChar)
{
	size_t	i;

	i = 0;
	if (!string)
		return (NULL);
	while (string[i])
	{
		if (string[i] == (char)searchedChar)
			return ((char *)&string[i]);
		i++;
	}
	if (searchedChar == '\0')
		return ((char *)&string[i]);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	char	*start;

	dest = malloc(ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	start = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (start);
}
