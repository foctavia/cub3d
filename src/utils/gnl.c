/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:01:42 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/28 16:14:55 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_nl(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
		{
			s[i + 1] = '\0';
			return (1);
		}
		i++;
	}
	return (0);
}

void	clean_buf(char *buf)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
		i++;
	i++;
	n = ft_strlen(buf) - i;
	if (n < 0)
	{
		buf[0] = '\0';
		return ;
	}
	j = 0;
	while (j < n)
		buf[j++] = buf[i++];
	buf[n] = '\0';
}

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE + 1];
	int				ret;
	char			*line;

	if ((fd < 0 || fd > 1024) || BUFFER_SIZE <= 0)
		return (NULL);
	ret = 1;
	line = NULL;
	line = ft_strjoin(line, buf, 1);
	while (ret && !has_nl(line))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			free(line);
			return (NULL);
		}
		if (ret)
		{
			buf[ret] = '\0';
			line = ft_strjoin(line, buf, 1);
		}
	}
	clean_buf(buf);
	return (line);
}
