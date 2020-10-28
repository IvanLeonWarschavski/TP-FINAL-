#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "gotoxy.h"
#include "stCliente.h"
#include "stConsumos.h"

#define ESC 27
#define YEAR 2020
#define FILECL "clientes.bin"
#define FILECO "consumos.bin"


/*MENU*/

void menu();
void menuDarDeBajaCliente();
void subcli();
void subcon();
void menact();

/*VALIDACIONES*/
int validaEmail (char email[]); /// VALIDACION DE E-MAIL
int validaExistencia(int dni); /// VALIDACION DE DNI
int cantRegistros(); /// CONTADOR DE REGISTROS
int validaDNI();
int validaMes();
int validaDia(int mes);


/// ESTADISTICAS

void opcionEstadisticas();
void mostrarMenuEstadisticas();
void estadisticasCliente();
void dibujarBarras(int a[]);
void cargarArrConsumoCliente(int a[],int idCliente);
int devolverTotalMes(int idCliente,int mes);
int sumarArr(int a[]);
void mostrarPromedios(int a[]);
int posMayor(int a[]);
int posMenor(int a[]);
void porcentajesGlobales();
int contarRegistros(char nomArch[],int tamanioReg);
void cargaRandomClientes();
int cargaArrClientes(stCliente c[],int v,int n);
void guardarArrCliente(stCliente c[],int v);


int main()
{

    stCliente cliente;
    int dni;

    srand(time(NULL));

/// MENU ///

    char opcion;
    system("color d");

    do
    {
        system("cls");
        menu();
        opcion = getch();
        system("cls");

        switch (opcion)
        {
        case 49: ///                                     SUBMENU CLIENTES

            printf("\t\t\t\t<<<<---SUBMENU CLIENTES--->>>");

            do
            {
                system("cls");
                subcli();
                opcion = getch();
                system("cls");

                switch (opcion)
                {
                case 49: /// opcion 1
                    printf("\t\t\t\t<<<<---INGRESAR NUEVO CLIENTE--->>>");

                    guardarCliente(cargarCliente());

                    printf("\n\n\n");
                    system("pause");
                    break;

                case 50: /// opcion 2
                    printf("\t\t\t\t<<<<---DAR BAJA A CLIENTE--->>>");
                    menuDarDeBajaCliente();
                    printf("\n\n\n");
                    system("pause");
                    break;

                case 51: /// opcion 3
                    printf("\t\t\t\t<<<<---MODIFICAR CLIENTE--->>>");
                    printf("\n\nINGRESE DNI DEL USUARIO A MODIFICAR: ");
                    scanf("%d", &dni);
                    system("cls");
                    modificarDatosCliente(dni);
                    printf("\n\n\n");
                    system("pause");
                    break;

                case 52: /// opcion 4
                    printf("\t\t\t\t<<<<---LISTAR CLIENTES ACTIVOS--->>>");

                    do                           ///MENU ACTIVOS///
                    {
                        system("cls");
                        menact();
                        opcion = getch();
                        system("cls");

                        switch (opcion)
                        {
                        case 49: /// opcion 1
							listarClientesEnAlta();
                            break;

                        case 50: /// opcion 2
                            mostrarClienteEspecifico();
                            printf("\n\n\n");
                            system("pause");
                            break;
                        }
                    }
                    while (opcion!='5' && opcion!='6');
                    printf("\n\n\n");
                    break;                            ///MENU ACTIVOS///

                case 53: /// opcion 5
                    printf("\t\t\t\t<<<<---LISTAR CLIENTES INACTIVOS POR E-MAIL--->>>\n\n");
                    listarClientesEnBaja();
                    break;

				/*case 54:
					cargaRandomClientes();
					break;*/
                }

            }while (opcion!='9');
            break;

        case 50: /// opcion 2                             SUBMENU CONSUMOS

            printf("\t\t\t\t<<<<---SUBMENU CONSUMOS--->>>");
            do
            {
                system("cls");
                subcon();
                opcion = getch();
                system("cls");

                switch (opcion)
                {
                case 49: /// opcion 1
                    printf("\t\t\t\t<<<<---ALTA DE CONSUMOS--->>>");
                    guardarConsumo(cargarConsumo());

                    printf("\n\n\n");
                    system("pause");
                    break;

                case 50: /// opcion 2
                    printf("\t\t\t\t<<<<---BAJA DE CONSUMOS--->>>");
                    menuDarDeBajaConsumo();
                    printf("\n\n\n");
                    system("pause");
                    break;

                case 51: /// opcion 3
                    printf("\t\t\t\t<<<<---MODIFICACION DEL CONSUMO--->>>");
                    modificarUNConsumo();
                    printf("\n\n\n");
                    system("pause");
                    break;

                case 52: /// opcion 4
                    printf("\t\t\t\t<<<<---LISTADO DE CONSUMOS--->>>");
                    listarConsumos();
                    break;

                case 53: /// opcion 5
                    printf("\t\t\t\t<<<<---ESTADISTICAS DE LOS CONSUMOS--->>>");
                    opcionEstadisticas();
                    printf("\n\n\n");
                    ///system("pause");
                    break;

                case 54:
                    printf("\t\t\t\t\t<<<<---CARGA ALEATORIA --->>>");
                    printf("\n");
                    menuCargaAleatoriaConsumoAnual();
                    printf("\n\n\n");
                    ///system("pause");
                    break;
                }

            }
            while (opcion!='9');
            break;
        }

    }
    while (opcion!=ESC);

    system("cls");
    system("color a");
    printf("\n\n\n\n\n\n\n\t\t\t<<<<---GRACIAS POR ELEGIR UT MOVIL, ESPERAMOS VERLO/A PRONTO!--->>>\n\n\n\n\n\n\n\n\n\n\n");
    puts("\n\n\n\n\t------------------------------------------------------------------------------------------------------\n");
    printf("\tIVAN WARSCHAVSKI. TM - 2020");
    getch();
    system("cls");

    return 0;
}

