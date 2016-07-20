/*
** get_next_line.c for  in /home/fernan_w/Téléchargements/backup/gnl
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:55:34 2016
** Last update Wed Jun  8 09:05:32 2016 
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "tools.h"
#include "my.h"

static int	my_linelen(char *s)
{
  int		i;
  int		len;

  i = 0;
  len = 0;
  while (s && s[i] && s[i] != '\n')
    {
      len++;
      i++;
    }
  return (len);
}

static char	*my_reappend(char *s1, char **s2)
{
  char		*res;
  char		*tmp;
  char		*res_tmp;

  if ((res = malloc(my_linelen(s1) + my_linelen(*s2) + 2)) == NULL)
    return (NULL);
  res_tmp = s1;
  tmp = res;
  while (s1 && *s1)
    *res++ = *s1++;
  free(res_tmp);
  while (s2 && *(*s2) && *(*s2) != '\n')
    {
      *res++ = *(*s2);
      ++(*s2);
    }
  *res++ = '\0';
  return (tmp);
}

static char	*read_till_n(int fd)
{
  int		red;
  char		*res;
  static char	*tmp;
  static char	*c;

  res = NULL;
  red = 0;
  while (1)
    {
      if (!c && !(c = malloc(BUFFSIZE)))
	return (NULL);
      if ((!tmp || !(*tmp)) && (tmp = c)
	  && (c = my_memset(c, BUFFSIZE - 1))
	  && (red = read(fd, c, BUFFSIZE - 1)) <= 0)
	return (res);
      if (red > 0)
	c[red] = '\0';
      res = my_reappend(res, &tmp);
      if (*tmp && *tmp == '\n')
	{
	  tmp++;
	  return (res);
	}
    }
  return (NULL);
}

char	*get_next_line(int fd)
{
  char	*res;

  if (fd < 0)
    return (NULL);
  res = read_till_n(fd);
  return (res);
}
