#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    if (parser(&pipex, argc, argv) == FAILURE)
        return (1);
    get_cmd_path(&pipex, envp);
    if (setup_pipe(&pipex) == FAILURE)
        return (1);
    if (launch_all_process(&pipex, envp) == FAILURE)
        return (1);
    return (0);

}