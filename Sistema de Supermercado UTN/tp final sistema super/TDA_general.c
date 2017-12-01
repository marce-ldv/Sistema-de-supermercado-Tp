//
// Created by Marcelo Fabian on 29/10/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TDA_general.h"

const char archiRegPersonas[]="registros.dat"; //Registro de personas (clientes del supermercado)

void _arbol()
{

}

nodoArbol *initArbol()
{
    return NULL;
}

nodoArbol *crearNodoArbol(stCliente cliente)
{
    nodoArbol *nuevoNodo=(nodoArbol*)malloc(sizeof(nodoArbol));
    strcpy(nuevoNodo->p.nombre,cliente.nombre);
    strcpy(nuevoNodo->p.apelllido,cliente.apelllido);
    nuevoNodo->p.medioPago=cliente.medioPago;
    nuevoNodo->p.tipoCliente=cliente.tipoCliente;
    nuevoNodo->p.cantArticulos=cliente.cantArticulos;
    nuevoNodo->p.tiempoEspera=cliente.tiempoEspera;
    nuevoNodo->p.tiempoProcesado=cliente.tiempoProcesado;
    nuevoNodo->p.id=cliente.id;
    nuevoNodo->p.eliminado=cliente.eliminado;
    nuevoNodo->izq=NULL;
    nuevoNodo->der=NULL;
    return nuevoNodo;
}


