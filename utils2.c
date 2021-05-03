/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:58:01 by nayache           #+#    #+#             */
/*   Updated: 2021/05/03 14:25:40 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_space(char c)
{
	if (c == '\r' || c == '\v' || c == '\f')
		return (1);
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

int		is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
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
int		is_empty_str(char *str)
{
	while (*str != '\0')
	{
		if (is_space(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

int		is_operator(t_tokentype type)
{
	if (type == Dirin || type == Dirout || type == Pipe || type == End_cmd)
		return (1);
	return (0);
}

int		check_special_char(char c)
{
	if (c == PIPE || c == DIRIN || c == DIROUT)
		return (1);
	if (c == END_CMD)
		return (1);
	return (0);
}
