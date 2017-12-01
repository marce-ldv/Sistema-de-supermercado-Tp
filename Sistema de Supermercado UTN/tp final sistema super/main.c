#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "matriz.h"
#include "TDA_general.h"

const char Programa[] = "data.dat"; // Archivo de usuarios
const char ProgramaClient[] = "dataClient.dat"; // Archivo de clientes

void MenuLogin();
void menuModificacion();
void modificacion(stUsuario usuario, int pos);
void mostrarUsuarioModificado(stUsuario usu);
stUsuario altaYbaja(stUsuario usuario);
stUsuario modificarContrasenia(stUsuario usuario);
stUsuario modificarUsuario(stUsuario usuario);
int comprobarID(stUsuario Usuario);
void GrabarArchivo(int a);
void Cantidad_Registro();
stCliente CargarDatos();
stCliente Cargar_Los_Datos_que_Desee();
int Cantidad_Registro_Estructura();
void leerStructClient();
void leerStructUser();
void Agregar_Dato_Al_Archivo();
void menuPrincipal();
int Comprobar_Nombre_Cliente(stCliente cliente);
void cargarMatrizEncriptada(float m[2][5],float encriptada[2][5]);
stUsuario CargarUsuario();
int Comprobar_Nombre_Usuario(stUsuario Usuario);
void agregarUsuario(stUsuario a);
void agregarCliente(stCliente a);
int comprobarUsernameAndPassword(stUsuario Usuario);
int comparaMatrizEncript(float matA[2][5],float matB[2][5]);
int loguearUsuario();
void Ver_listados_de_usuario();
void Ver_listados_de_cliente();
int buscarMenor(stCliente cliente [100],int pos,int validos);
void ordenarPorIdCliente();
void Ordernacion_por_insercionNombreCliente();
void Ver_listados_de_cliente_Arreglo(stCliente a[100], int val);
void ConsultarUsuario();
void ConsultarCliente();
int cuantosUsuariosHay();
void MostraCliente(stCliente cliente);
void menuModificacionCliente();
void modificacionParaCliente(char cliente[]);
void ordenarSeleccionDomicilio();
int posMenorDomicilio(stCliente c[100],int validos,int pos);
void menuCriterioArbol();
void funcionPrincipal();
void menuMainLogin();
void menuOPUsuarios();
void menuOpCliente();
void menuOpCajas();
void menuOpAvanzadas();

int main(){
    Cargando("\n\nIniciando sistema, por favor espere..\n");
    system("cls");
    funcionPrincipal();
    getchar();
    return 0;
}

