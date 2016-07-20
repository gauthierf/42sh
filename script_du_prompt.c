/*
** prompt_script.c for  in /home/fernan_w/Téléchargements/backup/start
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:03:47 2016
** Last update Wed Jun  8 10:00:29 2016 
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#include "tools.h"
#include "my.h"

char	*get_plug_ret(int fd)
{
  int	red;
  char	buff[255];
  char	*tmp;
  char	*res;

  res = NULL;
  while ((red = read(fd, buff, 255 - 1)) > 0)
    {
      tmp = res;
      if (buff[red - 1] == '\n')
	--red;
      if (red < 0)
	{
	  close(fd);
	  return (NULL);
	}
      if (red)
	buff[red] = '\0';
      res = my_append(res, buff);
      if (tmp != res && tmp)
	free(tmp);
    }
  close(fd);
  return (res);
}

static void	son_plug_exec(int mypipe[2], char *prog, char **env)
{
  int		cpid;

  close(mypipe[0]);
  if (dup2(mypipe[1], 1) == -1)
    exit(EXIT_FAILURE);
  close(mypipe[1]);
  cpid = getpid();
  if (isatty(0) && (setpgid(cpid, cpid) == -1
		    || signal(SIGINT, SIG_DFL) == SIG_ERR
		    || tcsetpgrp(0, cpid) == -1))
    exit(EXIT_FAILURE);
  execve(prog, (char *[]) {prog, NULL}, env);
  exit(EXIT_FAILURE);
}

static char	*execute_plugin(char *prog, char **env)
{
  int		mypipe[2];
  int		cpid;

  if (pipe(mypipe) == -1)
    return (NULL);
  if ((cpid = fork()))
    {
      if (isatty(0) && (setpgid(cpid, cpid) == -1
			|| tcsetpgrp(0, cpid) == -1))
	return (NULL);
      close(mypipe[1]);
      waitpid(cpid, 0, WUNTRACED);
    }
  else if (!cpid)
    son_plug_exec(mypipe, prog, env);
  return (get_plug_ret(mypipe[0]));
}

static char	*plugin_path(char *plugin)
{
  char		*tmp;
  char		*ret;
  static char	*sourcedir;

  if (!(sourcedir))
    sourcedir = getcwd(NULL, 0);
  tmp = my_append(sourcedir, "/plugins/");
  ret = my_append(tmp, plugin);
  free(tmp);
  return (ret);
}

char		*prompt_script(char *str, t_mini *shell)
{
  char		*tmp;
  char		*ret;
  static int	i;

  (void)str;
  if (!(shell->prompt_plugins))
    return (NULL);
  else if ((!shell->prompt_plugins[i]))
    i = 0;
  if (shell->prompt_plugins && shell->prompt_plugins[i])
    {
      if (access((tmp = plugin_path(shell->prompt_plugins[i++])), X_OK) != 0)
	return (NULL);
      ret = execute_plugin(tmp, shell->env);
      if (isatty(0) && tcsetpgrp(0, getpid()) == -1)
	return (NULL);
      free(tmp);
      return (ret);
    }
  return (NULL);
}
