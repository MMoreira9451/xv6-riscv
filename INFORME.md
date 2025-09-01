# INFORME - Tarea 0: Instalación y configuración de xv6

**Estudiante:** Mateo Moreira  
**Curso:** Sistemas Operativos TICS312  
**Fecha:** 1/9/2025  

## 1. Pasos seguidos para instalar xv6

### 1.1 Configuración del entorno
```bash
# Instalación de dependencias necesarias
sudo apt-get update
sudo apt-get install make qemu-system-misc bc gcc-riscv64-linux-gnu

# Configuración de git
git config --global user.name "MMoreira9451"
git config --global user.email "mi@email.com"
git config --global credential.helper store
```

### 1.2 Fork y clonación del repositorio
1. Creé un fork del repositorio oficial de xv6-riscv desde GitHub:
   - Repositorio original: https://github.com/mit-pdos/xv6-riscv
   - Mi fork: https://github.com/MMoreira9451/xv6-riscv

2. Cloné mi fork localmente:
```bash
git clone https://github.com/MMoreira9451/xv6-riscv.git
cd xv6-riscv
```

### 1.3 Creación de ramas de trabajo
```bash
# Creé varias ramas durante el proceso de aprendizaje
git checkout -b users/MMoreira9451/mi-primer-commit-clase1
git checkout riscv
git checkout -b Tarea-0
```

### 1.4 Compilación inicial
```bash
make qemu
```

## 2. Problemas encontrados y soluciones

### 2.1 Error de dependencias faltantes
**Problema:** Al ejecutar `make qemu` inicialmente obtuve errores de herramientas no encontradas:
```
*** Error: Couldn't find a riscv64 version of GCC/binutils.
qemu-system-riscv64: not found
make: gcc: No such file or directory
```

**Solución:** Instalé las dependencias necesarias:
```bash
sudo apt-get install make qemu-system-misc bc gcc-riscv64-linux-gnu
```

### 2.2 Problema de autenticación con GitHub
**Problema:** Error de autenticación al hacer push:
```
remote: Invalid username or token. Password authentication is not supported for Git operations.
fatal: Authentication failed
```

**Solución:** 
- Creé un Personal Access Token (PAT) en GitHub
- Configuré los permisos necesarios (repo access)
- Usé el token en lugar de la contraseña para autenticación

### 2.3 Error de permisos de compilación
**Problema:** Error de permisos al compilar:
```
fatal error: opening dependency file kernel/syscall.d: Permission denied
```

**Solución:** 
```bash
# Cambié los permisos del directorio
sudo chown -R ashy:ashy ~/xv6-riscv
make clean
make qemu
```

### 2.4 Errores de sintaxis en comandos git
**Problema:** Confusión con la sintaxis de creación de branches:
```bash
git checkout -b users/<alias>/<branch name>  # Sintaxis incorrecta con < >
```

**Solución:** Usé la sintaxis correcta sin los símbolos < >:
```bash
git checkout -b users/MMoreira9451/mi-primer-commit-clase1
```

## 3. Confirmación de que xv6 está funcionando correctamente

### 3.1 Compilación exitosa
El sistema compila sin errores:
```bash
make qemu
# Resultado: Compilación exitosa, xv6 inicia correctamente
```

### 3.2 Funcionalidad básica verificada
Una vez dentro de xv6, verifiqué los siguientes comandos:

```bash
$ ls
# Muestra la lista de programas disponibles

$ echo "Hello xv6"
# Funciona correctamente

$ cat README
# Muestra el contenido del archivo README
```

### 3.3 Programas de prueba básicos
Confirmé que los programas básicos funcionan:
- `cat` - para mostrar archivos
- `echo` - para mostrar texto
- `ls` - para listar archivos
- `grep` - para buscar en archivos

### 3.4 Salida del sistema
Verificué que puedo salir correctamente del sistema usando `Ctrl + A → X`.

### 3.5 Estado actual del repositorio
```bash
$ git branch
* Tarea-0
  mi-primer-commit-clase1  
  riscv
  users/MMoreira9451/mi-primer-commit-clase1

$ git status
On branch Tarea-0
nothing to commit, working tree clean
```

## 4. Conclusiones

- La instalación de xv6 fue exitosa después de resolver los problemas de dependencias y permisos
- El sistema operativo funciona correctamente y permite la ejecución de programas básicos
- La configuración de git y GitHub está funcionando apropiadamente
- El entorno está listo para implementar las modificaciones requeridas en las siguientes tareas

