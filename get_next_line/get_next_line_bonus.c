/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhankiskac <batuhankiskac@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:18:07 by batuhankisk       #+#    #+#             */
/*   Updated: 2024/12/01 18:39:08 by batuhankisk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_extract_line(char **buf_static)
{
	char	*new_line_pos;
	char	*temp;
	char	*line;

	if (!buf_static || !*buf_static)
		return (NULL);
	new_line_pos = ft_strchr(*buf_static, '\n');
	if (new_line_pos)
	{
		line = ft_substr(*buf_static, 0, new_line_pos - *buf_static + 1);
		temp = ft_substr(*buf_static,
				new_line_pos - *buf_static + 1,
				ft_strlen(*buf_static)
				- (new_line_pos - *buf_static + 1));
		free(*buf_static);
		*buf_static = temp;
		return (line);
	}
	line = ft_strdup(*buf_static);
	free(*buf_static);
	*buf_static = NULL;
	return (line);
}

char	*ft_allocate_buf(void)
{
	char	*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf_static[MAX_FILES_OPENED];
	char		*buf;
	ssize_t		bytes_read;

	buf = ft_allocate_buf();
	if (fd < 0 || fd >= MAX_FILES_OPENED || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		buf_static[fd] = ft_strjoin(buf_static[fd], buf);
		if (!buf_static[fd] || ft_strchr(buf_static[fd], '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (bytes_read < 0 || (!buf_static[fd] && bytes_read == 0))
	{
		free(buf_static[fd]);
		buf_static[fd] = NULL;
		return (NULL);
	}
	return (ft_extract_line(&buf_static[fd]));
}
