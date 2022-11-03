/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:15:59 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/03 09:26:59 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define TRUE 1
# define FALSE 0

# define BUFFER_SIZE 1

# define RED 255
# define GREEN 256
# define BLUE 257

# define NORTH_TEXTURE 100
# define SOUTH_TEXTURE 101
# define WEST_TEXTURE 102
# define EAST_TEXTURE 103
# define FLOOR 104
# define CEILING 105

// Errors
# define ERR_ARGS_COUNT -1
# define ERR_MAP_PATH -2
# define ERR_MAP_WRONGID -3
# define ERR_MAP_INCOMPLETEID -4
# define ERR_WRONG_FILE_EXTENSION -5
# define ERR_MALLOC -6
# define ERR_TOOMANY_ID -7
# define ERR_MAP_UNEXPECTED -8
# define ERR_MAP_WALL -9
# define ERR_FORBIDDEN_CHAR -10
# define ERR_RGB -11

#endif