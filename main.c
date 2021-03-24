/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:11:30 by nayache           #+#    #+#             */
/*   Updated: 2021/03/24 19:34:04 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error(void)
{
	if (errno != 0)
		perror("\e[1;4;31mERROR\e[0;38m");
}

static int	engine(char **buffer, t_token *token, char **env)
{
	if (ft_strcmp(*buffer, "exit") == 0)
	{
		free(*buffer);
		free_token(token);
		exit(EXIT_SUCCESS);
	}
	//lexer
	if (lexing(*buffer, token) == -1)
		return (-1);
	free_buf(buffer);
	// parser
	return (0);
}

int		main(int ac, char **av, char **env)
{
	const char	prompt[46] = "\e[1;3;40mMINISHELL\e[5;38m-\e[0;1;40m$\e[0;38m ";
	char		*buffer;
	t_token		*token;

	while (1)
	{
		ft_putstr((char *)prompt);
		if (get_next_line(STDIN_FILENO, &buffer) == -1)
		{
			error();
			return (EXIT_FAILURE);
		}
		if (!(token = init_token(NULL)) || engine(&buffer, token, env) == -1)
			error();
		else
			print_token(token);						// executer mes commandes.
		free_buf(&buffer);
		free_token(token);
	}
	return (EXIT_SUCCESS);
}
