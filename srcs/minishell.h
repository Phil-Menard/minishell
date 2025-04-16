/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:10:48 by lefoffan          #+#    #+#             */
/*   Updated: 2025/04/16 16:23:08 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include "../libft/libft.h"

# define HEREDOC	".tomatePastequeCitronMiel.tmp"

extern volatile sig_atomic_t	g_exit_signal;

typedef enum e_mod
{
	MOD_NORMAL,
	MOD_SINGLE,
	MOD_DOUBLE,
	MOD_QUOTED
}	t_mod;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INFILE,
	TOKEN_HEREDOC,
	TOKEN_OUTFILE,
	TOKEN_REDIR_FILE,
	// TOKEN_AND,
	// TOKEN_OR,
}	t_token_type;

typedef enum e_expand
{
	EXPANDABLE,
	EXPANDED,
	NOT_EXPANDABLE
}	t_expand;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd_line
{
	char	*cmd;
	char	**args;
	char	**infile;
	char	**outfile;
}			t_cmd_line;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

typedef struct s_var
{
	pid_t		*pids;
	t_cmd_line	*cmd_line;
	size_t		nb_cmd_line;
	size_t		i;
	t_token		*tokens;
	char		*line;
	char		*prompt;
	char		*path;
	int			exit_statut;
	char		*file_name;
}				t_var;

typedef struct s_tokenizer
{
	char	*buf;
	t_mod	mod;
	t_token	*tokens;
	int		i;
	t_env	*env;
}			t_tokenizer;

/**========================================================================
 *!                                  PARSING
 *========================================================================**/
t_mod		is_protected(char c);
int			count_heredoc_cmdline(t_token *tokens, size_t i_pipe);
char		**get_dels(t_token *tokens, size_t i_pipe, t_mod *mod);
void		ft_heredoc(t_token **tokens, t_var *vars, t_env *env);
void		parser(t_env **env, t_var *vars, t_env **export);
t_token		*tokenizer(char *line, t_env *env);
t_cmd_line	*set_cmd_line(t_token *tokens, t_var *vars);
char		*expand_str(char *str, t_env *env);
size_t		count_tokens_type(t_token *tokens, t_token_type type);
size_t		count_in_tokens(t_token *tokens, char *to_find);
void		free_tokens(t_token **tokens);
t_token		*new_token(char *s, t_token_type type, t_token *next);
t_token		*get_cmd_line_last_token(t_token *tokens, int *i, int i_pipe);
t_token		*last_token(t_token *tokens);
void		write_line_heredoc(char *line, int fd);
void		printlist(t_token *tokens);
/**========================================================================
 *!                           EXECUTION BUILTINS
 *========================================================================**/
void		check_pipes(t_var *vars, t_env **env, t_env **export);
void		ft_pwd(t_var *vars, int fd);
void		ft_env(t_env *env, t_var *vars, int fd);
void		ft_export(t_var *vars, t_env **env, t_env **export, int fd);
void		ft_echo(t_var *vars, int fd);
void		ft_cd(t_env **env, int fd, t_var *vars);
void		ft_unset(t_env **env, t_env **export, t_var *vars);
void		ft_exit(int *fd, t_var *vars, t_env **env, t_env **export);
/**========================================================================
 *!                        EXECUTION BASH COMMANDS
 *========================================================================**/
void		exec_cmds(t_var *vars, int *fd, t_env **env, t_env **export);
void		ft_execve(t_var *vars, t_env **env, t_env **export, int *fd);
void		builtin_or_cmd(t_var *vars, int *fd, t_env **env, t_env **exp);
char		*get_right_path(char *str, t_var *vars, t_env **env);
char		*get_next_path(char *arr, char *str, t_var *vars);
char		**split_path_var(t_env **env);
void		end_right_path(t_var *vars, char *str, char **arr);
/**========================================================================
 *!                                 PIPES
 *========================================================================**/
void		pipex(t_var *vars, t_env **env, t_env **export);
/**========================================================================
 *!                      UTILS FUNCTIONS FOR PIPES
 *========================================================================**/
void		close_previous_fd(int previous_fd);
void		wait_childs(t_var *vars, t_env **env);
void		outfile_dups(int *fd, int *pipefd, t_var *vars);
void		post_cmd(t_var *vars, int *pipefd, int *previous_fd, int *fd);
void		end_pipex(int *pipefd, t_var *vars, int prev_fd, t_env **env);
/**========================================================================
 *!                               UTILS
 *========================================================================**/
char		*ft_join_mid(char *s1, char slash, char *s2);
int			ft_cmpstr(char *s1, char *s2);
void		free_db_array(char **arr);
char		**fill_arg(t_var *vars);
char		*ft_straddstr(char *s1, char *s2);
int			double_arr_len(char **arr);
char		*ft_straddchar(char *str, char c);
int			find_occurences(char *str, char c);
int			ft_str_isalpha(char *str);
long int	ft_atol(char *nptr);
char		*ft_ltoa(long int n);
void		free_vars(t_var *vars);
void		free_and_close(t_var *vars, t_env **env, t_env **exp, int *fd);
void		init_vars(t_var *vars);
void		print_multiple_strfd(char *s1, char *var, char *s2);
void		start_loop(t_var *vars, t_env **env);
char		*set_prompt_arg(t_env **env);
char		*path_with_way(char *str, t_var *vars);
/**========================================================================
 *!                      UTILS FUNCTIONS FOR FD
 *========================================================================**/
int			*init_fd(void);
int			*set_fd(t_cmd_line *cmd_line, t_var *vars, t_env **env, int *fd);
int			*init_and_set_fd(t_cmd_line *cmd_line, t_var *vars, t_env **env);
void		close_multiple_fd(int *fd);
int			set_previous_fd(int *fd, int previous_fd);
char		*parse_redirections(char *line);
/**========================================================================
 *!                            REDIRECTIONS
 *========================================================================**/
int			is_redirected(char **infiles, char **outfiles);
void		prepare_redir(t_var *vars, int *fd, t_env **env, t_env **exp);
void		exec_redir(t_var *vars, int *fd, t_env **env, t_env **export);
/**========================================================================
 *!                                 ENV
 *========================================================================**/
t_env		*ft_new_env_node(char *content);
t_env		*fill_env(t_env **lst, char **envp);
t_env		*modify_env(t_env *env, char *var_name, char *content);
void		ft_env_add_back(t_env **lst, t_env *new);
char		*ft_getenv(t_env *env, char *content);
t_env		*remove_env_var(t_env **lst, char *str, int x);
int			env_size(t_env *lst);
void		free_env_node(char *var, t_env *node);
void		free_env(t_env *lst);
t_env		*add_var_env(t_env **env, char *line);
void		update_exit_env(t_env *env, t_var *vars);
/**========================================================================
 *!                                 EXPORT
 *========================================================================**/
t_env		*init_export_lst(t_env **env, t_env **lst);
int			var_already_exist(t_env **export, char *str);
t_env		*add_var_export(t_env **exp, t_env **env, char *line, t_var *vars);
t_env		*assign_export(t_env **exp, t_env **env, char *line, t_var *vars);
/**========================================================================
 *!                                 SIGNALS
 *========================================================================**/
void		set_signal_action(void);
void		handle_ctrl_d(t_env **env, t_env **export, t_var *vars);
int			rl_custom_hook(void);
void		update_status(t_var *vars, t_env **env);

#endif