# Heap Overflow

Alberto Miguel Diez - amigud00@estudiantes.unileon.es

## 1. Compilación del programa

Para compilar el programa se debe utiliar el siguiente comando:

```bash
gcc heapexample.c -w -g -no-pie -z execstack -o heapexample
```

En la siguiente imagen se puede comprobar la ejecución del programa con algunos argumentos. Se puede ver que la segunda ejecución da _Segmentation fault (core dumped)_ pues se pasan 101 caracteres cuando el buffer solo puede almacenar 64. Esto significa que no se controla la entrada en el código.

![Alt text](img/compilacion_ejecucion.png)

## 2. Examinar el funcionamiento del código

El objetivo en este paso es comprobar como está el mapa de memoria del programa. Para ello se ejecuta el comando _info proc map_ en gdb. Como input al programa se pasa la cadena `XXXX` que en hexadecimal es `0x58585858`.

```bash
gdb ./heapexample
(gdb) list 25,40
(gdb) b 38
(gdb) run XXXX
(gdb) info proc map
```

En la siguiente imagen se puede observar el mapa de memoria de la aplicación. En mi caso, la pila va de la posición `0x405000` a la `0x426000`.

![Alt text](img/info_proc_map.png)

A continuación, consulto la dirección de memoria `0x405000` para comprobar dónde se guarda la información de las estructuras para las que reserva memoria el programa.

```bash
(gdb) x/240x 0x405000
```

![Alt text](img/heap_state.png)

En la iamgen anterior se observa que en la posición `0x4052a0` se encuentra en hexadecimal el _input_ `XXXX`.

Posteriormente, realizo el desensamblado de la función `f_espero_fuera` utilizando la herramienta gdb y con el siguiente comando:

```bash
(gdb) disassemble f_espero_fuera
```

Se puede comprobar que la funciónn comienza en la posición de memoria `0x4011ad`. Esto implica que en el mapa de la pila se debe observar esta posición de memoria pues a la que apunta `f->fp` (se encuentra en la posición `0x4052f0` del _heap_).

![Alt text](img/disassemble.png)