/// MENU ///

void menu()
{
    printf("\n\t\t\t\t\t<<<<---UT Movil - MAIN MENU--->>>\n\n\n\n");
    printf("\tSELECCIONAR UNA OPCION.\n");
    printf("\t-----------------------\n\n\n");
    printf("\t[1] - CLIENTES\n\n");
    printf("\t[2] - CONSUMOS\n\n");
    puts("\n\n\t------------------------------------------------------------------------------\n");
    printf("\tIVAN WARSCHAVSKI. TM - 2020");
    printf("\t\t\t\t\t[ESC] TO QUIT.");
}

void subcli()                                                           /// SUBMENU CLIENTES
{
    printf("\n\t\t\t\t    <<<<---UT Movil - SUBMENU CLIENTES--->>>\n\n\n\n");
    printf("\tSELECCIONAR UNA OPCION.\n");
    printf("\t-----------------------\n\n");
    printf("\t[1] - INGRESAR UN NUEVO CLIENTE\n\n");
    printf("\t[2] - DAR BAJA A UN CLIENTE          \n\n");
    printf("\t[3] - MODIFICAR DATOS DEL CLIENTE  \n\n");
    printf("\t[4] - LISTAR CLIENTES ACTIVOS   \n\n");
    printf("\t[5] - LISTAR CLIENTES INACTIVOS \n\n");
    //printf("\t[6] - CARGAR CLIENTES RANDOM \n\n");
    puts("\n\n\t------------------------------------------------------------------------------\n");
    printf("\tIVAN WARSCHAVSKI. TM - 2020");
    printf("\t\t\t      [9] RETURN TO MAIN MENU.");
}

