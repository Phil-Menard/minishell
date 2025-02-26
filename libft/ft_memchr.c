/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lefoffan <lefoffan@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:57:59 by lefoffan          #+#    #+#             */
/*   Updated: 2024/11/18 14:56:02 by lefoffan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*x;

	if (!n)
		return (NULL);
	x = (unsigned char *) s;
	while (--n && *x != (unsigned char) c)
		x++;
	if (*x != (unsigned char) c)
		return (NULL);
	return (x);
}

//////////////////////////

// #include <stdio.h>
// #include <string.h>

// // Fonction de test générique pour memchr
// void	run_memchr_test(const void *mem, size_t size, int c)
// {
// 	// ft_memchr
// 	void *result = ft_memchr(mem, c, size);

// 	// Appel à memchr pour obtenir le résultat attendu
// 	void *expected = memchr(mem, c, size);

// 	// Comparaison des résultats
// 	if (result != expected)
// 	{
// 		printf("X - Test échoué : \n");
// 		printf("    Cherché : '%c' (0x%02x)\n", c, c);
// 		printf("    Résultat attendu : %p\n", expected);
// 		printf("    Résultat trouvé    : %p\n\n", result);
// 	}
// 	else
// 		printf("\n-->Test réussi\n\n");
// }

// int	main(void)
// {
// 	printf("Test avec une chaîne classique\n");
// 	char str[] = "Hello, world!";
// 	run_memchr_test(str, 13, 'o');
// 	printf("----------\n\n");

// 	printf("Test avec le char rechercher a la fin\n");
// 	run_memchr_test(str, 13, '!');
// 	printf("----------\n\n");

// 	printf("Test avec le char rechercher apres le n\n");
// 	run_memchr_test(str, 12, '!');
// 	printf("----------\n\n");

// 	printf("Test avec un bloc de mémoire pas terminer par 0\n");
// 	unsigned char block[] = {0x01, 0x02, 0x03, 0x04, 0x05};
// 	run_memchr_test(block, 5, 0x03);
// 	printf("----------\n\n");

// 	printf("Test avec un caractère non trouvé\n");
// 	run_memchr_test(str, 13, 'z');
// 	printf("----------\n\n");

// 	return (0);
// }
