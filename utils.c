/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:45:16 by nayache           #+#    #+#             */
/*   Updated: 2021/04/13 18:33:00 by nayache          ###   ########.fr       */
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

int			is_text(char c)
{
	if (is_space(c) == 1)
		return (0);
	if (c == DQUOTE || c == QUOTE)
		return (0);
	if (check_special_char(c) == 1)
		return (0);
	return (1);
}

int		check_special_char(char c)
{
	if (c == PIPE || c == DIRIN || c == DIROUT)
		return (1);
	if (c == END_CMD)
		return (1);
	return (0);
}
