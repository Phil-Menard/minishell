/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:10:26 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/11 11:10:42 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//set all variables with char * or char ** to NULL
void	nullify_arg_vars(t_var *vars)
{
	vars->cmd_line = NULL;
	vars->line = NULL;
	vars->path = NULL;
	vars->pids = NULL;
	vars->prompt = NULL;
}

void	free_db_vars(t_var *vars, size_t i)
{
	size_t	j;
	char	*tmp;

	tmp = ft_strdup("< .tomatePastequeCitronMiel");
	if (vars->cmd_line[i].infile)
	{
		j = 0;
		while (vars->cmd_line[i].infile[j])
		{
			if (ft_strncmp(tmp,
					vars->cmd_line[i].infile[j], ft_strlen(tmp)) == 0)
			{
				if (unlink(vars->cmd_line[i].infile[j] + 2) == -1)
					perror("unlink");
			}
			j++;
		}
		free_db_array(vars->cmd_line[i].infile);
	}
	if (tmp)
		free(tmp);
}

//free all variables from t_var and set them to NULL
void	free_vars(t_var *vars)
{
	size_t	i;

	i = -1;
	if (vars->prompt)
		free(vars->prompt);
	if (vars->cmd_line != NULL)
	{
		while (++i < vars->nb_cmd_line)
		{
			free_db_array(vars->cmd_line[i].args);
			free_db_vars(vars, i);
			if (vars->cmd_line[i].outfile)
				free_db_array(vars->cmd_line[i].outfile);
			free(vars->cmd_line[i].cmd);
		}
		free(vars->cmd_line);
	}
	if (vars->line)
		free(vars->line);
	if (vars->path)
		free(vars->path);
	if (vars->tokens)
		free_tokens(&vars->tokens);
	nullify_arg_vars(vars);
}

//set all variables in t_var to NULL or 0
void	init_vars(t_var *vars)
{
	nullify_arg_vars(vars);
	vars->tokens = NULL;
	vars->nb_cmd_line = 0;
	vars->exit_statut = 0;
	vars->i = 0;
}

void	free_and_close(t_var *vars, t_env **env, t_env **exp, int *fd)
{
	close_multiple_fd(fd);
	free_vars(vars);
	free_env(*env);
	free_env(*exp);
}
