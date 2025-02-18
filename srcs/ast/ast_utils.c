/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:01:00 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/15 13:50:48 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	print_command(t_ast *command);
// void	printTree(t_ast *command, int depth, int isRight, int *branch);
// char	*operator_type_to_str(int type);
// char	*type_to_str(int type);

// // void	print_AST(t_ast *command)
// // {
// // 	int array[1024] = {0};

// // 	command = ast_top(command);
// // 	printTree(command, 0, 0, array);
// // }

// void	print_ast_list(t_ast *command)
// {
// 	int	array[1024] = {0};

// 	printTree(command, 0, 0, array);
// }

// void	print_command(t_ast *command)
// {
// 	int	i;

// 	// char	*infile = "STDIN";
// 	// char	*outfile = "STDOUT";
// 	i = -1;
// 	if (command->commande->type == 10)
// 	{
// 		printf("%s$", command->commande->cmd_args[++i]);
// 		while (command->commande->cmd_args
// 			&& command->commande->cmd_args[++i] != NULL)
// 		{
// 			printf(" (\"%s$\")", command->commande->cmd_args[i]);
// 		}
// 	}
// 	printf("%s", operator_type_to_str(command->commande->type));
// }

// void	printTree(t_ast *command, int depth, int isRight, int *branch)
// {
// 	if (depth > 0)
// 	{
// 		for (int i = 0; i < depth - 1; i++)
// 		{
// 			if (branch[i])
// 				printf("│   ");
// 			else
// 				printf("    ");
// 		}
// 		printf("%s", isRight ? "└──" : "├──");
// 	}
// 	if (command == NULL)
// 	{
// 		printf("NULL\n");
// 		return ;
// 	}
// 	print_command(command);
// 	printf("\n");
// 	if (command->left != NULL || command->right != NULL)
// 	{
// 		branch[depth] = (command->right != NULL);
// 		printTree(command->left, depth + 1, command->right == NULL, branch);
// 		printTree(command->right, depth + 1, 1, branch);
// 	}
// }

// char	*operator_type_to_str(int type)
// {
// 	if (type == 5)
// 		return (ft_strdup("AND"));
// 	if (type == 6)
// 		return (ft_strdup("OR"));
// 	if (type == 8)
// 		return (ft_strdup("PIPE"));
// 	return (NULL);
// }

// bool	is_operator_type(int type)
// {
// 	return (type == 6 || type == 5 || type == 8);
// }

// bool	is_redirection_type(int type)
// {
// 	return (type == 1 || type == 2 || type == 3 || type == 4);
// }

// char	*type_to_str(int type)
// {
// 	if (type == 10)
// 		return (ft_strdup("CMD"));
// 	if (is_operator_type(type))
// 		return (ft_strdup("OPERATOR"));
// 	if (is_redirection_type(type))
// 		return (ft_strdup("REDIRECTION"));
// 	return (NULL);
// }
