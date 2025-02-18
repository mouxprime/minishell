/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:07:35 by mianni            #+#    #+#             */
/*   Updated: 2024/11/07 17:58:40 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*node_right(t_cmd *cmd)
{
	t_ast	*new_node_right;

	if (cmd->type != 8 && next_operator(&cmd) == 8)
	{
		new_node_right = build_ast(NULL, cmd->next, true);
		while (cmd->next->next && cmd->next->next->type != 5
			&& cmd->next->next->type != 6)
			cmd = cmd->next;
	}
	else
		new_node_right = ast_new_node(cmd->next);
	return (new_node_right);
}

t_cmd	*itere_cmd(t_cmd *cmd)
{
	if (cmd->type != 8 && next_operator(&cmd) == 8)
	{
		while (cmd->next->next && cmd->next->next->type != 5
			&& cmd->next->next->type != 6)
			cmd = cmd->next;
	}
	return (cmd);
}

t_ast	*build_ast(t_ast *ast, t_cmd *cmd, bool envoye)
{
	t_ast	*new_node;
	t_ast	*new_node_right;

	if (!ast)
	{
		ast = ast_new_node(cmd);
		cmd = cmd->next;
	}
	if (cmd == NULL)
		return (ast);
	new_node = ast_new_node(cmd);
	ast->prev = new_node;
	new_node->left = ast;
	new_node_right = node_right(cmd);
	cmd = itere_cmd(cmd);
	cmd = cmd->next;
	new_node_right->prev = new_node;
	new_node->right = new_node_right;
	if (envoye && (next_operator(&cmd) == 5 || next_operator(&cmd) == 6))
		return (new_node);
	if (cmd && cmd->next)
		new_node = build_ast(new_node, cmd->next, false);
	return (new_node);
}

int	next_operator(t_cmd **cmd_list)
{
	t_cmd	*cmd;
	int		type;

	type = 0;
	cmd = (*cmd_list)->next;
	while (cmd)
	{
		if (cmd->type == 5 || cmd->type == 6 || cmd->type == 8)
		{
			type = cmd->type;
			break ;
		}
		cmd = cmd->next;
	}
	return (type);
}

t_ast	*ast_new_node(t_cmd *cmd)
{
	t_ast	*ast;

	ast = ft_malloc(1, sizeof(t_ast), 0, 0);
	ast->commande = cmd;
	ast->left = NULL;
	ast->right = NULL;
	ast->prev = NULL;
	return (ast);
}
