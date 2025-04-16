/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmenard <pmenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:08:35 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/16 14:03:12 by pmenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//get OLDPWD var from env and print it in good fd
char	*cd_oldpwd(t_env *env, int fd, int *x, t_var *vars)
{
	char	*str;
	char	*path;

	path = NULL;
	path = ft_getenv(env, "OLDPWD");
	if (!path)
	{
		*x = 1;
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		vars->exit_statut = 1;
		return (NULL);
	}
	str = ft_strjoin(path, "\n");
	ft_putstr_fd(str, fd);
	free(str);
	return (path);
}

void	set_oldpwd(t_env **env, int x)
{
	t_env	*node;
	char	*cwd;
	char	*oldpwd;
	char	*temp;

	if (x == 0)
	{
		cwd = NULL;
		oldpwd = NULL;
		cwd = getcwd(NULL, 0);
		oldpwd = ft_getenv(*env, "OLDPWD");
		if (!oldpwd)
		{
			temp = ft_strjoin("OLDPWD=", getenv("OLDPWD"));
			node = ft_new_env_node(temp);
			ft_env_add_back(env, node);
			free(temp);
		}
		else
			free(oldpwd);
		*env = modify_env(*env, "OLDPWD", cwd);
		free(cwd);
	}
}

void	cd_print_invalid(char *arr, int *x, t_var *vars)
{
	*x = 1;
	print_multiple_strfd("minishell: cd: ", arr, ": invalid option\n", 2);
	vars->exit_statut = 2;
}

//set path for chdir
char	*set_path_dir(char *arg, t_env **env, int fd, t_var *vars)
{
	char	*path;
	int		x;

	path = NULL;
	x = 0;
	if (arg == NULL)
		path = ft_getenv(*env, "HOME");
	else if (ft_strncmp(arg, "-", 1) == 0)
	{
		if (ft_strlen(arg) == 1)
			path = cd_oldpwd(*env, fd, &x, vars);
		else
			cd_print_invalid(arg, &x, vars);
	}
	else if (ft_strncmp(arg, "~", 1) == 0)
		path = getenv("HOME");
	else
		path = ft_strdup(arg);
	if (!path && x != 1)
	{
		x = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	set_oldpwd(env, x);
	return (path);
}

void	ft_cd(t_env **env, int fd, t_var *vars)
{
	char	*path;

	path = NULL;
	if (double_arr_len(vars->cmd_line[vars->i].args) > 2 && fd == 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		vars->exit_statut = 1;
	}
	else
		path = set_path_dir(vars->cmd_line[vars->i].args[1], env, fd, vars);
	if (path)
	{
		vars->exit_statut = 0;
		if (chdir(path) == -1)
		{
			print_multiple_strfd("minishell: cd: ",
				vars->cmd_line[vars->i].args[1],
				": No such file or directory\n", 2);
			vars->exit_statut = 1;
		}
		*env = modify_env(*env, "PWD", path);
		if (!vars->cmd_line[vars->i].args[1] || (vars->cmd_line[vars->i].args[1]
				&& ft_strncmp(vars->cmd_line[vars->i].args[1], "~", 1) != 0))
			free(path);
	}
}
