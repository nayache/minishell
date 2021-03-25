/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:42:19 by nayache           #+#    #+#             */
/*   Updated: 2021/03/24 20:08:59 by nayache          ###   ########.fr       */
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
	else if (check_special_char(*str) == 0 && is_space(*str) == 0)
	{
		str++;
		while (*str != '\0' && !check_special_char(*str) && !is_space(*str))
		{
			str++;
			size++;
		}
	}
	return (size);
}

int			lexing(char *buf, t_token *token)
{
	int	size;

	delete_start_space(buf);
	while (*buf != '\0')
	{
		size = get_size_occur(buf);
		if (add_token(token, buf, size) == -1)
			return (-1);
		buf += size;
	}
	return (0);
}
