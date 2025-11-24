# Tarea 3: Protección de Lectura en XV6

## Funcionamiento y Lógica

Esta implementación permite marcar páginas de memoria como "write-only" (solo escritura),
removiendo temporalmente el permiso de lectura mientras se mantiene el de escritura.
Esto es útil para proteger datos sensibles como claves criptográficas.

### Mecanismo implementado:
1. `mrdprotect()`: Limpia el bit PTE_R de las PTEs en el rango especificado
2. `munrdprotect()`: Restaura el bit PTE_R 
3. La CPU genera un page fault si se intenta leer memoria sin PTE_R

## Modificaciones Realizadas

### Archivos modificados:
- `kernel/vm.c`: Implementación de mrdprotect() y munrdprotect()
- `kernel/defs.h`: Declaraciones de las nuevas funciones
- `kernel/sysproc.c`: Syscalls sys_mrdprotect() y sys_munrdprotect()
- `kernel/syscall.h` y `kernel/syscall.c`: Registro de syscalls
- `user/user.h` y `user/usys.pl`: Exposición al usuario
- `user/rdprotect_test.c`: Programa de prueba
- `Makefile`: Agregado programa de prueba

## Dificultades Encontradas

1. **Page Table Walking**: Entender cómo usar walk() para obtener PTEs
2. **Manipulación de bits**: Usar máscaras para modificar solo PTE_R
3. **Validaciones**: Asegurar que solo se modifiquen páginas de usuario válidas

## Posibles Casos de Uso

1. **Protección de claves criptográficas**: Write-only para actualizar, sin lectura
2. **Audit logs**: Escribir eventos sin permitir su lectura posterior
3. **Canarios de seguridad**: Detectar intentos de lectura no autorizados
4. **Sandboxing**: Aislar datos sensibles de procesos no confiables
