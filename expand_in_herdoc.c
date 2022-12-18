/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_herdoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:00:35 by kadjane           #+#    #+#             */
/*   Updated: 2022/12/18 14:52:46 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*expand_digit_herdoc_2(char *string_join, char **string_inp)
{
	char	*found;
	char	*found_digit;

	found = NULL;
	found_digit = NULL;
	*string_inp = *(string_inp + 2);
	while (ft_isdigit(**string_inp))
	{
		found_digit = ft_strjoin(found_digit, &(**string_inp));
		(*string_inp)++;
	}
	found = ft_strjoin(string_join, found_digit);
	ft_free(&found_digit);
	return (found);
}

char	*expand_digit_herdoc(char *string_join,
	char **string_inp, t_data **data)
{
	char	*ptr;

	ptr = *string_inp + 1;
	if (ft_isdigit(*ptr))
	{
		(*data)->sign_exp_digit = 1;
		return (expand_digit_herdoc_2(string_join, string_inp));
	}
	if (*ptr == '$')
	{
		*string_inp = *string_inp + 2;
		return (ft_strjoin(string_join, "$$"));
	}
	return (NULL);
}

int	ft_expand_herdoc_3(char **string_inp, char **str, char **ptr, char **env)
{
	int	i;

	i = 1;
	*str = *env;
	*ptr = *string_inp + 1;
	while (**ptr && **ptr == **str && **str != '=')
	{
		(*ptr)++;
		(*str)++;
		i++;
	}
	return (i);
}

char	*ft_expand_herdoc_2(char *string_join, char **string_inp)
{
	char	*ptr;
	char	*str;
	char	**env;
	int		i;

	env = g_state.env;
	while (env && *env)
	{
		i = ft_expand_herdoc_3(string_inp, &str, &ptr, env);
		if (*str == '=' && !ft_isalnum(*ptr))
		{
			str++;
			while (i--)
				(*string_inp)++;
			return (ft_strjoin(string_join, str));
			break ;
		}
		env++;
	}
	return (NULL);
}

char	*ft_expand_herdoc(char *string_join, char **string_inp, t_data **data)
{
	char	*found;

	found = NULL;
	if (*string_inp && (*string_inp) + 1
		&& (ft_isalnum(*(*string_inp + 1)) || **string_inp == '$'))
	{
		found = expand_digit_herdoc(string_join, string_inp, data);
		if (found)
			return (found);
		else
			return (ft_expand_herdoc_2(string_join, string_inp));
	}
	else
	{
		(*string_inp)++;
		return (ft_strjoin(string_join, "$"));
	}
}
