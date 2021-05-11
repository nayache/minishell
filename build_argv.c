/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:50:11 by nayache           #+#    #+#             */
/*   Updated: 2021/05/11 14:46:33 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**write_new_arg(char **argv, t_token *token, t_tokentype old_type,
		int size)
{
	char	**new;
	char	*tmp;
	
	if (old_type == Whitespace)
	{
		if ((new = ft_tabndup(argv, 1)) == NULL)
			return (NULL);
		free_tab(argv);
		if ((new[size] = ft_strdup(token->data)) == NULL)
			return (NULL);
		new[size + 1] = NULL;
		return (new);
	}
	tmp = argv[size - 1];
	if ((argv[size - 1] = ft_strjoin(tmp, token->data)) == NULL)
		return (NULL);
	free(tmp);
	return (argv);
}

char		**build_argv(char **argv, t_token *token, t_tokentype old_type)
{
	char	**new;
	int		size;

	if (argv == NULL)
	{
		if ((new = (char **)malloc(sizeof(char *) * 2)) == NULL)
			return (NULL);
		if ((new[0] = ft_strdup(token->data)) == NULL)
			return (NULL);
		new[1] = NULL;
		return (new);
	}
	size = tablen(argv);
	return (write_new_arg(argv, token, old_type, size));
}
