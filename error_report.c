/*
** report.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:01:48 2016
** Last update Wed Jun  8 09:23:25 2016 
*/

#include <unistd.h>
#include <stdlib.h>
#include "jobs.h"
#include "my.h"

static const t_dentifrice	g_dentifrice[] =
  {
    {SIGHUP, "hangup"},
    {SIGINT, "interrupted"},
    {SIGQUIT, "quit"},
    {SIGABRT, "abort"},
    {SIGFPE, "floating point exception"},
    {SIGSEGV, "segmentation fault"},
    {SIGPIPE, "broken pipe"},
    {SIGALRM, "alarm"},
    {SIGTERM, "terminated"},
    {SIGUSR1, "user defined signal 1"},
    {SIGUSR2, "user defined signal 2"},
    {SIGCONT, "continued"},
    {SIGSTOP, "stopped"},
    {SIGTSTP, "stopped at terminal"},
    {SIGTTIN, "tty input"},
    {SIGTTOU, "tty output"},
    {FAILURE, NULL}
  };

void	print_sig_msg(t_process *proc, int status, int job_id)
{
  int	i;

  i = 0;
  if (WIFSIGNALED(status))
    {
      i = 0;
      while (g_dentifrice[i].signal_num != FAILURE
	     && g_dentifrice[i].signal_num != WTERMSIG(status))
	i++;
      if (g_dentifrice[i].signal_num != FAILURE)
	my_printf("[%d]	%d	%s %s %s\n", job_id, (int)proc->pid,
		  g_dentifrice[i].msg, SHCOREDUMP(status),proc->cmd);
    }
  else if (WIFSTOPPED(status))
    {
      i = 0;
      while (g_dentifrice[i].signal_num != FAILURE
	     && g_dentifrice[i].signal_num != WSTOPSIG(status))
	i++;
      if (g_dentifrice[i].signal_num != FAILURE)
	my_printf("[%d]	%d %s	%s\n", job_id,
		  (int)proc->pid, g_dentifrice[i].msg, proc->cmd);
    }
}

static void	report_termination_end(int status, int job_id)
{
  t_process	*tmp;

  tmp = g_background.active_jobs[job_id];
  report_signal(g_background.active_jobs[job_id], status, 1, job_id);
  close_all(g_background.active_jobs[job_id]);
  remove_job(tmp->pid);
  free_proc(tmp);
  free(tmp);
}

void		report_termination(pid_t pid, int status)
{
  int		pgid;
  int		job_id;
  t_process	*tmp;

  if ((job_id = is_in_jobs_list(pid)) == -1 && g_background.frontjob
      && pid == g_background.frontjob->pid)
    {
      close_all(g_background.frontjob);
      report_signal(g_background.frontjob, status, 0, 0);
      tmp = g_background.frontjob;
      pgid = tmp->pgid;
      g_background.frontjob = NULL;
      if ((job_id = pgid_alive(pgid, pid)) != -1)
	{
 	  free_proc(tmp);
	  free(tmp);
	  tmp = g_background.active_jobs[job_id];
	  g_background.frontjob = proc_copy(g_background.active_jobs[job_id]);
	  remove_job(g_background.active_jobs[job_id]->pid);
	  free_proc(tmp);
	  free(tmp);
	}
    }
  else if (job_id != -1)
    report_termination_end(status, job_id);
}

void	report_continuation(pid_t pid, int status)
{
  int	job_id;

  (void)status;
  if ((job_id = is_in_jobs_list(pid)) != -1)
    {
      if (g_background.active_jobs[job_id]->mode != BACKGROUND)
	tcsetpgrp(0, g_background.active_jobs[job_id]->pgid);
      g_background.active_jobs[job_id]->status = RUNNING;
      my_printf("[%d]	%d continued	%s\n", job_id,
		(int)g_background.active_jobs[job_id]->pid,
		g_background.active_jobs[job_id]->cmd);
    }
}

void	report_stop(pid_t pid, int status)
{
  pid_t	pgid;
  int	job_id;

  if ((job_id = is_in_jobs_list(pid)) == -1)
    {
      put_to_background(proc_copy(g_background.frontjob), STOPPED);
      report_signal(g_background.frontjob, status, 0, 0);
      pgid = g_background.frontjob->pgid;
      g_background.frontjob = NULL;
      if ((job_id = pgid_alive(pgid, pid)) != -1)
	{
	  g_background.frontjob = proc_copy(g_background.active_jobs[job_id]);
	  remove_job(g_background.active_jobs[job_id]->pid);
	}
    }
  else
    {
      g_background.active_jobs[job_id]->status = STOPPED;
      report_signal(g_background.active_jobs[job_id], status, 0, job_id);
    }
}
