#include "pipex.h"

void close_all_pipes(t_pipex *pipex, int here_doc_fd[2])
{
	int	i;

	i = 0;
	while(i < pipex->cmd_count - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
	if (pipex->is_heredoc)
	{
		if(here_doc_fd[0] > 0)
			close(here_doc_fd[0]);
		if(here_doc_fd[1] > 0)
			close(here_doc_fd[1]);
	}
	else if (pipex->infile > 0)
		close(pipex->infile);
	if (pipex->outfile > 0)
		close(pipex->outfile);
}