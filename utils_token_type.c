/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:46:55 by nayache           #+#    #+#             */
/*   Updated: 2021/04/13 18:31:51 by nayache          ###   ########.fr       */
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
	if (c == END_CMD)
		return (End_cmd);
}

t_tokentype			get_type(char c)
{
	if (check_special_char(c) == 1)
		return (search_type(c));
	else if (c == QUOTE)
		return (Quote_text);
	else if (c == DQUOTE)
		return (Dquote_text);
	else if (c == BACKSLASH)
		return (Escape);
	else if (is_space(c) == 1)
		return (Whitespace);
	else
		return (Text);
}
