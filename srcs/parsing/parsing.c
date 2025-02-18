/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:37:21 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 14:11:25 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_operator(t_token *token_node)
{
	if (token_node->type == 5 || token_node->type == 6 || token_node->type == 8
		|| !token_node)
		return (true);
	else
		return (false);
}

t_cmd	*parse_it(t_token **token_list)
{
	t_cmd	*cmd_list;
	t_token	*token;
	int		len;

	len = 0;
	token = *token_list;
	cmd_list = NULL;
	while (token)
	{
		ft_lstadd_back_cmd(&cmd_list, concat_cmd(cmd_list, token));
		while (token && is_operator(token) == false)
			token = token->next;
		if (token)
			ft_lstadd_back_cmd(&cmd_list, put_operator(cmd_list, token));
		else if (!token)
			ft_lstadd_back_cmd(&cmd_list, NULL);
		if (token && token->next)
			token = token->next;
	}
	return (cmd_list);
}

t_cmd	*concat_cmd(t_cmd *cmd, t_token *token)
{
	t_files	*files;
	int		t_len;

	t_len = 0;
	files = NULL;
	if (token->token == NULL)
		token = token->next;
	t_len = count_cmd_args(&token);
	cmd = ft_malloc(1, sizeof(t_cmd), 0, 0);
	cmd->next = NULL;
	cmd->cmd_args = ft_malloc(t_len + 1, sizeof(char *), 0, 0);
	cmd->type = 10;
	return (concat_cmd_bis(cmd, token, files, 0));
}

t_cmd	*put_operator(t_cmd *cmd, t_token *token)
{
	if (is_operator(token) == true)
	{
		cmd = ft_malloc(1, sizeof(t_cmd), 0, 0);
		cmd->next = NULL;
		cmd->cmd_args = ft_malloc(2, sizeof(char *), 0, 0);
		cmd->cmd_args[0] = token->token;
		cmd->cmd_args[1] = NULL;
		cmd->type = token->type;
		cmd->files = NULL;
	}
	return (cmd);
}

int	count_cmd_args(t_token **token_list)
{
	t_token	*token;
	int		i;
	int		j;

	token = *token_list;
	i = 0;
	j = 0;
	while (token && is_operator(token) == false)
	{
		if (token->type >= 1 && token->type <= 4)
			j += 2;
		token = token->next;
		i++;
	}
	return (i - j);
}
