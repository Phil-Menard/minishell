#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include "../libft/libft.h"

# define LEX_BUFF_SIZE	200

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

typedef struct s_line
{
	pid_t	*pids;
	char	**arr;
	char	**cmd_split;
	char	*content;
	char	*prompt;
	char	*cmd_pipe;
	int		i;
}				t_line;

typedef enum e_token
{
	CMD,
	AND,
	OR,
	PIPE,
	QUOTE,
}	t_token;

typedef enum e_state
{
	NORMAL,
	WHITESPACE,
	SINGLE_QUOTES,
	DOUBLE_QUOTES,
}	t_state;

typedef struct s_ast
{
	t_token				token;
	char				*cmd;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef struct s_token_builder
{
	char					*buf;
	int						len;
	struct s_token_builder	*next;
}							t_token_builder;

/**========================================================================
 *!                                  PARSING
 *========================================================================**/
t_token_builder	*ft_new_tkb(size_t len, void *buf);
t_token_builder	*ft_get_last(t_token_builder *node);
t_token			ft_get_token(char *str);
int				ft_get_pos(char *str, int start, char c);
int				ft_check_pair(char *line, char what);
/**========================================================================
 *!                                  TREE
 *========================================================================**/
void			ft_free_list(t_ast *tree);
t_ast			*ft_new_node(char *cmd, t_token type);
void			ft_add_node_end(t_ast *tree, const char *branch, t_ast *node);
void			ft_parse(char *line, t_env *env);
void			ft_print_tree(t_ast *root, int space); // a retirer
/**========================================================================
 *!                           EXECUTION BUILTINS
 *========================================================================**/
void			check_pipes(t_line *line, t_env **env, t_env **export);
void			ft_pwd(int fd);
void			ft_env(t_env *env, int fd);
void			ft_export(char *line, t_env **env, t_env **export, int fd);
void			ft_echo(char *str, int fd);
void			ft_cd(char *str, t_env *env, int fd);
void			ft_unset(char *str, t_env **env, t_env **export);
void			ft_exit(int *fd, t_line *line, t_env **env, t_env **export);
/**========================================================================
 *!                        EXECUTION BASH COMMANDS
 *========================================================================**/
void			exec_cmds(char *str, int *fd, t_env **env);
void			ft_execve(char *path, char **arg, t_env **env);
void			builtin_or_cmd(t_line *line, int *fd, t_env **env, t_env **export);
char			*get_right_path(char *str);
char			*get_next_path(char *arr, char *str);
void			check_path_errors(char *argv, char **env, int *pipefd);
void			builtin_or_cmd(t_line *line, int *fd, t_env **env, t_env **export);
/**========================================================================
 *!                                 PIPES
 *========================================================================**/
void			pipex(t_line *line, t_env **env, t_env **export, int arr_size);
/**========================================================================
 *!                      UTILS FUNCTIONS FOR PIPES
 *========================================================================**/
void			close_previous_fd(int previous_fd);
void			wait_childs(pid_t *pids, int arr_size);
void			outfile_dups(int *fd, int *pipefd, int i, int arr_size);
void			post_cmd(int *pipefd, int *previous_fd, int *fd);
void			end_pipex(int *pipefd, pid_t *pids, int arr_size, int previous_fd);
/**========================================================================
 *!                               UTILS
 *========================================================================**/
char			*ft_join_mid(char *s1, char slash, char *s2);
void			free_db_array(char **arr);
char			**fill_arg(char *path, char *argv);
char			*ft_straddstr(char *s1, char *s2);
int				ft_strfind(char *s1, char *s2);
int				double_arr_len(char **arr);
char			*ft_straddchar(char *str, char c);
int				find_occurences(char *str, char c);
char			**prepare_line(char *line);
int				ft_str_isalpha(char *str);
long int		ft_atol(char *nptr);
char			*ft_ltoa(long int n);
/**========================================================================
 *!                      UTILS FUNCTIONS FOR FD
 *========================================================================**/
int				*init_fd(void);
int				*set_fd(char *line, int *fd);
int				*init_and_set_fd(char *line);
void			close_multiple_fd(int *fd);
int				set_previous_fd(int *fd, int previous_fd);
int				is_infile_valid(int fd, char *infile);
/**========================================================================
 *!                      CHECK QUOTES WHEN NEW LINE
 *========================================================================**/
int				check_quote(char *str);
char			*get_lines(char *line);
/**========================================================================
 *!                            REDIRECTIONS
 *========================================================================**/
int				is_redirected(char *str);
void			prepare_redir(char *str, int redirection, int *fd, t_env **env);
char			*str_without_redir(char *str);
char			*get_infile(char *str);
char			**get_outfile(char *str);
void			exec_redir(char *path, char **arg, int *fd, t_env **env);
/**========================================================================
 *!                                 ENV
 *========================================================================**/
t_env			*ft_new_env_node(char *content);
t_env			*fill_env(t_env **lst, char **envp);
t_env			*modify_env(t_env *env, char *var_name, char *content);
void			ft_env_add_back(t_env **lst, t_env *new);
char			*get_var(t_env *env, char *content);
t_env			*remove_env_var(t_env **lst, char *str, int x);
int				env_size(t_env *lst);
void			free_env_node(char *var, t_env *node);
void			free_env(t_env *lst);
t_env			*add_var_env(t_env **env, char *line);
/**========================================================================
 *!                                 EXPORT
 *========================================================================**/
t_env			*init_export_lst(t_env **env, t_env **lst);
void			print_t_list(t_list *lst);
int				var_already_exist(t_env **export, char *str);

#endif