void funcionPrincipal(){
    int op,opAux,a=1,b=1,c=-1,varID=1;
    int op1,op2,op3,op4;
    stUsuario usuario;
    stCliente cliente;
    int cantidadValidos = 0;
    nodoArbol *arbolito=initArbol();

    stCliente cl;
    nodo2 *nodoCliente = crearNodoArbol(cl);

    FILE *fp= fopen(ProgramaClient,"rb");
    while(fread(&cliente,sizeof(stCliente),1,fp)>0)
    {
        cantidadValidos++;
    }
    fclose(fp);

    do
    {
        a=1,b=1,c=-1;
        puts("\n");
        menuPrincipal();
        printf("Que opcion desea ingresar?.. ");
        puts("\n\n");
        fflush(stdin);
        scanf("%i",&op);
        switch(op) {
            case 1:
                system("CLS");
                printf("Administrador \n" );

                leerStructUser();

                while(a == 1)
                {
                    while(a == 1)
                    {
                        usuario = CargarUsuario();
                        a = Comprobar_Nombre_Usuario(usuario);
                        //printf("Si a vale 1, el usuario ya existe \n");
                        if(a == 1)
                        {
                            printf("Ingrese otro nombre \n"); //para el main
                        }
                    }

                    a = 1;
                    a = comprobarID(usuario); ///Devuelve 1 si el ID ya existe

                    //printf("si a vale 1, el ID ya existe \n");
                    //printf("a vale %i \n",a);
                    if(a == 1)
                    {
                        printf("Ingrese otro ID \n"); //para el main
                    }
                    else if(a == 0)
                    {
                        agregarUsuario(usuario);
                    }

                }

                system("pause");
                system("cls");
                break;

            case 2:
                system("CLS");
                printf("~  LOGIN  ~\n");
                c = loguearUsuario();
                if(c > -1) ///si vale 1, el usuario esta logueado
                {
                    do
                    {
                        menuMainLogin();
                        printf("Ingrese una opcion \n");
                        scanf("%i",&opAux);

                        switch(opAux)
                        {
                            case 1:
                                do {


                                    system("cls");
                                    menuOPUsuarios();
                                    printf("Ingrese una opcion \n");
                                    scanf("%i", &op1);
                                    switch (op1) {
                                        case 0:
                                            system("cls");

                                            printf("Volvio atras en el menu \n");

                                            system("pause");
                                            system("cls");
                                            break;
                                        case 1:
                                            system("cls");
                                            modificacion(usuario, c);
                                            system("pause");
                                            system("cls");
                                            break;
                                        case 2:
                                            system("cls");
                                            Ver_listados_de_usuario();
                                            system("pause");
                                            system("cls");
                                            break;
                                        default:
                                            system("cls");
                                            printf("Ha decidido volver atras en el menu \n");
                                            system("pause");
                                            system("cls");
                                            break;
                                    }
                                }while (op1>0 && op1<=2);
                                system("pause");
                                system("cls");
                                break;

                            case 2:
                                system("cls");
                                do {

                                    menuOpCliente();
                                    printf("Ingrese una opcion \n");
                                    scanf("%i", &op2);
                                    switch (op2) {
                                        case 1:
                                            system("cls");
                                            grabarClientesToArchivo(arbolito);
                                            system("pause");
                                            system("cls");
                                            break;
                                        case 2:
                                            system("cls");

                                            int cantClientesEnFichero = contarClientesArchivo();
                                            printf("Actualmente hay %i clientes en el archivo \n ",
                                                   cantClientesEnFichero);

                                            system("pause");
                                            system("cls");
                                            break;
                                        case 3:
                                            system("cls");
                                            ModificarCliente(arbolito);
                                            system("pause");
                                            system("cls");
                                            break;
                                        case 4:
                                            system("cls");
                                            arbolito = leerClienteDelArchivo(arbolito);
                                            system("pause");
                                            system("cls");
                                            break;
                                        default:
                                            system("cls");
                                            printf("Ha decidido volver atras en el menu \n");
                                            system("pause");
                                            system("cls");
                                            break;
                                    }
                                }while(op2>0 && op2<=5);
                                //system("pause");
                                //system("cls");
                                break;
                            case 3:
                                do {

                                    system("cls");
                                    menuOpCajas();
                                    printf("Ingrese una opcion \n");
                                    scanf("%i", &op3);
                                    switch (op3) {

                                        case 1:
                                            system("cls");
                                            SuperFuncionCaja(arbolito);
                                            system("pause");
                                            system("cls");
                                            break;
                                        case 2:
                                            system("cls");
                                            arbolito = leerClienteDelArchivo(arbolito);
                                            system("pause");
                                            system("cls");
                                            break;
                                        default:
                                            system("cls");
                                            printf("Ha decidido volver atras en el menu \n");
                                            system("pause");
                                            system("cls");
                                            break;
                                    }
                                }while(op3>0 && op3<=2);
                                system("pause");
                                system("cls");
                                break;
                            case 4:
                                do {

                                    system("cls");
                                    menuOpAvanzadas();
                                    printf("Ingrese una opcion \n");
                                    scanf("%i", &op4);
                                    switch (op4) {
                                        case 1:
                                            system("cls");
                                            menuCriterioArbol();

                                            int auxMostrarArbol;
                                            scanf("%i", &auxMostrarArbol);

                                            if (auxMostrarArbol == 1) {
                                                preorder(arbolito);
                                            } else if (auxMostrarArbol == 2) {
                                                inorder(arbolito);
                                            } else {
                                                postorder(arbolito);
                                            }

                                            system("pause");
                                            system("cls");
                                            break;
                                        case 2:
                                            system("cls");
                                            printf("ingrese dato de nodo a borrar (int) \n");
                                            int auxInt;
                                            scanf("%i", &auxInt);
                                            arbolito = borrarNodoArbol(arbolito, auxInt);
                                            printf("El cliente a sido borrado exitosamente \n");
                                            system("pause");
                                            system("cls");
                                            break;
                                        case 3:
                                            system("cls");
                                            printf("ingrese dato de nodo a borrar (String) \n");
                                            char auxString[30];
                                            fflush(stdin);
                                            gets(auxString);
                                            arbolito = borrarNodoArbolNombre(arbolito, auxString);
                                            printf("El cliente a sido borrado exitosamente \n");
                                            system("pause");
                                            system("cls");
                                            break;
                                        default:
                                            system("cls");
                                            printf("Ha decidido volver atras en el menu \n");
                                            system("pause");
                                            system("cls");
                                            break;
                                    }
                                }while(op4>0 && op4<=4);
                                //system("pause");
                                //system("cls");
                                break;

                            default:
                                system("cls");
                                printf("Ha decidido volver atras en el menu \n");
                                system("pause");
                                system("cls");
                                break;
                        }
                    }
                    while(opAux > 0 && opAux<=10);

                    //system("PAUSE");
                    //system("CLS");
                    break;

                    default:
                        system("CLS");
                        printf("Gracias por usar nuestro sistema \n" );
                        system("PAUSE");
                        system("CLS");
                    break;
                }
        }

    }
    while(op >0 && op <= 5);
}


