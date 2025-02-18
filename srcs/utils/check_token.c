/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:48:45 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/14 11:57:54 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*contain_variables(char *str, t_env *env)
{
	int		i;
	t_token	*trash_token_list;
	t_token	*initial_token_list;

	(void)env;
	i = 0;
	if (ft_strlen(str) == 1 || no_var_inside(str) == true)
		return (str);
	trash_token_list = ft_malloc(1, sizeof(t_token), 0, 0);
	ft_bzero(trash_token_list, sizeof(t_token));
	while (str[i++])
		soft_token_loop_creation(trash_token_list, str, &i);
	trash_token_list = trash_token_list->next;
	initial_token_list = trash_token_list;
	while (trash_token_list)
	{
		convert_chains(&trash_token_list, NULL);
		if (trash_token_list && trash_token_list->token == NULL)
			break ;
		if (trash_token_list)
			trash_token_list = trash_token_list->next;
	}
	str = concat_str(initial_token_list);
	return (str);
}

void	split_variables(t_token **token_list)
{
	char	*str;
	t_token	*token;
	t_data	*data;

	data = get_data(NULL);
	token = *token_list;
	while (token)
	{
		if (token->type == 9)
		{
			if (token->token[1] == '?' && ft_isalnum(token->token[2]))
			{
				str = ft_substr(token->token, 2, ft_strlen(token->token) - 2,
						0);
				token->token = ft_substr(token->token, 0, 2, 0);
				token->token = ft_itoa(data->status);
				token->token = ft_strjoin(token->token, str);
			}
		}
		token = token->next;
	}
}

bool	checking_token(t_token **token_list, t_env **env_list)
{
	t_token	*token;

	split_variables(token_list);
	expand_var(token_list, env_list);
	token = *token_list;
	while (token)
	{
		if (!token->token)
			return (false);
		if (token->type == 10)
			token->token = contain_variables(token->token, *env_list);
		if (token->type == 7)
		{
			if (is_operator_bis(token->prev) == false
				|| !check_parenthesis(token->token))
				return (error_token(token->token), false);
		}
		if (token->type >= 1 && token->type <= 4)
		{
			if (!token->next || token->next->type < 9 || token->next->type > 12)
				return (error_token(token->token), false);
		}
		token = token->next;
	}
	return (checking_token_bis(token_list));
}

void	check_var_expend(t_token *token_list)
{
	while (token_list)
	{
		if (token_list->type == 9)
		{
			if (token_list->token[0] == '$')
				token_list->token = NULL;
		}
		token_list = token_list->next;
	}
	return ;
}

bool	parse_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 1)
			return (false);
		i++;
	}
	return (true);
}
