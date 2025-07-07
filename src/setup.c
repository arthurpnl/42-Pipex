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
            return (FAILURE);
        }
        if (pipe(pipex->pipes[i]) == -1)
        {
            ft_putstr_fd("Pipe creation failed.\n", 2);
            return (FAILURE);
        }
        i++;
    }
        return (SUCCESS);
}

int handle_redirect(t_pipex *pipex, int i)
{
    int j;

    j = 0;
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
    while (j < pipex->cmd_count - 1)
    {
        close(pipex->pipes[j][0]);
        close(pipex->pipes[j][1]);
        j++;
    }
    close(pipex->infile);
    close(pipex->outfile);
    return (SUCCESS);
}