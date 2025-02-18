/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmenard <jmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:13:05 by jmenard           #+#    #+#             */
/*   Updated: 2024/11/13 18:12:19 by jmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_with_delay(char *str)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (j < 5000000)
			j++;
		ft_putchar(str[i]);
		i++;
	}
}

void	print_art(void)
{
	print_with_delay("\033[1;92m\t▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▖   ▗▖\n");
	print_with_delay("\t▐▛▚▞▜▌  █  ▐▛▚▖▐▌  █  ▐▌   ▐▌ ▐▌▐▌   ▐▌   ▐▌\n");
	print_with_delay("\t▐▌  ▐▌  █  ▐▌ ▝▜▌  █   ▝▀▚▖▐▛▀▜▌▐▛▀▀▘▐▌   ▐▌\n");
	print_with_delay("\t▐▌  ▐▌▗▄█▄▖▐▌  ▐▌▗▄█▄▖▗▄▄▞▘▐▌ ▐▌▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖\033[0m\n");
}

void	print_animation(void)
{
	int			pid;
	char		**env_array;
	t_env		*env;
	static char	*path = "/usr/bin/clear";
	static char	*args[] = {"clear", NULL};

	env = get_env(NULL);
	env_array = envlist_to_char(env);
	pid = fork();
	if (pid == 0)
		execve(path, args, env_array);
	printf("\n");
	print_art();
	usleep(10000);
	print_with_delay("\033[3m\t\tA 42project, by ");
	print_with_delay("\033[1;31mJmenard\033[0m");
	print_with_delay("\033[3m & \033[0m");
	print_with_delay("\033[1;31mMianni\033[0m\n\n");
}

char	*find_cwd(void)
{
	char	pwd[1024];
	int		last_slash;
	int		i;
	char	*new_str;

	i = 0;
	last_slash = 0;
	getcwd(pwd, sizeof(pwd));
	while (pwd[i])
	{
		if (pwd[i] == '/')
			last_slash = i + 1;
		i++;
	}
	new_str = ft_substr(pwd, last_slash, ft_strlen(pwd), 0);
	new_str = ft_strjoin("\001\033[32m\002", new_str);
	new_str = ft_strjoin(new_str, "\001\033[0m\002");
	new_str = ft_strjoin("(", new_str);
	new_str = ft_strjoin(new_str, "\001\033[1;37m\002)\001\033[0m\002");
	new_str = ft_strjoin("\001\033[1;37m\002@", new_str);
	return (new_str);
}

char	*print_prompt(void)
{
	char	*env;
	char	*name;
	int		i;
	char	*name_bis;
	char	*new_pwd;

	i = 0;
	new_pwd = find_cwd();
	env = getenv("SESSION_MANAGER");
	if (!env)
		return (readline("\033[1mminishell-> \033[0m"));
	else
	{
		name = ft_strnstr(env, "made", ft_strlen(env));
		while (name[i] != '.')
			i++;
		name_bis = ft_substr(name, 0, i, 0);
		name_bis = ft_strjoin("\001\033[1;37m\002", name_bis);
		name_bis = ft_strjoin(name_bis, "\001\033[0m\002");
		name_bis = ft_strjoin(name_bis, new_pwd);
		name_bis = ft_strjoin(name_bis, "\001\033[1;37m\002->\001\033[0m\002 ");
		return (readline(name_bis));
	}
}
