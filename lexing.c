/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:42:19 by nayache           #+#    #+#             */
/*   Updated: 2021/03/26 20:28:08 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_start_space(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (is_space(str[i]) == 1)
		i++;
	j = 0;
	while (str[i] != '\0')
	{
		str[j] = str[i++];
		j++;
	}
	str[j] = '\0';
}

static int	get_size_occur(char *str)
{
	int		size;

	size = 1;
	if (is_space(*str) == 1)
	{
		str++;
		while (*str != '\0' && is_space(*str))
		{
			str++;
			size++;
		}
		return (size);
	}
	else if (is_text(*str) == 1)
	{
		str++;
		while (*str != '\0' && is_text(*str))
		{
			str++;
			size++;
		}
	}
	return (size);
}

static int	index_quote(char *str, char quote)
{
	int		i;

	i = 1;
	while (str[i] != '\0' && str[i] != quote)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i - 1);
}

static int	lexing_quote(t_token *token, char *buf)
{
	int size;

	if ((size = index_quote(buf, *buf)) == -1)
	{
		printf("syntax error: expected quote %c or %c.\n", 39, 34);
		return (-1);
	}
	if (size > 0)
		if (add_token(token, buf, *buf, size) == -1)
			return (-1);
	return (size + 2);
}

int			lexing(char *buf, t_token *token)
{
	int	size;

	delete_start_space(buf);
	while (*buf != '\0')
	{
		if (*buf == QUOTE || *buf == DQUOTE)
		{
			if ((size = lexing_quote(token, buf)) == -1)
				return (-1);
		}
		else
			size = get_size_occur(buf);
		if (is_space(*buf) == 0 && *buf != QUOTE && *buf != DQUOTE)
			if (add_token(token, buf, *buf, size) == -1)
				return (-1);
		buf += size;
	}
	return (0);
}
