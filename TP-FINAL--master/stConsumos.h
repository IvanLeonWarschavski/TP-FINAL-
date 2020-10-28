#ifndef STCONSUMOS_H_INCLUDED
#define STCONSUMOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define FILECL "clientes.bin"
#define FILECO "consumos.bin"

typedef struct
{
    int id;              /// AUTOINCREMENTAL UNICO
    int idCliente;
    int anio;
    int mes;             /// 1 - 12
    int dia;             /// 1 - … (DEPENDE DEL MES)
    int datosConsumidos; /// MBs.
    int baja;            /// 0 = ACTIVO / 1 = INACTIVO

} stConsumos;

stConsumos cargarConsumo();
stConsumos copiaConsumo(int id);
void guardarConsumo(stConsumos c);
void guardaNuevoConsumo(stConsumos c);
void mostrarUnConsumo(stConsumos c);
void listarConsumos ();
void ordenararrConsumosXidCliente(stConsumos c[], int v);
void menuDarDeBajaConsumo();
void modificaConsumo(stConsumos c);
void menuCargaAleatoriaConsumoAnual();
void guardarArrDeConsumos(stConsumos arrConsumos[],int v);
void modificarUNConsumo();
int nuevoIdConsumos();
int copiarConsumos2Arreglo(stConsumos c[],int v, int mes, int dia);
int posMenorId(stConsumos c[], int v, int pos);
int arrConsumosAnual(int idCliente, stConsumos arrConsumos[], int v);
int buscaConsumo(int idCliente,int mes,int dia);
void cargarArrConsumo(int a[]);


#endif // STCONSUMOS_H_INCLUDED
