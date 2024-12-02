/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: batuhankiskac <batuhankiskac@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:39:15 by batuhankisk       #+#    #+#             */
/*   Updated: 2024/12/02 18:57:59 by batuhankisk      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*parse(char *line, char c)
{
	char	*left;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != c)
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	left = (char *)malloc(sizeof(char) * (ft_strlen(line - i) + 1));
	if (!left)
		return (NULL);
	i++;
	while (line[i])
		left[j++] = line[i++];
	left[j] = '\0';
	free(line);
	return (left);
}

static char	*new_line(char *line, char c)
{
	char	*new;
	int		i;

	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != c)
		i++;
	new = (char *)malloc(sizeof(char) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != c)
	{
		new[i] = line[i];
		i++;
	}
	if (line[i] == c)
	{
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*next_line(int fd, char *line, char c)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(buffer, c) && i != '\0')
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = next_line(fd, line[fd], '\n');
	if (line[fd])
	{
		str = new_line(line[fd], '\n');
		line[fd] = parse(line[fd], '\n');
		return (str);
	}
	return (NULL);
}
