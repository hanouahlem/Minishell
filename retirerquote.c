#include "minishell.h"
// "$USER'laisse"pasici'$PATH'rienderriere" vide '"quoteavant""""""""""""a
// ahbey'laissepasici$PATHrienderriere vide 'quoteavanta
char *retirerquote(char *str)
{
	char *new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	
	int i = 0;
	int n = 0;
	char c;
	while (str[i])
	{
		while (str[i] == SQUOTE || str[i] == DQUOTE)
		{
			c = str[i++];
			while (str[i] != c)
				new[n++] = str[i++];
			i++;
		}
		if (str[i])
			new[n++] = str[i++];
	}
	new[i] = '\0';
	return new;
}


