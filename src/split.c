#include "../include/philo.h"

int	ft_strlen(char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int word_counter(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		else
			i++;
	}
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*new_str;
	int		i;
	
	if (!str)
		return (NULL);
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);	
}

char	*ft_substr(char *str, int start, int len)
{
	char	*new_str;
	int		i;
	if (str[0] == '\0' || start > ft_strlen(str) || len == 0)
		return (ft_strdup(""));
	i = ft_strlen(str + start);
	if (i < len)
		len = i;
	i = 0;
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	while (i < len)
	{
		new_str[i] = str[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	temp_length(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char    **ft_split(char *str, char c)
{
	char    **new_array;
	char    *temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_array = malloc(word_counter(str, c) + 1);
	if (!new_array)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
		{
			temp = ft_substr((str + i), 0, temp_length(str + i, c));
			new_array[j] = ft_strdup(temp);
			i += temp_length((str + i), c);
			j++;
		}
		else
			i++;
	}
	new_array[j] = NULL;
	return (new_array);
}