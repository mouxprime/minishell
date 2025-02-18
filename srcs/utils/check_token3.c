/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:37:09 by mianni            #+#    #+#             */
/*   Updated: 2024/11/14 11:56:38 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand(char *str)
{
	t_env	*env;
	t_data	*data;

	data = get_data(NULL);
	env = get_env(NULL);
	if (str[0] == '?')
	{
		str = ft_itoa(data->status);
		return (str);
	}
	while (env)
	{
		if (env->name && env->name[0] != '\0' && ft_strcmp(str, env->name) == 0)
			str = ft_substr(env->content, 0, ft_strlen(env->content), 0);
		env = env->next;
	}
	return (str);
}

bool	var_exist(char *str)
{
	t_env	*env;

	env = get_env(NULL);
	while (env)
	{
		while ((!env->name || !env->content) && env->next)
			env = env->next;
		if ((!env->name || !env->content))
			return (false);
		if (ft_strcmp(env->name, str) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}

void	expand_var2(t_token *token, int j, char *var, char *new_str)
{
	int	i;
	int	len;

	len = 1;
	i = 0;
	if (no_var_inside(token->token) == true)
		return ;
	while (token->token[i] != '$')
		i++;
	new_str = ft_substr(token->token, 0, i, 0);
	i++;
	j = i;
	while (token->token[i++] && ft_isalnum(token->token[i]) == 1)
		len++;
	var = ft_substr(token->token, j, len, 0);
	if (var_exist(var) == true)
	{
		var = expand(var);
		new_str = ft_strjoin(new_str, var);
		var = ft_substr(token->token, i, ft_strlen(&token->token[i]), 0);
		new_str = ft_strjoin(new_str, var);
		if (new_str)
			(token->token = new_str);
		token->type = 10;
	}
}

int	count_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	expand_var(t_token **token_list, t_env **env_list)
{
	t_token	*token;
	int		len;
	int		count;
	int		i;

	(void)env_list;
	len = 1;
	i = 0;
	token = *token_list;
	while (token)
	{
		i = 0;
		if (token->type == 9 || token->type == 12 || token->type == 10)
		{
			count = count_dollar(token->token);
			while (i < count)
			{
				expand_var2(token, 0, NULL, NULL);
				i++;
			}
		}
		token = token->next;
	}
}
