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
# include "../libft/libft.h"

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

typedef struct s_tree
{
	char			*cmd;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

//---------------------TREE--------------------
void	ft_free_list(t_tree *tree);
void	ft_execute(char *line, t_env **env);
//---------------EXECUTION--------------------
void	builtins(char *line, t_env **env);
void	ft_pwd(int fd);
void	ft_env(t_env *env, int fd);
void	ft_echo(char *str, int fd);
void	ft_cd(char *str, t_env *env, int fd);
void	ft_unset(char *str, t_env **env);
void	ft_exit();
void	exec_cmds(char *str, int *fd, int id);
void	ft_execve(char *path, char **arg);
char	*get_right_path(char *str);
char	*get_next_path(char *arr, char *str);
void	check_path_errors(char *argv, char **env, int *pipefd);
void	find_correct_function(char *line, int *fd, t_env **env, int id);
//---------------PIPES----------------------
void	pipex(char **arr, t_env **env, int *fd);
//---------------UTILS--------------------
char	*ft_join_mid(char *s1, char slash, char *s2);
void	free_db_array(char **arr);
char	**fill_arg(char *path, char *argv);
char	*ft_straddstr(char *s1, char *s2);
int		ft_strfind(char *s1, char *s2);
int		double_arr_len(char **arr);
char	*ft_straddchar(char *str, char c);
int		find_occurences(char *str, char c);
char	**prepare_line(char *line);
//---------------UTILS FUNCTIONS FOR FD--------------------
int		*init_fd(void);
int		*set_fd(char *line, int *fd);
void	close_multiple_fd(int *fd);
// int		get_opened_fd_output(int *fd);
//---------------CHECK QUOTES WHEN NEW LINE--------------------
int		check_quote(char *str);
char	*get_lines(char *line);
//---------------REDIRECTIONS--------------------
int		is_redirected(char *str);
void	prepare_redir(char *str, int redirection, int *fd, int id);
char	*str_without_redir(char *str);
char	*get_infile(char *str);
char	*get_outfile(char *str);
void	exec_redir(char *path, char **arg, int *fd, int id);
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