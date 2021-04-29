/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:11:30 by nayache           #+#    #+#             */
/*   Updated: 2021/04/29 14:36:38 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error(void)
{
	if (errno != 0)
		perror("\e[1;4;31mERROR\e[0;38m");
}

static t_btree	*engine(char **buffer, t_token *token, t_btree *cmd, char **env)
{
	if (ft_strcmp(*buffer, "exit") == 0)
	{
		free(*buffer);
		free_token(token);
		exit(EXIT_SUCCESS);
	}
	if (**buffer == '\0')
		return (NULL);
	if (lexing(*buffer, token) == -1)
		return (NULL);
	//	free_buf(buffer);      en cas d'exit plus loin.
	if (parsing(token) == -1)
		return (NULL);
	if ((cmd = init_node()) == NULL || (cmd = build_btree(cmd, token)) == NULL)
		return (NULL);
	return (cmd);
}

void	print_btree(t_btree *tree)
{
	if (tree == NULL)
		return;
	if (tree->flux != NULL)
	{
		printf("\e[1;32mLeft : \e[0;38m\e[31m(%s)\e[0;38m  ", tree->flux);
	}
	else
	{
		printf("\e[1;32mNode :\e[0;38m\n\n");
		ft_putstr("            ");
		print_tab(tree->argv);
		ft_putstr("\n");
	}
	if (tree->left != NULL)
		print_btree(tree->left);
	if (tree->right != NULL)
		print_btree(tree->right);
}

int		main(int ac, char **av, char **env)
{
	const char	prompt[46] = "\e[1;3;40mMINISHELL\e[5;38m-\e[0;1;40m$\e[0;38m ";
	char		*buffer;
	t_token		*token;
	t_btree		*cmd;

	while (1)
	{
		ft_putstr((char *)prompt);
		if (get_next_line(STDIN_FILENO, &buffer) == -1)
		{
			error();
			return (EXIT_FAILURE);
		}
		if (!(token = init_token(NULL)) || (cmd = engine(&buffer, token, cmd, env)) == NULL)
			error();
		else
		{
			//print_token(token);
			print_btree(cmd);
		}
		free_buf(&buffer);
		free_token(token);
		free_btree(cmd);
	}
	return (EXIT_SUCCESS);
}
