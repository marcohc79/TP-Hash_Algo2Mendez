<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Repositorio de Marco Huamani - 95392 - mhcaballero79@gmail.com 

<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Repositorio de Marco Huamani - 95392 - mhcaballero79@gmail.com 

- Para compilar:

```bash
make
```

Para mayor pruebas provistas por la catedra:

```bash
./.algo2/test.sh
```

- Para ejecutar:

```bash
./pruebas_alumno
```

- Para ejecutar con valgrind:
```bash
valgrind ./pruebas_alumno
```
---
##  Funcionamiento

Se programará una implementación del tipo hash abierto. Las colisiones se trabajaran implementando la técnica de encadenamiento (explicado mas adelantes).

<div align="center">
    <img width="75%" src="img/tabla.svg">
</div>

En el caso que se ingrese dos claves iguales, haremos una actualización del valor sobre escribiendo con el valor nuevo y devolviendo el viejo valor.

<div align="center">
    <img width="75%" src="img/repetido.svg">
</div>


## Respuestas a las preguntas teóricas

# Diccionario

Un diccionario es una estructura de datos que almacena información en pares clave-valor. Cada elemento se identifica por una clave única, 
que actúa como un identificador para acceder al valor asociado de manera eficiente.

Los diccionarios se caracterizan por realizar búsquedas rápidas. Utilizan una función hash, que convierte la clave en un valor entero, 
el cual se utiliza como índice en una estructura interna, generalmente una tabla hash. Esta técnica permite una búsqueda directa del valor
asociado a una clave específica en tiempo constante, sin importar el tamaño del diccionario.

Sin embargo, no todo es perfecto. Las colisiones son una problemática común en los diccionarios. Esto ocurre cuando dos claves diferentes generan el mismo 
índice en la tabla hash. Para solucionar este problema, se emplean técnicas como el encadenamiento, donde las colisiones se resuelven almacenando múltiples
elementos en la misma posición mediante listas enlazadas, o el rehashing, que re-calcula un nuevo índice para evitar las colisiones.

En resumen, los diccionarios son una herramienta poderosa en informática. Permiten almacenar y acceder eficientemente a datos a través de claves únicas. 
Su función hash y las técnicas de resolución de colisiones determinan su eficiencia. 

# Función hash

Una función de hash, es una función que toma una clave y la transforma en un valor numérico de longitud fija, conocido como el hash o valor hash. 
El propósito principal de una función de hash es mapear datos de manera eficiente para su uso en estructuras de datos como diccionarios o tablas hash. <br>
Es por ello que tienen que tener una serie de características que garanticen la mejor eficiencia, las cuales pueden ser: 
+ Unicidad: Cada clave tiene que tener un valor hash único asociado. Se debe garantizar que dos entradas distintas deben tener hashes diferentes. Sin embargo, en la practica, es
casi imposible garantizar una unicidad absoluta debido a la limitación de la lentitud fija del valor hash.
+ Eficiencia: La función debe ser "rápida" de calcular. Es deseable que el tiempo de cálculo del hash sea proporcional al tamaño de la entrada y no dependa del tamaño del espacio de salida.
+ Cambios mínimos: Pequeños cambios en la entrada debería generar cambios significativos en el valor hash resultante. Esto garantiza que dos entradas similares produzcan hashes diferentes, 
lo cual lo hace útil para detectar cambios en los datos o verificar su integridad.
+ Resistente a colisiones: Aunque es difícil evitar completamente las colisiones, una buena función de hash debe minimizar las colisiones. 
+ Determinismo: La función de hash debe set determinista, es decir, para una misma entrada, siempre debe producir el mismo hash. Esto es importante para garantizar la consistencia y
la integridad de lo datos almacenados.

<div align="center">
    <img width="65%" src="img/diccionario.svg">
</div>


# Tabla Hash

