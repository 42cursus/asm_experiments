#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>

int	main(void)
{
	/* write(STDOUT_FILENO,"Hey!\n", 5); */
	char	*str;
	size_t	len;

	str = "Wello Horld!\n";
	len = strlen(str);
	syscall(SYS_write, STDOUT_FILENO, str, len);
	return (0);
}