void subcon()                                                            /// SUBMENU CONSUMOS
{
    printf("\n\n\t\t\t    <<<<---UT Movil - SUBMENU CONSUMOS--->>>\n\n\n\n");
    printf("\tSelect an option.\n");
    printf("\t-----------------\n\n");
    printf("\t[1] - CREAR CONSUMO.\n\n");
    printf("\t[2] - DAR BAJA A UN CONSUMO.\n\n");
    printf("\t[3] - MODIFICAR UN CONSUMO.\n\n");
    printf("\t[4] - LISTADO DE CONSUMOS.\n\n");
    printf("\t[5] - ESTADISTICAS.\n\n");
    printf("\t[6] - CARGAR CLIENTE CON CONSUMOS RANDOM.\n\n");
    puts("\n\n\t------------------------------------------------------------------------------\n");
    printf("\tIVAN WARSCHAVSKI. TM - 2020");
    printf("\t\t\t      [9] RETURN TO MAIN MENU.");
}

void menact()                                                            /// SUBMENU CLIENTES ACTIVOS
{
    printf("\n\n\t\t\t     <<<<---MOSTRAR CLIENTES ACTIVOS--->>>\n\n\n\n");
    printf("\tSELECCIONAR UNA OPCION.\n");
    printf("\t----------------------\n\n");
    printf("\t[1] - MOSTRAR TODOS.\n\n");
    printf("\t[2] - BUSCAR CLIENTE ESPECIFICO.\n\n");
    puts("\n\n\t------------------------------------------------------------------------------\n");
    printf("\tIVAN WARSCHAVSKI. TM - 2020");
    printf("    [5] RETURN TO SUBMENU   [6] RETURN TO MAIN MENU.");
}


int cantRegistros()
{
    stCliente c;
    int cont=0;

    FILE *pArchCliente = fopen(FILECL, "rb");
    if(pArchCliente)
    {
        fseek(pArchCliente, 0, SEEK_END);
        cont = ftell(pArchCliente)/sizeof(stCliente);
        fclose(pArchCliente);
    }

    return cont;
}

/// VALIDACIONES ///

int validaEmail(char email[])
{

    int validos = strlen(email);
    int i=0;
    int flag = 0;

    while (i<validos && flag == 0)
    {
        if (email[i] == 64)
        {
            flag = 1;
        }
        i++;
    }
    return flag;
}

int validaExistencia(int dni)
{
    stCliente c;
    char opcion='s';

    FILE *pArchCliente = fopen(FILECL, "rb");
    if(pArchCliente)
    {
        while(fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(dni == c.dni)
            {
                system("cls");
                printf("\nDNI EXISTENTE EN BASE DE DATOS!\n");

                return -1;
            }
        }
        fclose(pArchCliente);
    }

    return dni;
}

int validaDia(int mes)
{
    int dia,limite=31;

	if(mes == 2)
    {
        if (YEAR%4==0 || (YEAR%100==0 && YEAR%400==0)) // en caso de que YEAR (const de año) sea bisiesto
		{
        	limite=limite-2; //29
        }
        else
		{
			limite=limite-3; //28
		}
    }
    else
	{
		if(mes == 4 || mes == 6 || mes == 9 || mes == 11)
		{
			limite=limite-1; //30
		}
	}

	printf("\n\t");
	do
	{
		printf("DIA (1-%d):       \b\b\b\b\b\b",limite);
		fflush(stdin);
		scanf("%d", &dia);

		if (dia<1 || limite<dia)
		{
			gotoxy(4,whereY()-1);
			printf("*DIA FUERA DE RANGO, ");
		}

	} while (dia<1 || limite<dia);

    return dia;
}

int validaMes() // solicita y retorna mes valido (1<mes<12)
{
    int mes;

	printf("\n\t");
    do
    {
        printf("INGRESE MES (1-12) :       \b\b\b\b\b\b");
        scanf("%d",&mes);

        if (mes<1 || mes>12)
        {
        	gotoxy(4,whereY()-1);
            printf("*MES FUERA DE RANGO, ");
        }
	}while (mes<1 || mes>12);

    return mes;
}

