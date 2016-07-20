/*
** redirections.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:59:38 2016
** Last update Wed Jun  8 10:10:05 2016 
*/

#include <unistd.h>
#include <fcntl.h>
#include "tools.h"
#include "shell.h"
#include "my.h"

static int	open_pipe(t_process *proc)
{
  int		mypipe[2];

  if (proc->next && proc->next->input)
    {
      if (pipe(mypipe) == -1)
	return (FAILURE);
      proc->outfd = mypipe[1];
      proc->next->infd = mypipe[0];
    }
  else
    return (FAILURE);
  return (SUCCESS);
}

static int	get_output(t_process *proc)
{
  int		fd;

  if (proc->output->file)
    {
      if ((fd = open(proc->output->file,
		     OP_MODE(proc->output->append_or_not), RIGHTS)) == -1)
	{
	  my_print_error("%s: no such file\n", proc->output->file);
	  return (FAILURE);
	}
      proc->outfd = fd;
    }
  else if (proc->output->is_pipe == SUCCESS && open_pipe(proc) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

static int	input_loop(t_input *tmp, int mypipe[2])
{
  while (tmp)
    {
      if (tmp->file)
	{
	  if (append_file_to_fd(tmp->file, mypipe[1]) == FAILURE)
	    {
	      my_print_error("42sh: %s: no such file or directory\n",
			     tmp->file);
	      return (FAILURE);
	    }
	}
      else if (tmp->heredoc)
	{
	  if (write(mypipe[1], tmp->heredoc, my_strlen(tmp->heredoc)) == -1)
	    return (FAILURE);
	}
      tmp = tmp->next;
    }
  return (SUCCESS);
}

static int	get_input(t_process *proc)
{
  int		mypipe[2];
  t_input	*tmp;

  if (pipe(mypipe) == -1)
    return (FAILURE);
  tmp = proc->input;
  input_loop(tmp, mypipe);
  proc->infd = mypipe[0];
  if (close(mypipe[1]) == -1)
    return (FAILURE);
  return (SUCCESS);
}

int	put_redirections(t_process *proc)
{
  if (proc->input && proc->input->is_pipe == FAILURE
      && get_input(proc) == FAILURE)
    return (FAILURE);
  else if (proc->output && get_output(proc) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}
