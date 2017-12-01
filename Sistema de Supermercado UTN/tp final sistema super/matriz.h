//
// Created by marce on 11/22/2017.
//

#ifndef TP_2DO_MATRIZ_H
#define TP_2DO_MATRIZ_H

void cargaYchequeaContrasenia (char A[]);
int ChequeaCantidadCaracteres (char Aux[]);
int ChequeaQueSeanLetras (char Aux[], int dim);
void encriptaContras (char A[10], float encriptada[2][5]);
void mostrarArregloChar (char A[]);
void pasarTodoAMinusculas (char A[]);
void generarArregloAscii (char A[], float B[]);
void mostrarArregloFloat (float B[]);
void ArregloAsciiATablaAlfabetica(float B[]);
void pasarArregloAmatriz (float B[], float M[2][5]);
void mostrarMatriz (float M[2][5]);
void multiplicacionMatriz(float matriz1[2][2],float matriz2[2][5],float rta[2][5]);
void desencriptaContras (float encriptada[2][5], char Ccontrasenia[10]);
float determinanteMatrizTestigo(float matriz[2][2]);
void inversaMatrizTestigo(float testigo[2][2], float inversa[2][2]);
void pasarMatrizToArreglo (float M[2][5], float C[]);
void pasarTablaAlfabeticaToAscii(float C[]);
void pasarAsciiAChar (float C[], char D[]);

#endif //TP_2DO_MATRIZ_H