void menuCriterioArbol(){
    printf("Muestra el arbol \n");
    printf("1-PreOrder 2- InOrder 3- PostOrder \n");
    printf("Ingrese el criterio con el que quiere ver el arbol \n");
}

void menuMainLogin(){
    printf("0~ Volver atras \n");
    printf("1~ Acceder a las Opciones de usuario \n");
    printf("2~ Acceder a las Opciones de cliente \n");
    printf("3~ Acceder a las opciones de Caja \n");
    printf("4~ Opciones avanzadas \n");
}

void menuOPUsuarios(){
    printf("0~ Volver atras \n");
    printf("1~ Modificar Usuario \n");
    printf("2~ Mostrar listado de usuarios \n");
}
void menuOpCliente(){
    printf("0~ Volver atras \n");
    printf("1~ Crear cliente \n");
    printf("2~ Ver la cantidad de clientes en el Supermercado UTN \n");
    printf("3~ Modificar Cliente \n");
    printf("4~ Cargar clientes en el Supermercado UTN\n");
}
void menuOpCajas(){
    printf("0~ Volver atras \n");
    printf("1~ Opciones de las cajas del super \n");
    printf("2~ Cargar clientes en el Supermercado UTN\n");
}
void menuOpAvanzadas(){
    printf("0~ Volver atras \n");
    printf("1~ Mostrar arbol \n");
    printf("2~ Borrar cliente del arbol (dato entero) \n");
    printf("3~ Borrar cliente del arbol (dato cadena de caracteres) \n");
}

void MenuLogin() //Menu De Login
{
    printf("0~ Volver atras \n");
    printf("1~ Modificar Usuario \n");
    printf("2~ Mostrar listado de usuarios \n");
    printf("3~ Cargar un cliente en el archivo\n");
    printf("4~ Mostrar arbol \n");
    printf("5~ Borrar cliente del arbol (int) \n");
    printf("6~ Borrar cliente del arbol (nombre) \n");
    printf("7~ Cuenta los clientes que hay en un archivo \n");
    printf("8~ Modificar Cliente \n");
    printf("9~ Lee el archivo Muestra los clientes y pasa los clientes al arbol \n");
    printf("10~ Super Funcion De Caja \n");
}
void menuModificacion() //Menu de Modificacion
{
    printf("\n1~ Modificar Usuario \n");
    printf("\n2~ Modificar contrasenia \n");
    printf("\n3~ Altas y Bajas de usuarios \n");
    printf("\n0~ Para volver atras presione 0 \n");
}

