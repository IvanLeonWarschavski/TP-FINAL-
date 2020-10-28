#ifndef STCLIENTE_H_INCLUDED
#define STCLIENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct
{
    int id;                 /// AUTOINCREMENTAL UNICO
    char nombre[30];
    char apellido[30];
    int dni;
    char email[30];
    char domicilio[45];
    char movil[30];
    int baja;

}stCliente;

void guardarCliente(stCliente c);
void mostrarCliente(stCliente c);
void muestraClientes();
void modificaCliente(stCliente c);
void modificarDatosCliente(int dni);
void listarClientesEnBaja();
void mostrarClienteEspecifico();
void ordenarArrClientes(stCliente c[],int v,char criterio);
void listarClientesEnAlta();
int buscaCliente(int dni);
int copiarBajas2Arr(stCliente c[], int v);
int copiarAltas2Arr (stCliente c[],int v);
int posMenorDNI(stCliente c[], int v, int pos);
int posMenorApellido(stCliente c[], int v, int pos);
int posMenorEmail(stCliente c[], int v, int pos);
stCliente copiaCliente(int dni);
stCliente cargarCliente();
stCliente cargarModificado(stCliente c);
int nuevoId();
int devolverIdXDNI(int dni);
void menuDarDeBajaCliente();

#endif // STCLIENTE_H_INCLUDED
