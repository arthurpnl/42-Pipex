#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;
	int	here_doc_fd[2] = {-1, -1};

    if (parser(&pipex, argc, argv) == FAILURE)
    {
        cleanup(&pipex);
        return (1);
    }
    if (pipex.is_heredoc == 1)
    	handle_here_doc(argv[2], here_doc_fd);
    get_cmd_path(&pipex, envp);
    if (setup_pipe(&pipex) == FAILURE)
    {
        cleanup(&pipex);
        return (1);
    }
    if (launch_all_process(&pipex, envp, here_doc_fd) == FAILURE)
    {
        cleanup(&pipex);
        return (1);
    }
    cleanup(&pipex);
    return (0);
}
