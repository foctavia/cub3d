/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:15:59 by owalsh            #+#    #+#             */
/*   Updated: 2022/11/09 17:53:26 by owalsh           ###   ########.fr       */
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
# define ERR_MAP_WRONGID -2
# define ERR_MAP_INCOMPLETEID -3
# define ERR_WRONG_FILE_EXTENSION -4
# define ERR_MALLOC -5
# define ERR_TOOMANY_ID -6
# define ERR_MAP_UNEXPECTED -7
# define ERR_MAP_WALL -8
# define ERR_MAP_PLAYER -10
# define ERR_FORBIDDEN_CHAR -11
# define ERR_RGB -12

#endif