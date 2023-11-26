
**INTEGRANTES:**

 > Tomás Lopera

 > Pedro Sierra

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

1. **double numero = std::stod(nota);**: Esta línea convierte la cadena nota en un número de punto flotante (double) utilizando std::stod, que es una función que convierte una cadena en su equivalente numérico en punto flotante.

2. **La serie de if-else if statements:** Estas son declaraciones condicionales que evalúan el valor de numero y determinan la calificación correspondiente:

- Si numero está entre 0 y 3 (ambos inclusive), se imprime "Nota: A".
- Si numero está entre 3 (exclusivo) y 4 (inclusive), se imprime "Nota: B".
- Si numero está entre 4 (exclusivo) y 5 (inclusive), se imprime "Nota: C".
- Si numero está entre 5 (exclusivo) y 7 (inclusive), se imprime "Nota: D".
- Si numero está entre 7 (exclusivo) y 9 (exclusivo), se imprime "Nota: E".
- Si numero está entre 9 (inclusive) y 10 (inclusive), se imprime "Nota: F".
- Si ninguna de las condiciones anteriores se cumple, se imprime "Nota fuera de rango. Debe estar entre 0 y 10.".

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

**Función raices():** Esta función toma los tres coeficientes ingresados por el usuario, los convierte en valores double y calcula las raíces de un polinomio de grado 2 utilizando la fórmula cuadrática. 

1. **double a = std::stod(x);, double b = std::stod(y);, double c = std::stod(z);**: Estas líneas convierten las cadenas **x, y** y **z** en números de punto flotante (double) utilizando std::stod, que es una función que convierte una cadena en su equivalente numérico en punto flotante.

2. **double discriminante, raiz1, raiz2;**: Se declaran tres variables de punto flotante: discriminante, raiz1 y raiz2. El discriminante es una parte crucial en la fórmula cuadrática y se utiliza para determinar el tipo de raíces que tiene la ecuación cuadrática.

3. **discriminante = b * b - 4 * a * c;**: Se calcula el discriminante utilizando la fórmula b^2 - 4ac. Esto determina si las raíces son reales o complejas.

4. **if** **(discriminante >= 0) {...} else {...}**: Esta estructura de control if-else se utiliza para manejar dos casos diferentes:

4.1. **Caso 1 (Discriminante no negativo)**: Si el discriminante es mayor o igual a cero, entonces las raíces son reales. En este caso, se calculan las dos raíces utilizando la fórmula cuadrática estándar.

4.2. **Caso 2 (Discriminante negativo):** Si el discriminante es negativo, entonces las raíces son complejas. Se calculan tanto la parte real como la parte imaginaria de las raíces complejas.

En ambos casos, se imprime el resultado en la consola.

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

        std::cout << "Raíces complejas: " << parteReal << " + " << parteImaginaria << "i y " << parteReal << " - " << parteImaginaria << "i" << std::endl;
    }

    return "";
}
```

**MAIN** 

Se esta analizando la entrada del teclado (1,2 o 3) segun esto inicializa la funcion determinada, ya sea la de rgb calculo de raices o el de las notas, segun esto lee y guarda en arreglos los valores necesarios que empleará cada método, los coeficientes para el polinomio, el codigo hexadecimal para el RGB o la nota para analizar el rango. Se implementa una bandera para que se repita un while en cada caso según seleccione el usuario para que no se salga y la bandera cambia a false cuando se cumple cierta condición necesaria para que el sistema termine.

1. **string tecla = "";**: Declara una cadena tecla y la inicializa como una cadena vacía.

2. **while (true) {...}**: Inicia un bucle infinito, lo que significa que el programa continuará ejecutándose indefinidamente hasta que se interrumpa manualmente.

3. **tecla = escribir();**: Llama a una función escribir() que es esponsable de obtener la entrada del usuario mediante el teclado matricial y asigna el resultado a la variable tecla.

4. **if (tecla != "") {...}**: Verifica si la entrada del usuario no es una cadena vacía. Si es así, ejecuta el bloque de código dentro del if.

5. Dentro del bloque if (tecla != "") {...}, el programa realiza diferentes acciones según el valor de tecla:

- Si tecla es "1", el programa espera recibir tres coeficientes y luego calcula e imprime las raíces de la ecuación cuadrática.

- Si tecla es "2", el programa espera recibir una nota y luego calcula e imprime la calificación correspondiente.

- Si tecla es "3", el programa espera recibir un número hexadecimal y luego llama a la funcion colorLed que se encarga de encender un led rgb a partir de los datos ingresados por el usuario.

- Si tecla no coincide con ninguna de las opciones anteriores, el programa imprime "Número no válido".

6. return 0;: La función main retorna 0, indicando que el programa finalizó correctamente.

```
int main()
{
    string tecla = "";
    while (true) {
        //     cout << "Selecciona una opción: \n" << endl;
        //     cout << "1. Aplicación que calcule las raices del polinomio de grado 2 \n" << endl;
        //     cout << "2. Ingreso de una Nota N con devolución de una letra \n" << endl;
        //     cout << "3. Colores en un LED rgb \n" << endl;
        tecla = escribir();
        if (tecla != "") {
            cout << tecla << endl;
            if (tecla == "1"){
                // Ingresa tres coeficientes               
                std:string coeficientes[3];
                int i = 0;
                bool flag = true;
                while (flag){
                    coeficientes[i++] = escribir();
                    if (i == 2){
                        string x = coeficientes[0];
                        string y = coeficientes[1];
                        string z = coeficientes[2];
                        raices(x, y, z);
                        if (x != "" && y != "" && z != ""){
                            i++;
                            flag = false;
                        }
                    }
                }                
            } else if (tecla == "2"){
                // Ingrese una Nota
                string nota = "";
                bool flag = true;
                while (flag){
                    nota = escribir();
                    if (nota != ""){
                        calculoNota(nota);
                        flag = false;
                    }
                }
            } else if (tecla == "3"){
                // LED rgb
                std::string numeroHexadecimal = "";
                int i = 0;
                bool flag = true;
                while (flag){
                    numeroHexadecimal += escribir();
                    if (numeroHexadecimal != ""){
                        cout << numeroHexadecimal << endl;
                        i++;
                    }
                    if (numeroHexadecimal.length() == 6){
                        char inputHex[7];
                        numeroHexadecimal.copy(inputHex, numeroHexadecimal.length() + 1);
                        unsigned int colorValue;
                        if (sscanf(inputHex, "%6x", &colorValue) == 1) {
                            printf("Valor hexadecimal válido \n");
                            colorLed(colorValue); // Controla el LED RGB con el valor hexadecimal almacenado
                        } else {
                            printf("Valor hexadecimal no válido.\n");
                        }
                        if (i == 5){
                            flag = false;
                        }
                    }
                }
            } else {
                cout << "Número no válido" << endl;
            }
        }
    }
}
```
