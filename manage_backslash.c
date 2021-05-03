/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 20:15:28 by nayache           #+#    #+#             */
/*   Updated: 2021/04/12 19:38:38 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_backslash(char *data, int type)
{
	int	i;

	i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == BACKSLASH && type == Dquote_text)
		{
			if (data[i + 1] == BACKSLASH)
				ft_strcpy(data + i, data + i + 1);
			else if (data[i + 1] == DQUOTE)
				ft_strcpy(data + i, data + i + 1);
			else if (data[i + 1] == QUOTE)
				ft_strcpy(data + i, data + i + 1);
		//	else if (data[i + 1] == DOLLAR)
		//		ft_strcpy(data + i, data + i + 1);
		}
		else if (data[i] == BACKSLASH && type == Escape)
			ft_strcpy(data + i, data + i + 1);
		i++;
	}
	return (0);
}

/*static int	invalid_escape(char *data)
{
	int	count;

	if (ft_strlen(data) == 1)
		return (1);
	count = 0;
	while (*data != '\0')
	{
		if (*data == BACKSLASH)
			count++;
		data++;
	}
	return (0);
}*/

int			manage_backslash(t_token *token)
{
	if (token->data == NULL)
		return (0);
	while (token != NULL)
	{
		if (token->type != Quote_text)
		{
			if (ft_strchr(token->data, BACKSLASH) != NULL)
			{
				if (ft_strlen(token->data) == 1)
				{
					printf("Syntax error: `\\` expected character\n");
					return (-1);
				}
				if (apply_backslash(token->data, token->type) == -1)
					return (-1);
			}
		}
		token = token->next;
	}
	return (0);
}
