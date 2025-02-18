/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:15:49 by jmenard           #+#    #+#             */
/*   Updated: 2024/10/31 14:15:57 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

int	isline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	isline_bis(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		if (buffer[i + 1] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

char	*line_read(int fd, char *buffer)
{
	char	*buffer_temp;
	char	*buffer_bis;
	int		read_len;

	read_len = 2;
	buffer_temp = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer_temp)
		return (NULL);
	if (!buffer)
		buffer = do_malloc(buffer);
	if (!buffer)
		return (free(buffer_temp), NULL);
	while (read_len > 0)
	{
		read_len = read(fd, buffer_temp, BUFFER_SIZE);
		if (read_len == -1)
			return (free(buffer_temp), NULL);
		buffer_temp[read_len] = '\0';
		buffer_bis = buffer;
		buffer = ft_strjoin(buffer_bis, buffer_temp);
		free(buffer_bis);
		if (isline(buffer_temp) >= 0 || read_len <= 0 || !buffer)
			break ;
	}
	return (free(buffer_temp), buffer);
}

char	*do_malloc(char *buf)
{
	buf = malloc(1 * sizeof(char));
	if (!buf)
		return (NULL);
	buf[0] = '\0';
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf[1024];
	char		*ret;
	char		*bis;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(buf[fd]), buf[fd] = NULL);
	bis = line_read(fd, buf[fd]);
	if (!bis)
		return (NULL);
	ret = ft_substr_bis(bis, 0, isline_bis(bis) + 1);
	if (!ret)
		return (free(bis), free(buf[fd]), buf[fd] = NULL);
	buf[fd] = ft_substr_bis(bis, ft_strle(ret), ft_strle(bis) - ft_strle(ret));
	if (!buf[fd])
		return (free(ret), free(bis), free(buf[fd]), buf[fd] = NULL);
	if (ret[0] == '\0')
		return (free(ret), free(buf[fd]), free(bis), buf[fd] = NULL);
	return (free(bis), ret);
}
