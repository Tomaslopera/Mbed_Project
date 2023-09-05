/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>
#include <string>

// Objeto para establecer la comunicación serial con el Pc
UnbufferedSerial serial(USBTX, USBRX, 9600);

// Objeto pa leer la matriz numerica
DigitalIn filas[] = {D2, D3, D4, D5};
DigitalOut columnas[] = {D6, D7, D8};

using namespace std;

string teclado[][3] = {
    {"1", "2", "3"},
    {"4", "5", "6"},
    {"7", "8", "9"},
    {"*", "0", "#"}
};

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
    
    return 0;
}


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

    return 0;
}

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
                string coeficientes[3];
                int i = 0;
                bool flag = true;
                while (flag){
                    coeficientes[i] = escribir();
                    i++;
                    if (i == 2){
                        string x = coeficientes[0];
                        string y = coeficientes[1];
                        string z = coeficientes[2];
                        raices(x, y, z);
                        flag = false;
                    }
                }                
            } else if (tecla == "2"){
                // Ingrese una Nota
                bool flag = true;
                while (flag){
                    string nota = escribir();
                    calculoNota(nota);
                    if ()
                }
            } else if (tecla == "3"){
                cout << "Hexadecimal: " << endl;
                std::string numeroHexadecimal = "";
                for (int i = 0; i < 6; i++){
                    cout << "-> " << numeroHexadecimal << endl;
                    numeroHexadecimal += escribir();
                }
                char inputHex[7];
                numeroHexadecimal.copy(inputHex, numeroHexadecimal.length());
                unsigned int colorValue;
                if (sscanf(inputHex, "%6x", &colorValue) == 1) {
                    printf("Valor hexadecimal válido \n");
                    colorLed(colorValue); // Controla el LED RGB con el valor hexadecimal almacenado
                } else {
                    printf("Valor hexadecimal no válido.\n");
                }
            } else {
                cout << "Número no válido" << endl;
            }
        }
    }
}






