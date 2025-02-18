/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:35:53 by mianni            #+#    #+#             */
/*   Updated: 2024/11/15 14:20:57 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	convert_chains(t_token **token_list, t_env *env)
{
	env = get_env(env);
	if (token_list == NULL || (*token_list)->token[0] == '\0')
		return ;
	if ((*token_list)->token[0] != '$' && (*token_list)->token[1])
		(*token_list)->token = ft_substr((*token_list)->token, 0,
				ft_strlen((*token_list)->token), 0);
	else
		(*token_list)->token = ft_substr((*token_list)->token, 1,
				ft_strlen((*token_list)->token), 0);
	while ((*token_list) && (*token_list)->token[0] != '$'
		&& (*token_list)->token)
		(*token_list) = (*token_list)->next;
	while (env && token_list)
	{
		if ((*token_list) && env->name[0] != '\0'
			&& ft_strncmp(&(*token_list)->token[1], env->name,
				ft_strlen((*token_list)->token) - 1) == 0)
			(*token_list)->token = env->content;
		env = env->next;
	}
	if ((*token_list) && (*token_list)->token[0] == '$')
		(*token_list)->token = NULL;
	return ;
}

char	*concat_str(t_token *token_list)
{
	char	*str;
	char	*tmp;

	if (token_list->token)
		str = ft_strdup(token_list->token);
	if (token_list->next)
		token_list = token_list->next;
	else if (!token_list->next || !token_list->token)
		return (ft_strjoin("$", str));
	while (token_list)
	{
		tmp = ft_strjoin(str, token_list->token);
		str = tmp;
		token_list = token_list->next;
	}
	return (str);
}

char	*soft_token_loop_creation(t_token *token_list, char *str, int *i)
{
	char	*new_str;
	int		j;

	j = 0;
	while (str[*i + j] && is_a_special_space(str[*i + j]) == false)
		j++;
	if (i == 0)
		new_str = ft_substr(str, *i, j, 0);
	else
		new_str = ft_substr(str, *i - 1, j + 1, 0);
	if (new_str[0] != '\0')
		token_list = new_token(token_list, new_str, 10);
	*i += j;
	return (NULL);
}

void	create_first_token(t_token *token_list, char *str)
{
	char	*new_str;
	int		len;

	len = 0;
	while (str[len] && is_a_special_space(str[len]) == false)
		len++;
	new_str = ft_substr(str, 0, len, 0);
	token_list = new_token(token_list, new_str, 10);
}

bool	no_var_inside(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
			return (false);
		i++;
	}
	return (true);
}
