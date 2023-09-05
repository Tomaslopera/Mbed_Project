Librerías Utilizadas: #include "mbed.h": Incluye la librería "mbed" que proporciona una abstracción para interactuar con el hardware, en este caso la tarjeta


Matriz de Teclado Numérico: Se define una matriz de teclado numérico representada por objetos DigitalIn para las filas y DigitalOut para las columnas.

Matriz de Traducción: Se define una matriz bidimensional de strings llamada teclado que asocia las teclas del teclado numérico con valores numéricos o letras.

Función escribir(): Esta función verifica qué tecla se ha presionado en la matriz de teclado numérico y 
devuelve el valor asociado a esa tecla según la matriz de traducción, utiliza dos ciclos For para reconocer segun la fila y la columna 
cual fue la tecla precionada en el teclado 

Función colorLed(): Esta función toma un valor hexadecimal ingresado por el usuario y lo convierte en valores de colores para controlar un LED RGB.
 a     Inicializa tres objetos PwmOut llamados ledR, ledG y ledB para controlar los LEDs rojo, verde y azul, respectivamente. Estos objetos permiten generar señales de modulación por ancho de pulso (PWM) para ajustar la intensidad luminosa de los LEDs. 

b.     Establece el período de la señal PWM para cada LED mediante los métodos period().

c. Lee una cadena de entrada de longitud 7 desde la comunicación serie utilizando pc.read(input, sizeof(input));. Esto se hace para recibir comandos de cambio de color en formato hexadecimal (#RRGGBB). 

d. Utiliza la función sscanf() para convertir la cadena hexadecimal en tres valores enteros: r (rojo), g (verde) y b (azul). Cada valor se convierte desde su representación hexadecimal de dos dígitos a su valor decimal correspondiente.

g. Ajusta las señales PWM de los LEDs utilizando el método write() en los objetos ledR, ledG y ledB. La inversión (1 - valor) se utiliza porque se leen las señales (binario) al contrario, una señal PWM de 1.0 apaga el LED y una señal de 0.0 lo enciende.

Función calculoNota(): Esta función toma una cadena que representa una nota numérica, la convierte en un valor double y luego determina la letra de nota correspondiente según los rangos especificados.

Función raices(): Esta función toma tres coeficientes ingresados por el usuario, los convierte en valores double y calcula las raíces de un polinomio de grado 2 utilizando la fórmula cuadrática.

MAIN 

se esta analizando la entrada del teclado (1,2 o 3) segun esto inicializa la funcion determinada, ya sea la de rgb calculo de raices o el de las notas, segun esto lee y guarda en arreglos los valores 
necesarios que empleara cada metodo, los coeficientes para el polinomio, el codigo hexadecimal para el RGB o la nota para analizar el rango.
