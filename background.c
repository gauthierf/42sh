/*
** background.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:59:57 2016
** Last update Wed Jun  8 10:55:08 2016 
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "jobs.h"
#include "my.h"

void	report_signal(t_process *proc, int status, int mode, int job_id)
{
  if (WIFSIGNALED(status) || WIFSTOPPED(status))
    print_sig_msg(proc, status, job_id);
  else if (WIFEXITED(status) && mode && !OUT_IS_PIPE(proc))
    my_printf("[%d]	%d done	%s\n", job_id, (int)proc->pid, proc->cmd);
  else if (WIFEXITED(status))
    proc->status = WEXITSTATUS(status);
}

void	check_jobs(int signum)
{
  int	pid;
  int	status;

  (void)signum;
  while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
      if (WIFSTOPPED(status))
	report_stop(pid, status);
      else if (WIFSIGNALED(status) || WIFEXITED(status))
	report_termination(pid, status);
      else if (WIFCONTINUED(status))
	report_continuation(pid, status);
    }
}

int	wait_for_pgid(pid_t pgid)
{
  int	pid;
  int	status;

  if (!isatty(0))
    pgid = 1;
  while ((pid = waitpid(- (pgid), &status, WUNTRACED)) > 0)
    {
      if (WIFSTOPPED(status))
	report_stop(pid, status);
      else if (WIFSIGNALED(status) || WIFEXITED(status))
	report_termination(pid, status);
      else if (WIFCONTINUED(status))
	report_continuation(pid, status);
      if (!g_background.frontjob)
	return (SUCCESS);
    }
  return (SUCCESS);
}

int	put_to_foreground(t_process *proc, char **env)
{
  int	job_id;

  (void)env;
  g_background.frontjob = proc;
  close_all(proc);
  if ((job_id = is_in_jobs_list(proc->pid)) != -1)
    remove_job(proc->pid);
  if (isatty(0) && ((getpgid(proc->pid) != proc->pgid
		     && setpgid(proc->pid, proc->pgid) == -1)
		    || tcsetpgrp(0, proc->pgid) == -1))
    return (FAILURE);
  else if (proc->status == STOPPED && kill(- (proc->pgid), SIGCONT) == -1)
    return (FAILURE);
  (void)(job_id);
  return (wait_for_pgid(proc->pgid));
}

int	put_to_background(t_process *proc, int status)
{
  int	job_id;

  if (!proc)
    return (FAILURE);
  if (isatty(0) && getpgid(proc->pid) != proc->pgid
      && (setpgid(proc->pid, proc->pgid) == -1))
    return (FAILURE);
  else if (isatty(0) && OUT_IS_PIPE(proc) && tcgetpgrp(0) != proc->pgid
	   && tcsetpgrp(0, proc->pgid) == -1)
    return (FAILURE);
  else if (isatty(0) && proc->mode == BACKGROUND && tcgetpgrp(0) != getpgrp()
	   && (tcsetpgrp(0, getpgrp()) == -1))
    return (FAILURE);
  if ((job_id = is_in_jobs_list(proc->pid) == -1))
    {
      if (!OUT_IS_PIPE(proc))
	my_printf("[%d] %d\n", g_background.active_jobs_count, proc->pid);
      job_id = add_job(proc);
      proc->status = status;
    }
  else if (g_background.active_jobs[job_id]->status == STOPPED
	   && kill(- (g_background.active_jobs[job_id]->pgid), SIGCONT) == -1)
    return (FAILURE);
  return (SUCCESS);
}
