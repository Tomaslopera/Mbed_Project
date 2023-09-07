
**INTEGRANTES: Tomas Lopera, Pedro Sierra**

**Librerías Utilizadas**: #include "mbed.h": Incluye la librería "mbed" que proporciona una abstracción para interactuar con el hardware, en este caso la tarjeta


**Matriz de Teclado Numérico:** Se define una matriz de teclado numérico representada por objetos DigitalIn para las filas y DigitalOut para las columnas.

```
 string teclado[][3] = {
      {"1", "2", "3"},
      {"4", "5", "6"},
      {"7", "8", "9"},
      {"*", "0", "#"}
  };
```

**Matriz de Traducción:** Se define una matriz bidimensional de strings llamada teclado que asocia las teclas del teclado numérico con valores numéricos o letras.

**Función escribir():** Esta función verifica qué tecla se ha presionado en la matriz de teclado numérico y 
devuelve el valor asociado a esa tecla según la matriz de traducción, utiliza dos ciclos For para reconocer segun la fila y la columna 
cual fue la tecla precionada en el teclado 

```
string escribir() {

    ThisThread::sleep_for(500ms);

    for (int i=0; i<3; i++) {
        columnas[i] = 0;

        for (int j=0; j<4; j++) {
            if (filas[j]==0) {
                columnas[i] = 1;
                return teclado[j][i];
            }
        }

        columnas[i] = 1;
    }

    return "";
}
```

**Función colorLed():** Esta función toma un valor hexadecimal ingresado por el usuario y lo convierte en valores de colores para controlar un LED RGB. <br>
a.     Inicializa tres objetos PwmOut llamados ledR, ledG y ledB para controlar los LEDs rojo, verde y azul, respectivamente. Estos objetos permiten generar señales de modulación por ancho de pulso (PWM) para ajustar la intensidad luminosa de los LEDs.

b.     Establece el período de la señal PWM para cada LED mediante los métodos period().

c. Lee una cadena de entrada de longitud 7 desde la comunicación serie utilizando pc.read(input, sizeof(input));. Esto se hace para recibir comandos de cambio de color en formato hexadecimal (#RRGGBB). 

d. Utiliza la función sscanf() para convertir la cadena hexadecimal en tres valores enteros: r (rojo), g (verde) y b (azul). Cada valor se convierte desde su representación hexadecimal de dos dígitos a su valor decimal correspondiente.

g. Ajusta las señales PWM de los LEDs utilizando el método write() en los objetos ledR, ledG y ledB. La inversión (1 - valor) se utiliza porque se leen las señales (binario) al contrario, una señal PWM de 1.0 apaga el LED y una señal de 0.0 lo enciende.


```
void colorLed(unsigned int colorValue) {
    PwmOut ledR(LED1);
    PwmOut ledG(LED2);
    PwmOut ledB(LED3);

    ledR.period(0.01);
    ledG.period(0.01);
    ledB.period(0.01);

    unsigned char red, green, blue;
    red = (1 - (float)((colorValue >> 16) & 0xFF) / 255.0f);
    green = (1 - (float)((colorValue >> 8) & 0xFF) / 255.0f);
    blue = (1 - (float)(colorValue & 0xFF) / 255.0f);

    ledR = red;
    ledG = green;
    ledB = blue;
}
```

**Función calculoNota():** Esta función toma una cadena que representa una nota numérica, la convierte en un valor double y luego determina la letra de nota correspondiente según los rangos especificados.

```
string calculoNota(string nota){

    double numero = std::stod(nota);

    if (numero >= 0 && numero <= 3) {
        std::cout << "Nota: A" << std::endl;
    } else if (numero > 3 && numero <= 4) {
        std::cout << "Nota: B" << std::endl;
    } else if ( numero> 4 && numero <= 5) {
        std::cout << "Nota: C" << std::endl;
    } else if (numero > 5 && numero <= 7) {
        std::cout << "Nota: D" << std::endl;
    } else if (numero > 7 && numero < 9) {
        std::cout << "Nota: E" << std::endl;
    } else if (numero >= 9 && numero <= 10) {
        std::cout << "Nota: F" << std::endl;
    } else {
        std::cout << "Nota fuera de rango. Debe estar entre 0 y 10." << std::endl;
    }
    
    return "";
}
```

**Función raices():** Esta función toma tres coeficientes ingresados por el usuario, los convierte en valores double y calcula las raíces de un polinomio de grado 2 utilizando la fórmula cuadrática.

```
string raices(string x ,string y, string z){

    double a = std::stod(x);
    double b = std::stod(y);
    double c = std::stod(z);

    double discriminante, raiz1, raiz2;

    // Calcular el discriminante
    discriminante = b * b - 4 * a * c;

    // Calcular las raíces utilizando la fórmula general
    if (discriminante >= 0) {
        raiz1 = (-b + sqrt(discriminante)) / (2 * a);
        raiz2 = (-b - sqrt(discriminante)) / (2 * a);

        std::cout << "Las raíces son: " << raiz1 << " y " << raiz2 << std::endl;
    } else {
        double parteReal = -b / (2 * a);
        double parteImaginaria = sqrt(-discriminante) / (2 * a);

        std::cout << "Raíces complejas: " << parteReal << " + " << parteImaginaria << "i y " << parteReal << " - " << parteImaginaria          << "i" << std::endl;
    }

    return "";
}
```

**MAIN** 

Se esta analizando la entrada del teclado (1,2 o 3) segun esto inicializa la funcion determinada, ya sea la de rgb calculo de raices o el de las notas, segun esto lee y guarda en arreglos los valores necesarios que empleará cada método, los coeficientes para el polinomio, el codigo hexadecimal para el RGB o la nota para analizar el rango. Se implementa una bandera para que se repita un while en cada caso para que no se salga y la bandera cambia a false cuando se cumple cierta condición necesaria para que el sistema termine.

```

```
