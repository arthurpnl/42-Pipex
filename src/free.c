#include "pipex.h"

void	free_pipes(t_pipex *pipex, int count)
{
	int	i;

	i = 0;
	while(i < count)
	{
		if (pipex->pipes)
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