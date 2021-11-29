/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:55:10 by kangkim           #+#    #+#             */
/*   Updated: 2021/11/29 13:31:05 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	size_t	s_len;
	char	*mem;
	size_t	idx;

	s_len = ft_strlen(s1);
	mem = (char *)malloc((s_len + 1) * sizeof(char));
	if (!mem)
		return (NULL);
	idx = 0;
	while (s1[idx])
	{
		mem[idx] = s1[idx];
		idx++;
	}
	mem[idx] = '\0';
	return (mem);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1 || !s2)
	{
		if (!s1)
			return (ft_strdup(s2));
		else
			return (ft_strdup(s1));
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str + s1_len, s2, s2_len + 1);
	return (str);
}

size_t	ft_strlen(const char *s)
{
	const char	*a;

	a = s;
	while (*a)
		a++;
	return ((size_t)(a - s));
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	idx;

	src_len = ft_strlen(src);
	idx = 0;
	if (!dest && !src)
		return (0);
	if (size == 0)
		return (src_len);
	while (idx < src_len && idx + 1 < size)
	{
		dest[idx] = src[idx];
		idx++;
	}
	dest[idx] = '\0';
	return (src_len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	idx;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len + 1 > size)
		return (src_len + size);
	idx = 0;
	while (src[idx] && (dest_len + idx + 1) < size)
	{
		dest[dest_len + idx] = src[idx];
		idx++;
	}
	dest[dest_len + idx] = '\0';
	return (dest_len + src_len);
}
