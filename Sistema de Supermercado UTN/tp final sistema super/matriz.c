//
// Created by marce on 11/22/2017.
//

#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int comparaMatrizEncript(float matA[2][5],float matB[2][5])
{
    int i,j;
    int cont=0;
    int flag = 0;

    for(i=0; i<2; i++)
    {
        for(j=0; j<5; j++)
        {
            if(matA[i][j] == matB[i][j])
            {
                cont++;
            }
        }
    }

    if(cont == 10)
    {
        flag = 1;
    }

    return flag;
}



void cargaYchequeaContrasenia (char A[])
{
    int rta1;
    int rta2;
    int i;
    char Aux[30]= {0}; /*a este arreglo le dimos una dimension mayor a 10 para prever el caso que el usuario ingrese mas de 10 letras en la contraseña
                  (en cuyo caso, dentro de la funcion de cargar se cuentan las letras y se le avisa al usuario que ingrese de nuevo la contraseña por
                   queno son 10, y no continúa adelante hasta que se corrija este error y se ingresen 10). Lo inicializamos en 0 para evitar que haya
                   basura en las posiciones no cargadas con la contraseña. */

    printf("\nIngrese su clave personal (solo letras, excluyendo la enie)(deben ser 10 letras, ni mas ni menos). \n");
    gets (Aux); //carga como palabra entera (no letra por letra, porque si no los enter luego de cada letra tambien se transformarian luego a Nros,
    // ya que al enter también le corresponde un código ascii). Lo carga en un arreglo aux para luego hacer los chequeos

    rta1 = ChequeaCantidadCaracteres (Aux);

    rta2 = ChequeaQueSeanLetras (Aux, 10);

    while ((rta1==1) || (rta2==1)) // flag 1 en cualquiera de las rtas significa que la contrasenia tiene distinta cantidad de letras de la requerida
        // o que se ingresaron caracteres que no son letras, y el programa no va a seguir avanzando hasta que el usuario no lo corrija
    {
        printf ("\nHa ingresado caracteres que no son letras o una cantidad de letras distinta de 10, vuelva a ingresar su clave personal (solo letras, excluyendo la enie)(deben ser 10 letras, ni mas ni menos))\n");
        gets (Aux);
        rta1 = ChequeaCantidadCaracteres (Aux); // vuelve a hacer los chequeos por si el usuario cometió un nuevo error
        rta2 = ChequeaQueSeanLetras (Aux, 10);
    }
    for (i=0; i<10; i++) //se sale del while y se sigue avanzando para la encriptacion cuando AMBAS rtas valen 0 (lo cual equivale a que la contraseña
        // cumple los requisitos: sólo consta de letras y son 10)
    {
        A[i]=Aux[i];//luego de este último chequeo,la contraseña ya se carga en el array char definitivo, el A, que es retornado ya cargado por parametro
    }
}

int ChequeaCantidadCaracteres (char Aux[])// funcion aux de la de carga, para chequear que la contraseña ingresada sea de 10 caracteres, ni más ni menos
{
    int flag=0;

    if (strlen (Aux)!=10)
    {
        flag=1;
    }

    return flag;
}

int ChequeaQueSeanLetras (char Aux[], int dim)// funcion aux de la de carga, para chequear que solo se hayan ingresado letras y no otros caracteres
{
    int flag=0;
    int i;

    for (i=0; i<dim; i++)
    {
        if ((Aux[i]<65)||((Aux[i]>90)&&(Aux[i]<97))||(Aux[i]>122))//por codigo ascii, las letras mayusculas van del 65 al 90 y las minusculas del 97
            // al 122. Por ende, si los caracteres son menores a 65, o mayores a 90 y menores a 97, o mayores a 122, es porque no son letras
        {
            flag=1;
        }
    }
    return flag;
}

void encriptaContras (char A[10], float encriptada[2][5])
{
    float B[10];
    float contrasenia[2][5];
    float testigo[2][2] = {{-3,4},{-1,2}}; //matriz de encriptacion

    pasarTodoAMinusculas (A); //por si el usuario ingresó mezcla de minúsculas y mayúsculas, pasamos todo a minúsculas para poder luego hacer mejor
    // la conversión a la tabla alfabética

    generarArregloAscii (A, B); //transforma la contraseña de letras a Nros por codigo ascii, pasando los elementos del array char a un array float

    ArregloAsciiATablaAlfabetica(B); //transforma el array de Nº segun codigo ascii a un array c/los Nº que le corresponde a c/u de acuerdo a la
    // tabla alfabetica que nos indicaron en la consigna del TP

    pasarArregloAmatriz (B, contrasenia); //carga la contraseña (ahora ya pasada a Nros) en una matriz, para luego encriptarla

    multiplicacionMatriz(testigo,contrasenia,encriptada); // encripta la contraseña
}

void mostrarArregloChar (char A[])
{
    int i=0;
    for (i=0; i<10; i++)
    {
        printf ("%c", A[i]);
    }
    printf("\n");
}