int validaDNI() // pide el dni del cliente y retorna id del cliente si lo encuentra, sino -1
{
    int dni, id,margen,encabezado;
    char opcion=0;


	do
    {
    	printf("\n\n\t\t");
        printf(" DNI :       \b\b\b\b\b\b");
        fflush(stdin);
        scanf("%d",&dni);

		id = buscaCliente(dni);
		if (id == -1)
        {
        	system("cls");
            printf("\n\t\t*DNI INGRESADO NO EXISTE");
            printf("\n\n\t\t[ENTER] REINTENTAR  - [ESC] SALIR\n\n");
            opcion=getch();
        }
    }while(opcion != 27 && id == -1);

    return id;
}

/// MENU ESTADISTICAS //////////////////////////////////////////////////////////////////////////////////////
void opcionEstadisticas()
{
	char op;

	do
	{
		system("cls");
		mostrarMenuEstadisticas();
		op=getch();
		system("cls");

		switch(op)
		{
			case '1':
				estadisticasCliente();
				break;

			case '2':
				estadisticasGlobales();
				break;

            case 27:
                    break;

			default:
				printf("\nOPCION NO VALIDA.\n");
		}

		printf("\n\n\n");

	} while (op!=27);
}

void mostrarMenuEstadisticas()
{
	printf("\t\t\t\t\t<<<<--MENU DE ESTADISTICAS--->>>>\n");
	printf("\n\n\tSELECCIONAR UNA OPCION.\n");
    printf("\t-----------------------\n");
	printf("\n\t[1] - ESTADISTICAS DE UN CLIENTE EN PARTICULAR.");
	printf("\n");
	printf("\n\t[2] - ESTADISTICAS GLOBALES.");
	puts("\n\n\t------------------------------------------------------------------------------\n");
    printf("\tCOMICOS CUBICOS. TM - 2020");
    printf("\t\t\t\t\t[ESC] VOLVER.");
}

void estadisticasCliente()
{
    int consumosXMes[13];
	int idCliente;

	printf("\t\t\t\t\t<<<<--MENU DE ESTADISTICAS--->>>>\n");
	printf("\n\n\n");
	printf("\n\tINGRESE DNI A BUSCAR PARA MOSTRAR ESTADISTICAS.");
	printf("\n");

	idCliente = validaDNI();

	if (idCliente != -1)
    {
        system("cls");

        printf("\t\t\t\t\t<<<<--ESTADISTICAS DEL CLIENTE--->>>>\n");
        printf("\n\tCLIENTE :	 APELLIDO, NOMBRE  |  DNI  |  E-MAIL  |  DOMICILIO  |  MOVIL  |  CONDICION\n");

        mostrarCliente(copiaCliente(idCliente));

        cargarArrConsumoCliente(consumosXMes, idCliente);

		if(sumarArr(consumosXMes)==0)
		{
			printf("\n\n\t\tEL CLIENTE NO POSEE NINGUN CONSUMO\n\n\t");
		}
		else
		{
			mostrarPromedios(consumosXMes);

			gotoxy(40,6);

			dibujarBarras(consumosXMes);
		}

		printf("\n");
		system("pause");
	}
}

void dibujarBarras(int a[])
{
	int margen,encabezado,y,i,total;
	float porc,j;

	margen=whereX();
	encabezado=whereY();

	gotoxy(margen,encabezado);

	for (y=0;y<27;y++)
	{
		printf("|");
		gotoxy(margen,whereY()+1);
	}

	gotoxy(margen+3,encabezado+1);

	printf("CANTIDAD DE DATOS CONSUMIDOS POR MES");

	gotoxy(margen,whereY()+1);

	for (i=1;i<13;i++)
	{
		j=0;

		gotoxy(margen+1,whereY()+1);

		printf(" MES %d:\t%d\t",i,a[i]);

		total=sumarArr(a);
		if (total==0)
		{
			porc=0;
		}
		else
		{
			porc=(float)a[i]/total*100;
		}

		while( j < porc)
		{
			color(i*16+1);
			printf(" ");
			color(13);
			j=j+2;
		}

		printf(" (%.2f%%)",porc);
		printf("\n");
	}

	gotoxy(margen+1,whereY()+1);
	printf("-----------------------------------------------------------");
}

