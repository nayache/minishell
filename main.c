/* ************************************************************************** *
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:11:30 by nayache           #+#    #+#             */
/*   Updated: 2021/05/03 15:01:45 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			error(void)
{
	if (errno != 0)
		perror(NULL);
}

void			print_preorder(t_btree *tree)
{
	if (tree == NULL)
		return;
	if (tree->flux != NULL)
		printf("%s\n", tree->flux);
	else
	{
		print_tab(tree->argv);
		ft_putchar('\n');
	}
	if (tree->left != NULL)
	{
		printf("\e[32m-----\e[0;38m\n");
		print_preorder(tree->left);
	}
	if (tree->right != NULL)
	{
		printf("\e[31m-----\e[0;38m\n");
		print_preorder(tree->right);
	}
}

static t_btree	*engine(char *buf, t_btree *cmd)
{
	t_token *token;

	if (*buf == '\0' || (token = init_token(NULL)) == NULL)
		return (NULL);
	if (lexing(buf, token) == -1 || parsing(token) == -1)
	{
		free(buf);
		free_token(token);
		return (NULL);
	}
	free(buf);
	//print_token(token);
	if ((cmd = init_node()) == NULL || (cmd = build_btree(cmd, token)) == NULL)
	{
		free_token(token);
		return (NULL);
	}
	free_token(token);
	return (cmd);
}

int				main(int ac, char **av, char **envp)
{
	const char	prompt[46] = "\e[1;3;40mMINISHELL\e[5;38m-\e[0;1;40m$\e[0;38m ";
	char		*buffer;
	t_btree		*cmd;
	t_env		*env;

	if ((env = init_env()) == NULL || copy_env(envp, env) == -1)
	{
		error();
		return (EXIT_FAILURE);
	}
	while (1)
	{
		ft_putstr((char *)prompt);
		if (get_next_line(STDIN_FILENO, &buffer) == -1)
		{
			error();
			return (EXIT_FAILURE);
		}
		if ((cmd = engine(buffer, cmd)) == NULL)
			error();
		else
			preorder_process(cmd, cmd, env);
		free_btree(cmd);
	}
	return (EXIT_SUCCESS);
}
