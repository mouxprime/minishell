/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:16:57 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/15 14:29:57 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*struc;

	struc = *lst;
	if (struc == NULL)
		*lst = new;
	else
	{
		while (struc->next != NULL)
			struc = struc->next;
		struc->next = new;
	}
}

void	ft_lstadd_back_files(t_files **lst, t_files *new)
{
	t_files	*struc;

	struc = *lst;
	if (struc == NULL)
		*lst = new;
	else
	{
		while (struc->next != NULL)
			struc = struc->next;
		struc->next = new;
	}
}

t_files	*create_files_lst(t_token *chevron, t_token *filename)
{
	t_files	*files;

	files = ft_malloc(1, sizeof(t_files), 0, 0);
	files->type = chevron->type;
	files->files_name = ft_malloc(ft_strlen(filename->token) + 1, sizeof(char),
			0, 0);
	files->files_name = filename->token;
	files->fd = -1;
	files->next = NULL;
	return (files);
}

t_cmd	*concat_cmd_bis(t_cmd *cmd, t_token *token, t_files *files, int i)
{
	while (token)
	{
		if (is_operator(token) == true || !token)
			break ;
		else if (token->type >= 1 && token->type <= 4)
		{
			ft_lstadd_back_files(&files, create_files_lst(token, token->next));
			token = token->next;
			if (token->next)
				token = token->next;
			else
				break ;
		}
		else if ((token->type >= 9 && token->type <= 12) || token->type == 7)
		{
			cmd->cmd_args[i] = token->token;
			if (i == 0)
				cmd->type = token->type;
			i++;
			token = token->next;
		}
	}
	cmd->cmd_args[i] = NULL;
	cmd->files = files;
	return (cmd);
}

// void	print_cmd_list(t_cmd **cmd, int a)
// {
// 	t_cmd	*cmd_list;
// 	t_files	*file_temp;
// 	int		i;
// 	int		j;
// 	int		f;

// 	i = 0;
// 	j = 1;
// 	cmd_list = *cmd;
// 	printf("PRINT LIST \n");
// 	printf("////////////////////////////\n");
// 	while (cmd_list)
// 	{
// 		i = 0;
// 		printf("CMD NUM %d\n", j);
// 		while (cmd_list->cmd_args[i])
// 		{
// 			printf("cmd %d ; %s\n", i, cmd_list->cmd_args[i]);
// 			i++;
// 		}
// 		printf("type ; %d\n", cmd_list->type);
// 		f = 1;
// 		file_temp = cmd_list->files;
// 		while (cmd_list->files)
// 		{
// 			printf("\tFILES %d\n", f);
// 			printf("\tfile name ; %s\n", cmd_list->files->files_name);
// 			printf("\tfd ; %d\n", cmd_list->files->fd);
// 			printf("\ttype ; %d\n", cmd_list->files->type);
// 			cmd_list->files = cmd_list->files->next;
// 			f++;
// 		}
// 		cmd_list->files = file_temp;
// 		cmd_list = cmd_list->next;
// 		j++;
// 		printf("\n-------------------\n");
// 		if (a == 1)
// 			break ;
// 	}
// 	printf("////////////////////////////\n");
// }