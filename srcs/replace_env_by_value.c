#include "../include/minishell.h"

int get_var_name_len(char *str, int i)
{
	int len;

	len = 0;
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
		len++;
	}
	return (len);
}


char *replace_env_by_value(char *str, t_list *env)
{
	int i;
	int var_len;
	char *new;
	char *var_name;
	int malloc_size;
	char *var_value;

	i = -1;
	malloc_size = -1;
	while (str[++i] != '\0')
	{
		malloc_size++;
		if (str[i] == '$')
		{
			var_len = get_var_name_len(str, i);
			var_name = ft_substr(str, i, var_len);
			var_value = var_value(env, var_name);
			malloc_size += ft_strlen(var_value);
		}
	}
}