void modificacion(stUsuario usuario, int pues) // Funcion principal que modifica usuario,contraseña y administra el borrado logico (altas y bajas)
// Como para acceder a este menú de modificacion, previamente se introdujo el nombre de usuario y la contraseña, y ya
// se validó al loguearse que ambos fueran correctos, ya no vuelven a pedirse y verificarse estos datos
{
    FILE *fp;
    int op;
    stUsuario aux;
    int flag = 0;
    stUsuario aux2;
    stUsuario aux3[100];
    int pos=0;
    fp = fopen(Programa,"r+b");
    if(fp != NULL)
    {
        while ((fread(&aux2,sizeof(stUsuario),1,fp)>0) && (flag==0))
        {
            aux3[pos]=aux2;
            if(strcmp(usuario.usuario,aux2.usuario) == 0)
            {
                flag = 1;
            }
            pos++;
        }
    }
    aux=aux3[pues];
    do
    {
        menuModificacion();
        printf("\nIngrese una opcion..  ");
        scanf("%i",&op);
        switch(op)
        {
            case 1: //MODIFICA EL NOMBRE DE USUARIO
                system("cls");

                aux = modificarUsuario(aux);

                fseek(fp,(pos-1)*sizeof(stUsuario),0); // AHORA POSICIONAMOS DE NUEVO EL CURSOR PARA PODER GRABAR EL ARCHIVO

                fwrite(&aux,sizeof(stUsuario),1,fp); // Y GRABAMOS EL USUARIO CON LAS MODIFICACIONES INDCORPORADAS

                system("cls");
                break;

            case 2: // MODIFICA LA CONTRASEÑA
                system("cls");

                aux = modificarContrasenia(aux);

                fseek(fp,(pos-1)*sizeof(stUsuario),0); // AHORA POSICIONAMOS DE NUEVO EL CURSOR PARA PODER GRABAR EL ARCHIVO (

                fwrite(&aux,sizeof(stUsuario),1,fp); // Y GRABAMOS EL USUARIO CON LAS MODIFICACIONES INDCORPORADAS

                system("pause");
                system("cls");
                break;

            case 3: // ADMINISTRA LAS ALTAS Y BAJAS
                system("CLS");

                aux = altaYbaja (aux);

                fseek(fp,(pos-1)*sizeof(stUsuario),0); // AHORA POSICIONAMOS DE NUEVO EL CURSOR PARA PODER GRABAR EL ARCHIVO

                fwrite(&aux,sizeof(stUsuario),1,fp); // Y GRABAMOS EL USUARIO CON LAS MODIFICACIONES INDCORPORADAS

                system("CLS");
                break;

            case 4:
                system("cls");

                system("cls");
                break;


            default:
                system("cls");
                break;
        }
    }
    while(op >0 && op <5);
    printf("antes de guardar vale???  %d \n",pues);
    system("pause");
    aux3[pues]=aux;
    fseek(fp,0,SEEK_SET);
    int i=0;
    while(pos>i)
    {
        fwrite(&aux3[i],sizeof(stUsuario),1,fp);
        i++;
    }
    fclose(fp);

    printf("\nAsi han quedado los datos del usuario:\n");

    mostrarUsuarioModificado(aux);
}

void mostrarUsuarioModificado(stUsuario usu)
{
    char contrasenia[10];

    printf("\nNick del usuario: %s", usu.usuario);
    printf("\nNombre: %s",usu.nombre);
    printf("\nApellido: %s",usu.apelllido);
    printf("\nNro de identificacion del usuario: %d", usu.id_cliente);
    printf("\nContrasenia\n");
    desencriptaContras(usu.pass,contrasenia);//Desencripta la contrasenia
    mostrarArregloChar(contrasenia); // la mostramos desencriptada
    printf("Estado del cliente (1 activo / 0 dado de baja): %d\n", usu.eliminado);
    printf("_________________________________________________________________\n\n\n\n\n");
}

stUsuario altaYbaja(stUsuario usuario) // Funcion de Borrado logico. Funcion aux de la principal que se ocupa de todas las modificaciones
{
    int op;

    printf("\n1~ Dar de alta el usuario ");
    printf("\n2~ Dar de baja el usuario \n");
    printf("\nSeleccione una opcion.. ");
    scanf("%i",&op);

    switch(op)
    {
        case 1: // dar de alta al usuario que fue dado de baja en algun momento
            system("cls");

            if(usuario.eliminado == 1)
            {
                printf("\nEl Usuario ya se encontraba dado de alta. \n");
            }
            else
            {
                usuario.eliminado = 1;
                printf("Acaba de dar de alta al usuario. \n");
            }
            system("pause");
            system("cls");
            break;

        case 2: // dar de baja al usuario (borrado logico, no lo borra del archivo, sólo lo deja como eliminado, inactivo)
            system("cls");

            if(usuario.eliminado == 0)
            {
                printf("\nEl Usuario ya se encontraba dado de baja. ");
            }
            else
            {
                usuario.eliminado = 0;
                printf("El usuario acaba de ser dado de baja. \n");
            }

            system("pause");
            system("cls");
            break;

        default:
            system("cls");
            printf("\n Ha ingresado una opción inválida. \n");
            system("pause");
            system("cls");
            break;
    }
    return usuario;
}

