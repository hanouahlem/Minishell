#include "minishell.h"

// STR = $USER,moha,$TEST$SHLVL
// retour = ahbey,moha,1

char	*ft_value_from_key(char *str, t_mini *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
		{
			printf("str = %s  value = %s\n", str, tmp->value);
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_get_key2(char *str, int *i)
{
	int		j;
	char	*c;

	j = 0;
	c = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_')
		&& !ft_isdigit(str[1]))
	{
		c[j++] = str[(*i)++];
	}
	c[j] = '\0';
	return (c);
}