void cargarArrConsumoCliente(int a[],int idCliente)
{
	int i;

	for (i=1;i<13;i++)
	{
		a[i]=devolverTotalMes(idCliente,i);
	}

}

int devolverTotalMes(int idCliente,int mes) // devuelve la cantidad de datos consumidos en el mes y cliente recibido
{
	int total=0;
	stConsumos c;
	FILE *pArch = fopen(FILECO,"rb");

	if (pArch)
	{
		while (fread(&c,sizeof(stConsumos),1,pArch)>0)
		{
			if (c.mes==mes && c.idCliente==idCliente)
			{
				total=total+c.datosConsumidos;
			}
		}
		fclose(pArch);
	}

	return total;
}

int sumarArr(int a[])
{
	int total=0,i;

	for (i=1;i<=12;i++)
	{
		total=total+a[i];
	}

	return total;
}

void mostrarPromedios(int a[])
{
	int total,i,margenX,margenY;

	total=sumarArr(a);

	if (total!=0)
	{
		printf("\n\n\n PROMEDIO DE DATOS CONSUMIDOS:\n");
		printf("\n\t* POR DIA : %.1f MBs/DIA\n",(float)(total/366));
		printf("\n\t* POR MES : %.1f MBs/MES",(float)(total/12));

		printf("\n\n\n MES CON MENOR CONSUMO:\n");
		i=posMenor(a);
		printf("\n\t*MES %d : %d MBs",i,a[i]);

		printf("\n\n MES CON MAYOR CONSUMO:\n");
		i=posMayor(a);
		printf("\n\t*MES %d : %d MBs",i,a[i]);
		printf("\n\n-------------------------------------------\n");
	}
}

int posMayor(int a[])
{
	int i,posMayor,mayor;

	posMayor=1;
	mayor=a[1];

	for (i=2;i<=12;i++)
	{
		if (a[i]>mayor)
		{
			mayor=a[i];
			posMayor=i;
		}
	}

	return posMayor;
}

int posMenor(int a[])
{
	int i,posMenor,menor;

	posMenor=1;
	menor=a[1];

	for (i=2;i<=12;i++)
	{
		if (a[i]<menor)
		{
			menor=a[i];
			posMenor=i;
		}
	}

	return posMenor;
}

/// ESTADISTICAS GLOBALES /////////////////////////////////////////////////////////////////////////////////////////////////////////

void estadisticasGlobales()
{
	int consumosXMes[13];
	int i;

	printf("\t\t\t\t\t<<<<--ESTADISTICAS GLOBALES--->>>>\n");

	gotoxy(1,1);

	cargarArrConsumo(consumosXMes);

	mostrarPromedios(consumosXMes);

	porcentajesGlobales();

	gotoxy(40,2);

	dibujarBarras(consumosXMes);

	gotoxy(0,30);
	system("pause");
}

void porcentajesGlobales()
{
	int bajas=0,total;
	float porcBajas;
	stCliente aux[500];

	total=contarRegistros(FILECL,sizeof(stCliente));
	bajas=copiarBajas2Arr(aux,bajas);

	if (bajas==0)
	{
		porcBajas=0;
	}
	else
	{
		porcBajas=(float)bajas/total*100;
	}

	printf("\n PORCENTAJE DE CLIENTES :");
	printf("\n\n\tACTIVOS   : %.1f %%",100-porcBajas);
	printf("\n\n\tINACTIVOS : %.1f %%",porcBajas);
}

int contarRegistros(char nomArch[],int tamanioReg) //cantidad de registros = (nombre del archivo,tamañoXreg)
{
	int total;
	FILE *pArch=fopen(nomArch,"rb");

	if (pArch)
	{
		fseek(pArch,0,SEEK_END);
		total=ftell(pArch)/tamanioReg;
		fclose(pArch);
	}
	return total;
}



