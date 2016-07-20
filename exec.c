/*
** execute.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:59:29 2016
** Last update Wed Jun  8 09:33:35 2016 
*/

#include <unistd.h>
#include <stdlib.h>
#include "jobs.h"
#include "tools.h"
#include "builtins.h"
#include "my.h"

static int	exec_father(t_process *proc, t_mini *shell, pid_t cpid)
{
  proc->pid = cpid;
  if (proc->pgid == FAILURE)
    proc->pgid = proc->pid;
  if (proc->output && proc->output->is_pipe == SUCCESS && proc->next)
    proc->next->pgid = proc->pgid;
  if (close_all(proc) == FAILURE)
    return (FAILURE);
  if (isatty(0)
      && ((proc->mode == BACKGROUND)
	  || (proc->output && proc->output->is_pipe == SUCCESS)))
    return (put_to_background(proc_copy(proc), RUNNING));
  return (put_to_foreground(proc, shell->env));
}

static void	exec_son(t_process *proc, t_mini *shell)
{
  set_all_signals(0);
  proc->pid = getpid();
  if (proc->pgid == FAILURE)
    proc->pgid = proc->pid;
  if (set_redirections(proc) == FAILURE)
    exit(EXIT_FAILURE);
  if (isatty(0))
    setpgid(proc->pid, proc->pgid);
  if (proc->path_cmd)
    {
      if (shell->is_env_exec == SUCCESS)
	execve(proc->path_cmd, proc->cmd_argv, shell->env_exec);
      else
	execve(proc->path_cmd, proc->cmd_argv, shell->env);
      exit(EXIT_FAILURE);
    }
  else if (proc->is_builtin != -1)
    exit(builtins(shell, proc));
}

static int	real_execution(t_process *proc, t_mini *shell)
{
  pid_t		cpid;

  if (!(proc->outfd) && put_redirections(proc) == FAILURE)
    return (SUCCESS);
  if ((cpid = fork()) == 0)
    exec_son(proc, shell);
  else if (cpid > 0)
    return (exec_father(proc, shell, cpid));
  return (FAILURE);
}

int my_execute(t_process *proc, t_mini *shell)
{
  proc->status = 1;
  if (check_builtins(proc) == SUCCESS);
  else if (proc->cmd && (proc->cmd[0] == '.' || proc->cmd[0] == '/'))
    {
      if (direct_execute(proc) == FAILURE)
	return (FAILURE);
    }
  else if (proc->cmd && inpath_execute(proc, shell) == FAILURE)
    return (FAILURE);
  if (proc->path_cmd || OUT_IS_PIPE(proc)
      || (proc->is_builtin > MAX_BUILT_FORK && proc->is_builtin != MAX_BUILT))
    return (real_execution(proc, shell));
  else if ((proc->is_builtin <= MAX_BUILT_FORK || proc->is_builtin == MAX_BUILT)
	   && proc->is_builtin != -1)
    return (built_no_fork(proc, shell));
  return (FAILURE);
}
