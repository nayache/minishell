/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:45:16 by nayache           #+#    #+#             */
/*   Updated: 2021/03/24 19:15:43 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_buf(char **buffer)
{
	if (*buffer != NULL)
		free(*buffer);
	*buffer = NULL;
}

int		is_space(char c)
{
	if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

int		check_special_char(char c)
{
	if (c == QUOTE || c == DQUOTE || c == DOLLAR || c == EQUAL_ASSIGN)
		return (1);
	if (c == PIPE || c == DIR_IN || c == DIR_OUT)
		return (1);
	if (c == OPEN_ROUND || c == CLOSE_ROUND || c == END_CMD)
		return (1);
	return (0);
}