void preorder(nodoArbol *arbol)
{
    if(arbol==NULL)
    {
        printf(""); //Esta vacio, por lo tanto simplemente muestro un guion
    }
    else
    {
        mostrarCliente(arbol);
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void inorder(nodoArbol *arbol)
{
    if(arbol==NULL)
    {
        printf("");
    }
    else
    {
        inorder(arbol->izq);
        mostrarCliente(arbol);
        inorder(arbol->der);
    }
}

void postorder(nodoArbol *arbol)
{
    if(arbol==NULL)
    {
        printf("");
    }
    else
    {
        postorder(arbol->izq);
        postorder(arbol->der);
        mostrarCliente(arbol);
    }
}

nodoArbol * buscar_ID_Arbol(nodoArbol *arbol,int dato)
{
    nodoArbol *rta=NULL;

    if(arbol!=NULL)
        if(dato==arbol->p.id)
            rta=arbol;
        else if(dato > arbol->p.id)
            rta=buscar_ID_Arbol(arbol->der,dato);
        else
            rta=buscar_ID_Arbol(arbol->izq,dato);
    return rta;
}

nodoArbol *buscarApellido(nodoArbol *arbol,char apellido[30])
{
    nodoArbol *rta=NULL;

    if(arbol!=NULL)
        if(strcmp(apellido,arbol->p.apelllido)==0)
            rta=arbol;
        else
        {
            rta=buscarApellido(arbol->der,apellido);
            rta=buscarApellido(arbol->izq,apellido);
        }

    return rta;
}

nodoArbol *buscarNombre(nodoArbol *arbol,char nom[30])
{
    nodoArbol *rta=NULL;

    if(arbol!=NULL)
        if(strcmp(nom,arbol->p.nombre)==0)
            rta=arbol;
        else
        {
            rta=buscarNombre(arbol->der,nom);
            rta=buscarNombre(arbol->izq,nom);
        }

    return rta;
}


int esHoja(nodoArbol *arbol)
{
    int rta=0;

    if(arbol!=NULL)
        if((arbol->der==NULL) && (arbol->izq==NULL))
            rta= 1; //es hoja
    return rta;
}

int contarHojas(nodoArbol *arbol)
{
    int rta;

    if(esHoja(arbol)==0)
        rta =contarHojas(arbol->izq)+contarHojas(arbol->der);
    else
        rta= 1;

    return rta;
}
//metodo creado para considerar que lado tiene mas niveles en el arbol
int mayor(int izq, int der)
{
    int rta=0;

    if(izq > der)
    {
        rta=izq;
    }
    else
    {
        rta=der;
    }
    return rta;
}

int contarNiveles(nodoArbol *arbol)
{

    int nivel=0;
    if(arbol==NULL)
    {
        nivel =0;
    }
    else
    {
        if(arbol->izq!=NULL || arbol->der!=NULL)
            nivel = 1 + mayor(contarNiveles(arbol->izq),contarNiveles(arbol->der));
        else if(esHoja(arbol))
        {
            nivel=1;
        }
    }
    return nivel;
}

nodoArbol *nodoMasIzq(nodoArbol *arbol)
{
    nodoArbol *rta=NULL;
    if(arbol)
    {
        if(arbol->izq==NULL)
        {
            rta=arbol; //en el primer caso devolves la raiz,sino el subarbol
        }
        else
        {
            rta=nodoMasIzq(arbol->izq);
        }
    }
    return rta; //return arbol o rta????
}

nodoArbol *nodoMasDer(nodoArbol *arbol)
{
    nodoArbol *rta=NULL;
    if(arbol)
    {
        if(arbol->der==NULL)
        {
            rta=arbol;
        }
        else
        {
            rta=nodoMasDer(arbol->der);
        }
    }
    return rta;
}

nodoArbol *insertarClienteToArbol(nodoArbol *arbol,nodoArbol *nn){

    if(arbol==NULL)
    {
        arbol=nn;
    }
    else
    {
        if(strcmp(nn->p.nombre,arbol->p.nombre)>0)
        {
            arbol->der=insertarClienteToArbol(arbol->der,nn);
        }
        else
        {
            arbol->izq=insertarClienteToArbol(arbol->izq,nn);
        }
    }
    return arbol;

}

nodoArbol *insertarClientesToArbol(nodoArbol *a,stCliente cl)
{
    nodoArbol *nodoCliente = crearNodoArbol(cl);
    a=insertarClienteToArbol(a,nodoCliente);
    return a;
}

nodoArbol *borrarNodoArbol(nodoArbol *arbol,int dato)
{
    if(arbol != NULL)
    {
        if(arbol->p.cantArticulos < dato) //Busca nodo a borrar
        {
            arbol->der=borrarNodoArbol(arbol->der,dato);
        }
        else
        {
            if(arbol->p.cantArticulos> dato)
            {

                arbol->izq=borrarNodoArbol(arbol->izq,dato);
            }
        }

        //borra un nodo hoja, es decir sin hijos
        if((esHoja(arbol)) && (arbol->p.cantArticulos==dato))
        {
            free(arbol);
            arbol=NULL;
        }
        else
        {
            if((arbol->der != NULL)&&(arbol->p.cantArticulos==dato)) //Si no es hoja, borrar un nodo con hijos
            {
                nodoArbol * NMI = nodoMasIzq(arbol->der);
                arbol->p.cantArticulos = NMI->p.cantArticulos;
                strcpy(arbol->p.nombre,NMI->p.nombre);
                arbol->der = borrarNodoArbol(arbol->der,NMI->p.cantArticulos);
            }
            else if((arbol->izq != NULL)&&(arbol->p.cantArticulos==dato))
            {
                nodoArbol * NMD = nodoMasDer(arbol->izq);
                arbol->p.cantArticulos = NMD->p.cantArticulos;
                strcpy(arbol->p.nombre,NMD->p.nombre);
                arbol->izq = borrarNodoArbol(arbol->izq,NMD->p.cantArticulos);
            }
        }
    }
    return arbol;
}

nodoArbol * borrarNodoArbolNombre(nodoArbol * arbol,char nombre[])
{
    if(arbol != NULL) {
        if((strcmpi(arbol->p.nombre,nombre)<0)) //Busca nodo a borrar
        {
            arbol->der=borrarNodoArbolNombre(arbol->der,nombre); //si el primero es mayor a 0 va a la derecha
        }
        else
        {
            if((strcmp(arbol->p.nombre,nombre)>0)) {

                arbol->izq=borrarNodoArbolNombre(arbol->izq,nombre);
            }
        }

        //borra un nodo hoja, es decir sin hijos
        if((esHoja(arbol)==1) && (strcmpi(arbol->p.nombre,nombre)==0)) {
            free(arbol);
            arbol=NULL;
        }
        else
        {
            if((arbol->der != NULL)&& ((strcmpi(arbol->p.nombre,nombre)==0)))//Si no es hoja, borrar un nodo con hijos
            {
                nodoArbol * NMI = nodoMasIzq(arbol->der);
                arbol->p=NMI->p;
                arbol->der = borrarNodoArbolNombre(arbol->der,NMI->p.nombre);
            }
            else if((arbol->izq != NULL)&&(strcmpi(arbol->p.nombre,nombre)==0))
            {
                nodoArbol * NMD = nodoMasDer(arbol->izq);
                arbol->p=NMD->p;
                arbol->izq = borrarNodoArbolNombre(arbol->izq,NMD->p.nombre);
            }
        }
    }
    return arbol;
}


nodo2 * borrarNodoListaPorNombre(nodo2 *lista,char nombre[]){
    if(lista!=NULL)
    {
        stCliente aux2= lista->cliente;
        if(strcmpi(nombre,aux2.nombre)==0)
        {
            nodo2*aux=lista;
            lista=lista->sig;
            free(aux);
        }
        else
        {
            nodo2 * prox;
            nodo2 * seg=lista->sig;
            nodo2 * ante=lista;
            aux2=seg->cliente;
            //recorro la lista
            while(seg!=NULL && (strcmpi(aux2.nombre,nombre)!=0))
            {
                ante=seg;
                seg=seg->sig;
                aux2=seg->cliente;
            }
            if(strcmpi(aux2.nombre,nombre)==0)
            {
                prox=seg->sig;
                ante->sig=prox;
                prox->ante=ante;
                free(seg);
            }
        }
    }

    return lista;
}

caja CrearCaja(char nombre[],int numeroDeCaja,int TipoDePago)
{
    int rp=5;
    caja cajita;
    InicCola(&cajita.fila);
    strcpy(cajita.nombreCajero,nombre);
    cajita.nro_de_caja=numeroDeCaja;
    cajita.tipo_pago=TipoDePago;
    printf("Que algoritmo de plaficacion desea ingresar?\n");
    printf("1: FIFO\n");
    printf("2: SJF\n");
    printf("3: PRIORIDAD\n");
    printf("4: ROUND ROBIN\n");
    while(rp>4)
    {
        printf("Entras al while? \n");
        fflush(stdin);
        scanf("%d",&rp);
        if(rp==1)
        {
            strcpy(cajita.algoritmoPlanificacion,"fifo");
        }
        else if(rp==2)
        {
            strcpy(cajita.algoritmoPlanificacion,"sjf");
        }
        else if(rp==3)
        {
            strcpy(cajita.algoritmoPlanificacion,"prioridad");
        }
        else if(rp==4)
        {
            strcpy(cajita.algoritmoPlanificacion,"rr");
        }
        else
        {
            printf("ingrese una opcion validad\n");
            printf("1: FIFO\n");
            printf("2: SJF\n");
            printf("3: PRIORIDAD\n");
            printf("4: ROUND ROBIN\n");
        }
    }
    cajita.abiertaOcerrada=1;

    return cajita;
}

int agregarCaja(caja cajero[],int valido)
{
    int rp=4;
    int pos=valido-1;
    char nombre[100];
    int tipoPago;

    printf("ingrese el nombre del cajero: \n");
    fflush(stdin);
    gets(nombre);
    printf("ingrese el tipo de pago: \n");
    printf("1: Efectivo \n");
    printf("2: Credito o Debito\n");
    printf("3: Todos los medios \n");
    while(rp>3)
    {
        fflush(stdin);
        scanf("%d",&rp);
        if(rp==1)
        {
            tipoPago=1;
        }
        else if(rp==2)
        {
            tipoPago=2;
        }
        else if(rp==3)
        {
            tipoPago=3;
        }
        else
        {
            printf("ingrese una opcion validad\n");
            printf("1: Efectivo \n");
            printf("2: Credito o Debito\n");
            printf("3: Todos los medios \n");
        }
    }

    cajero[pos+1]=CrearCaja(nombre,1,valido+1);

    return valido+1;
}

void CajaAltaYBaja(caja cajero[],int val)
{
    int pos=val+1;
    printf("que caja desea modificar?");
    while(pos>val)
    {
        scanf("%d",&pos);
        if(pos>val)
        {
            printf("ingrese una posicion valida, la cantidad de cajas que hay es de: %d \n",val);
        }
    }
    int op;
    printf("Seleccione una opcion:\n ");
    printf("1~ Dar de alta la caja \n");
    printf("2~ Dar de baja la caja \n");
    scanf("%i",&op);
    switch(op)
    {
        case 1: // dar de alta la caja que fue dado de baja en algun momento
            system("cls");

            if(cajero[pos].abiertaOcerrada == 1)
            {
                printf("La caja %d ya se encontraba dado de alta \n",pos);
            }
            else
            {
                cajero[pos].abiertaOcerrada= 1;
                printf("Acaba de dar de alta a la caja %d \n",pos);
            }
            system("pause");
            system("cls");
            break;

        case 2: // dar de baja al usuario (borrado logico, no lo borra del archivo, sólo lo deja como eliminado, inactivo)
            system("cls");

            if(cajero[pos].abiertaOcerrada == 0)
            {
                printf("La caja %d ya se encontraba dado de baja",pos);
            }
            else
            {
                cajero[pos].abiertaOcerrada = 0;
                printf("Acaba de dar de alta a la caja %d\n",pos);
            }

            system("pause");
            system("cls");
            break;

        default:
            system("cls");
            printf("Ha ingresado una opción inválida. \n");
            printf("Seleccione una opcion:\n ");
            printf("1~ Dar de alta la caja \n");
            printf("2~ Dar de baja la caja \n");
            system("pause");
            system("cls");
            break;
    }
}

void cola()
{

}

void InicCola(Cola*fila)
{
    fila->cabeza=NULL;
    fila->cola=NULL;
}


void AgregarPpioCola(Cola*fila,nodo2*nuevoNodo)
{
    if(fila->cabeza == NULL)
    {
        fila->cabeza=nuevoNodo;
        fila->cola=nuevoNodo;
    }
    else
    {
        nodo2*aux=fila->cabeza; //la nueva cabeza es auxiliar
        nuevoNodo->sig=fila->cabeza;
        aux->ante=nuevoNodo;
        fila->cabeza=nuevoNodo;
    }
}

void AgregarFinalCola(Cola*fila,nodo2*nuevoNodo)
{
    if(fila->cabeza == NULL)
    {
        fila->cabeza=nuevoNodo;
        fila->cola=nuevoNodo;
    }
    else
    {
        nodo2* cola=fila->cola;
        cola->sig =  nuevoNodo;
        nuevoNodo->ante=cola;
        fila->cola=nuevoNodo;
    }
}
void Agregar_Final_Cola(Cola * fila, stCliente nuevoCliente)
{
    nodo2 * nuevo=crearNodoLista(nuevoCliente);

    if(!fila->cabeza)
    {
        fila->cabeza=nuevo;
    }
    else
    {
        fila->cabeza=agregarFinal(fila->cabeza,nuevo);
    }

    fila->cola=nuevo;
}
int ExtraerCola(Cola*fila)
{
    int guardar;
    nodo2*eliminado;
    if(fila->cabeza==fila->cola)
    {
        eliminado=fila->cabeza;
        guardar = eliminado->cliente.tipoCliente;
        //actualizo la cabeza y la cola en null por que estan vacias
        fila->cabeza=NULL;
        fila->cola=NULL;
        free(eliminado);
    }
    else
    {
        //guardo la cabeza en una variable auxiliar para futuramente eliminarla con free()
        eliminado=fila->cabeza;
        nodo2*nodoSig=eliminado->sig;
        nodoSig->ante=NULL;

        fila->cabeza=nodoSig;
        free(eliminado);
    }

    return guardar;

}

int PrimeroCola(Cola*fila)
{
    int rta;
    if(fila->cabeza)
    {
        nodo2*aux=fila->cabeza;
        rta=aux->cliente.tipoCliente;
    }
    return rta;
}

int ColaVacia(Cola*fila)
{
    int rta=0;
    if(fila->cabeza!=NULL)
    {
        rta=1; //devuelve 1 si tiene datos
    }
    return rta;
}

int contarCola(Cola *fila){
    int cant=0;
    nodo2 * seg=fila->cabeza;
    if(seg==NULL){
        cant=0;
    }else{
        while(seg != NULL){
            seg=seg->sig;
            cant++;
        }
    }

    return cant;
}

int menorCantPersonas(caja cajero[]){  //falta prototipo

    int posM,i=0;

    while(i<7){
        if(cajero[i].abiertaOcerrada == 1){ ///Si la caja esta cerrada.. si es 1 cerrada, 0 abierta
            ///puts("La caja se encuentra cerrada.. \n");
            i++;
        }else{
            while(cajero[i].fila.cabeza != NULL){
                ///La caja esta abierta
                int cant=contarCola(&cajero[i].fila);
                i++;
                if(cant < posM){
                    posM=i;
                }
            }
        }
    }

    ///Retorna la posicion de la caja con menos gente
    return posM;
}

nodo2 * pasarArbolToLista (nodoArbol * arbol, nodo2 * lista)
{
    nodo2 * aux=NULL;
    if(arbol!=NULL)
    {

        lista=pasarArbolToLista(arbol->izq,lista);

        aux=crearNodoArbol(arbol->p);
        lista=agregarFinal(lista, aux);

        lista=pasarArbolToLista(arbol->der,lista);
    }
    return lista;
}

void de_Lista_a_Caja(nodo2 * lista, caja cajero[],int val)///funcion principal
{
    nodo2 * aux=lista; //la recibe bien
    nodo2 * aux2;
    nodo2 * aux3=initLista();
    int validos;
    int posMenor;
    int cajasvalidas[val];
    if(lista==NULL) {

    }
    else {
        validos=buscarCajasValidas(cajero,cajasvalidas,aux->cliente.medioPago,val);
        posMenor=buscarMenorEnLasCajas(cajasvalidas,cajero,validos);
        aux2=lista;
        Agregar_Final_Cola(&cajero[posMenor].fila,aux2->cliente);
        //AgregarFinalCola(&cajero[posMenor].fila,aux2);
        de_Lista_a_Caja(aux->sig,cajero,val);
    }
}
void Ordenar(caja cajero[],int val)
{
    int i=0;
    nodo2 * aux=initLista();
    nodo2 * aux2;
    while(i<val)
    {
        if((strcmpi(cajero[i].algoritmoPlanificacion,"sjf")==0)&&(cajero[i].fila.cabeza!=NULL))
        {
            aux=ordenarPorCantidadArticulo(cajero[i]);
            cajero[i].fila.cabeza=aux;
            aux2=buscarUltimo(aux);
            cajero[i].fila.cola=aux2;
        }
        else if((strcmpi(cajero[i].algoritmoPlanificacion,"prioridad")==0)&&(cajero[i].fila.cabeza!=NULL))
        {
            aux=ordenarPorPrioridad(cajero[i]);
            cajero[i].fila.cabeza=aux;
            //mostrarLista(aux);
            //system("pause");
            aux2=buscarUltimo(aux);
            cajero[i].fila.cola=aux2;
        }
        i++;
    }

}
int buscarCajasValidas(caja cajeros[],int posCajasValidas[],int tipoPago,int habilitadas)///Esta funcion devuelve un arreglo con las posiciones de las cajas validas y tambien devuelve la cantidad de validos de cajasValidas
{
    int validos=0;
    int i = 0;
    while( i < habilitadas)
    {
        if((cajeros[i].tipo_pago == tipoPago)||(cajeros[i].tipo_pago == 3)&&(cajeros[i].abiertaOcerrada==0))
        {
            posCajasValidas[validos]=i;
            validos++;
        }
        i++;
    }
    return validos;
}
nodo2 * ordenar_Por_Prioridad_Uno(nodo2 * lista)
{
    nodo2 * listaEmbarazada=initLista();
    nodo2 * listaJubilado=initLista();
    nodo2 * listaResto=initLista();
    if(lista==NULL)
    {
        printf("");
    }
    else
    {
        if (lista->cliente.tipoCliente == 1)///Gordas
        {
            listaEmbarazada = agregarPpio(listaEmbarazada, ordenar_Por_Prioridad_Uno(lista->sig));
        }
        else if (lista->cliente.tipoCliente == 2)///Brujas
        {
            listaJubilado = agregarPpio(listaJubilado, ordenar_Por_Prioridad_Uno(lista->sig));
        }
        else if (lista->cliente.tipoCliente == 3)/// Persona Comun que no destaca antes nadie
        {
            listaResto = agregarPpio(listaResto, ordenar_Por_Prioridad_Uno(lista->sig));
        }
    }
    while (listaJubilado!=NULL)
    {
        listaEmbarazada=agregarPpio(listaEmbarazada,listaJubilado);
        listaJubilado=listaJubilado->sig;
    }
    while (listaResto!=NULL)
    {
        listaEmbarazada=agregarPpio(listaEmbarazada,listaResto);
        listaJubilado=listaResto->sig;
    }
    return listaEmbarazada;
}
int buscarMenorEnLasCajas(int cajasValidas[],caja cajero[],int validos){

    int posM = 0,i=0,cantidad=0;
    int menor=999999999;
    //printf("cajasValidas[i] %d \n",cajasValidas[i]);
    //printf("cajero[cajasValidas[i]] %s \n",cajero[cajasValidas[i]].nombreCajero);

    while(i<validos){
        nodo2 * seg=cajero[cajasValidas[i]].fila.cabeza;
        if(seg==NULL){
            cantidad=0;
        }else{
            while(seg != NULL){
                seg=seg->sig;
                cantidad++;
            }
        }
        if(cantidad <= menor)
        {
            posM=cajasValidas[i];
            menor=cantidad;
        }
        i++;
    }
    ///Retorna la posicion de la caja con menos gente
    return posM;
}

void mostrarCaja(caja cajero[],int valido){
    int pos=valido+1;
    printf("cuanto vale pos? %d\n",pos);
    printf("cuanto vale valido? %d\n",valido);
    printf("ingrese la posicion que deseas buscar?\n");
    while(pos>valido)
    {
        scanf("%d",&pos);
        pos=pos-1;
        printf("y aca? %d\n",pos);
        if(pos>=valido)
        {
            printf("la posicion no puede ser mayor a la caja recuerde que hay %d cajas\n",valido);
        }
    }

    mostrarCola(cajero[pos].fila);
}

void mostrarCola(Cola fila)
{
    nodo2*aux=fila.cabeza;
    while(aux!=NULL)
    {
        printf("Nombre: %s \n",aux->cliente.nombre);
        fflush(stdin);
        printf("Apellido: %s \n",aux->cliente.apelllido);
        fflush(stdin);
        printf("ID: %d \n",aux->cliente.id);
        fflush(stdin);
        printf("Cantidad de Articulos: %d \n",aux->cliente.cantArticulos);
        fflush(stdin);
        if(aux->cliente.tipoCliente==1)
        {
            printf("Tipo de cliente: Embarazada \n");
        }
        else if(aux->cliente.tipoCliente==2)
        {
            printf("Tipo de cliente: Jubilado \n");
        }
        else if(aux->cliente.tipoCliente==3)
        {
            printf("Tipo de cliente: Comun \n");
        }
        if(aux->cliente.medioPago==1)
        {
            printf("Medio de pago: Efectivo \n");
        }
        else if(aux->cliente.medioPago==2)
        {
            printf("Medio de pago: Credito o Debito \n");
        }
        else if(aux->cliente.medioPago==3)
        {
            printf("Medio de pago: Cualquiera \n");
        }
        aux=aux->sig;
    }

}

void AgregarClienteAcola(caja cajero[],stCliente nuevoCliente,int validos)
{
    nodo2 * aux;
    aux->cliente= nuevoCliente;
    int posMenor;
    int cajasvalidas[8];

    validos = buscarCajasValidas(cajero, validos, aux->cliente.medioPago,validos);
    posMenor = buscarMenorEnLasCajas(cajasvalidas[validos], cajero[8].fila.cabeza, validos);
    if(aux->cliente.tipoCliente==1)
    {
        AgregarPpioCola(cajero[posMenor].fila.cola, aux);
    }
    else
    {
        AgregarFinalCola(cajero[posMenor].fila.cola, aux);
    }
}

void _lista()
{

}

//inicia la lista
nodo2 *initLista()
{
    return NULL;
}
//Crea un nodo con memoria dinamica y: null<-- aux -->null
nodo2 *crearNodoLista(stCliente c)
{
    nodo2 *aux=(nodo2*)malloc(sizeof(nodo2));
    strcpy(aux->cliente.nombre,c.nombre);
    strcpy(aux->cliente.apelllido,c.apelllido);
    aux->cliente.medioPago=c.medioPago;
    aux->cliente.cantArticulos=c.cantArticulos;
    aux->cliente.eliminado=c.eliminado;
    aux->cliente.tipoCliente=c.tipoCliente;
    aux->cliente.id=c.id;
    aux->cliente.tiempoProcesado;
    aux->cliente.tiempoEspera;
    aux->ante=NULL;
    aux->sig=NULL;

    return aux;
}
//Añade un nodo al principio de la lista y dependiendo el caso cambia la referencia de la lista
nodo2 *agregarPpio(nodo2 *lista,nodo2 *nuevoNodo)
{
    if(lista!=NULL)
    {
        //Simplemente le digo que lista ahora es nuevo nodo y no cambio nada.
        lista=nuevoNodo;
    }
    else
    {
        //Engancho el nuevo nodo sig con la referencia del primer nodo de la lista
        nuevoNodo->sig=lista;
        //Engancho lista anterior con el nuevo nodo asi quedan doblemente vinculadas
        lista->ante=nuevoNodo;
        //Cambio la referencia de lista, y le digo que ahora lista es el primer nodo de la lista
        lista=nuevoNodo;
    }
    //Retorno Lista,es decir la referencia al primer nodo, ya devuelva los datos de mi nuevo nodo, o tambien puede devolver null
    return lista;
}

/*nodo2 *buscarUltimo(nodo2 *lista)
{
    nodo2*rta;

    if(lista->sig==NULL)
    {
        rta=lista;
    }
    else
    {
        rta=buscarUltimo(lista->sig);
    }
    return rta;
}*/
nodo2 *buscarUltimo(nodo2 *lista)
{
    nodo2 * aux=lista;
    if(aux){
        while(aux->sig!=NULL)
        {
            aux=aux->sig;
        }
    }

    return aux;
}
//Agrega un nodo al final de la lista
nodo2 *agregarFinal(nodo2 *lista, nodo2 *nuevoNodo)
{
    nodo2*aux;
    if(lista==NULL)
    {
        lista=nuevoNodo; //Agrego el nodo a la lista y punto
    }
    else
    {
        //Busco mi ultimo nodo llamando a mi metodo buscar nodo
        aux=buscarUltimo(lista);
        //Engancho mi nuevo nodo adelante del viejo ultimo(aux)
        aux->sig=nuevoNodo;
        nuevoNodo->ante=aux;
    }
    return lista; //siempre retorno lista por que es la referencia al primer nodo de mi lista

}

nodo2 * borrarNodo(nodo2* lista, int dato)
{
    nodo2*seg;

    if(lista)
    {
        if(lista->cliente.tipoCliente == dato)
        {
            nodo2*aux=lista;
            lista=lista->sig;
            free(aux);
        }
        else
        {
            nodo2*seg=lista->sig;
            nodo2*ante=lista;
            //recorro la lista
            while(seg->sig && seg->cliente.tipoCliente!=dato)
            {
                ante=seg;
                seg=seg->sig;
            }
            //nodo prox seria el sig del nodo que quiero borrar, es decir el sig de seguidora
            nodo2*prox=seg->sig;
            ante->sig=prox;

            if(prox)
            {
                prox->ante=ante;
                ante->sig=prox;
                free(seg);
            }
        }
    }

    return lista;
}

void mostrarLista(nodo2 *lista)
{
    if(lista)
    {
        printf("Nombre: %s %s\n",lista->cliente.nombre,lista->cliente.apelllido);
        printf("%d \n",lista->cliente.id);
        if(lista->cliente.tipoCliente==1)
        {
            printf("Tipo de cliente: Embarazada \n");
        }
        else if(lista->cliente.tipoCliente==2)
        {
            printf("Tipo de cliente: Jubilado \n");
        }
        else if(lista->cliente.tipoCliente==3)
        {
            printf("Tipo de cliente: Comun \n");
        }
        if(lista->cliente.medioPago==1)
        {
            printf("Medio de pago: Efectivo \n");
        }
        else if(lista->cliente.medioPago==2)
        {
            printf("Medio de pago: Credito o Debito \n");
        }
        else if(lista->cliente.medioPago==3)
        {
            printf("Medio de pago: Cualquiera \n");
        }
        printf("Cantidad de Articulos: %d \n",lista->cliente.cantArticulos);
        printf("ID del cliente: %i \n",lista->cliente.id);
        printf("\n\n");
        mostrarLista(lista->sig);
    }
}

void _persona()
{

}

stCliente CargarPersona() {
    int op=4;
    stCliente p;
    printf("ingrese el nombre de la persona \n");
    fflush(stdin);
    gets(p.nombre);

    printf("ingrese el apellido de la persona \n");
    fflush(stdin);
    gets(p.apelllido);

    printf("Ingrese cantidad de articulos \n");
    scanf("%d",&p.cantArticulos);

    printf("Ingrese tipo de cliente \n");
    printf("1)embarazada \n");
    printf("2)jubilado \n");
    printf("3)cliente comun \n");
    while (op > 3) {
        scanf("%i",&op);
        if (op == 1)
        {
            p.tipoCliente=1;
        }
        else if (op == 2)
        {
            p.tipoCliente=2;
        }
        else if (op == 3)
        {
            p.tipoCliente=3;
        }
        else
        {
            printf("Ingrese una opcion valida\n");
            printf("1)embarazada \n");
            printf("2)jubilado \n");
            printf("3)cliente comun \n");
        }
    }
    op=4;
    printf("Ingrese medio de pago \n");
    printf("1)efectivo \n");
    printf("2)credito \n");
    printf("3)todo \n");
    while (op > 3)
    {
        scanf("%i",&op);
        if (op == 1)
        {
            p.medioPago=1;
        }
        else if (op == 2)
        {
            p.medioPago=2;
        }
        else if (op == 3)
        {
            p.medioPago=3;
        }
        else
        {
            printf("Ingrese una opcion valida\n");
            printf("1)efectivo \n");
            printf("2)credito \n");
            printf("3)todo \n");
        }
    }


    return p;
}

void _usuario()
{

}

stUsuario cargarUsuario()
{
    stUsuario p;
    printf("ingrese el nombre de la usuario \n");
    fflush(stdin);
    gets(p.nombre);

    printf("ingrese el apellido de la usuario \n");
    fflush(stdin);
    gets(p.apelllido);

    p.eliminado=1;

    printf("Ingrese su nick (nombre de usuario) \n");
    gets(p.usuario);

    printf("Ingrese contraseña \n");///hay que pasarlo a matriz igual
    gets(p.usuario);

    return p;
}

void _caja()
{

}

int posicionMenor (stCliente A[], int pos,int val)
{
    int menor = A[pos].cantArticulos;
    int posmenor = pos;
    int i = pos +1;
    while (i<val)
    {
        if (menor > A[i].cantArticulos)
        {
            menor = A[i].cantArticulos;
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}

void ordenacionSeleccionPorArticulo (stCliente A[],int val)
{
    int posmenor;
    stCliente aux;
    int i = 0;
    while (i<val)
    {
        posmenor = posicionMenor(A,i,val);
        aux = A[posmenor];
        A[posmenor]=A[i];
        A[i]= aux;
        i++;
    }
}
///Recibe como argumento un arreglo de cliente y sus validos y lo ordena por seleccion
void ordenarClientesSegunArticulo(stCliente aux[],int val){
    ordenacionSeleccionPorArticulo(aux,val);
}
///Ver el tema de los punteros
void SJF(caja cajita)
{
    int tiempoProceso=0;
    int i=0;
    nodo2 * lista=initLista();
    int timeEsp=0;
    nodo2 * aux=cajita.fila.cabeza;
    while(aux!=NULL)
    {
        printf("------------------------------------------------------------------\n");
        printf("\n\nEL cliente %s  %s ya finalizo su compra.. \n",aux->cliente.nombre, aux->cliente.apelllido);
        aux->cliente.tiempoProcesado=aux->cliente.cantArticulos;
        printf("Su tiempo de proceso es: %d \n",aux->cliente.tiempoProcesado);
        tiempoProceso=tiempoProceso + aux->cliente.cantArticulos;
        aux->cliente.tiempoEspera=timeEsp;
        printf("Su tiempo de Espera es: %d\n",aux->cliente.tiempoEspera);
        timeEsp=timeEsp+aux->cliente.cantArticulos;
        printf("EL medio de pago fue el  %d\n",aux->cliente.medioPago);
        aux->cliente.eliminado=1;
        system("pause");
        //lista=agregarFinal(lista,aux);
        aux=aux->sig;
        i++;
    }

        printf("\nFin de la cola, Su tiempo Medio de retorno es de: %d \n",timeEsp/i);
        printf("\nFin de la cola, Su tiempo Medio de Proceso es de: %d \n",tiempoProceso/i);

}
///Entra a la caja sin acomodar
void FIFO(caja cajita)///entra la caja que acomodamos la lista por prioridad
{
    nodo2 * lista=initLista();
    int timeEsp=0,tiempoProceso=0;
    int i=0;
    nodo2 * aux=cajita.fila.cabeza;
    while(aux!=NULL)
    {
            printf("------------------------------------------------------------------\n");
            printf("EL cliente %s  %s ya termino su compra\n",aux->cliente.nombre, aux->cliente.apelllido);
            aux->cliente.tiempoProcesado=aux->cliente.cantArticulos;
            printf("Su tiempo de proceso es: %d\n",aux->cliente.tiempoProcesado);
            tiempoProceso=tiempoProceso + aux->cliente.cantArticulos;
            aux->cliente.tiempoEspera=timeEsp;
            printf("Su tiempo de Espera es:%d\n",aux->cliente.tiempoEspera);
            timeEsp=timeEsp+aux->cliente.cantArticulos;
            printf("EL medio de pago fue el  %d\n",aux->cliente.medioPago);
            aux->cliente.eliminado=1;
            i++;
            //lista=agregarFinal(lista,aux);

            system("pause");
            aux=aux->sig;
    }

        printf("Fin de la cola, Su tiempo Medio de retorno es de: %d \n",timeEsp/i);
        printf("Fin de la cola, Su tiempo Medio de Proceso es de: %d \n",tiempoProceso/i);
}

void ROUND_ROBIN(caja cajita)
{
    nodo2 * lista=initLista();
    int i=0,tiempoProceso=0;
    int timeEsp=0;
    nodo2 * aux=cajita.fila.cabeza;
    while(aux!=NULL)
    {
        if(aux->cliente.cantArticulos<=8)
        {
            printf("------------------------------------------------------------------\n");
            printf("EL cliente %s  %s ya termino su compra\n",aux->cliente.nombre, aux->cliente.apelllido);
            aux->cliente.tiempoProcesado=aux->cliente.cantArticulos;
            printf("Su tiempo de proceso es: %d\n",aux->cliente.tiempoProcesado);
            tiempoProceso=tiempoProceso + aux->cliente.cantArticulos;
            aux->cliente.tiempoEspera=timeEsp;
            printf("Su tiempo de Espera es:%d\n",aux->cliente.tiempoEspera);
            timeEsp=timeEsp+aux->cliente.cantArticulos;
            printf("EL medio de pago fue el  %d\n",aux->cliente.medioPago);
            aux->cliente.eliminado=1;
            i++;
            //lista=agregarFinal(lista,aux);
            system("pause");
        }
        else {
            aux->cliente.tiempoEspera=timeEsp;
            timeEsp=timeEsp+8;
            aux->cliente.tiempoProcesado=8;
            tiempoProceso=tiempoProceso + 8;
            aux->cliente.cantArticulos = aux->cliente.cantArticulos-8;
            nodo2*nn=crearNodoLista(aux->cliente);
            //aux=agregarFinal(aux,nn);
        }
        aux=aux->sig;
    }

        //printf("Fin de la cola, Su tiempo Medio de retorno es de: %d \n",timeEsp/i);
        //printf("Fin de la cola, Su tiempo Medio de Proceso es de: %d \n",tiempoProceso/i);


}

void prioridades(caja cajita)///entra la caja que acomodamos la lista por prioridad
{
    nodo2 * aux= initLista();
    int timeEsp=0;
    int tiempoProceso=0;
    int i=0;
    nodo2 * lista=initLista();
    aux=cajita.fila.cabeza;
    while(aux!=NULL)
    {
        printf("------------------------------------------------------------------\n");
        printf("EL cliente %s  %s ya termino su compra\n",aux->cliente.nombre, aux->cliente.apelllido);
        aux->cliente.tiempoProcesado=aux->cliente.cantArticulos;
        printf("Su tiempo de proceso es: %d\n",aux->cliente.tiempoProcesado);
        tiempoProceso=tiempoProceso + aux->cliente.cantArticulos;
        aux->cliente.tiempoEspera=timeEsp;
        printf("Su tiempo de Espera es: %d\n",aux->cliente.tiempoEspera);
        timeEsp=timeEsp+aux->cliente.cantArticulos;
        printf("EL medio de pago fue el  %d\n",aux->cliente.medioPago);
        aux->cliente.eliminado=1;
        system("pause");
        //lista=agregarFinal(lista,aux);
        aux=aux->sig;
        i++;
    }

        printf("Fin de la cola, Su tiempo Medio de retorno es de: %d \n",timeEsp/i);
        printf("Fin de la cola, Su tiempo Medio de Proceso es de: %d \n",tiempoProceso/i);
}

nodo2 * ordenarPorCantidadArticulo(caja  cajita)
{
    stCliente aux[100];
    int val=0;
    nodo2 * lista=initLista();
    val=pasarCajaAArreglo(aux,cajita);
    //printf("\n");
    //printf("validos vale?::  %d \n",val);
    //system("pause");
    ordenarClientesSegunArticulo(aux,val);
    lista=pasarArregloALista(aux,val);
    //mostrarLista(lista);
    //system("pause");
    return lista;
}

nodo2 * extraerCLienteDecaja(caja *cajita)
{
    nodo2 * guardar;
    nodo2*eliminado;
    if(cajita->fila.cabeza==cajita->fila.cola)
    {
        eliminado=cajita->fila.cabeza;
        guardar->cliente= eliminado->cliente;
        //actualizo la cabeza y la cola en null por que estan vacias
        cajita->fila.cabeza=NULL;
        cajita->fila.cola=NULL;
        free(eliminado);
    }
    else
    {
        //guardo la cabeza en una variable auxiliar para futuramente eliminarla con free()
        eliminado=cajita->fila.cabeza;
        guardar->cliente = eliminado->cliente;
        nodo2* nodoSig=eliminado->sig;
        nodoSig->ante=NULL;
        cajita->fila.cabeza=nodoSig;
        free(eliminado);
    }

    return guardar;
}

void mostrarCliente(nodoArbol *arbol){
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Nombre: %s \n",arbol->p.nombre);
    printf("Apellido: %s \n",arbol->p.apelllido);
    printf("Medio de pago: %i \n",arbol->p.medioPago);
    printf("Tipo de Cliente: %i \n",arbol->p.tipoCliente);
    printf("Cant de articulos: %i \n",arbol->p.cantArticulos);
    printf("ID del cliente: %i \n",arbol->p.id);
}

void grabarClientesToArchivo(nodoArbol *arbol){

    FILE *fichero =fopen(archiRegPersonas,"a+b");
    char ctrl='s';
    int i=0;
    int cantClientes;
    stCliente cl[50];

    if(fichero != NULL){
        while(ctrl=='s'){
            cl[i] = CargarPersona();

            cantClientes = contarClientesArchivo();
            cl[i].id = cantClientes+i+1;

            fwrite(&cl[i],sizeof(stCliente),1,fichero);
            i++;

            printf("Desea seguir agregando clientes al archivo? s/n\n");
            fflush(stdin);
            scanf("%c",&ctrl);
            ///ctrl = getchar();
        }
    }

    fclose(fichero);
}

nodoArbol *leerClienteDelArchivo(nodoArbol *arbolito) {
    stCliente aux2;
    int i=0;
    nodoArbol *nuevoNodoArbol=crearNodoArbol(aux2);
    FILE *fichero =fopen(archiRegPersonas,"rb");

    if(fichero!=NULL){
        while(fread(&aux2,sizeof(stCliente),1,fichero)>0) {
            nuevoNodoArbol->p=aux2;
            arbolito =insertarClientesToArbol(arbolito,aux2);
            mostrarCliente(nuevoNodoArbol);
            i++;
        }
    }

    fclose(fichero);

    return arbolito;
}


int contarClientesArchivo()
{
    FILE *fichero = fopen(archiRegPersonas,"rb");
    stCliente cl;
    long longitud;
    int cantidad=0;

    fseek(fichero,0,SEEK_END);
    longitud = ftell(fichero);

    cantidad = (int)longitud/(int)sizeof(stCliente);

    fclose(fichero);

    return cantidad;
}

nodoArbol * ModificarCliente(nodoArbol * arbol) {
    char letra[100];
    int id, op = 4, op2;
    nodoArbol *aux;

    printf("Porque medio desea buascar al usuario?\n");
    printf("1: Buscar por Nombre \n");
    printf("2: Buscar por apellido \n");
    printf("3: Buscar por ID \n");

    while (op > 3) {
        fflush(stdin);
        scanf("%d",&op);
        if (op == 1) {
            printf("Ingree el nombre del cliente a modificar\n");
            fflush(stdin);
            gets(letra);
            aux = buscarNombre(arbol,letra);
        } else if (op == 2) {
            printf("Ingree el Apellido del cliente a modificar\n");
            fflush(stdin);
            gets(letra);
            aux = buscarApellido(arbol,letra);
        } else if (op == 3) {
            printf("Ingree el ID del cliente a modificar\n");
            fflush(stdin);
            scanf("%d",&id);
            aux = buscar_ID_Arbol(arbol,id);
        } else {
            printf("Ingrese una opcion valida\n");
            printf("1: Buscar por Nombre \n");
            printf("2: Buscar por apellido \n");
            printf("3: Buscar por ID \n");
        }
    }
    do {
        printf("Ingrese una opcion \n");
        printf("1: modicar nombre \n");
        printf("2: modicar apellido \n");
        printf("3: modicar cantidad de articulo \n");
        printf("4: modicar medio de pago \n");
        printf("5: modicar tipo de cliente \n");
        fflush(stdin);
        scanf("%i",&op2);
        switch (op2) {
            case 1:
                system("cls");
                printf("ingrese el nuevo nombre \n");
                fflush(stdin);
                gets(letra);
                strcpy(aux->p.nombre, letra);
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                printf("ingrese el nuevo apellido \n");
                fflush(stdin);
                gets(letra);
                strcpy(aux->p.apelllido, letra);
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                printf("Ingrese la cantidad de articulo\n");
                fflush(stdin);
                scanf("%d",&aux->p.cantArticulos);
                system("pause");
                system("cls");
                break;
            case 4:
                op = 4;
                system("cls");
                printf("Ingrese medio de pago \n");
                printf("1)efectivo \n");
                printf("2)credito \n");
                printf("3)todo \n");
                while (op > 3) {
                    scanf("%i",&op);
                    if (op == 1) {
                        aux->p.medioPago = 1;
                    } else if (op == 2) {
                        aux->p.medioPago = 2;
                    } else if (op == 3) {
                        aux->p.medioPago = 3;
                    } else {
                        printf("Ingrese una opcion valida\n");
                        printf("1)efectivo \n");
                        printf("2)credito \n");
                        printf("3)todo \n");
                    }
                    system("pause");
                    system("cls");
                    break;
                    case 5:
                        system("cls");
                    op = 4;
                    system("cls");
                    printf("Ingrese tipo de cliente \n");
                    printf("1)Embarazada \n");
                    printf("2)Jubilado \n");
                    printf("3)Persona Comun \n");
                    while (op > 3) {
                        fflush(stdin);
                        scanf("%i",&op);
                        if (op == 1) {
                            aux->p.tipoCliente = 1;
                        } else if (op == 2) {
                            aux->p.tipoCliente = 2;
                        } else if (op == 3) {
                            aux->p.tipoCliente = 3;
                        } else {
                            printf("Ingrese una opcion valida\n");
                            printf("1)Embarazada \n");
                            printf("2)Jubilado \n");
                            printf("3)Persona Comun \n");
                        }
                    }
                        system("pause");
                        system("cls");
                        break;
                        default:
                            system("cls");
                            printf("Fin de modificacion de clietne\n");
                            system("pause");
                            system("cls");
                        break;
                    }
                }

        }while ((op2 > 0) && (op2 <= 5));


    return arbol;
}

void SuperFuncionCaja(nodoArbol * arbol)
{
    int op;
    int habilitadas;
    nodo2 *lista;
    stCliente cliente[100];
    lista=initLista();
    caja cajero[100];
    lista= pasarArbolToLista(arbol,lista);
    //pasarListaAArreglo(cliente,lista);
    stCliente cl;
    habilitadas=CajasCargada(cajero);
    do
    {
        menuSuperFuncionCaja();
        printf("\nIngrese una opcion..  ");
        fflush(stdin);
        scanf("%i",&op);
        switch(op)
        {
            case 1:
                system("cls");
                de_Lista_a_Caja(lista,cajero,habilitadas);
                Ordenar(cajero,habilitadas);
                Cargando("Pasando cliente de la lista a la caja, por favor espere..\n");
                printf("\nLos clientes han sido pasados a la caja exitosamente.. \n");
                system("pause");
                system("cls");
                break;

            case 2:
                system("cls");
                //rp=4;
                habilitadas=agregarCaja(cajero,habilitadas);

                system("pause");
                system("cls");
                break;

            case 3:
                system("CLS");
                mostrarALLcajas(cajero,habilitadas);
                system("pause");
                system("CLS");
                break;

            case 4:
                system("cls");
                cl =CargarPersona();
                AgregarClienteAcola(cajero,cl,habilitadas);
                system("pause");
                system("cls");
                break;
            case 5:
                system("cls");
                ///Algoritmo de planificacion en TODAS las cajas
                FuncionDePlanificacion(cajero,habilitadas);
                system("pause");
                system("cls");
                break;
            case 6:
                system("cls");
                abrirTodasLasCajas(cajero,habilitadas);
                printf("Las cajas han sido abiertas exitosamente.. \n");
                system("pause");
                system("cls");
                break;
            case 7:
                system("cls");
                cerrarTodasLasCajas1(cajero,habilitadas);
                system("pause");
                system("cls");
                break;
            case 8:
                system("cls");
                int posCaj;
                printf("Ingrese el numero de caja que quiera cerrar \n");
                scanf("%i",&posCaj);
                CerrarUnaCaja(cajero,(posCaj-1));
                printf("La caja %i ha sido cerrado con exito \n",posCaj-1);
                system("pause");
                system("cls");
                break;
            case 9:
                system("cls");
                int posCaj2;
                printf("Ingrese el numero de caja que quiera abrir \n");
                scanf("%i",&posCaj2);
                abrirUnaCaja(&cajero[posCaj2-1]);
                printf("La caja %i ha sido cerrado con exito \n",posCaj-1);

                system("pause");
                system("cls");
                break;
            default:
                system("cls");
                break;
        }
    }
    while(op >0 && op <10);
}
int CajasCargada(caja cajero[])
{
    cajero[0].tipo_pago=2;
    cajero[0].nro_de_caja=1;
    cajero[0].abiertaOcerrada=0;
    strcpy(cajero[0].algoritmoPlanificacion,"sjf");
    strcpy(cajero[0].nombreCajero,"Alberto");

    cajero[1].tipo_pago=2;
    cajero[1].nro_de_caja=2;
    cajero[1].abiertaOcerrada=0;
    strcpy(cajero[1].algoritmoPlanificacion,"rr");
    strcpy(cajero[1].nombreCajero,"Bruno");

    cajero[2].tipo_pago=3;
    cajero[2].nro_de_caja=3;
    cajero[2].abiertaOcerrada=0;
    strcpy(cajero[2].algoritmoPlanificacion,"prioridad");
    strcpy(cajero[2].nombreCajero,"Carla");

    cajero[3].tipo_pago=2;
    cajero[3].nro_de_caja=4;
    cajero[3].abiertaOcerrada=0;
    strcpy(cajero[3].algoritmoPlanificacion,"fifo");
    strcpy(cajero[3].nombreCajero,"Dario");

    cajero[4].tipo_pago=1;
    cajero[4].nro_de_caja=5;
    cajero[4].abiertaOcerrada=0;
    strcpy(cajero[4].algoritmoPlanificacion,"fifo");
    strcpy(cajero[4].nombreCajero,"Ema");

    cajero[5].tipo_pago=3;
    cajero[5].nro_de_caja=6;
    cajero[5].abiertaOcerrada=0;
    strcpy(cajero[5].algoritmoPlanificacion,"rr");
    strcpy(cajero[5].nombreCajero,"Franco");

    cajero[6].tipo_pago=1;
    cajero[6].nro_de_caja=7;
    cajero[6].abiertaOcerrada=0;
    strcpy(cajero[6].algoritmoPlanificacion,"prioridad");
    strcpy(cajero[6].nombreCajero,"Gonzalo");

    cajero[7].tipo_pago=1;
    cajero[7].nro_de_caja=8;
    cajero[7].abiertaOcerrada=0;
    strcpy(cajero[7].algoritmoPlanificacion,"sjf");
    strcpy(cajero[7].nombreCajero,"Hugo");

    return 8;
}
void menuSuperFuncionCaja(){
    printf("~0 Salir \n");
    printf("1~ Cargar las cajas con clientes \n");
    printf("2~ Agregar Caja \n");
    printf("3~ Mostrar todas las Cajas \n");
    printf("4~ Agregar Cliente a la Fila \n");
    printf("5~ Atender los clientes \n");
    printf("6~ Abrir todas las cajas \n");
    printf("7~ Cerrar todas las cajas \n");
    printf("8~ Cerrar una caja en particular \n");
    printf("9~ Abrir una caja en particular \n");
}

nodo2 * FuncionDePlanificacion(caja cajero[],int valido)
{
    int i=0;
    nodo2 * lista=initLista();
    while(i<valido)
    {
        if(strcmpi(cajero[i].algoritmoPlanificacion,"fifo")==0)
        {
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("FIFO  ");
            printf("Caja: %d \n\n",cajero[i].nro_de_caja);
            //mostrarCaja2(cajero[i]);
            //lista=agregarFinal(lista,FIFO(cajero[i]));
            FIFO(cajero[i]);
            InicCola(&cajero[i].fila);
        }
        else if(strcmpi(cajero[i].algoritmoPlanificacion,"prioridad")==0)
        {
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("Prioridad ");
            printf("Caja: %d \n\n",cajero[i].nro_de_caja);
            //mostrarCaja2(cajero[i]);
            //lista=agregarFinal(lista,prioridades(cajero[i]));
            prioridades(cajero[i]);
            InicCola(&cajero[i].fila);
        }
        else if(strcmpi(cajero[i].algoritmoPlanificacion,"sjf")==0)
        {
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("SJF ");
            printf("Caja: %d \n\n",cajero[i].nro_de_caja);
            //mostrarCaja2(cajero[i]);
            //lista=agregarFinal(lista,SJF(cajero[i]));
            SJF(cajero[i]);
            InicCola(&cajero[i].fila);
        }
        else
        {
            printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            printf("Round Robin ");
            printf("Caja: %d \n\n",cajero[i].nro_de_caja);
            //mostrarCaja2(cajero[i]);
            //lista=agregarFinal(lista,ROUND_ROBIN(cajero[i]));
            ROUND_ROBIN(cajero[i]);
            InicCola(&cajero[i].fila);
        }
        i++;
    }
    return lista;
}

nodo2 * ordenarPorPrioridad(caja cajita)
{
    stCliente aux[100];

    int val=0;
    int i=0;
    nodo2 * lista=initLista();
    nodo2 *auxNodo;
    val=pasarCajaAArreglo(aux,cajita);
    ordenarClientesSegunPrioridad(aux,val);
    //mostrarArreglo(aux,val);
    //system("pause");
    lista=pasarArregloALista(aux,val);
    //mostrarLista(lista);
    //system("pause");
    return lista;
}
int pasarCajaAArreglo(stCliente a[], caja  cajero)
{
    int i=0;
    nodo2 * aux;
    aux=cajero.fila.cabeza;
    while(aux!=NULL)
    {
        a[i]=aux->cliente;
        aux=aux->sig;
        i++;
    }
    return i;
}
nodo2 * pasarArregloALista(stCliente arreglo[],int validos)
{
    nodo2 * seg=initLista();
    int i=0;
    while(i<validos)
    {
        nodo2 * nn=crearNodoLista(arreglo[i]);
        seg=agregarFinal(seg,nn);
        i++;
    }
    return seg;
}
void mostrarArreglo(stCliente a[],int validos)
{
    int i=0;
    while(i<validos)
    {
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Nombre: %s \n",a[i].nombre);
        printf("Apellido: %s \n",a[i].apelllido);
        printf("Medio de pago: %i \n",a[i].medioPago);
        printf("Tipo de Cliente: %i \n",a[i].tipoCliente);
        printf("Cant de articulos: %i \n",a[i].cantArticulos);
        printf("ID del cliente: %i \n",a[i].id);
        i++;
    }
}
void ordenarClientesSegunPrioridad(stCliente aux[],int val)
{
    ordenacionSeleccionPorPrioridad(aux,val);
}
void ordenacionSeleccionPorPrioridad (stCliente A[],int val)
{
    int posmenor;
    stCliente aux;
    int i = 0;
    while (i<val)
    {
        posmenor = posicionMenorprioridad(A,i,val);
        aux = A[posmenor];
        A[posmenor]=A[i];
        A[i]= aux;
        i++;
    }
}
int posicionMenorprioridad(stCliente A[], int pos,int val)
{
    int menor = A[pos].tipoCliente;
    int posmenor = pos;
    int i = pos +1;
    while (i<val)
    {
        if (menor > A[i].tipoCliente)
        {
            menor = A[i].tipoCliente;
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}

int comprobarIDCliente(stCliente cl) //Comprueba el ID
{
    int a=0;
    FILE *fichero= fopen(archiRegPersonas,"rb");
    stCliente aux;
    while(fread(&aux,sizeof(stCliente),1,fichero)>0)
    {
        if(aux.id== cl.id)
        {
            printf("El ID ya existe \n");
            a=1;
        }
    }
    fclose(fichero);
    return a; //retorna 1 si el ID ya existe
}

void mostrarALLcajas(caja cajero[],int valido)
{
    int i=0;
    while(i<valido)
    {
        mostrarCaja2(cajero[i]);
        i++;
    }
}

void mostrarCaja2(caja cajero)//muestra una caja
{
    char tipoPago [30]="Efectivo";
    char estado [30]="Abierta";
    printf("\nNumero de caja: %d",cajero.nro_de_caja);
    printf("\nNombre de cajero: %s",cajero.nombreCajero);
    if(cajero.tipo_pago==2)
    {
        strcpy(tipoPago,"Credito o debito");
    }
    else if(cajero.tipo_pago==3)
    {
        strcpy(tipoPago,"Todos");
    }
    printf("\nTipo de pago: %d (%s)",cajero.tipo_pago,tipoPago);
    if(cajero.abiertaOcerrada==0)
    {
        strcpy(estado,"Abierta");
    }else{
        strcpy(estado,"Cerrada");
    }
    printf("\nEstado: %d (%s)",cajero.abiertaOcerrada,estado);
    printf("\nAlgoritmo de planificacion: %s \n\n",cajero.algoritmoPlanificacion);
    printf("\nPersonas en la fila: \n");

    mostrarCola(cajero.fila);
    printf("\n--------------------------------------------\n");
}

void pasarListaAArreglo(stCliente arreglo[],nodo2 * lista)
{
    int i=0;
    nodo2 * seg=lista;
    while(seg)
    {
        arreglo[i]=seg->cliente;
        seg=seg->sig;
        i++;
    }
}

void abrirOCerrarCaja(caja * cajita)
{
    cajita->abiertaOcerrada=0;
}
int CerrarUnaCaja(caja cajita[],int pos) {

    int flag=0;
    if(cajita[pos].fila.cabeza == NULL) {
        cajita[pos].abiertaOcerrada = 1;
        system("pause");
    }
    else{
        //FuncionDePlanificacion(cajita, 1);
        cajita[pos].abiertaOcerrada = 0;
        printf("La caja  aun tiene clientes, atiendalos antes de cerrarlos \n");
        flag=1;
    }
    return flag;
}

void abrirUnaCaja(caja *cajita)
{
    if(&cajita->fila==NULL) {
        cajita->abiertaOcerrada=0;
    }
    else {
        cajita->abiertaOcerrada=1;
    }
}

void abrirTodasLasCajas(caja cajita[20],int val)
{
    int i=0;
    while(i<val)
    {
        if(cajita[i].abiertaOcerrada==1) //la caja se encuentra cerrada, hay que abrirla
        {
            abrirOCerrarCaja(&cajita[i]);
        }
        i++;
    }
}
/*
void cerrarTodasLasCajas(caja cajita[20],int validos)
{
    int i=0;
    while(i<validos)
    {
        if(cajita[i].abiertaOcerrada==1)
        {
            abrirOCerrarCaja(&cajita[i]);
        }
        i++;
    }
}*/
void cerrarTodasLasCajas1(caja cajita[20],int validos)//cierra todas las cajas
{
    int i=0,flag=0;
printf("%d",validos);
    while((i<validos)) {
        flag += CerrarUnaCaja(cajita,i);
        i++;
    }
    if (flag == 0)
        printf("Las cajas se han cerrado con exito.. \n");
    else{
        printf("Hay clientes en las cajas \n");
        printf("Atiendalos antes de cerrar las cajas \n");
        system("pause");
    }

}

void Cargando(char tipo[60])
{
    int i;
    printf("%s..\n\n",tipo);
    for(i=0; i<100; i++)
    {
        barra(i,20);
        if(strcmpi(tipo,"Procesando datos")==0)
            _sleep(5);
        else
            _sleep(30);
    }
    printf("\nPresione la tecla Enter para continuar \n");
    getchar();
}

void barra(int porc,int larg)
{
    int i;
    printf("\r[");
    for(i=0; i<larg; i++)
    {
        if(porc*larg/100<i)
            putchar('_');
        else
            putchar('#');
    }
    printf("] %d%% Completado...",porc+1);
}

int comprobarCajasCerradas(caja cajita[],int validos){
    int i=0,flag=0;

    if(cajita->fila.cabeza == NULL){ //si todas las cajas estan abiertas y no hay gente
        printf("No hay clientes en ninguna caja \n");
    }else{
        while(i < validos){
            if(&cajita[i].fila != NULL){
                flag=1;
            }
            i++;
        }
    }
    return flag;
}