void pasarTodoAMinusculas (char A[])
{
    int i=0;
    for (i=0; i<10; i++)
    {
        A[i] = tolower (A[i]);
    }
}

void generarArregloAscii (char A[], float B[])
{
    int i=0;
    for (i=0; i<10; i++)
    {
        B[i]=A[i];
    }
}

void mostrarArregloFloat (float B[])
{
    int i=0;
    for (i=0; i<10; i++)
    {
        printf ("| %.0f |", B[i]); //en las funciones de mostrar array float usamos .0 para no mostrar los decimales y ensuciar el muestreo,
        // ya que sabemos que los arreglos son de Nros enteros (solo hay decimales al multiplicar por la inversa)
    }
    printf("\n------------------------------------------\n");
}

void ArregloAsciiATablaAlfabetica(float B[])
{
    int i;
    for (i=0; i<10; i++)
    {
        B[i]=B[i]-96;
    }
}

void pasarArregloAmatriz (float B[], float M[2][5])
{
    int indF=0;
    int indC=0;
    int indArray=0;

    for (indF=0; indF<2; indF++)
    {
        for (indC=0; indC<5; indC++)
        {
            M[indF][indC]=B[indArray];
            indArray++;
        }
    }
}

void mostrarMatriz (float M[2][5])
{
    int f=0;
    int c=0;

    printf("\nContenido de la matriz: \n");
    for(f=0; f<2; f++)
    {
        for(c=0; c<5; c++)
        {
            printf("%.2f ", M[f][c]);
        }
        printf("\n");
    }
}

void multiplicacionMatriz(float matriz1[2][2],float matriz2[2][5],float rta[2][5])
{
    int f;
    int c;

    for(f=0; f<2; f++)
    {
        for(c=0; c<5; c++)
        {
            rta[f][c]=(matriz1[f][0]*matriz2[0][c])+(matriz1[f][1]*matriz2[1][c]); //0 y 1 son valores fijos de filas y columnas porque siempre se
            //multiplica asi: de la matriz 1 (la testigo o la inversa de la testigo), 1º una columna y despues la otra,
            //y eso lo multiplico 1º por la 1ª fila y luego por la 2ª de la matriz 2 (la contraseña o la encriptada)
        }
    }
}

void desencriptaContras (float encriptada[2][5], char Ccontrasenia[10])
{
    float testigo[2][2] = {{-3,4},{-1,2}}; //matriz de encriptacion
    float inversaTestigo[2][2]; //matriz de desencriptacion
    float C[10];
    float Fcontrasenia[2][5];

    inversaMatrizTestigo(testigo, inversaTestigo);

    multiplicacionMatriz(inversaTestigo,encriptada, Fcontrasenia); //desencripta la contraseña

    pasarMatrizToArreglo (Fcontrasenia, C); // para desencriptar y poder mostrar la contraseña, se hace el paso inverso a cuando se encriptaba:
    // pasamos de 1 matriz a un arreglo float y luego a uno char

    pasarTablaAlfabeticaToAscii(C);

    pasarAsciiAChar (C, Ccontrasenia);
}

float determinanteMatrizTestigo(float matriz[2][2])
{
    float determinante=0;

    determinante=(matriz[0][0]*matriz[1][1]-matriz[0][1]*matriz[1][0]);

    return determinante;

}

void inversaMatrizTestigo(float testigo[2][2], float inversa[2][2])
{
    float determinante=0;
    int f=0;
    int c=0;

    /* usamos el metodo abreviado de obtención de la matriz inversa en matrices de orden 2: el primer y cuarto elemento cambian de lugar entre sí, y
       el segundo y el tercero son multiplicados por -1. Luego, se debe obtener la determinante y dividirla por cada numero de la matriz.*/

    determinante=determinanteMatrizTestigo(testigo);

    inversa[0][0]=testigo[1][1];  // se copia el valor del cuarto en el primero
    inversa[1][1]=testigo[0][0];  // se copia el valor del primero en el cuarto
    inversa[0][1]=testigo[0][1]*(-1);//se copia el valor del 2º Nº y se lo multiplica por -1
    inversa[1][0]=testigo[1][0]*(-1); // se copia el valor del 3º Nº y se lo multiplica por -1

    for(f=0; f<2; f++)
    {
        for(c=0; c<2; c++)
        {
            inversa[f][c]=inversa[f][c]/determinante; // divide c/u de los Nº de la matriz por la determinante
        }
    }
}

void pasarMatrizToArreglo (float M[2][5], float C[])
{
    int indF=0;
    int indC=0;
    int indArray=0;

    for (indF=0; indF<2; indF++)
    {
        for (indC=0; indC<5; indC++)
        {
            C[indArray] = M[indF][indC];
            indArray++;
        }
    }
}

void pasarTablaAlfabeticaToAscii(float C[])
{
    int i;
    for (i=0; i<10; i++)
    {
        C[i] = C[i]+96;
    }
}

void pasarAsciiAChar (float C[], char D[])
{
    int i=0;
    for (i=0; i<10; i++)
    {
        D[i] = C[i];
    }
}
