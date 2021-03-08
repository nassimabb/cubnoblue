/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:39:50 by nabboudi          #+#    #+#             */
/*   Updated: 2019/10/30 00:55:51 by nabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H

# define FT_LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *b, size_t n);
void		*ft_memmove(void *des, const void *src, size_t n);
void		*ft_memccpy(void *des, const void *src, int c, size_t n);
void		*ft_memchr(const void *src, int c, size_t n);
void		*ft_memcpy(void *des, const void *src, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strdup(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isprint(int c);
int			ft_isascii(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_strchr(const char *src, int c);
char		*ft_strrchr(const char *src, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *s1, const char *b, size_t n);
char		*ft_substr(char const *s, unsigned int star, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(const char *str, char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
#endif
