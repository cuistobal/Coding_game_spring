#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void run_executable_with_test_file(const char *executable_path, FILE *test_file) {
    int status;
    pid_t pid;
    char line[256];
    FILE *temp_file;
    char temp_filename[] = "temp_test_XXXXXX";

    // Créer un fichier temporaire pour chaque test
    int temp_fd = mkstemp(temp_filename);
    if (temp_fd == -1) {
        perror("Erreur lors de la création du fichier temporaire");
        exit(EXIT_FAILURE);
    }
    temp_file = fdopen(temp_fd, "w+");

    // Lire le fichier de test ligne par ligne
    while (fgets(line, sizeof(line), test_file))
	{
        if (strcmp(line, "\n") == 0) 
		{
            fclose(temp_file);

            pid = fork();
            if (pid == 0) 
			{
                int temp_test_file = open(temp_filename, O_RDONLY);
                
				if (temp_test_file == -1)
				{
                    perror("Erreur lors de l'ouverture du fichier temporaire");
                    exit(EXIT_FAILURE);
                }

                dup2(temp_test_file, STDIN_FILENO);
                close(temp_test_file);

                execl(executable_path, executable_path, (char *)NULL);

                perror("Erreur lors de l'exécution de l'exécutable");
                exit(EXIT_FAILURE);
            }
			else if (pid > 0) 
			{
                waitpid(pid, &status, 0);

                temp_file = fopen(temp_filename, "w+");
                if (temp_file == NULL) 
				{
                    perror("Erreur lors de l'ouverture du fichier temporaire");
                    exit(EXIT_FAILURE);
                }

            } 
			else
                exit(EXIT_FAILURE);
			printf("===============NEXT TEST====================\n");
        } 
		else
            fputs(line, temp_file);
    }

    fclose(temp_file);
    unlink(temp_filename);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
	{
        fprintf(stderr, "Usage: %s <chemin_executable> <chemin_fichier_test>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *executable_path = argv[1];
    const char *test_file_path = argv[2];

    FILE *test_file = fopen(test_file_path, "r");
    
	if (test_file == NULL)
	{
        perror("Erreur lors de l'ouverture du fichier de test");
        return EXIT_FAILURE;
    }

    run_executable_with_test_file(executable_path, test_file);

    fclose(test_file);
    
	return EXIT_SUCCESS;
}

