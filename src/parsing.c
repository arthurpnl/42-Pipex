#include "pipex.h"

int	parser(t_pipex *pipex, int argc, char **argv)
{
	if (validate_args(pipex, argc, argv) == FAILURE)
		return (FAILURE);
	if (open_files(pipex, argc, argv) == FAILURE)
		return (FAILURE);
	if (parse_commands(pipex, argc, argv) == FAILURE)
		return (FAILURE);
	return (SUCCESS); 
}
int	validate_args(t_pipex *pipex, int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putstr_fd("Not enough args\n", 2);
		return (FAILURE);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			ft_putstr_fd("here_doc requires at leats 6 args\n", 2);
			return (FAILURE);
		}
		pipex->is_heredoc = 1;
	}
	else
		pipex->is_heredoc = 0;
	return (SUCCESS);
}


int	open_files(t_pipex *pipex, int argc, char **argv)
{
	if (pipex->is_heredoc)
	{
		pipex->infile = -1;
		pipex->outfile = open (argv[argc -1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (pipex->outfile == -1 || (pipex->infile == -1 && !pipex->is_heredoc))
	{
		ft_putstr_fd(FILE_ERROR, 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
	
int	parse_commands(t_pipex *pipex, int argc, char **argv)
{
	int	start;
	int	i;

	start = 2;
	if (pipex->is_heredoc)
		start = 3;
	pipex->cmd_count = argc - start - 1;
	pipex->cmd_args = malloc(sizeof(char **) * pipex->cmd_count);
	if (!pipex->cmd_args)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (FAILURE);
	}
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmd_args[i] = ft_split(argv[start + i], ' ');
		if (!pipex->cmd_args[i])
		{
			ft_putstr_fd("Split failed\n", 2);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

