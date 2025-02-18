/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:09:56 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/15 14:27:25 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

t_ast	*parsing(char *cmd_line, t_env *env_list)
{
	t_token	*token_list;
	t_cmd	*cmd_list;
	t_ast	*ast_list;

	token_list = create_token(cmd_line);
	if (!checking_token(&token_list->next, &env_list))
		return (get_data(NULL)->status = 2, NULL);
	cmd_list = parse_it(&token_list);
	open_all_heredoc(&cmd_list);
	ast_list = build_ast(NULL, cmd_list, false);
	while (ast_list->prev)
		ast_list = ast_list->prev;
	cmd_list = NULL;
	token_list = NULL;
	return (ast_list);
}

void	signal_catch(t_data *data)
{
	data->signaled = 0;
	clear_soft_data();
}

char	*handle_input(void)
{
	char	*str_bis;
	char	*str;
	t_data	*data;

	data = get_data(NULL);
	while (1)
	{
		if (g_status != 0 || data->signaled != 0)
		{
			get_data(NULL)->status = g_status;
			g_status = 0;
			data->signaled = 0;
			continue ;
		}
		str_bis = print_prompt();
		if (check_signal(data, str_bis) == false)
			continue ;
		if (!str_bis)
			return (free(str_bis), NULL);
		str = ft_strdup(str_bis);
		add_history(str);
		rl_redisplay();
		free(str_bis);
		return (str);
	}
}

void	process_command(char *str, t_env *env_list, t_data *data,
		t_ast **ast_list)
{
	*ast_list = parsing(str, env_list);
	if (!(*ast_list))
		return ;
	check_files_cmd_exist_left(*ast_list);
	if ((*ast_list)->right)
		check_files_cmd_exist_right(*ast_list);
	if (data->signaled == 1)
	{
		signal_catch(data);
		return ;
	}
	execute(*ast_list, data);
	clear_soft_data();
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*env_list;
	t_ast			*ast_list;
	t_data			data;
	char			*str;
	struct termios	term;

	(void)argc;
	(void)argv;
	if (isatty(STDIN_FILENO) == false)
		return (0);
	env_list = NULL;
	ast_list = NULL;
	initialize_data(&data, &env_list, envp);
	while (1)
	{
		tcgetattr(STDOUT_FILENO, &term);
		set_parent_signals();
		get_env(env_list);
		str = handle_input();
		if (!str)
			return (exit_now(data.status), 1);
		process_command(str, env_list, &data, &ast_list);
		tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	}
	return (printf("exit\n"), exit_now(data.status), 0);
}
