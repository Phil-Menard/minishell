#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

void	ft_pwd(void);
void	ft_env(char **env);
void	ft_echo(char *str);
void	ft_cd(char *str);
void	ft_exit(int *exit_code);
char	*ft_strjoin_middle(char const *s1, char slash, char const *s2);
void	free_db_array(char **arr);

#endif