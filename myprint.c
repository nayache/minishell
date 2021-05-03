#include "minishell.h"

void	myprint_tree(t_btree *root)
{
	if (root == NULL)
		return;
	if (root->argv != NULL)
		print_tab(root->argv);
	else
		ft_putstr(root->flux);
	if (root->right != NULL)
	{
		for(int i = 0; i < 8; i++)
			ft_putchar(' ');
		myprint_tree(root->right);
	}
}

void	myprint_two(t_btree *root)
{
	if (root == NULL)
		return;
	if (root->left != NULL)
	{
		if (root->left->argv != NULL)
			print_tab(root->left->argv);
		else
			ft_putstr(root->left->flux);
	}
	if (root->right != NULL)
	{
		for(int i = 0; i < 9; i++)
			ft_putchar(' ');
		myprint_two(root->right);
	}
}

void	myprint(t_btree *root)
{
	myprint_tree(root);
	ft_putstr("\n\n");
	myprint_two(root);
	ft_putchar('\n');
}
