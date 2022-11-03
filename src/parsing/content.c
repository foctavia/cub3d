/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:19:06 by foctavia          #+#    #+#             */
/*   Updated: 2022/11/03 19:09:12 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_content(t_game *game, t_content *content)
{
	int		i;
	char	*line;
	display_map(game->map);
	i = 0;
	line = NULL;
	if (content && content->line)
		line = content->line;
	while (line && line[i] && is_space(line[i]))
				i++;
	if (!content->prev || !content->next)
	{
		while (line && line[i])
		{
			if (line[i] != '1' && line[i] != ' ')
				ft_error(ERR_MAP_WALL, 0, game->path, game);
			i++;
		}
	}
	else
	{
		if (line[i] != '1')
			ft_error(ERR_MAP_WALL, 0, game->path, game);
		while (line && line[i])
		{
			if ((line[i] != '1' && line[i] != ' ')
				&& ((line[i + 1] == ' ' || line[i + 1] == '\n')
				|| (i && line[i - 1] == ' ')))
				ft_error(ERR_MAP_WALL, 0, game->path, game);
			else if ((line[i] != '1' && line[i] != ' ') &&
				(content->prev && content->prev->line && content->prev->line[i] == ' '))
			{
				line[i] = 'X';
				display_map(game->map);
				ft_error(ERR_MAP_WALL, 0, game->path, game);
			}
			else if ((line[i] != '1' && line[i] != ' ') &&
				(content->next && content->next->line && content->next->line[i] == ' '))
				ft_error(ERR_MAP_WALL, 0, game->path, game);
			i++;
		}
	}
	if (content->next)
		check_map_content(game, content->next);
}

static void	add_content(t_content *new, t_content **content)
{
	t_content	*tmp;

	if (*content)
	{
		tmp = *content;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
		*content = new;
}

static t_content	*create_content(t_game *game, char *line, int start, int end)
{
	t_content	*new;

	new = malloc(sizeof(t_content));
	if (!new)
		ft_error(ERR_MALLOC, 0, NULL, game);
	new->line = line;
	new->start = start;
	new->end = end;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

static int	check_allowed_char(char c, t_game *game)
{
	int		i;
	char	*allowed;

	i = 0;
	allowed = "10NWSO ";
	while (allowed && allowed[i])
	{
		if (allowed[i] == c)
			return (EXIT_SUCCESS);
		i++;
	}
	ft_error(ERR_FORBIDDEN_CHAR, 0, game->path, game);
	return (EXIT_FAILURE);
}

void check_end_map(char *line, int fd, t_game *game)
{
	int	i;

	while (line)
	{
		i = 0;
		while (line && line[i])
		{
			if (!is_space(line[i]))
				ft_error(ERR_MAP_UNEXPECTED, 0, game->path, game);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
}

char	*copy_line(char *line, int n, t_game *game)
{
	char	*copy;
	int		i;

	copy = malloc(sizeof(char) * (game->map->width + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (line && line[i] && i < n)
	{
		copy[i] = line[i];
		i++;
	}
	while (i < game->map->width)
	{
		copy[i] = ' ';
		i++;
	}
	copy[i] = '\0';
	return (copy); 
}

int	get_map_content(int fd, t_game *game)
{
	int		i;
	int		j;
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
		line = get_next_line(fd);
	while (line)
	{
		i = 0;
		if (line[0] != '\n')
		{
			while (line[i] && is_space(line[i]))
				i++;
			j = i;
			while (line && line[i] && line[i] != '\n' \
				&& !check_allowed_char(line[i], game))
				i++;
			if (i > game->map->width)
				game->map->width = i;
			add_content(create_content(game, copy_line(line, i, game), j, i), \
				&game->map->content);
		}
		else
			break;
		game->map->height++;
		free(line);
		line = get_next_line(fd);
	}
	check_end_map(line, fd, game);
	return (EXIT_SUCCESS);
}

void	check_map(t_game *game, char **tab, int *line)
{
	int	i;
	int	j;
	int	k;

	i = *line;
	while (tab && tab[i])
	{
		j = 0;
		if (tab[i][0] != '\n')
		{
			while (tab[i][j] && is_space(tab[i][j]))
				j++;
			k = j;
			while (tab && tab[i][j] && tab[i][j] != '\n' \
				&& !check_allowed_char(tab[i][j][i], game))
				j++;
			if (i > game->map->width)
				game->map->width = i;
			add_content(create_content(game, copy_line(line, i, game), j, i), \
				&game->map->content);
		}
		else
			break;
		game->map->height++;
		free(line);
		line = get_next_line(fd);
	}
}
