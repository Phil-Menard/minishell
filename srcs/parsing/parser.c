# include "../minishell.h"

// static int	check_tokens(t_token *tokens)
// {
// 	char	*path;

// 	path = NULL;
// 	while (tokens)
// 	{
// 		if (find_occurences(tokens->buf, '/') != 0)
// 		{
// 			if (access(tokens->buf, X_OK) == 0)
// 				return (printf("1\n"), 1);
// 		}
// 		else
// 		{
// 			path = ft_straddstr(path, "/bin/usr/");
// 			path = ft_straddstr(path, tokens->buf);
// 			if (access(path, X_OK) == 0)
// 				return (free(path), path = NULL, printf("1\n"), 1);
// 			free(path);
// 			path = NULL;
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (0);
// }

static void	free_tokens(t_token **tokens, char *temp, char *str, char **split)
{
	t_token	*tmp;
	size_t	i;

	i = -1;
	while (tokens[++i])
	{
		tmp = tokens[i]->next;
		free(tokens[i]->buf);
		tokens[i]->buf = NULL;
		free(tokens[i]);
		tokens[i] = tmp;
	}
	free(tokens);
	free(str);
	free(temp);
	free_db_array(split);
}

/* static void	printlist(t_token *tokens)
{
	while (tokens)
	{
		printf("%s, ", tokens->buf);
		tokens = tokens->next;
	}
} */

// ajoute espace, retire redir, split au | et tokenise
// Put in vars->cmd the first node cmd
static void	setcmd(t_var *vars, char *line, t_env *env)
{
	char	**split;
	char	*tmp;
	char	*str;
	t_token	**tokens;
	int		i;

	tmp = parse_redirections(line);
	if (!tmp)
		return ;
	str = str_without_redir(tmp);
	if (!str)
		return ;
	split = ft_split(str, "|");
	if (!split)
		return ;
	tokens = ft_calloc(sizeof(t_token *), double_arr_len(split) + 1);
	if (!tokens)
		return ;
	vars->cmd = ft_calloc(sizeof(char *), double_arr_len(split) + 1);
	if (!vars->cmd)
		return ;
	i = -1;
	while (split[++i])
	{
		tokens[i] = tokenizer(split[i], env, 0);
		vars->cmd[i] = ft_strdup(tokens[i]->buf);
	}
	free_tokens(tokens, tmp, str, split);
}



static char	*list_to_string(t_token *tokens)
{
	char			*res;
	t_token	*tmp;

	res = NULL;
	while (tokens && tokens->buf)
	{
		res = ft_straddstr(res, tokens->buf);
		res = ft_straddchar(res, ' ');
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->buf);
		tmp->buf = NULL;
		free(tmp);
		tmp = NULL;
	}
	if (tokens && tokens->buf == NULL)
	{
		free(tokens->buf);
		free(tokens);
		tokens = NULL;
	}
	return (res);
}

void	parsing(t_env **env, t_var *vars, t_env **export)
{
	// t_ast			*tree;
	t_token	*tokens;

	if (!vars->line)
		return ;
	if (check_pair(vars->line) == 0)
		quit("Unclosed quotes\n", 2, vars);
	if (ft_strfind)
	if (ft_strfind(vars->line, "<<") == 1)
	{
		heredoc(vars->line);
		vars->line = trunc_heredoc(vars->line);
	}
	tokens = tokenizer(vars->line, *env, 0);
	setcmd(vars, vars->line, *env);
	setarg(); //todo
	free(vars->line);
	vars->line = NULL;
	// if (check_tokens(tokens) == 0)
	// 	printf("error\n");
	vars->line = list_to_string(tokens);
	if (vars->line)
		check_pipes(vars, env, export);
	// create tree
	// exec
	// free_list(tree);
}

/* static void	create_tree(t_ast *tree, char **split, int i_arg)
{

} */
