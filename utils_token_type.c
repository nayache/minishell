/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:46:55 by nayache           #+#    #+#             */
/*   Updated: 2021/03/26 20:22:07 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokentype	search_type(char c)
{
	if (c == DIRIN)
		return (Dirin);
	if (c == DIROUT)
		return (Dirout);
	if (c == PIPE)
		return (Pipe);
	if (c == OPEN_ROUND)
		return (Open_round);
	if (c == CLOSE_ROUND)
		return (Close_round);
	if (c == DOLLAR)
		return (Dollar);
	if (c == EQUAL_ASSIGN)
		return (Equal_assign);
	if (c == END_CMD)
		return (End_cmd);
}

t_tokentype			get_type(char c)
{
	if (check_special_char(c) == 1)
		return (search_type(c));
	else if (c == QUOTE)
		return (Literally);
	else
		return (Text);
}
