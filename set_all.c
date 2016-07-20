/*
** set_all.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:59:49 2016
** Last update Wed Jun  8 10:10:35 2016 
*/

#include <unistd.h>
#include "jobs.h"
#include "my.h"

int	have_var(char *str)
{
  int	index;

  index = 0;
  while (str && str[index])
    {
      if (str[index] == '$' && ((index == 0 || str[index - 1] != '\\')
				&&  str[index + 1]  != '('))
	return (index);
      index++;
    }
  return (-1);
}

int	pgid_alive(pid_t pgid, int pid)
{
  int	i;

  i = 0;
  while (i < g_background.max_job_count)
    {
      if (g_background.active_jobs[i]
	  && g_background.active_jobs[i]->pgid == pgid
	  && g_background.active_jobs[i]->pid != pid
	  && g_background.active_jobs[i]->status == RUNNING)
	return (i);
      i++;
    }
  return (-1);
}

int	set_redirections(t_process *proc)
{
  if (proc->outfd != FAILURE)
    {
      if (dup2(proc->outfd, 1) == -1)
	return (FAILURE);
      close(proc->outfd);
    }
  if (proc->infd != FAILURE)
    {
      if (dup2(proc->infd, 0) == -1)
	return (FAILURE);
      close(proc->infd);
    }
  if (proc->output && proc->output->is_pipe == SUCCESS && proc->next)
    {
      proc->next->pgid = proc->pgid;
      if (close(proc->next->infd) == -1)
	return (FAILURE);
    }
  return (SUCCESS);
}

void	set_all_signals(int nb)
{
  (void)nb;
  signal(SIGINT, SIG_DFL);
  signal(SIGTSTP, SIG_DFL);
  signal(SIGSTOP, SIG_DFL);
  signal(SIGQUIT, SIG_DFL);
  signal(SIGCHLD, SIG_DFL);
  signal(SIGTTIN, SIG_DFL);
  signal(SIGTTOU, SIG_DFL);
}

int	close_all(t_process *proc)
{
  if (proc->outfd > 0)
    {
      if (close(proc->outfd) == -1)
	return (FAILURE);
    }
  if (proc->infd > 0)
    {
      if (close(proc->infd) == -1)
	return (FAILURE);
    }
  return (SUCCESS);
}
