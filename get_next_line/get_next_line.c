/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:45:36 by agruet            #+#    #+#             */
/*   Updated: 2025/02/06 11:33:55 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char c)
{
	char	*str;
	int		i;

	str = malloc(ft_strlen(s1) + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = c;
	str[i] = 0;
	free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	char	buffer;
	char	*result;
	int		r_val;
	int		i;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	r_val = read(fd, &buffer, 1);
	if (r_val <= 0)
		return (NULL);
	result = malloc(2);
	if (!result)
		return (NULL);
	result[0] = buffer;
	result[1] = 0;
	i = 0;
	while (result && result[i] != '\n')
	{
		r_val = read(fd, &buffer, 1);
		if (r_val < 0)
			return (NULL);
		if (r_val == 0)
			break ;
		i++;
		result = ft_strjoin(result, buffer);
	}
	return (result);
}

/* #include <fcntl.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int		fd;
	char	*gnl;

	if (ac <= 1)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	// gnl = get_next_line(fd);
	// while (gnl)
	// {
	// 	printf("%s", gnl);
	// 	free(gnl);
	// 	gnl = get_next_line(fd);
	// }
	gnl = get_next_line(fd);
	printf("%s", gnl);
	free(gnl);
	gnl = get_next_line(fd);
	printf("%s", gnl);
	free(gnl);
	close(fd);
	return (0);
} */
