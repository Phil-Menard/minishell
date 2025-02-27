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

void	ft_pwd(void);
void	ft_env(char **env);
void	ft_echo(char *str);
void	ft_cd(char *str);
void	ft_exit(int *exit_code);
char	*ft_strjoin_middle(char const *s1, char slash, char const *s2);
void	free_db_array(char **arr);
void	exec_cmds(char *str);
int		is_redirected(char *str);
void	prepare_redir(char *str);
void	ft_execve(char *path, char **arg);
char	*get_right_path(char *str);
char	*get_next_path(char *arr, char *str);
char	**fill_arg(char *path, char *argv);
char	*ft_stradd(char *s1, char *s2);
char	*ft_add_end_space(char *str);
int		check_quote(char *str);
char	*get_lines(char *line);

#endif