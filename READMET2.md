# Tarea 2: Lottery Scheduling en XV6

## Funcionamiento y Lógica de la Implementación

El Lottery Scheduling es un algoritmo de planificación probabilístico donde cada proceso
posee un número de "tickets" que representan su probabilidad de ser elegido para ejecutar.
Los procesos con más tickets tienen mayor probabilidad de obtener tiempo de CPU.

### Algoritmo implementado:
1. Se suman todos los tickets de procesos RUNNABLE
2. Se genera un número aleatorio entre 1 y el total
3. Se recorren los procesos acumulando tickets hasta alcanzar el número ganador
4. El proceso seleccionado ejecuta durante su quantum

## Modificaciones Realizadas

### Archivos modificados:
- `kernel/proc.h`: Agregados campos `tickets` y `cpu_slices` en struct proc
- `kernel/proc.c`: Modificado scheduler() y funciones de inicialización
- `kernel/sysproc.c`: Implementada syscall sys_settickets()
- `kernel/syscall.h` y `kernel/syscall.c`: Registrada nueva syscall
- `user/user.h` y `user/usys.pl`: Expuesta syscall al usuario
- `user/demo.c`: Programa de prueba creado
- `Makefile`: Agregado programa demo

## Dificultades Encontradas y Soluciones

1. **Generación de números aleatorios**: xv6 no tiene rand(), usé una fórmula basada en ticks
2. **Sincronización**: Necesité locks al acceder a tickets para evitar condiciones de carrera
3. **Herencia de tickets**: Los procesos hijos deben heredar tickets del padre

## Posibles Problemas del Lottery Scheduling

1. **Starvation inversa**: Procesos con pocos tickets pueden no ejecutar por largos períodos
2. **No determinismo**: Dificulta debugging y reproducción de problemas
3. **Overhead**: Calcular la lotería en cada decisión añade costo computacional
4. **Injusticia a corto plazo**: La proporcionalidad solo se cumple en el largo plazo
5. **Dificultad para establecer tickets**: No es intuitivo determinar cuántos tickets asignar
6. **Acumulación de tickets**: Procesos que crean muchos hijos pueden monopolizar CPU
