/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouarar <mouarar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:06:25 by mouarar           #+#    #+#             */
/*   Updated: 2024/11/20 10:41:28 by mouarar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*line(int fd, char *str)
{
	char	*buffer;
	int		c_read;

	c_read = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!str)
		str = ft_strdup("");
	while (c_read != 0 && (ft_strchr(str, '\n') == NULL))
	{
		c_read = read(fd, buffer, BUFFER_SIZE);
		if (c_read < 0)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[c_read] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*fill(char *line)
{
	size_t	i;
	char	*new_line;

	if (ft_strlen(line) == 0)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	new_line = ft_substr(line, 0, i);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*new_result(char *text)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (text[i] == '\n')
		i++;
	if (text[i] == '\0')
	{
		free(text);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(text + i) + 1));
	if (!tmp)
		return (NULL);
	while (text[i])
		tmp[j++] = text[i++];
	tmp[j] = '\0';
	free(text);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*text[1024];
	char		*str_1;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	text[fd] = line(fd, text[fd]);
	if (text[fd] == NULL)
		return (NULL);
	str_1 = fill(text[fd]);
	text[fd] = new_result(text[fd]);
	return (str_1);
}
