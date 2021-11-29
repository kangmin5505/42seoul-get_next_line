/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:03:07 by kangkim           #+#    #+#             */
/*   Updated: 2021/11/29 17:21:56 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	static char	*s_fdbuf[OPEN_MAX];
	char		*buf;
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	if (!s_fdbuf[fd])
		s_fdbuf[fd] = ft_strdup("");
	if (ft_read_file(s_fdbuf, fd, buf) < 0)
	{
		ft_free_ptr(buf);
		ft_free_ptr(s_fdbuf[fd]);
		return (NULL);
	}
	line = ft_get_line(s_fdbuf, fd);
	if (line == NULL)
	{
		ft_free_ptr(buf);
		return (NULL);
	}
	ft_free_ptr(buf);
	return (line);
}

char	*ft_get_line(char **s_fdbuf, int fd)
{
	char	*line;
	char	*fdbuf_temp;
	char	*fdbuf;

	if (s_fdbuf[fd] == NULL)
		return (NULL);
	fdbuf = s_fdbuf[fd];
	if (ft_strchr(s_fdbuf[fd], '\n') == NULL)
	{
		line = ft_strjoin(s_fdbuf[fd], NULL);
		s_fdbuf[fd] = NULL;
	}
	else
	{
		fdbuf_temp = s_fdbuf[fd];
		while (*fdbuf_temp != '\n')
			fdbuf_temp++;
		line = (char *)malloc(fdbuf_temp - s_fdbuf[fd] + 2);
		if (line == NULL)
			return (NULL);
		if (ft_strlcpy(line, s_fdbuf[fd], fdbuf_temp - s_fdbuf[fd] + 2) == 0)
			return (NULL);
		s_fdbuf[fd] = ft_strdup(fdbuf_temp + 1);
	}
	ft_free_ptr(fdbuf);
	return (line);
}

ssize_t	ft_read_file(char **s_fdbuf, int fd, char *buf)
{
	ssize_t	read_bytes;
	char	*fdbuf_temp;

	read_bytes = 1;
	while (ft_strchr(s_fdbuf[fd], '\n') == NULL && read_bytes)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		buf[read_bytes] = '\0';
		fdbuf_temp = s_fdbuf[fd];
		s_fdbuf[fd] = ft_strjoin(s_fdbuf[fd], buf);
		ft_free_ptr(fdbuf_temp);
	}
	return (read_bytes);
}

void	ft_free_ptr(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	find;
	char	*ret;

	find = (char)c;
	ret = (char *)s;
	while (*ret)
	{
		if (*ret == find)
			return (ret);
		ret++;
	}
	if (*ret == find)
		return (ret);
	return (NULL);
}
/*
int	main(void)
{
	int fd;

	fd = open("text", O_RDONLY);
	printf("%s", get_next_line(fd));
	close(fd);
	system("leaks a.out");
}
*/
