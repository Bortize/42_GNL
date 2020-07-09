/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgomez-r <bgomez-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:14:52 by bgomez-r          #+#    #+#             */
/*   Updated: 2020/02/10 19:56:04 by bgomez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (const char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	new = malloc(sizeof(char) * (len + 1));
	if (new)
	{
		i = 0;
		if (ft_strlen(s) > start)
			while (i < len)
			{
				new[i] = s[start + i];
				i++;
			}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	size_s1;
	unsigned int	size_s2;
	unsigned int	i;
	unsigned int	j;
	char			*new;

	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	new = malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (new)
	{
		i = -1;
		while (++i < size_s1)
			new[i] = s1[i];
		j = 0;
		while (j < size_s2)
			new[i++] = s2[j++];
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}
