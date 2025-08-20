/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenasurovtseva <elenasurovtseva@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:18:15 by elenasurovt       #+#    #+#             */
/*   Updated: 2025/08/21 01:36:50 by elenasurovt      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_printf.h"

int	ft_printf(const char *string, ...)
{
	int		length;
	va_list	args;

	length = 0;
	va_start(args, string);
	while (*string)
	{
		if (*string == '%')
		{
			string++;
			if (*string == 'c')
				ft_putcharacter_length(va_arg(args, int), &length);
			else if (*string == 's')
				ft_string(va_arg(args, char *), &length);
			else if (*string == 'd' || *string == 'i')
				ft_number(va_arg(args, int), &length);
			else if (*string == 'u')
				ft_unsigned_int(va_arg(args, unsigned int), &length);
			else if (*string == 'x' || *string == 'X')
				ft_hexadecimal(va_arg(args, unsigned int), &length, *string);
			else if (*string == 'p')
				ft_pointer(va_arg(args, size_t), &length);
			else if (*string == '%')
				ft_putcharacter_length('%', &length);
		}
		else
			ft_putcharacter_length(*string, &length);
		string++;
	}
	va_end(args);
	return (length);
}
