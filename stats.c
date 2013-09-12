#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#define _GNU_SOURCE

int main(int argc, char *argv[]) {
	
	int opt_sum = 0;
	int opt_avg = 0;
	int opt_num = 0;
	int opt_hlp = 0;
	int opt_ver = 0;
	
	int c;

	while (1)
	{
		static struct option long_options[] =
		{
			/* These options set a flag. */
			{"avg",     no_argument,       NULL,        'a'},
			{"count",   no_argument,       NULL,        'n'},
			{"num",     no_argument,       NULL,        'n'},
			{"sum",     no_argument,       NULL,        's'},
			{"help",    no_argument,       NULL,        200},
			{"version", no_argument,       NULL,        201},
			{0,         0,                 0,            0}
			// EXAMPLE: {"verbose-level", required_argument, 0, 'v'},
		};

		int option_index = 0;

		c = getopt_long (argc, argv, "achns", long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c)
		{
			case 0:
				break;

			case 'a':
				opt_avg = 1;
				break;

			case 'c':
				opt_num = 1;
				break;

			case 'n':
				opt_num = 1;
				break;

			case 's':
				opt_sum = 1;
				break;

			case 200:
				opt_hlp = 1;
				break;

			case 201:
				opt_ver = 1;
				break;

			case '?':
				/* getopt_long already printed an error message. */
				break;

			default:
				abort ();
		}
	}

	if (opt_hlp) {
		printf("usage: stats [-acns]\n");
		printf("\n");
		printf("Options:\n");
		printf("	-a		Show average.\n");
		printf("	-c, -n  Show item count.\n");
		printf("	-s		Show sum.\n");
		printf("\n");
		exit(EXIT_SUCCESS);
	}

	if (opt_ver) {
		printf("stats v0.1\n");
		exit(EXIT_SUCCESS);
	}

	long double sum = 0;
	int num = 0;

	size_t l = 0;
	char *lineptr = NULL;

	while (getline(&lineptr, &l, stdin) != -1) {
		sum = sum + atof(lineptr);
		++num;
	}

	free(lineptr);

	int opt_n = opt_sum + opt_num + opt_avg;

	if (opt_sum)
		printf("%s%LG\n", opt_n > 1 ? "sum....: " : "", sum);

	if (opt_num)
		printf("%s%d\n", opt_n > 1 ? "num....: " : "", num);

	if (opt_avg)
		printf("%s%LG\n", opt_n > 1 ? "avg....: " : "", sum / num);

}
