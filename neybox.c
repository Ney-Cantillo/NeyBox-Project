#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>

// 1. Versión de la Box
int ney_version(int argc, char *argv[]) {
    printf("NeyBox v2.4 - Ney Lopo Shell (Universal Edition)\n");
    return 0;
}

// 2. Mostrar la hora actual
int ney_time(int argc, char *argv[]) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%s", asctime(tm));
    return 0;
}

// 3. Listar directorio (ls básico)
int ney_ls(int argc, char *argv[]) {
    DIR *d = opendir(".");
    if (d) {
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL) {
            printf("%s  ", dir->d_name);
        }
        printf("\n");
        closedir(d);
    } else {
        perror("neybox: ls");
        return 1;
    }
    return 0;
}

// 4. Mostrar el directorio actual (pwd)
int ney_pwd(int argc, char *argv[]) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("neybox: pwd");
        return 1;
    }
    return 0;
}

// 5. Imprimir texto (echo)
int ney_echo(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}

// 6. Mostrar el usuario actual (whoami para Termux)
int ney_whoami(int argc, char *argv[]) {
    struct passwd *pw = getpwuid(getuid());
    if (pw && pw->pw_name) {
        printf("%s\n", pw->pw_name);
    } else {
        printf("unknown\n");
    }
    return 0;
}

// 7. Crear directorio (mkdir)
int ney_mkdir(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "neybox mkdir: falta el nombre del directorio\n");
        return 1;
    }
    if (mkdir(argv[1], 0777) == -1) {
        perror("neybox: mkdir");
        return 1;
    }
    return 0;
}

// 8. Limpiar pantalla (clear)
int ney_clear(int argc, char *argv[]) {
    printf("\033[H\033[J");
    return 0;
}

// 9. Leer archivos de texto (cat)
int ney_cat(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "neybox cat: falta indicar el archivo\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("neybox: cat");
        return 1;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        printf("%s", buffer);
    }
    fclose(f);
    return 0;
}

// 10. Ejecutar comandos externos del sistema (como fastfetch, python, etc.)
void run_external_command(char **argv) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(argv[0], argv);
        // Si execvp falla, el comando no existe
        printf("Ney Lopo Shell: comando externo '%s' no encontrado.\n", argv[0]);
        exit(127);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("neybox: fork");
    }
}

// Analizador y enrutador de comandos dentro de la shell
void run_command(char *cmd_line) {
    char line_copy[256];
    strncpy(line_copy, cmd_line, sizeof(line_copy));
    
    char *argv[64];
    int argc = 0;
    
    char *token = strtok(line_copy, " \t\n");
    while (token != NULL && argc < 63) {
        argv[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    argv[argc] = NULL;
    
    if (argc == 0) return;

    if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "quit") == 0) {
        printf("Saliendo de Ney Lopo Shell...\n");
        exit(0);
    } else if (strcmp(argv[0], "version") == 0) {
        ney_version(argc, argv);
    } else if (strcmp(argv[0], "time") == 0) {
        ney_time(argc, argv);
    } else if (strcmp(argv[0], "ls") == 0) {
        ney_ls(argc, argv);
    } else if (strcmp(argv[0], "pwd") == 0) {
        ney_pwd(argc, argv);
    } else if (strcmp(argv[0], "echo") == 0) {
        ney_echo(argc, argv);
    } else if (strcmp(argv[0], "whoami") == 0) {
        ney_whoami(argc, argv);
    } else if (strcmp(argv[0], "mkdir") == 0) {
        ney_mkdir(argc, argv);
    } else if (strcmp(argv[0], "clear") == 0) {
        ney_clear(argc, argv);
    } else if (strcmp(argv[0], "cat") == 0) {
        ney_cat(argc, argv);
    } else {
        // Si no es interno, se delega al sistema (ej. fastfetch)
        run_external_command(argv);
    }
}

// Función de bienvenida con el Logo de la Caja en ASCII
void start_ney_lopo_shell() {
    printf("\033[1;33m");
    printf("       +------------------------+\n");
    printf("      /                        /|\n");
    printf("     +------------------------+ |\n");
    printf("     |   [ NEYBOX ] v2.4      | +\n");
    printf("     |   Ney Lopo Shell       |/\n");
    printf("     +------------------------+\n");
    printf("\033[0m");
    
    printf("\033[1;36m Internos: ls, pwd, time, echo, whoami, mkdir, cat, clear, version\033[0m\n");
    printf("\033[1;35m Externos: ¡Puedes usar fastfetch y cualquier comando del sistema!\033[0m\n");
    printf("------------------------------------------------------------------\n");

    char input[256];
    while (1) {
        printf("\033[1;32mNeyLopo>\033[0m ");
        fflush(stdout);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) continue;
        
        run_command(input);
    }
}

int main(int argc, char *argv[]) {
    char *cmd = strrchr(argv[0], '/');
    cmd = cmd ? cmd + 1 : argv[0];

    if (strcmp(cmd, "neybox") == 0 || argc == 1) {
        start_ney_lopo_shell();
        return 0;
    }

    // Modo enlaces simbólicos individuales
    if (strcmp(cmd, "version") == 0) return ney_version(argc, argv);
    if (strcmp(cmd, "time") == 0)    return ney_time(argc, argv);
    if (strcmp(cmd, "ls") == 0)      return ney_ls(argc, argv);
    if (strcmp(cmd, "pwd") == 0)     return ney_pwd(argc, argv);
    if (strcmp(cmd, "echo") == 0)    return ney_echo(argc, argv);
    if (strcmp(cmd, "whoami") == 0)  return ney_whoami(argc, argv);
    if (strcmp(cmd, "mkdir") == 0)   return ney_mkdir(argc, argv);
    if (strcmp(cmd, "clear") == 0)   return ney_clear(argc, argv);
    if (strcmp(cmd, "cat") == 0)     return ney_cat(argc, argv);

    start_ney_lopo_shell();
    return 0;
}

