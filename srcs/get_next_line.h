/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlas <acharlas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:40:07 by acharlas          #+#    #+#             */
/*   Updated: 2020/01/21 21:21:45 by acharlas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
#define BUFFER_SIZE 4096
char			*ft_strdup(const char *s);
char			*ft_substr(const char *s, unsigned int start, size_t len);
unsigned int	ft_strlen(const char *s);
char			*join(char *s1, char *s2, int len1, int len2);
void			*ft_memcpy(void *dst, const void *src, size_t len);
int				get_next_line(const int fd, char **line);
void			*ft_memchr(const void *s, int c, size_t n);
#endif
