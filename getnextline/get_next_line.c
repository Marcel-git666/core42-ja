/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakand <jakand@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:43:28 by jakand            #+#    #+#             */
/*   Updated: 2024/12/10 20:50:18 by jakand           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	line = ft_calloc((ft_strlen(buffer) - i), sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
	{
		line[j++] = buffer[i++];
	}
	line[j] = '\0';
	free(buffer);
	return (line);
}

char	*ft_take_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_get_line(int fd, char *buffer)
{
	char	*line;
	int		char_read;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	if (!buffer)
		return (NULL);
	line = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!line)
		return (NULL);
	char_read = 1;
	while (char_read > 0)
	{
		char_read = read(fd, line, BUFFER_SIZE);
		if (char_read == -1)
			return (free(line), free(buffer), NULL);
		line[char_read] = '\0';
		buffer = ft_free(buffer, line);
		if (!buffer)
			return (free(buffer), NULL);
		if (ft_strchr(line, '\n'))
			break ;
	}
	free(line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*read_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = ft_get_line(fd, buffer);
	if (!buffer)
		return (NULL);
	read_line = ft_take_line(buffer);
	// if (!read_line)
	// {
	// 	free(buffer);
	// 	buffer = NULL;
	// 	return (NULL);
	// }
	buffer = next_line(buffer);
	return (read_line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	i = -1;
// 	fd = open("file.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }

// void simulate_read_error(int fd)
// {
//     printf("Simulating read error...\n");
//     close(fd); // Force close the file descriptor
// }

// int main(void)
// {
//     int     fd;
//     char    *next_line;
//     int     count;

//     count = 0;

//     printf("Reading using BUFFER_SIZE: %d\n", BUFFER_SIZE);
//     // Open the test file (make sure read.txt exists and has content)
//     fd = open("file.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         printf("Error opening file\n");
//         return (1);
//     }

//     // Print each line read from the file
//     while (1)
//     {
//         next_line = get_next_line(fd);
//         if (next_line == NULL)
//             break;
//         count++;
//         printf("[%d]:%s\n", count, next_line); // Show line number and content
//         free(next_line);
//     }

//     // Test 1: Simulate read error after a few lines
//     simulate_read_error(fd);
//     next_line = get_next_line(fd);  // This should fail due to the forced read error
//     if (next_line == NULL)
//     {
//         printf("Read error handled correctly (NULL returned)\n");
//     }
//     else
//     {
//         printf("Error: Read error not handled correctly\n");
//         free(next_line);  // Clean up if somehow allocated
//     }

//     // Reopen the file and read again to test static buffer reset
//     fd = open("file.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         printf("Error reopening file\n");
//         return (1);
//     }

//     printf("\nRe-reading the file after resetting static buffer:\n");
//     count = 0;
//     while (1)
//     {
//         next_line = get_next_line(fd);
//         if (next_line == NULL)
//             break;
//         count++;
//         printf("[%d]:%s\n", count, next_line);
//         free(next_line);
//     }

//     // Close the file descriptor
//     close(fd);
//     printf("Read using BUFFER_SIZE: %d\n", BUFFER_SIZE);
//     // If using valgrind, you can include this line to trigger memory checking
//     // system("valgrind --leak-check=full ./a.out");  // Uncomment if running valgrind

//     return (0);
// }
