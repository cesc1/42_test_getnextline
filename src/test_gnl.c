#include "unity.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	assert_file(char *file, char **res_lines, int res_n)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(file, O_RDONLY);
	TEST_ASSERT_TRUE_MESSAGE(fd != -1, "Error: Failed to read file.");
	count = 0;
	while (count < res_n)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		TEST_ASSERT_EQUAL_STRING(*res_lines, line);
		free(line);
		res_lines++;
		count++;
	}
	line = get_next_line(fd);
	TEST_ASSERT_NULL(line);
	TEST_ASSERT_EQUAL_INT(res_n, count);
	close(fd);
	return (1);
}

void	test_escalonat(void)
{
	char	*arr[] = {
		"\n",
		"h\n",
		"ho\n",
		"hol\n",
		"hola\n",
		"hola \n",
		"hola q\n",
		"hola qu\n",
		"hola que\n",
		"hola que \n",
		"hola que h\n",
		"hola que ha\n",
		"hola que has\n",
		"hola que hase\n",
		"hola que hase!\n",
		"hola hola hola\n",
		"hola que hase!\n",
		"hola que hase\n",
		"hola que has\n",
		"hola que ha\n",
		"hola que h\n",
		"hola que \n",
		"hola que\n",
		"hola qu\n",
		"hola q\n",
		"hola \n",
		"hola\n",
		"hol\n",
		"ho\n",
		"h\n",
	};

	assert_file("test_files/escalonat.txt", arr, 30);
}

void	test_lore_ipsum(void)
{
	char	*arr[] = {
		"Lorem Ipsum\r\n",
		"\"Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit...\"\r\n",
		"\"There is no one who loves pain itself, who seeks after it and wants to have it, simply because it is pain...\"\r\n",
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris quis pulvinar lacus. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Mauris sodales elit id risus aliquam efficitur. Fusce maximus posuere leo, vitae semper ipsum egestas vel. Quisque eu tempus mi. Nam at malesuada nisi. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Aenean nec elit rhoncus, accumsan orci quis, venenatis augue. Duis at nisi sapien.\r\n",
		"\r\n",
		"Sed in faucibus diam, et blandit neque. Phasellus lobortis erat a risus ornare blandit. Mauris ligula massa, sollicitudin quis ligula vel, congue mollis mauris. Vestibulum finibus orci sed urna pulvinar, sed pellentesque mi rutrum. Praesent ornare facilisis viverra. Mauris ac mi eget tortor ultrices vestibulum. Sed neque tellus, condimentum tempor posuere sit amet, pharetra ut lacus. Quisque vel tincidunt lectus. Duis in ligula fermentum, iaculis tortor fringilla, molestie sem. Sed id hendrerit lorem. Integer tristique diam neque, ac sollicitudin erat ornare sit amet. Aliquam non pharetra ex. Suspendisse in tortor ac mauris fermentum dignissim sed in nisi. Morbi id odio arcu. Proin quis sem urna. Donec nec porta erat.\r\n",
		"\r\n",
		"Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Sed id vestibulum ex. Fusce venenatis non enim sed finibus. Ut ut magna id leo consectetur ultricies. Donec egestas erat eu diam pharetra luctus. Quisque et pharetra mi. Mauris sagittis sem nec nunc molestie, vitae vestibulum tortor accumsan. Proin euismod nibh eu eros posuere sagittis. Nullam nec laoreet orci. Donec tincidunt hendrerit libero ac auctor. Vivamus neque sem, efficitur feugiat euismod quis, aliquam vitae odio. Mauris et arcu mollis nisi tincidunt commodo eu id lectus. Morbi vitae semper lectus. Curabitur pharetra nunc vitae aliquet finibus. Aenean sodales ex at velit scelerisque ultrices.\r\n",
		"\r\n",
		"Ut gravida placerat purus eget maximus. Duis in arcu et neque dignissim dictum nec in metus. Cras venenatis tempor viverra. Suspendisse mollis felis vel egestas finibus. Aliquam eget interdum libero, quis suscipit nunc. Fusce ultrices urna ut urna maximus vestibulum. Pellentesque fringilla ante id odio dictum, sit amet efficitur risus luctus. Pellentesque pretium facilisis massa, et pulvinar urna. Maecenas sapien ex, congue vitae diam sit amet, varius vestibulum mauris.\r\n",
		"\r\n",
		"Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Quisque placerat purus pulvinar rhoncus blandit. Morbi tempor eu quam vel sagittis. In nec enim libero. Mauris faucibus leo leo, in pulvinar neque hendrerit in. Ut porta semper ipsum, in commodo justo molestie sit amet. Curabitur condimentum faucibus magna quis maximus. Suspendisse in elit scelerisque, scelerisque leo sit amet, luctus nisi. Aenean eu tempor libero. Suspendisse vel accumsan sapien. Nulla elementum neque non lobortis lobortis. Duis ullamcorper a neque sed fringilla. Maecenas ut ullamcorper ipsum. Sed venenatis urna orci, sit amet dapibus eros fringilla in. Suspendisse sit amet dictum mi. Pellentesque vitae enim a mi ultricies aliquam at ut ante.",
	};

	assert_file("test_files/lore_ipsum.txt", arr, 12);
}

void	test_empty(void)
{
	assert_file("test_files/empty.txt", NULL, 0);
}

void	test_perms(void)
{
	int		fd;
	char	*line;

	fd = open("test_files/lore_ipsum.txt", O_WRONLY);
	TEST_ASSERT_TRUE_MESSAGE(fd != -1, "Error: Failed to read file.");
	line = get_next_line(fd);
	TEST_ASSERT_NULL(line);
	close(fd);
}

void	test_bonus(void)
{
	int		fd1;
	int		fd2;
	int		i1;
	int		i2;
	char	*line;
	char	*arr1[] = {
		"fd0 line0__\n",
		"fd0 line1__\n",
		"fd0 line2__\n",
		"fd0 line3__\n"
	};
	char	*arr2[] = {
		"fd1 line0 .-\n",
		"fd1 line1 .-.-\n",
		"fd1 line2 .-.-.-\n",
		"fd1 line3 .-.-.-.-\n"
	};

	fd1 = open("test_files/bonus1.txt", O_RDONLY);
	fd2 = open("test_files/bonus2.txt", O_RDONLY);
	TEST_ASSERT_TRUE_MESSAGE(fd1 != -1, "Error: Failed to read file.");
	TEST_ASSERT_TRUE_MESSAGE(fd2 != -1, "Error: Failed to read file.");
	i1 = 0;
	i2 = 0;
	while (1)
	{
		line = get_next_line(fd1);
		if (!line)
			break ;
		TEST_ASSERT_EQUAL_STRING(arr1[i1], line);
		free(line);
		i1++;
		line = get_next_line(fd2);
		if (!line)
			break ;
		TEST_ASSERT_EQUAL_STRING(arr2[i2], line);
		free(line);
		i2++;
	}
	line = get_next_line(fd1);
	TEST_ASSERT_NULL(line);
	line = get_next_line(fd2);
	TEST_ASSERT_NULL(line);
	TEST_ASSERT_EQUAL_INT(8, i1 + i2);
	close(fd1);
	close(fd2);
}
