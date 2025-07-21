#include "pipex.h"

void	free_pipes(t_pipex *pipex, int count)
{
	int	i;

	i = 0;
	while(i < count)
	{
		if (pipex->pipes[i])
			free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
	pipex->pipes = NULL;
}

void	free_args(t_pipex *pipex, int count)
{
	int	i;
	int j;

	i = 0;
	while(i < count)
	{
		j = 0;
		if (pipex->cmd_args[i])
		{
			while (pipex->cmd_args[i][j])
			{
				free(pipex->cmd_args[i][j]);
				j++;
			}
			free(pipex->cmd_args[i]);
		}
		i++;
	}
	free(pipex->cmd_args);
	pipex->cmd_args = NULL;
}

void	free_split(t_pipex *pipex)
{
	int	i;

	i = 0;
	while(pipex->path[i])
	{
		free(pipex->path[i]);
		i++;
	}
	free(pipex->path);
	pipex->path = NULL;
}

void cleanup(t_pipex *pipex)
{
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->pipes)
		free_pipes(pipex, pipex->cmd_count - 1);
	if (pipex->cmd_args)
		free_args(pipex, pipex->cmd_count);
	if (pipex->path)
		free_split(pipex);
}