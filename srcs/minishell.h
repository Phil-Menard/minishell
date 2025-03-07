#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define LEX_BUFF_SIZE	200

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

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
	char					buf[LEX_BUFF_SIZE];
	int						len;
	struct s_token_builder	*next;
}							t_token_builder;

//---------------PARSING------------------------
int		ft_get_pos(char *str, int start, char c);
t_token	ft_get_token(char *str);
char	**ft_duptab(char **tab, int *start, int end);
int		ft_check_pair(char *line, char what);
//---------------------TREE--------------------
void	ft_free_list(t_ast *tree);
t_ast	*ft_new_node(char *cmd, t_token type);
void	ft_add_node_end(t_ast *tree, const char *branch, t_ast *node);
void	ft_parse(char *line, t_env *env, int *exit_code);
void	ft_print_tree(t_ast *root, int space); //! a retirer
//---------------BUILTINS COMMANDS--------------------
void	ft_pwd(int *fd);
void	ft_env(t_env *env, int *fd);
void	ft_echo(char *str, int *fd);
void	ft_cd(char *str, t_env *env, int *fd);
void	ft_unset(char *str, t_env **env);
void	ft_exit(int *exit_code);
void	exec_cmds(char *str, int *fd);
void	ft_execve(char *path, char **arg);
char	*get_right_path(char *str);
char	*get_next_path(char *arr, char *str);
//---------------UTILS--------------------
char	*ft_join_mid(char *s1, char slash, char *s2);
void	free_db_array(char **arr);
char	**fill_arg(char *path, char *argv);
char	*ft_straddstr(char *s1, char *s2);
int		ft_strfind(char *s1, char *s2);
int		double_arr_len(char **arr);
char	*ft_straddchar(char *str, char c);
int		find_occurences(char *str, char c);
//---------------UTILS FUNCTIONS FOR FD--------------------
int		*set_fd(char *line, int *fd);
void	close_multiple_fd(int *fd);
int		get_opened_fd_output(int *fd);
//---------------CHECK QUOTES WHEN NEW LINE--------------------
int		check_quote(char *str);
char	*get_lines(char *line);
//---------------REDIRECTIONS--------------------
int		is_redirected(char *str);
void	prepare_redir(char *str, int redirection, int *fd);
char	*str_without_redir(char *str);
char	*get_infile(char *str);
char	*get_outfile(char *str);
void	exec_redir(char *path, char **arg, int *fd);
//---------------ENV--------------------
t_env	*ft_new_env_node(char *content);
t_env	*fill_env(t_env **lst, char **envp);
t_env	*modify_env(t_env *env, char *old_var, char *new_var);
void	ft_env_add_back(t_env **lst, t_env *new);
char	*get_var(t_env *env, char *content);
t_env	*remove_env_var(t_env **lst, char *str);
void	print_env(t_env *lst, int fd);
void	free_env_node(char *var, t_env *node);
void	free_env(t_env *lst);

#endif