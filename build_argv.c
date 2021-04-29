/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:50:11 by nayache           #+#    #+#             */
/*   Updated: 2021/04/29 13:02:45 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**write_new_arg(char **argv, t_token *token, t_tokentype old_type,
		int size)
{
	char	*tmp;
	
	tmp = argv[size - 1];
	if (old_type == Whitespace)
	{
		if ((argv[size - 1] = ft_strdup(token->data)) == NULL)
			return (NULL);
	}
	else
	{
		if ((argv[size - 1] = ft_strjoin(tmp, token->data)) == NULL)
			return (NULL);
	}
	free(tmp);
	return (argv);
}

static char	**add_block_argv(char **new, char **argv, t_token *token, int size)
{
	if ((new = ft_tabndup(argv, 1)) == NULL)
			return (NULL);
	free_tab(argv);
	if ((new[size] = ft_strdup(token->data)) == NULL)
	{
		free_tab(new);
		return (NULL);
	}
	new[size + 1] = NULL;
	return (new);
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
	if (token->type == Whitespace)
		return (add_block_argv(new, argv, token, size));
	return (write_new_arg(argv, token, old_type, size));
}
