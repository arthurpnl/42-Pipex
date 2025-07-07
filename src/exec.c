#include "pipex.h"

int exec_cmd(t_pipex *pipex, int i, char **envp)
{
    char    *cmd_path; 
    char    *full_path;
    char    *cmd;
    int     j;

    j = 0;
    cmd = pipex->cmd_args[i][0];
    while(pipex->path && pipex->path[j])
    {
        full_path = ft_strjoin(pipex->path[j], "/");
        cmd_path = ft_strjoin(full_path, cmd);
        free(full_path);

        if (access(cmd_path, X_OK) == 0)
        {
            execve(cmd_path, pipex->cmd_args[i], envp);
            perror("Execve failed.\n");
            free(cmd_path);
            exit(EXIT_FAILURE);
        }
        free(cmd_path);
        j++;
    }
    ft_putstr_fd("Command not found\n", 2);
    exit(EXIT_FAILURE);
}