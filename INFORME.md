# INFORME - Tarea 1: Implementación de Llamadas al Sistema

**Estudiante:** Mateo Moreira
**Curso:** Sistemas Operativos TICS312
**Fecha:** 9/25/2025

## 1. Funcionamiento de las llamadas al sistema implementadas

### 1.1 Llamada al sistema `getppid()`

**Propósito:** Retorna el ID del proceso padre del proceso que la invoca.

**Funcionamiento:**
- La función accede a la estructura del proceso actual usando `myproc()`
- Obtiene el puntero al proceso padre a través de `myproc()->parent`
- Retorna el PID del proceso padre: `myproc()->parent->pid`

**Casos de uso:**
- Identificar relaciones padre-hijo entre procesos
- Debugging y monitoreo de procesos
- Implementación de jerarquías de procesos

### 1.2 Llamada al sistema `getancestor()` (Implementación Avanzada)

**Propósito:** Retorna el ancestro indicado en el parámetro de entrada.

**Funcionamiento:**
- `getancestor(0)`: Retorna el PID del mismo proceso
- `getancestor(1)`: Retorna el PID del proceso padre
- `getancestor(n)`: Retorna el PID del ancestro n niveles hacia arriba
- Retorna -1 si el nivel solicitado no existe

**Algoritmo:**
1. Validar que el parámetro sea no negativo
2. Si es 0, retornar el PID actual
3. Recorrer la cadena de procesos padre n veces
4. Si se encuentra un parent null antes de completar n iteraciones, retornar -1
5. Si se completan todas las iteraciones, retornar el PID del ancestro encontrado

## 2. Explicación de las modificaciones realizadas

### 2.1 Archivos modificados para `getppid()`

#### `kernel/syscall.h`
- Agregado: `#define SYS_getppid 23`
- Propósito: Definir el número identificador único para la llamada al sistema

#### `kernel/syscall.c`
- Agregado: `extern uint64 sys_getppid(void);`
- Agregado: `[SYS_getppid] sys_getppid,` en el array syscalls[]
- Propósito: Declarar la función y registrarla en la tabla de llamadas al sistema

#### `kernel/sysproc.c`
- Agregado: Implementación completa de `sys_getppid()`
```c
uint64 sys_getppid(void) {
  return myproc()->parent->pid;
}
```
- Propósito: Lógica de ejecución de la llamada al sistema

#### `user/user.h`
- Agregado: `int getppid(void);`
- Propósito: Declaración de la función para programas de usuario

#### `user/usys.pl`
- Agregado: `entry("getppid");`
- Propósito: Generar código de ensamblador para la transición user-kernel

### 2.2 Archivos modificados para `getancestor()` (Implementación Avanzada)

Los mismos archivos que `getppid()`, pero con:
- `#define SYS_getancestor 24`
- Implementación más compleja en `sysproc.c` con validación de parámetros
- Manejo de errores y casos límite

### 2.3 Programa de prueba `yosoytupadre.c`

**Funcionalidades implementadas:**
- Mostrar PID del proceso actual y su padre
- Crear proceso hijo para demostrar relación padre-hijo
- Probar ambas llamadas al sistema (`getppid()` y `getancestor()`)
- Validar casos límite (ancestros inexistentes)

**Modificación del Makefile:**
- Agregado `$U/_yosoytupadre\` en la sección UPROGS
- Permite compilar e integrar el programa en xv6

## 3. Dificultades encontradas y soluciones

### 3.1 Comprensión de la estructura de procesos
**Problema:** Inicialmente no comprendía cómo xv6 mantiene la jerarquía de procesos.

**Solución:** 
- Estudié la estructura `struct proc` en `proc.h`
- Analicé cómo el campo `parent` mantiene la referencia al proceso padre
- Revisé el código de `fork()` para entender cómo se establece la relación

### 3.2 Validación de parámetros en `getancestor()`
**Problema:** Manejar casos donde se solicita un ancestro que no existe.

**Solución:**
- Implementé validación del parámetro de entrada usando `argint()`
- Agregué verificación de que el parámetro sea no negativo
- Implementé loop con verificación de `parent != 0` para detectar fin de cadena

### 3.3 Integración del programa de prueba
**Problema:** El programa no aparecía disponible en xv6 después de compilar.

**Solución:**
- Verifiqué que el nombre en el Makefile coincidiera exactamente con el archivo
- Me aseguré de usar el formato correcto `$U/_nombre\` con backslash al final
- Ejecuté `make clean` antes de `make qemu` para forzar recompilación completa

### 3.4 Debugging de las llamadas al sistema
**Problema:** Dificultad para verificar que las llamadas funcionaran correctamente.

**Solución:**
- Creé programa de prueba exhaustivo con múltiples casos
- Implementé pruebas con procesos padre e hijo
- Agregué validación de casos límite y manejo de errores

## 4. Pruebas realizadas

### 4.1 Pruebas básicas de `getppid()`
-  Programa simple retorna PID del padre correctamente
-  Proceso hijo identifica correctamente al padre
-  Relación padre-hijo se mantiene consistente

### 4.2 Pruebas avanzadas de `getancestor()`
-  `getancestor(0)` retorna PID del proceso actual
-  `getancestor(1)` equivale a `getppid()`
-  `getancestor(n)` con n > niveles existentes retorna -1
-  Parámetros negativos retornan -1
-  Funciona correctamente en jerarquías de múltiples niveles

### 4.3 Pruebas de integración
-  Programa `yosoytupadre` compila sin errores
-  Programa se ejecuta correctamente en xv6
-  Output es claro y comprensible
-  No hay memory leaks ni crashes del sistema

## 5. Conclusiones

- La implementación de llamadas al sistema requiere modificaciones coordinadas en múltiples archivos
- La comprensión de la estructura de datos del kernel es fundamental
- El manejo de casos límite y validación de parámetros es crucial para la robustez
- Las pruebas exhaustivas son necesarias para garantizar funcionamiento correcto
- La documentación clara facilita el mantenimiento y comprensión del código

## 6. Archivos entregados

### Código fuente modificado:
- `kernel/syscall.h` - Definiciones de system calls
- `kernel/syscall.c` - Tabla y declaraciones de system calls
- `kernel/sysproc.c` - Implementaciones de las funciones
- `user/user.h` - Declaraciones para programas de usuario
- `user/usys.pl` - Generación de código de transición
- `Makefile` - Integración del programa de prueba

### Programas de prueba:
- `user/yosoytupadre.c` - Programa principal de prueba


