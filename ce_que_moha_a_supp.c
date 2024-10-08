#include "minishell.h"

// STR = $USER,moha,$TEST$SHLVL
// retour = ahbey,moha,1
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
int	ft_expand_len2(char *str, t_mini *data)
{
	int		i;
	int		n;
	char	*key;
	char	*value;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] && str[i] == '$')
		{
			i++;
			key = ft_get_key2(str, &i);
			value = ft_value_from_key(key, data);
			if (value)
				n += ft_strlen(value);
		}
		if (!str[i])
			break ;
		i++;
		n++;
	}
	return (n);
}

char	*ft_expand2(char *str, t_mini *data)
{
	int i = 0;
	int n = 0;
	char *new;
	char *key;
	char *value;

	new = ft_calloc(10000, 1);
	while (str[i])
	{
		while (str[i] && str[i] == SQUOTE)
		{
			printf("je suis [%c]{%i}\n", str[i], i);
			i++;
			while (str[i] && str[i] != SQUOTE)
			{
				new[n++] = str[i++];
			}
			i++;
		}

		if (!str[i])
			break ;
		while (str[i] && str[i] == DQUOTE)
		{
			i++;
			while (str[i] && str[i] != DQUOTE)
			{
				while (str[i] && str[i] == '$')
				{
					i++;
					key = ft_get_key2(str, &i);
					value = ft_value_from_key(key, data);
					if (value)
					{
						strcat(new, value);
						n += ft_strlen(value);
					}
				}
				new[n++] = str[i++];
			}
			i++;
		}
		if (!str[i])
			break ;
		while (str[i] && str[i] == '$')
		{
			i++;
			key = ft_get_key2(str, &i);
			value = ft_value_from_key(key, data);
			if (value)
			{
				strcat(new, value);
				n += ft_strlen(value);
			}
		}
		if (str[i])
			new[n++] = str[i++];
	}
	new[n] = '\0';
	return (new);
}