stUsuario modificarContrasenia(stUsuario usuario) // funcion aux de la ppal (que se ocupa de todas las modificaciones). Esta modifica el pass del usuario
{
    char contrasenia[10];

    desencriptaContras(usuario.pass,contrasenia);//Desencripta la contrasenia
    printf("Esta es su contrasenia actual \n");
    mostrarArregloChar(contrasenia); // Muestra al usuario su contraseña actual ya desencriptada
    printf("Ingrese su nueva contrasenia \n");
    fflush(stdin);
    cargaYchequeaContrasenia(contrasenia); //Carga la nueva contrasenia que ingresa el user
    puts("Esta es su nueva contrasenia \n");
    mostrarArregloChar(contrasenia);
    encriptaContras(contrasenia,usuario.pass); //Encripta la nueva contaseña y la guarda en el campo pass del usuario a modificar

    return usuario;
}

stUsuario modificarUsuario(stUsuario usuario) // funcion aux de la ppal. (que se ocupa de todas las modificaciones). Esta modifica el nombre de user
{
    printf("Ingrese su nuevo nombre de usuario \n");
    fflush(stdin);
    gets(usuario.usuario);
    return usuario;
}

int comprobarID(stUsuario Usuario) //Comprueba el ID
{
    int a=0;
    FILE*fp;
    fp = fopen(Programa,"rb");
    stUsuario aux;
    while(fread(&aux,sizeof(stUsuario),1,fp)>0)
    {
        if(aux.id_cliente== Usuario.id_cliente)
        {
            printf("El ID ya existe \n");
            a=1;
        }
    }
    fclose(fp);
    return a; //retorna 1 si el ID ya existe
}

void Cantidad_Registro()
{
    FILE*fp=fopen(Programa,"rb");
    int i;
    long f;
    fseek(fp,0,SEEK_END);
    f=ftell(fp);
    i=f/sizeof(stUsuario);
    printf("La cantidad de registro es de: %d \n",i);
    fclose(fp);
}

//Conocer la cantidad de registros que tiene una estructura
int Cantidad_Registro_Estructura()
{
    FILE*fp;

    fp = fopen(Programa,"rb");
    float i;
    long f;
    fseek(fp,0,SEEK_END);
    f = ftell(fp);
    i = f/sizeof(stCliente);

    fclose(fp);
    return i;
}
//Lee la estructura del cliente
void leerStructClient()
{
    stCliente client;
    FILE *fp;
    fp = fopen(ProgramaClient,"rb");
    while(fread(&client, sizeof(stCliente),1,fp)>0)
    {
        printf("Nombre: %s\n",client.nombre);
    }

    fclose(fp);
}
//Lee la estructura del usuario
void leerStructUser()
{
    stUsuario a;
    FILE*fp;
    fp=fopen(Programa,"rb");
    while (fread(&a, sizeof(stUsuario),1,fp)>0)
    {
        printf("Nombre: %s\n",a.usuario);
    }
    fclose(fp);
}
//Menu prinicipal con 3 casos + default
void menuPrincipal()
{
    printf("~ BIENVENIDO ~\n");
    printf("~ SISTEMA DE SUPERMERCADO UTN ~\n");
    printf("~ MENU PRINCIPAL ~\n\n");
    printf("1~ Administracion de Usuario \n" );
    printf("2~ Login \n" );
    printf("0~ Salir del Sistema\n");
}
///

void cargarMatrizEncriptada(float m[2][5],float encriptada[2][5])
{
    int i,j;

    for(i=0; i<2; i++)
    {
        for(j=0; j<5; j++)
        {
            m[i][j] = encriptada[i][j];
        }
    }
}