Una tabla hash, es una estructura de datos que asocia llaves o claves con valares. Donde la operación principal que soporta de manera eficiente es la búsqueda. Dicho acceso a los elementos
es a partir de una clave la cual se aplica una *funcion hash* devolviendo un número que identifica la posición donde la tabla hash localiza el valor deseado. <br>
Las tablas hash proveen tiempo constante de búsqueda promedio *O(1)*, sin importar el número de elementos en la tabla. Como se dijo es *promedio* ya que en se puede dar que el tiempo
de búsqueda llegue a ser *O(n)*, esto está ligado principalmente de que la función hash sea "buena". <br>
También vimos que se nos presenta otro problema que es el de las colisiones, es decir, dos elementos tienen el mismo índice en la tabla hash. Es por ello que se implementan distintas formas
para manejarlos. A continuación veremos dos implementaciones posibles:
+ Tabla de hash abierto con direccionamiento cerrado. 
+ Tabla de hash cerrado con direccionamiento abierto.

#### Tablas de hash abierto (Direccionamiento cerrado)

El hash abierto es un enfoque general en el manejo de colisiones en tablas hash en el cual los elementos colisionan-tes se manejan dentro de la propia tabla, sin utilizar estructuras externas. 
En lugar de almacenar los elementos directamente en la ubicación calculada por la función hash, se realiza una serie de cálculos adicionales para encontrar una ubicación alternativa cuando se
produce una colisión.

Una de las técnicas más comunes utilizadas en el hash abierto es el encadenamiento. En este método, cada celda de la tabla hash contiene una lista enlazada. Cuando se produce una colisión, 
el nuevo elemento se agrega a la lista correspondiente en la celda. De esta manera, varios elementos con la misma función hash se almacenan en la misma ubicación de la tabla, formando una cadena 
de elementos.

<div align="center">
    <img width="95%" src="img/encadenamiento.svg">
</div>

Otro factor importante a tener en cuenta es el **factor de carga** cuya ecuación es `α = n / m`, donde _n_ cantidad de elementos ingresados y _m_ es la capacidad de almacenamiento.
Dicho factor se utiliza para  medir la ocupación o la densidad de elementos en la tabla, el cual nos dará pie para realizar el rehasheo el cual consiste en re dimensionar la tabla, creando una nueva
mucho mas grande y redistribuyendo los elementos existentes en las nuevas ubicaciones. El factor de carga también se utilizara para las tablas de hash cerrado, el cual veremos a continuación.


#### Tablas de hash cerrado (Direccionamiento abierto)

Es una técnica utilizada en el manejo de colisiones en tablas hash donde los elementos colisionantes se manejan dentro de la propia estructura de la tabla hash, sin la necesidad de estructuras de
datos externas como listas enlazadas.
En el hash cerrado, cuando se produce una colisión (es decir, dos elementos tienen la misma posición calculada mediante la función hash), se busca una nueva posición dentro de la tabla 
utilizando una estrategia de probing lineal, cuadrático, hash doble, zona de desborde entre otras. <br>

Veamos de que se trata la estrategia **probing lineal**.
En este enfoque, cuando se produce una colisión, se busca la siguiente celda disponible en la tabla hash de manera secuencial. Si la celda está ocupada, se sigue avanzando hasta 
encontrar una celda vacía. La idea es explorar linealmente la tabla hasta encontrar un lugar libre para el nuevo elemento.

<div align="center">
    <img width="85%" src="img/probing.svg">
</div>

En la imagen anterior vemos que el elemento `<53420, 10>` aplicando la función debería estar ubicado en la posición `0` pero no puedo hacerlo porque ya había un elemento por lo cual empieza a buscar
el próximo lugar vacío y se inserta.

Otra estrategia es la de zona de desborde, el cual consiste en tener un porcentaje de la tabla en el cual se ubicaran todos los elemento colisionados y de esta forma mantendremos la tabla
principal limpia de desbordes.

<div align="center">
    <img width="55%" src="img/desborde.svg">
</div>
