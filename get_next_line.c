/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kangkim <kangkim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:03:07 by kangkim           #+#    #+#             */
/*   Updated: 2021/11/29 23:03:14 by kangkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	static char	*s_fdbuf[FOPEN_MAX];
	char		*buf;
	char		*line;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	if (!s_fdbuf[fd])
		s_fdbuf[fd] = ft_strdup("");
	if (ft_read_file(s_fdbuf, fd, buf) == false)
	{
		ft_free_ptr(buf);
		return (NULL);
	}
	line = ft_get_line(s_fdbuf, fd);
	if (line == NULL)
	{
		ft_free_ptr(s_fdbuf[fd]);
		return (NULL);
	}
	ft_free_ptr(buf);
	return (line);
}

bool	ft_read_file(char **s_fdbuf, int fd, char *buf)
{
	ssize_t	read_bytes;
	char	*fdbuf_temp;
	int	flag;

	flag = 0;
	read_bytes = 1;
	if (s_fdbuf[fd] == NULL)
		return (NULL);
	while (ft_strchr(s_fdbuf[fd], '\n') == NULL && read_bytes)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if ((flag == 0 && read_bytes == 0) || read_bytes == -1)
			return (false);
		buf[read_bytes] = '\0';
		fdbuf_temp = s_fdbuf[fd];
		s_fdbuf[fd] = ft_strjoin(s_fdbuf[fd], buf);
		ft_free_ptr(fdbuf_temp);
		flag = 1;
	}
	return (true);
}

char	*ft_get_line(char **s_fdbuf, int fd)
{
	char	*line;
	char	*fdbuf;
	int	buf_idx;

	fdbuf = s_fdbuf[fd];
	if (ft_strchr(fdbuf, '\n') == NULL)
	{
		line = ft_strjoin(fdbuf, NULL);
		s_fdbuf[fd] = NULL;
	}
	else
	{
		buf_idx = 0;
		while (fdbuf[buf_idx] != '\n')
			buf_idx++;
		line = (char *)malloc(buf_idx + 2);
		if (line == NULL)
			return (NULL);
		if (ft_strlcpy(line, fdbuf, buf_idx + 2) == 0)
			return (NULL);
		s_fdbuf[fd] = ft_strdup((char *)(fdbuf + buf_idx + 1));
	}
	ft_free_ptr(fdbuf);
	return (line);
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
int	main(void)
{
	int fd;

	fd = open("text", O_RDONLY);
	printf("%s", get_next_line(fd));
	close(fd);
}