//Carga los datos del usuario y devuelve un usuario
stUsuario CargarUsuario()
{
    char contrasenia[10];
    float encriptada[2][5];
    stUsuario user;
    printf("ingrese su username (Nick): \n");
    fflush(stdin);
    gets(user.usuario);
    printf("Ingrese su Nombre \n");
    fflush(stdin);
    gets(user.nombre);
    printf("Ingrese su apellido \n");
    fflush(stdin);
    gets(user.apelllido);
    printf("ingrese su ID \n");
    fflush(stdin);
    scanf("%i", &user.id_cliente);

    cargaYchequeaContrasenia(contrasenia);
    encriptaContras(contrasenia,encriptada);
    cargarMatrizEncriptada(user.pass,encriptada);

    user.eliminado=1;//el 1 indica que no esta eliminado

    return user;
}
//Comprueba si el nombre de usuario existe
int Comprobar_Nombre_Usuario(stUsuario Usuario)
{
    int a=0;
    FILE*fp;
    fp=fopen(Programa,"rb");
    stUsuario aux;
    while(fread(&aux,sizeof(stUsuario),1,fp)>0)
    {
        if(strcmp(aux.usuario,Usuario.usuario)==0)
        {
            printf("El usuario ya existe \n");
            a=1;
        }
    }
    fclose(fp);
    return a;
}

///Grabar file usuario
void agregarUsuario(stUsuario a)
{
    FILE*fp;
    fp = fopen(Programa,"ab");
    fwrite(&a,sizeof(stUsuario),1,fp);
    fclose(fp);
}

///Grabar file cliente
void agregarCliente(stCliente a)
{
    FILE*fp;
    fp = fopen(ProgramaClient,"ab");
    fwrite(&a,sizeof(stCliente),1,fp);
    fclose(fp);
}
int loguearUsuario()
{
    int a=-1;
    int flag = 0;
    char aux [50] = {0};
    stUsuario aux2;
    int i=0;
    FILE*fp;
    fp = fopen(Programa,"rb");

    while(a == -1)
    {
        printf("\nIngrese su nombre de usuario \n");
        fflush(stdin);
        gets(aux);

        fseek(fp,0, SEEK_SET); //en la 1º vuelta posiciona el cursor al inicio del archivo, pero en las posteriores vueltas del while, lo vuelve a
        // posicionar de nuevo al ppio del archivo para volver a recorrerlo leyéndolo

        while(fread(&aux2,sizeof(stUsuario),1,fp)>0) //lee el archivo con los usuarios cargados
        {
            //La funcion compara si el usuario es correcto, en caso de que si, devuelve 0
            if(strcmp(aux,aux2.usuario) == 0)
            {
                printf("Usuario valido \n\n");
                a = i;
            }
            i++;
        }
        //Compara, si el usuario no existe, te pide que lo vuelvas a ingresar
        if (a == -1)
        {
            printf("\n Usuario incorrecto.. \n");
        }
    }

    if(a > -1)
    {
        char contrasenia[10];
        float encriptada[2][5];

        cargaYchequeaContrasenia(contrasenia);
        encriptaContras(contrasenia,encriptada);

        //Funcion auxiliar que compara matrices, y devuelve 1 si las matrices son iguales
        flag = comparaMatrizEncript(encriptada,aux2.pass);

        while (flag == 0)
        {
            printf("\nContrasenia incorrecta \n");
            fflush(stdin);
            cargaYchequeaContrasenia(contrasenia);
            encriptaContras(contrasenia,encriptada);

            flag = comparaMatrizEncript(encriptada,aux2.pass); //Funcion auxiliar que compara matrices. Devuelve 1 si son iguales
        }
        printf("\nContrasenia correcta \n\n");
    }

    fclose(fp);

    return a;
}

///Comprueba si existe el usuario y la contrasenia
int comprobarUsernameAndPassword(stUsuario Usuario)
{
    int a=0;
    int b=1;
    int i = 0;
    int op;
    char control = 'y';
    FILE*fp;
    fp=fopen(Programa,"rb");
    stUsuario aux;
    stUsuario aux2;

    printf("Enter Username \n");
    fflush(stdin);
    gets(aux.usuario);

    while(a == 0)
    {
        while(a == 0)
        {
            if(strcmp(aux.usuario,Usuario.usuario)==0)
            {
                printf("User correct \n");
                a=1;
                system("PAUSE");
                system("CLS");
            }
            else
            {
                printf("User incorrect \n");

            }
        }


        if(strcmp(aux.pass,aux2.pass)==0)
        {
            printf("Contrasenia correcta \n");
            b=0;
        }
        else
        {
            printf("Contrasenia incorrecta \n");
        }

    }

    fclose(fp);
    return a;
}
///////

