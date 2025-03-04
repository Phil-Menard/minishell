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

typedef struct s_hist
{
	char			*last_dir;
	char			*last_cmd;
	struct s_hist	*next;
}	t_hist;

typedef struct s_tree
{
	char			*cmd;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

void	ft_execute(char *line, char **env, int *exit_code, t_hist **historic);
//---------------BUILTINS COMMANDS--------------------
void	ft_pwd(int *fd);
void	ft_env(char **env, int *fd);
void	ft_echo(char *str, int *fd);
void	ft_cd(char *str, t_hist **historic);
void	ft_exit(int *exit_code);
void	exec_cmds(char *str, int *fd);
void	builtins(char *line, char **env, int *exit_code, t_hist **historic);
//---------------UTILS FUNCTIONS--------------------
char	*ft_join_mid(char *s1, char slash, char *s2);
void	free_db_array(char **arr);
char	**fill_arg(char *path, char *argv);
char	*ft_straddstr(char *s1, char *s2);
int		ft_strfind(char *s1, char *s2);
char	*ft_straddchar(char *str, char c);
int		find_occurences(char *str, char c);
//---------------UTILS FUNCTIONS FOR FD--------------------
int		*set_fd(char *line, int *fd);
void	close_multiple_fd(int *fd);
int		get_opened_fd_output(int *fd);
//---------------HANDLE CMDS EXCEPT BUILTINS--------------------
void	ft_execve(char *path, char **arg);
char	*get_right_path(char *str);
char	*get_next_path(char *arr, char *str);
//---------------CHECK QUOTES WHEN NEW LINE--------------------
int		check_quote(char *str);
char	*get_lines(char *line);
//---------------HANDLE REDIRECTIONS--------------------
int		is_redirected(char *str);
void	prepare_redir(char *str, int redirection, int *fd);
char	*str_without_redir(char *str);
char	*get_infile(char *str);
char	*get_outfile(char *str);
void	exec_redir(char *path, char **arg, int *fd);
//---------------HISTORY CMDS (WORK IN PROGRESS)--------------------
t_hist	*ft_new_cmd(char *cmd);
void	ft_cmdadd_front(t_hist **lst, t_hist *new);
void	print_hist(t_hist *lst);
void	free_historic(t_hist *lst);

#endif