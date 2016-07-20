/*
** wd_tools.c for  in /home/fernan_w/Téléchargements/backup/start
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:03:25 2016
** Last update Wed Jun  8 10:01:30 2016 
*/

#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"
#include "tools.h"
#include "my.h"

static int	count_dirs(char *wd)
{
  int		i;
  int		dirs;

  i = 0;
  dirs = 0;
  while (wd && wd[i])
    {
      if (wd[i++] == '/')
	dirs++;
    }
  return (dirs);
}

static void	need_free_or_not(char *wd, int i, char *tmp)
{
  if (wd[i] == '/')
      free(tmp);
  return ;
}

static char	*prompt_simple_wd(char *wd, char *tmp, char *tmp2)
{
  int		i;
  int		in_home;
  int		dirs;
  char		*short_wd;

  i = 0;
  in_home = FAILURE;
  if ((dirs = count_dirs(wd)) <= 1 || !(tmp2 = get_homedir()))
    return (wd);
  while (wd && wd[i] && dirs > 0)
    {
      if (wd[i] == '/' && my_strcmp(tmp = my_str_copy(wd, i), tmp2))
	in_home = SUCCESS;
      need_free_or_not(wd, i, tmp);
      if (wd[i++] == '/')
	dirs--;
    }
  if (in_home == SUCCESS)
    short_wd = my_append("~/", wd + i);
  else
    short_wd = my_append("/", wd + i);
  return (short_wd);
}

char	*prompt_mini_wd(char *ignore_this, t_mini *shell)
{
  char	*tmp1;
  char	*tmp2;
  char	*tmp3;
  char	*wd;
  char	*ret;

  (void)ignore_this;
  (void)shell;
  tmp1 = NULL;
  tmp2 = NULL;
  tmp3 = NULL;
  wd = getcwd(NULL, 0);
  if ((tmp3 = get_homedir()))
    {
      if (my_strcmp(tmp3, wd) == 0)
	{
	  free(tmp3);
	  free(wd);
	  return (ret = my_str_copy("~/", 0));
	}
      free(tmp3);
    }
  ret = prompt_simple_wd(wd, tmp1, tmp2);
  return (ret);
}
