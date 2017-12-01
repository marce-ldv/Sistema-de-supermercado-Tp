//
// Created by Marcelo Fabian on 29/10/2017.
//

#ifndef TP_2DO_TDA_GENERAL_H
#define TP_2DO_TDA_GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// STRUCT DEL CLIENTE:
typedef struct
{
    int id;
    char nombre[30];
    char apelllido[40];
    int tipoCliente; /// Prioridad 1:embarazada, 2:jubilado y 3:cliente común
    int medioPago;	 /// 1:efectivo, 2:crédito y 3:todos
    int cantArticulos; /// es el tiempo de ejecución
    int tiempoEspera;  /// es el tiempo de respuesta
    int tiempoProcesado; /// es el tiempo que ya fue procesado en la línea de caja
    int eliminado; // indica 1 o 0 si el cliente fue eliminado
} stCliente; //Estructura Persona

// STRUCT DEL USUARIO: (aca se guarda encriptada la contraseña)
typedef struct
{
    int id_cliente;//ID e id cliente tiene que ser el mismo valor, va en 2 archivos diferentes por que son 2 estucturas diferentes
    char usuario[20];
    float pass[2][5]; // guarda la contraseña encriptada
    int eliminado; // indica 1 o 0 si el cliente fue eliminado
    char nombre[30];
    char apelllido[30];
} stUsuario;

typedef struct
{
    stCliente p;
    struct nodo*izq;
    struct nodo*der;
} nodoArbol;

typedef struct{
    struct nodo2*cabeza;
    struct nodo2*cola;
}Cola;

typedef struct
{
    int nro_de_caja;
    char nombreCajero[40];
    int tipo_pago;                 //  1 efectivo, 2 crédito o débito, 3 todos
    int abiertaOcerrada;
    char algoritmoPlanificacion[30];  // debe informar que tipo de alg. de planificación utiliza la caja
    Cola fila;
} caja;

typedef struct{
    stCliente cliente;
    struct nodo2*ante;
    struct nodo2*sig;
}nodo2;

void _arbol(); //Prototipo de ayuda de busqueda

nodoArbol *initArbol();
nodoArbol *crearNodoArbol(stCliente cliente);
void preorder(nodoArbol *arbol);
void inorder(nodoArbol *arbol);
void postorder(nodoArbol *arbol);
nodoArbol *ingresarPersona();
nodoArbol *ingresarMuchasP(nodoArbol * Arbol);
nodoArbol * buscar_ID_Arbol(nodoArbol *arbol,int dato);
nodoArbol *buscarNombre(nodoArbol *arbol,char nom[30]);
nodoArbol *buscarApellido(nodoArbol *arbol,char apellido[30]);
int esHoja(nodoArbol *arbol);
int contarHojas(nodoArbol *arbol);
int mayor(int izq, int der);
int contarNiveles(nodoArbol *arbol);
nodoArbol *nodoMasIzq(nodoArbol *arbol);
nodoArbol *nodoMasDer(nodoArbol *arbol);
nodo2 * pasarArbolToLista (nodoArbol * arbol, nodo2 * lista);
nodo2 *agregarFinal(nodo2 *lista, nodo2 *nuevoNodo);
nodoArbol *insertarClientesToArbol(nodoArbol *a,stCliente cl);
nodoArbol *insertarClienteToArbol(nodoArbol *arbol,nodoArbol *nn);
nodoArbol * borrarNodoArbolNombre(nodoArbol * arbol,char nombre[]);
nodoArbol *borrarNodoArbol(nodoArbol *arbol,int dato);

void _caja(); //Prototipo de ayuda de busqueda
int CajasCargada(caja cajero[]);

