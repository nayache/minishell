#include "minishell.h"

int	main()
{
	char	**src = malloc(sizeof(char *) * 5);
	char	**src2 = malloc(sizeof(char *) * 3);
	
	t_cmd *cmd = malloc(sizeof(t_cmd));
	t_cmd *cmd2 = malloc(sizeof(t_cmd));

	src[0] = ft_strdup("salut");
	src[1] = ft_strdup("cava");
	src[2] = ft_strdup("mon");
	src[3] = ft_strdup("ami");
	src[4] = NULL;

	src2[0] = ft_strdup("Hello");
	src2[1] = ft_strdup("World!");
	src2[2] = NULL;

	cmd->argv = ft_tabdup(src);
	cmd->next = cmd2;
	cmd2->argv = ft_tabdup(src2);
	cmd2->next = NULL;
	print_cmd(cmd);
}
