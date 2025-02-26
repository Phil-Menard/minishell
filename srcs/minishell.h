#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

void	ft_pwd(void);
void	ft_env(char **env);
void	ft_echo(char *str);
void	ft_cd(char *str);
void	ft_exit(int *exit_code);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_middle(char const *s1, char slash, char const *s2);
char	*ft_strdup(const char *s);
void	free_db_array(char **arr);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);

#endif