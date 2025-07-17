#include "pipex.h"

int launch_all_process(t_pipex *pipex, char **envp, int here_doc_fd[2])
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
        	if (pipex->is_heredoc)
        		handle_heredoc_redirect(pipex, i, here_doc_fd);
        	else
            	handle_redirect(pipex, i);
            exec_cmd(pipex, i, envp);
            exit(EXIT_FAILURE);
        }
        i++;
    }
	close_all_pipes(pipex, here_doc_fd);
    while (wait(NULL) > 0 )
        ;
    return SUCCESS;
}