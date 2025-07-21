#include "pipex.h"

int setup_pipe(t_pipex *pipex)
{
    int i;

    i = 0;
    pipex->pipes = malloc(sizeof(int *) * (pipex->cmd_count - 1));
    if (!pipex->pipes)
    {
        ft_putstr_fd(MALLOC_FAILED, 2);
        return (FAILURE);
    }
    while(i < pipex->cmd_count - 1)
    {
        pipex->pipes[i] = malloc(sizeof(int) * 2);
        if (!pipex->pipes[i])
        {
            ft_putstr_fd(MALLOC_FAILED, 2);
			free_pipes(pipex, i);
            return (FAILURE);
        }
        if (pipe(pipex->pipes[i]) == -1)
        {
            ft_putstr_fd("Pipe creation failed.\n", 2);
            free_pipes(pipex, i);
            return (FAILURE);
        }
        i++;
    }
        return (SUCCESS);
}


// 1 ecriture
// 0 lecture
void handle_redirect(t_pipex *pipex, int i)
{
    if (i == 0)
    {
        dup2(pipex->infile, STDIN_FILENO);
        dup2(pipex->pipes[0][1], STDOUT_FILENO);
    }
    else if (i < pipex->cmd_count - 1)
    {
        dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
        dup2(pipex->pipes[i][1], STDOUT_FILENO);
    }
    else
    {
        dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
        dup2(pipex->outfile, STDOUT_FILENO);
    }
	close_all_pipes(pipex, NULL);
}

int	handle_heredoc_redirect(t_pipex *pipex, int i, int here_doc_fd[2])
{
	if (i == 0)
	{
		dup2(here_doc_fd[0], STDIN_FILENO);
		dup2(pipex->pipes[0][1], STDOUT_FILENO);
	}
	else if (i < pipex->cmd_count - 1)
	{
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
		dup2(pipex->pipes[i][1], STDOUT_FILENO);
	}
	else
	{
		dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
	}
	close_all_pipes(pipex, here_doc_fd);
	return(SUCCESS);
}