void Ver_listados_de_usuario()
{
    FILE *fp = fopen(Programa,"r+b");
    int i = 0;
    stUsuario usuario;
    stUsuario userAux[100];
    if(fp != NULL)
    {
        while(fread(&usuario,sizeof(stUsuario),1,fp)>0)
        {
            printf("Nick de Usuario: %s \n",usuario.usuario);
            printf("Nombre: %s \n",usuario.nombre);
            printf("Apellido: %s \n",usuario.apelllido);
            printf("ID: %i\n",usuario.id_cliente);
            if(usuario.eliminado==1)
            {
                printf("Usuario Activo \n");
            }
            else
            {
                printf("Usuario desactivado \n");
                printf("Posicion: %d \n",i+1);
                i++; // cant de registros leidos
            }

        }
    }
    fclose(fp);
}

void Ver_listados_de_cliente()
{
    FILE *archi = fopen(ProgramaClient,"r+b");
    int i = 0;
    stCliente cliente;
    if(archi != NULL)
    {
        while(fread(&cliente,sizeof(stCliente),1,archi)>0)
        {
            printf("Nombre del cliente: %s\n",cliente.nombre);
            printf("Apellido del cliente: %s\n",cliente.apelllido);
            printf("Tipo de cliente: %i\n",cliente.tipoCliente);
            printf("Medio de pago: %i\n",cliente.medioPago);
            printf("Cantidad de articulos: %i\n",cliente.cantArticulos);
            printf("El cliente esta o no activo: %i: \n",cliente.eliminado);
            printf("ID: %i\n",cliente.id);
            printf("Posicion: %d\n",i+1);
            i++; // cant de registros leidos
        }
    }
    fclose(archi);
}


void Ver_listados_de_cliente_Arreglo(stCliente a[100], int val)
{
    int i=0;
    while(i < val)
    {
        printf("Nombre del cliente: %s\n",a[i].nombre);
        printf("Apellido del cliente: %s\n",a[i].apelllido);
        printf("Tipo de cliente: %i\n",a[i].tipoCliente);
        printf("Medio de pago: %i\n",a[i].medioPago);
        printf("Cantidad de articulos: %i\n",a[i].cantArticulos);
        printf("El cliente esta o no activo: %i: \n",a[i].eliminado);
        printf("ID: %i\n",a[i].id);
        printf("Posicion: %d\n",i+1);
        i++; // cant de registros leidos
    }
}

void ConsultarUsuario()
{
    FILE * fp;
    fp = fopen(Programa,"rb");
    stUsuario a;
    char us[100];
    printf("Ingrese el Usuario que desea buscar \n");
    scanf("%s",&us);

    while(fread(&a,sizeof(stUsuario),1,fp)>0)
    {
        if(strcmpi(a.usuario,us)==0)
        {
            printf("Nombre de Usuario: %s\n",a.usuario);
            printf("ID: %i\n",a.id_cliente);
            if(a.eliminado == 1)
            {
                printf("Usuario Activo \n");
            }
            else
                printf("Usuario desactivado \n");
        }
    }

    fclose(fp);
}

int cuantosUsuariosHay()
{
    FILE *archi = fopen(Programa,"rb");
    stUsuario u;
    long longitud;
    int cantidad=0;

    fseek(archi,0,SEEK_END);
    longitud = ftell(archi);

    cantidad = (int)longitud/(int)sizeof(stUsuario);

    printf("Cantidad ingresada en el archivo: %d \n",cantidad);

    fclose(archi);

    return cantidad;
}

void MostraCliente(stCliente cliente)
{
    printf("Nombre del cliente: %s\n",cliente.nombre);
    printf("Apellido del cliente: %s\n",cliente.apelllido);
    printf("Tipo de cliente: %i\n",cliente.tipoCliente);
    printf("Medio de pago: %i\n",cliente.medioPago);
    printf("Cantidad de articulos: %i\n",cliente.cantArticulos);
    printf("El cliente esta o no activo: %i: \n",cliente.eliminado);
    printf("ID: %i\n",cliente.id);
}
void menuModificacionCliente()
{
    printf("1:\nModificar Nombre\n");
    printf("2:\nModificar Apellido\n");
    printf("3:\nModificar Tipo de cliente\n");
    printf("3:\nModificar Medio de pago\n");
    printf("3:\nCantidad de articulos\n");
    printf("3:\nEliminado o no\n");
    printf("0:\nSalir\n");
    printf("\n\n");
}


