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

typedef struct s_tree
{
	char			*cmd;
	char			*option;
	char			*arg;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

void	ft_pwd(void);
void	ft_env(char **env);
void	ft_echo(char *str);
void	ft_cd(char *str);
void	ft_exit(int *exit_code);
char	*ft_strjoin_middle(char const *s1, char slash, char const *s2);
void	free_db_array(char **arr);
void	exec_cmds(char *str);
int		is_redirected(char *str);
void	prepare_redir(char *str, int redirection);
void	ft_execve(char *path, char **arg);
char	*get_right_path(char *str);
char	*get_next_path(char *arr, char *str);
char	**fill_arg(char *path, char *argv);
char	*ft_stradd(char *s1, char *s2);
char	*ft_add_end_space(char *str);
int		find_occurences(char *str, char c);
int		check_quote(char *str);
char	*get_lines(char *line);
char	*get_infile(char *str);
char	*get_outfile(char *str);
void	redir_input(char *str, int *pipefd, char *path, char **arg);
void	redir_output(char *str, int *pipefd, char *path, char **arg);
void	redir_in_and_out(char *str, int *pipefd, char *path, char **arg);
void	redir_output_append(char *str, int *pipefd, char *path, char **arg);

#endif