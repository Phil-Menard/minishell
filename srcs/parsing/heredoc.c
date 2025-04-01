#include "../minishell.h"

// cat <<1  << 2 << 3 < Makefile << 4 < out << 5 > 6 << 7
// 123457
static char	**getdel(char *line)
{
	char	**split;
	char	**tmp;
	size_t	i;

	split = ft_split(line, "<<");
	if (!split)
		return (NULL);
	i = -1;
	while (split[++i])
	{
		tmp = ft_split(split[i], " ");
		if (!tmp)
			return (NULL);
		free(split[i]);
		split[i] = ft_strdup(tmp[0]);
		if (!split[i])
			return (NULL);
		free_db_array(tmp);
	}
	return (split);
}

void	heredoc(char *line)
{
	res = NULL
	del = \n1\n2\n3\n
	> cat << 1 << 2 << 3
	>pipi
	>caca
	>1
	>2
	>1
	>3
	del = straddstr(split) = "\n1\n2\n3\n4\n5\n7\n";
	while (ft_strfind(res, del) == 0)
	{
		readline();
		res = straddstr(res, readline);
	}
	cut(res, del)
}

/*
res = NULL;
while (split[i])
{
	line = readline();
	if (ft_strlen(line) == ft_strlen(split[i]))
	{
		if (ft_strncmp(line, split[i], ft_strlen(line) == 0))
			FOUND
	}
	i++;
}
*/