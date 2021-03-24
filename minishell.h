/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayache <nayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:11:51 by nayache           #+#    #+#             */
/*   Updated: 2021/03/24 18:48:15 by nayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define QUOTE 39
# define DQUOTE 34
# define OPEN_ROUND '('
# define CLOSE_ROUND ')'
# define DOLLAR '$'
# define DIR_IN '<'
# define DIR_OUT '>'
# define PIPE '|'
# define END_CMD ';'
# define EQUAL_ASSIGN '='

typedef struct	s_token
{
	char			*data;
	struct s_token	*next;
}				t_token;

void			print_token(t_token *list);
void			free_token(t_token *list);
t_token			*init_token(void);
int				add_token(t_token *list, char *item, int size);
void			free_token(t_token *list);
int				check_special_char(char c);
int				is_space(char c);
int				lexing(char *buf, t_token *token);
void			free_buf(char **buffer);
#endif
