/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 18:45:16 by nayache           #+#    #+#             */
/*   Updated: 2021/05/03 14:54:13 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_buf(char **buffer)
{
	if (*buffer != NULL)
		free(*buffer);
	*buffer = NULL;
}

void	free_btree(t_btree *tree)
{
	if (tree == NULL)
		return;
	if (tree->left != NULL)
		free_btree(tree->left);
	if (tree->argv != NULL)
		free_tab(tree->argv);
	if (tree->flux != NULL)
		free(tree->flux);
	if (tree->right != NULL)
		free_btree(tree->right);
	free(tree);
}

int		is_uppercase(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}
