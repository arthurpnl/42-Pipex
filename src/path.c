#include "pipex.h"

void    get_cmd_path(t_pipex *pipex, char **envp)
{
    int     i;
    char    *path_line;

    i = 0;
    while(envp[i])
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_line = envp[i] + 5;
            pipex->path = ft_split(path_line, ':');
        }
        i++;
    }
}