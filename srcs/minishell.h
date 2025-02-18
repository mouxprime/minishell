/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:05:23 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/15 13:59:05 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# ifndef FAIL
#  define FAIL -1
# endif

extern volatile sig_atomic_t	g_status;

typedef struct s_token
{
	char						*token;
	int							type;
	struct s_token				*next;
	struct s_token				*prev;
}								t_token;

typedef struct s_cmd
{
	char						**cmd_args;
	int							type;
	struct s_files				*files;
	struct s_cmd				*next;
	struct s_cmd				*prev;
}								t_cmd;

typedef struct s_files
{
	char						*files_name;
	int							fd;
	int							type;
	struct s_files				*next;
	struct s_files				*prev;
}								t_files;

typedef struct s_ast
{
	struct s_ast				*prev;
	struct s_ast				*left;
	struct s_ast				*right;
	struct s_cmd				*commande;
}								t_ast;

typedef struct s_env
{
	struct s_env				*prev;
	struct s_env				*next;
	char						*name;
	char						*content;
	int							global;
}								t_env;

# define GLOBAL 1;

typedef struct s_data
{
	char						*name;
	t_env						*env;
	int							status;
	int							is_child;
	int							signaled;
}								t_data;

// minishell.c
// main
// TOKENISATION

// tokenisation.c						"FULL"
t_token							*token_loop_creation(t_token *token_list,
									char *command_line, int *i);

// tokenisation1.c				"FULL"
void							define_token_type(t_token *token_list);
int								create_token_separator(t_token *token_list,
									char *command_line, int i);
t_token							*create_token(char *command_line);
t_token							*new_token(t_token *token_list, char *txt,
									int type);
bool							check_quotes(char *command_line,
									int single_quote, int parenthesis,
									int double_quote);

// UTILS

// utils1.c
int								skip_spaces(char *command_line, int i);
bool							is_a_separator(char c);
bool							is_a_word(char *command_line, int i);
bool							is_a_space(char c);

// utils2.c			"3 PLACES RESTANTES"
bool							separator_in_word(char *command_line, int i);
bool							variable_test(char *str);
bool							check_token_list(t_token *token_list);
bool							is_a_quote(char c);

// PARSING

// parsing.c 				"FULL"
bool							is_operator(t_token *token_node);
t_cmd							*parse_it(t_token **token_list);
t_cmd							*concat_cmd(t_cmd *cmd, t_token *token);
t_cmd							*put_operator(t_cmd *cmd, t_token *token);
int								count_cmd_args(t_token **token_list);

// parsing_utils.c				"FULL"
void							print_cmd_list(t_cmd **cmd, int a);
void							ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void							ft_lstadd_back_files(t_files **lst,
									t_files *new);
t_files							*create_files_lst(t_token *chevron,
									t_token *filename);
t_cmd							*concat_cmd_bis(t_cmd *cmd, t_token *token,
									t_files *files, int i);

// ast_generator.c
t_ast							*build_ast(t_ast *ast, t_cmd *cmd, bool envoye);
int								next_operator(t_cmd **cmd_list);
t_ast							*ast_new_node(t_cmd *cmd);

// ast_utils.c
void							print_ast_list(t_ast *node);

// minishell_utils.c
void							print_token_list(t_token **token);
int								quoted_tokens(t_token *token_list,
									char *command_line, int index, char quote);
void							type_token(t_token *token_list);

// check_token.c
bool							checking_token(t_token **token_list,
									t_env **env_list);
void							expand_var(t_token **token_list,
									t_env **env_list);

// open_files.c
int								open_files(t_cmd *cmd);
int								open_heredoc(t_files *files);
void							open_all_heredoc(t_cmd **cmd_list);

// error.c			"4PLACES RESTANTES"
void							print_error(int error_type, char *incorrect_str,
									t_data *data);
int								perror_r(char *error_type, char *token);
void							error_token(char *token);

void							print_art(void);
void							print_animation(void);
char							*print_prompt(void);

t_env							*new_node(t_env *env, char *name,
									char *content);
t_env							*char_to_list(char **envp, t_env *env);
void							print_env(t_env *env, int flag);
t_env							*get_env(t_env *env);

// BUILTINS

int								ft_cd(char **path, int i, t_data *data);
void							ft_echo(char **command_line, t_data *data);
void							ft_env(t_data *data);
void							ft_export(char **command_line, t_data *data);
void							ft_pwd(t_data *data);
void							ft_exit(char **args, t_data *data);
void							ft_unset(char **command);

// EXEC

bool							search_builtins(char **command);
bool							do_builtins(char **command, t_data *data);
char							**envlist_to_char(t_env *env);
char							*copy_str(char *env_array, t_env *env, int len);
t_data							*get_data(t_data *data);
bool							is_a_subshell(t_ast *ast);
int								exec(t_ast *ast, t_data *data);
char							*get_path(char *cmd, char **env);
char							*get_path_bis(char *cmd, char **env);
bool							is_a_special_space(char c);
void							signal_handler(int signum);
void							exit_status(int status, t_data *data);
void							execute(t_ast *top, t_data *data);
void							first_child_process(int fd[2], t_ast *ast,
									t_data *data);
void							wait_for_children(int pid1, int pid2,
									t_data *data);
void							second_child_process(int fd[2], t_ast *ast,
									t_data *data);
void							pipe_function(t_ast *ast, t_data *data);
int								print_command_not_found(char *cmd);
void							fork_and_exec(t_ast *ast, t_data *data);
bool							check_if_fork_needed(t_ast *ast);
void							and_function(t_ast *ast);
void							or_function(t_ast *ast, t_data *data);
int								subshell_function(t_ast *ast, t_data *data);

// wildcards.c
int								found_files(char *file, char *cmd);
char							**create_cmd_tab(char **cmd, int len_malloc,
									char **files, int it);
char							**expand_wildcard(char **cmd, int it);
char							**find_wildcards(t_cmd *cmd);

// wildcards_utils.c
int								count_dir_files(void);
int								count_len_malloc(char **cmd_args);
char							**create_files_tab(void);
char							*remove_star(char *files);

void							set_parent_signals(void);
void							print_double_array(char **str);
void							ft_env_export(t_data *data);
t_ast							*parsing(char *cmd_line, t_env *env_list);
bool							no_var_inside(char *str);
char							*soft_token_loop_creation(t_token *token_list,
									char *str, int *i);
void							convert_chains(t_token **token_list,
									t_env *env);
char							*concat_str(t_token *token_list);
bool							search_in_env(t_env *env, t_data *data);
void							initialize_data(t_data *data, t_env **env_list,
									char **envp);
bool							option_n(char *str);
bool							open_n_do_builtins(t_cmd *cmd, t_data *data,
									t_files *files, int dup_status);
void							print_data(t_data *data);
bool							check_signal(t_data *data, char *str_bis);
bool							is_operator_bis(t_token *token_node);
bool							checking_token_bis(t_token **token_list);
char							**copy_remaining_cmd(char **cmd, char **new_cmd,
									int *i, int *c);
void							error_heredoc(char *token);
void							set_child_signals(void);
bool							check_parenthesis(char *str);
bool							check_files_cmd_exist_left(t_ast *ast_list);
bool							check_files_cmd_exist_right(t_ast *ast_list);
bool							export_invalid_char(char c);
void							error_export(char *command_line);

#endif
