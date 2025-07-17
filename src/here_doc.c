#include "pipex.h"

int	is_it_delimiter(char *line, char *delimiter)
{
	size_t	delimiter_len;

	if (!line)
		return (0);
	delimiter_len = ft_strlen(delimiter);
	if (ft_strncmp(line, delimiter, delimiter_len) == 0)
	{
	if (line[delimiter_len] == '\n' || line[delimiter_len] == '\0')
		return (1);
	}
	return (0);
}


void	handle_here_doc(char *delimiter, int pipe_fd[2])
{
	char	*line;

	if (pipe(pipe_fd) < 0)
	{
		ft_putstr_fd("Pipe creation failed for here_doc", 2);
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		ft_putstr_fd("heredoc>", 1);
		line = get_next_line(STDIN_FILENO);
    if (is_it_delimiter(line, delimiter) == 1)
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
}

