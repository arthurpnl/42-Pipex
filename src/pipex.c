#include "pipex.h"

int launch_all_process(t_pipex *pipex, char **envp)
{
    int i;
    pid_t   pid;

    i = 0;
    while (i < pipex->cmd_count)
    {
        pid = fork();
        if (pid < 0)
        {
            ft_putstr_fd("Fork error\n", 2);
            return (FAILURE);
        }
        else if (pid == 0)
        {
            handle_redirect(pipex, i);
            exec_cmd(pipex, i, envp);
            exit(EXIT_FAILURE);
        }

        i++;
    }
    for (int i = 0; i < pipex->cmd_count - 1; i++)
    {
        close(pipex->pipes[i][0]);
        close(pipex->pipes[i][1]);
    }
    while (wait(NULL) > 0 )
        ;
    return SUCCESS;
}