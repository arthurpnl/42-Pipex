#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
# include "../Libft/includes/ft_printf.h"
# include "../Libft/includes/get_next_line.h"
# include "../Libft/includes/libft.h"

# define SUCCESS 0
# define FAILURE 1
# define FILE_ERROR "Couldn't open the file\n"
# define MALLOC_FAILED "Allocation memory failed\n"

typedef struct s_pipex
{
    int     infile;
    int     outfile;
    int     cmd_count;
    int     is_heredoc;
    int     **pipes;
    char    **path;
    char    ***cmd_args; 
}   t_pipex;

// parsing.c 
int	parser(t_pipex *pipex, int argc, char **argv);
int	validate_args(t_pipex *pipex, int argc, char **argv);
int	open_files(t_pipex *pipex, int argc, char **argv);
int	parse_commands(t_pipex *pipex, int argc, char **argv);

// setup 
int setup_pipe(t_pipex *pipex);
int handle_redirect(t_pipex *pipex, int i);

// exec
int exec_cmd(t_pipex *pipex, int i, char **envp);

// path
void    get_cmd_path(t_pipex *pipex, char **envp);

// pipex
int launch_all_process(t_pipex *pipex, char **envp);

#endif