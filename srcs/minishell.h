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

# define HEREDOC	"tomatePastequeCitronMiel"

extern volatile int unblock_sigquit;

typedef struct s_cmd_line
{
	char	*cmd;
	char	**args;
	char	**infile;
	char	**outfile;
}			t_cmd_line;

typedef struct s_leaf
{
	t_cmd_line		*cmd_line; // tableau de cmd_line[nb de pipe + 1]
	struct s_leaf	*left;
	struct s_leaf	*right;
}					t_leaf;

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
	char		*line;
	char		*prompt;
	char		*path;
	int			exit_statut;
}				t_var;

// typedef struct s_ast
// {
// 	t_type				type;
// 	char				*content;
// 	struct s_ast		*left;
// 	struct s_ast		*right;
// }						t_ast;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_OPERATOR
}	t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

t_cmd_line	*set_cmd_line(t_token *tokens, t_var *vars);
size_t		count_in_tokens(t_token *tokens, char *to_find);
void		free_tokens(t_token **tokens);
t_token		*tokenizer(char *line);
void		parser(t_env **env, t_var *vars, t_env **export);
// /**========================================================================
//  *!                                  PARSING
//  *========================================================================**/
// t_token		*tokenizer(char *line, t_env *env, size_t i);
// t_token		*new_tkb(size_t len, void *buf);
// t_token		*get_last(t_token *node);
// t_token		get_token(char *str);
// size_t		get_pos(char *str, size_t start, char c);
// int			check_pair(char *line);
// void		heredoc(char *str);
// char		*trunc_heredoc(char *line);
// /**========================================================================
//  *!                                  TREE
//  *========================================================================**/
// void		free_list(t_ast *tree);
// t_ast		*new_node(char *cmd, t_token type);
// void		add_node_end(t_ast *tree, const char *branch, t_ast *node);
// void		parsing(t_env **env, t_var *vars, t_env **export);
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
void		check_path_errors(char *argv, char **env, int *pipefd);
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
void		wait_childs(t_var *vars);
void		outfile_dups(int *fd, int *pipefd, t_var *vars);
void		post_cmd(int *pipefd, int *previous_fd, int *fd);
void		end_pipex(int *pipefd, t_var *vars, int prev_fd);
/**========================================================================
 *!                               UTILS
 *========================================================================**/
char		*ft_join_mid(char *s1, char slash, char *s2);
int			ft_cmpstr(char *cmd, char *builtin);
void		free_db_array(char **arr);
char		**fill_arg(t_var *vars);
char		*ft_straddstr(char *s1, char *s2);
int			ft_strfind(char *s1, char *s2);
int			double_arr_len(char **arr);
char		*ft_straddchar(char *str, char c);
int			find_occurences(char *str, char c);
char		**prepare_line(char *line);
int			ft_str_isalpha(char *str);
long int	ft_atol(char *nptr);
char		*ft_ltoa(long int n);
void		free_vars(t_var *vars);
void		free_and_close(t_var *vars, t_env **env, t_env **exp, int *fd);
void		quit(char *msg, int exit_status, t_var *vars);
void		init_vars(t_var *vars);
/**========================================================================
 *!                      UTILS FUNCTIONS FOR FD
 *========================================================================**/
int			*init_fd(void);
int			*set_fd(char *line, int *fd, t_var *vars, t_env **env);
int			*init_and_set_fd(char *line, t_var *vars, t_env **env);
void		close_multiple_fd(int *fd);
int			set_previous_fd(int *fd, int previous_fd);
int			is_infile_valid(int fd, char *infile);
char		*parse_redirections(char *line);
/**========================================================================
 *!                      CHECK QUOTES WHEN NEW LINE
 *========================================================================**/
int			check_quote(char *str);
char		*get_vars(char *line);
/**========================================================================
 *!                            REDIRECTIONS
 *========================================================================**/
int			is_redirected(char *str);
void		prepare_redir(t_var *vars, int *fd, t_env **env, t_env **exp);
char		*str_without_redir(char *str);
char		**get_infile(char *str);
char		**get_outfile(char *str);
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
void		print_t_list(t_list *lst);
int			var_already_exist(t_env **export, char *str);
t_env		*add_var_export(t_env **export, t_env **env, char *line, t_var *vars);
t_env		*assign_var_export(t_env **export, t_env **env, char *line, t_var *vars);
/**========================================================================
 *!                                 SIGNALS
 *========================================================================**/
void		set_signal_action(void);
void		handle_ctrl_d(t_env **env, t_env **export, t_var *vars);

#endif