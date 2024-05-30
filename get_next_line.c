/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:05:57 by drhaouha          #+#    #+#             */
/*   Updated: 2024/05/30 17:49:24 by drhaouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_buffer(char *buf, char **trunc, char *cat)
{
	unsigned int	pos;

	pos = 0;
	while (buf[pos] != '\n' && buf[pos])
	{
		cat[pos] = buf[pos];
		pos++;
	}
	if (buf[pos] == '\n')
		cat[pos++] = '\n';
	cat[pos] = '\0';
	*trunc = ft_strcat(*trunc, cat);
	if (ft_strchr(buf, '\n'))
		ft_strcpy(buf, buf + pos);
	else
		buf[0] = '\0';
	return (*trunc);
}

char	*get_trunc(unsigned int size, char *cat, int fd, int *ret)
{
	static char		buf[BUFFER_SIZE + 1] = {0};
	char			*trunc;
	unsigned int	i;

	trunc = (char *)malloc(sizeof(char) * (BUFFER_SIZE * (size + 1) + 1));
	if (trunc == NULL)
		return (NULL);
	trunc[0] = '\0';
	i = 0;
	while (i < size)
	{
		if (ft_strlen(buf) == 0)
		{
			*ret = read(fd, buf, BUFFER_SIZE);
			if (*ret == -1)
				return (free(trunc), NULL);
			buf[*ret] = '\0';
			i++;
		}
		trunc = update_buffer(buf, &trunc, cat);
		if (ft_strchr(trunc, '\n') || *ret == 0)
			break ;
	}
	return (trunc);
}

int	read_file(char **line, char *cat, int fd)
{
	char			*trunc;
	char			*tmp;
	int				ret;
	unsigned int	size;

	ret = 1;
	size = 1;
	while (ret != 0)
	{
		if (ft_strchr(*line, '\n'))
			break ;
		trunc = get_trunc(size, cat, fd, &ret);
		if (trunc == NULL)
			return (-1);
		tmp = *line;
		*line = ft_strjoin(*line, trunc);
		free(trunc);
		free(tmp);
		if (*line == NULL || ft_strlen(*line) == 0)
			return (-1);
		size += size;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*cat;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	cat = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (cat == NULL)
		return (NULL);
	line = ft_strjoin("", "");
	if (!line || read_file(&line, cat, fd) == -1)
		return (free(cat), free(line), NULL);
	return (free(cat), line);
}
