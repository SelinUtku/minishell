# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
#include "include/minishell.h"

int main (int argc, char **argv, char **env)
{
	char *str1;
	char *str2;
	char *str3;
	char *str4;
	char *last;

	// while (env[++i])
	// {
	// 	printf("%s\n",env[i]);
	// }
	// char *ar[] = { "/bin/ls", "/Users/cutku/Projects", 0 };
	// chdir("/Users/cutku/Projects");
	// printf("1.%s\n", getenv("PWD="));
	// printf("1.%s\n", getcwd(NULL, 0));
    // chdir("/Users/cutku/Projects");
	// printf("2.%s\n", getenv("PWD="));
	// char **ptr;
	// *(getenv("PATH=") - 5) = '\0';
	// ptr = malloc(3 * sizeof(char *));
	// ptr[0] = "/bin/ls";
	// ptr[1] = "env";
	// ptr[1] = NULL;
	// free(env);
	// env = NULL;
	// if (chdir("/Users/cutku/Projects")==-1)
	// 	perror("chdir");
	// printf("2.%s\n",getcwd(NULL, 0));

// 	char *envp[] =
//     {
//         "HOME=/",
//         "PATH=/bin:/usr/bin",
//         "TZ=UTC0",
//         "USER=beelzebub",
//         "PWD=beelzebub",
//         "LOGNAME=tarzan",
//         0
//     };
// 	// setenv("PWD=", "/usr/bin", 1);

	// execve(*ar, ar , env);
	// str1 = ft_strdup("");
	// str2 = ft_strdup("heyyy");
	// str3 = ft_strdup("");
	// str4 = ft_strdup("selamm\n");
	// last = ft_strjoin(str1, str2);
	// printf("%s\n", last);
	// last = ft_strjoin(last, str3);
	// printf("%s\n", last);
	// last = ft_strjoin(last, str4);
	// printf("%s\n", last);
// 	// printf("%s\n", env[0]);
	return (0);
}
