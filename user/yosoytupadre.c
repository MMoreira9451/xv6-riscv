#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int my_pid = getpid();
    int parent_pid = getppid();
    
    printf("=== Programa yosoytupadre ===\n");
    printf("Mi PID: %d\n", my_pid);
    printf("PID de mi padre: %d\n", parent_pid);
    
    // Probar getancestor (si está implementado)
    printf("\n--- Prueba de getancestor() ---\n");
    printf("getancestor(0) (yo mismo): %d\n", getancestor(0));
    printf("getancestor(1) (mi padre): %d\n", getancestor(1));
    printf("getancestor(2) (mi abuelo): %d\n", getancestor(2));
    printf("getancestor(5) (ancestro inexistente): %d\n", getancestor(5));
    
    // Crear un proceso hijo para mostrar la relación padre-hijo
    int child_pid = fork();
    
    if (child_pid == 0) {
        // Código del proceso hijo
        printf("\n--- Proceso HIJO ---\n");
        printf("Soy el proceso hijo, mi PID: %d\n", getpid());
        printf("Mi padre tiene PID: %d\n", getppid());
        
        printf("Prueba de getancestor() desde el hijo:\n");
        printf("  getancestor(0) (yo): %d\n", getancestor(0));
        printf("  getancestor(1) (mi padre): %d\n", getancestor(1));
        printf("  getancestor(2) (mi abuelo): %d\n", getancestor(2));
        
        exit(0);
    } else if (child_pid > 0) {
        // Código del proceso padre
        wait(0); // Esperar a que termine el hijo
        printf("\n--- Proceso PADRE ---\n");
        printf("Soy el proceso padre, mi PID: %d\n", getpid());
        printf("Mi hijo tuvo PID: %d\n", child_pid);
        printf("¡Proceso hijo terminado!\n");
    } else {
        printf("Error al crear proceso hijo\n");
    }
    
    exit(0);
}
