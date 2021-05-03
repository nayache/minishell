/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:48:39 by nayache           #+#    #+#             */
/*   Updated: 2021/05/03 14:59:40 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char *str)
{
	const char	builtin[7][7] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit"};
	int			index;

	index = 0;
	while (index < 7)
	{
		if (ft_strcmp(str, (char *)builtin[index]) == 0)
			return (index);
		index++;
	}
	return (-1);
}

int		execute_cmd(t_btree *head, char **argv, t_env *env)
{
	int		(*builtin[7])(t_btree *head, char **argv, t_env *env);
	int		index;

	builtin[0] = echo;
	builtin[1] = cd;
	builtin[2] = pwd;
	builtin[3] = export_var;
	builtin[4] = unset;
	builtin[5] = env_display;
	builtin[6] = exit_shell;
	index = is_builtin(argv[0]);
	if (index != -1)
		return (builtin[index](head, argv + 1, env));
	return (0);
}

int		preorder_process(t_btree *head, t_btree *cmd, t_env *env)
{
	if (cmd == NULL)
		return (0);

	if (cmd->argv != NULL)
	{
		execute_cmd(head, cmd->argv, env);
	}

	if (cmd->left != NULL)
		preorder_process(head, cmd->left, env);
	if (cmd->right != NULL)
		preorder_process(head, cmd->right, env);
}