int buscarMenorEnLasCajas(int cajasValidas[],caja cajero[],int validos);
int buscarCajasValidas(caja cajeros[],int posCajasValidas[],int tipoPago,int habilitadas);
void SJF(caja cajita);
void FIFO(caja cajita);
void ROUND_ROBIN(caja cajita);
void prioridades(caja cajita);
void mostrarCaja(caja cajero[],int valido);
void AgregarClienteAcola(caja cajero[],stCliente nuevoCliente,int validos);
caja CrearCaja(char nombre[],int numeroDeCaja,int TipoDePago);
int agregarCaja(caja cajero[],int valido);
void de_Lista_a_Caja(nodo2 * lista, caja cajero[8],int val);
void CajaAltaYBaja(caja cajero[],int val);
void SuperFuncionCaja(nodoArbol * arbol);
nodo2 * FuncionDePlanificacion(caja cajero[],int valido);
void menuSuperFuncionCaja();
nodo2 * ordenarPorPrioridad(caja  cajita);
void mostrarALLcajas(caja cajero[],int valido);
void mostrarCaja2(caja cajero);

void _lista(); //Prototipo de ayuda de busqueda

nodo2 *initLista();
nodo2 *crearNodoLista(stCliente c);
nodo2 *agregarPpio(nodo2 *lista,nodo2 *nuevoNodo);
nodo2 *borrarNodo(nodo2*lista,int dato);
nodo2 *buscarUltimo(nodo2*lista);
nodo2 *intercalar(nodo2 *l1,nodo2 *l2,nodo2 *l3);
void mostrarLista(nodo2 *lista);
nodo2 *borrarNodoPorNombre(nodo2 *lista, char nombre[]);
nodo2 * ordenar_Por_Prioridad_Uno(nodo2 * lista);
nodo2 * borrarNodoListaPorNombre(nodo2 *lista,char nombre[]);

void _cola(); //Prototipo de ayuda de busqueda

void InicCola(Cola*fila);
void AgregarPpioCola(Cola*fila,nodo2*nuevoNodo);
void Agregar_Final_Cola(Cola * fila, stCliente nuevoCliente);
int ColaVacia(Cola*fila);
int ExtraerCola(Cola*fila);
void LeerCola(Cola*fila);
int PrimeroCola(Cola*fila);
int contarCola(Cola *fila);
int menorCantPersonas(caja cajero[]);

void ordenarClientesSegunArticulo(stCliente aux[],int val);
nodo2 * extraerCLienteDecaja(caja * cajita);
nodo2 * ordenarPorCantidadArticulo(caja cajita);

void mostrarCola(Cola fila);

void _persona(); //Prototipo de ayuda de busqueda

int posicionMenor (stCliente A[], int pos,int val);
void ordenacionSeleccionPorArticulo(stCliente A[],int val);
stCliente CargarPersona();
void mostrarCliente(nodoArbol *arbol);
nodoArbol * ModificarCliente(nodoArbol * arbol);
void ordenarClientesSegunPrioridad(stCliente aux[],int val);
int posicionMenorprioridad(stCliente A[], int pos,int val);
void ordenacionSeleccionPorPrioridad (stCliente A[],int val);

void _usuario(); //Prototipo de ayuda de busqueda
void grabarClientesToArchivo(nodoArbol *arbol);
nodoArbol *leerClienteDelArchivo(nodoArbol *arbolito);
int contarClientesArchivo();
int comprobarIDCliente(stCliente cl);

void pasarListaAArreglo(stCliente arreglo[],nodo2 * lista);
int buscarCajaPorPago (caja cajero[],int tipoDePago);
int pasarCajaAArreglo(stCliente a[], caja  cajero);
nodo2 * pasarArregloALista(stCliente arreglo[],int validos);
void mostrarArreglo(stCliente a[],int validos);
void abrirOCerrarCaja(caja * cajita);
int CerrarUnaCaja(caja cajita[],int pos);
void abrirTodasLasCajas(caja cajita[20],int val);
void cerrarTodasLasCajas(caja cajita[20],int validos);
void cerrarTodasLasCajas1(caja cajita[20],int validos);

void Cargando(char tipo[60]);
void barra(int porc,int larg);
void Ordenar(caja  cajero[],int val);
#endif //TP_2DO_TDA_GENERAL_H
