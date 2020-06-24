#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "gotoxy.h"


#define ESC 27
#define YEAR 2020
#define FILECL "clientes.bin"
#define FILECO "consumos.bin"

typedef struct	///cliente
{
    int id; /// AUTOINCREMENTAL UNICO
    char nombre[30];
    char apellido[30];
    int dni;
    char email[30];
    char domicilio[45];
    char movil[30];
    int baja;

} stCliente;

typedef struct	///consumo
{
    int id;              /// AUTOINCREMENTAL UNICO
    int idCliente;
    int anio;
    int mes;             /// 1 - 12
    int dia;             /// 1 - … (DEPENDE DEL MES)
    int datosConsumidos; /// MBs.
    int baja;            /// 0 = ACTIVO / 1 = INACTIVO
} stConsumos;

/// PROTOTIPADOS CLIENTES ///

/*MENU*/

void menu();
void menuDarDeBajaCliente();
void subcli();
void subcon();
void menact();

/*VOID*/

void guardarCliente(stCliente c);
void mostrarCliente(stCliente c);
void muestraClientes();
void modificaCliente(stCliente c);
void modificarDatosCliente(int dni);
void listarClientesEnBaja();
void ordenarClientesBaja(stCliente c[], int v);	/// seleccion
void mostrarClienteEspecifico();
void ordenarArrClientes(stCliente c[],int v,char criterio);
void listarClientesEnAlta();

/*INT*/

int validaEmail (char email[]); /// VALIDACION DE E-MAIL
int validaExistencia(int dni); /// VALIDACION DE DNI
int cantRegistros(); /// CONTADOR DE REGISTROS
int devolverIdXDNI(int dni); ///
int nuevoId();
int copiarBajas2Arr(stCliente c[], int v);
int copiarAltas2Arr (stCliente c[],int v);
int posMenorDNI(stCliente c[], int v, int pos);
int posMenorApellido(stCliente c[], int v, int pos);
int posMenorEmail(stCliente c[], int v, int pos);
int buscaCliente(int dni);
int validaDNI();
int validaMes();

/*STCLIENTE*/

stCliente copiaCliente(int dni);
stCliente cargarCliente();
stCliente cargarModificado(stCliente c);
stCliente buscaUnClienteDNI(int dni);

/// PROTOTIPADOS CONSUMOS ///

/*STCONSUMOS*/

stConsumos cargarConsumo();
stConsumos copiaConsumo(int id);

/*VOID*/

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


/*INT*/

int nuevoIdConsumos();
int validaDia(int mes);
int copiarConsumos2Arreglo(stConsumos c[],int v, int mes, int dia);
int posMenorId(stConsumos c[], int v, int pos);
int arrConsumosAnual(int idCliente, stConsumos arrConsumos[], int v);
int getConsumo();

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
    printf("\tCOMICOS CUBICOS. TM - 2020");
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
    printf("\tCOMICOS CUBICOS. TM - 2020");
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
    printf("\tCOMICOS CUBICOS. TM - 2020");
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
    printf("\tCOMICOS CUBICOS. TM - 2020");
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
    printf("\tCOMICOS CUBICOS. TM - 2020");
    printf("    [5] RETURN TO SUBMENU   [6] RETURN TO MAIN MENU.");
}

/// FUNCIONES CLIENTES///

stCliente cargarCliente()
{
    stCliente c;
    int dniingresado;
    int valid;

    int valem;

    printf("\n\n\tDNI: ");
    scanf("%d", &dniingresado);
    valid = validaExistencia(dniingresado);

/// Si validaExistencia retorna -1 el DNI esta repetido y corta el ciclo, si no es -1, este retorna un DNI valido y continua ///

    if(valid != -1)
    {

        c.dni = valid;

        c.id = nuevoId(); /// Incrementa el ID ///

        printf("\nNOMBRE: ");
        fflush(stdin);
        gets(c.nombre);

        printf("\nAPELLIDO: ");
        fflush(stdin);
        gets(c.apellido);

        printf("\nEMAIL: ");
        fflush(stdin);
        gets(c.email);
        valem = validaEmail(c.email);

        while(!valem)  /// hasta que no exista un @ en el email no avanza en la carga.
        {
            system("cls");
            printf("\nERROR: EMAIL INVALIDO, INGRESE NUEVAMENTE: ");
            fflush(stdin);
            gets(c.email);
            valem = validaEmail(c.email);

        }

        printf("\nDOMICILIO: ");
        fflush(stdin);
        gets(c.domicilio);

        printf("\nT. CELULAR: ");
        gets(c.movil);

        c.baja = 0;

        return c;
    }
    else /// El ID retornara -1 en caso de ser repetido el DNI y no se cargara ///
    {
        c.id = -1;
        return c;
    }
}

void mostrarCliente(stCliente c)
{
	//printf("\n\t\t\tID :%d",c.id);
    printf("\n\t\t\t%s, ",c.apellido);
    printf("%s ",c.nombre);
    printf("| %d ",c.dni);
    printf("| %s ",c.email);
    printf("| %s ",c.domicilio);
    printf("| %s ",c.movil);
    printf("| %s",(c.baja)? "INACTIVO":"ACTIVO");
    printf("\n\t\t\t\b---------------------------------------------------------------------------------");
}

void muestraClientes()  /// funcion que se usa en la opcion LISTAR CLIENTES ACTIVOS y muestra si hay o no clientes en alta.
{
    stCliente c;
    int flag = 0;
    FILE *pArchCliente = fopen(FILECL,"rb");
    if (pArchCliente)
    {
        while (fread(&c,sizeof(stCliente),1,pArchCliente) > 0)
        {
            if (c.baja == 0)
            {
                mostrarCliente(c);
                flag = 1;
            }
        }

        if(flag == 0)
        {
            printf("\n\n\n NO HAY CLIENTES ACTIVOS EN EL REGISTRO!\n");
        }
        fclose(pArchCliente);
    }

}

void guardarCliente(stCliente c)
{
    FILE *pArchCliente = fopen(FILECL, "ab");
    if(pArchCliente)
    {
        if(c.id != -1) /// Si recibe un ID = -1, no se cargara al archivo ///
        {
            fwrite(&c, sizeof(stCliente), 1, pArchCliente);
        }
        fclose(pArchCliente);
    }
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

int devolverIdXDNI(int dni)
{
    stCliente c;
    FILE *pArchCliente = fopen(FILECL,"rb");
    int flag = -1;

    if (pArchCliente)
    {
        while (flag == -1 && fread(&c,sizeof(stCliente),1,pArchCliente) > 0)
        {
            if (c.dni == dni)
            {
                flag = c.id;
            }
        }
        fclose(pArchCliente);
    }

    return flag;
}

stCliente copiaCliente(int id)
{
    stCliente c,aux;
    FILE *pArchCliente=fopen(FILECL,"rb");

    if (pArchCliente)
    {
        while (fread(&aux,sizeof(stCliente),1,pArchCliente) > 0)
        {
            if (aux.id == id)
            {
                c=aux;
            }
        }

        fclose(pArchCliente);
    }

    return c;
}

void modificaCliente(stCliente c) /// funcion usada en la opcion MODIFICAR CLIENTE del menu clientes.
{
    stCliente aux;
    int flag = 0;

    FILE *pArchCliente = fopen(FILECL,"r+b");
    if (pArchCliente)
    {
        while(flag == 0 && fread(&aux, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(c.id == aux.id)
            {
                fseek(pArchCliente, -sizeof(stCliente), SEEK_CUR);
                fwrite(&c,sizeof(stCliente),1,pArchCliente);
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
}

void menuDarDeBajaCliente() /// funcion que da de baja un cliente, teniendo en cuenta si ya estaba o no dado de baja y si existe dicho
/// cliente en el archivo.
{
    stCliente c;
    char opcion = 's';
    int dni;

    do
    {
        printf("\n\nINGRESE DNI DEL USER A BUSCAR: ");
        scanf("%d", &dni);
        system("cls");

        if (buscaCliente(dni)==-1)
        {
            printf("\nEL CLIENTE NO EXISTE EN EL ARCHIVO.");
        }
    }while(buscaCliente(dni)==-1);

    c=copiaCliente(buscaCliente(dni));

    mostrarCliente(c);

    if(c.baja == 1)
    {
        printf("\n\nDICHO DNI YA SE ENCUENTRA DADO DE BAJA.");
    }
    else
    {
        printf("\nDESEA DAR DE BAJA? (S/N)\n");
        fflush(stdin);
        opcion = getch();

        if (opcion == 's')
        {
            c.baja = 1;
            modificaCliente(c);
            system("cls");
            printf("\n\nCLIENTE MODIFICADO!\n");
        }
    }



}

int nuevoId() /// comprueba el ultimo ID para asignar uno nuevo.
{
    int id=0;
    stCliente c;
    FILE *pArch = fopen(FILECL, "rb");

    if(pArch)
    {
        fseek(pArch, sizeof(stCliente)*(-1), SEEK_END);
        if(fread(&c, sizeof(stCliente), 1, pArch) > 0)
        {
            id = c.id;
        }
        fclose(pArch);
    }

    return id+1;
}

void modificarDatosCliente(int dni)
{
    stCliente c;

    int flag = 0;
    FILE *pArchCliente = fopen(FILECL,"rb");
    if (pArchCliente)
    {
        while (flag == 0 &&fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if (c.dni == dni)
            {
                c = cargarModificado(c);
                modificaCliente(c);
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("\n\nNO SE ENCONTRO EL DNI INGRESADO!");
        }
        fclose(pArchCliente);
    }

}

stCliente cargarModificado(stCliente c)
{
    stCliente m;
    int dniingresado;
    int valid;
    int valem;
    char op;

    do
    {
        op = 'n';
        printf("\nUSUARIO A MODIFICAR: \n");
        mostrarCliente(c);

        printf("\nINGRESE NUEVO DNI: ");
        scanf("%d", &dniingresado);
        valid = validaExistencia(dniingresado);

        if(valid == -1 && dniingresado != c.dni)
        {
            c.id = -1;
            return m;
        }

        if(dniingresado == c.dni)
        {
            printf("\nSE MODIFICARA EL DNI: [%d]", c.dni);
            printf("\n\nCONTINUAR? s/n");
            op = getch();
        }
        else
        {
            op = 's';
        }

        if(op == 's')
        {
            system("cls");

            m.dni = dniingresado;
            printf("\nNUEVO DNI INGRESADO: [%d]", m.dni);

            m.id = c.id;

            printf("\n\nNOMBRE: ");
            fflush(stdin);
            gets(m.nombre);

            printf("\nAPELLIDO: ");
            fflush(stdin);
            gets(m.apellido);

            printf("\nEMAIL: ");
            fflush(stdin);
            gets(m.email);
            valem = validaEmail(m.email);

            while(!valem)
            {
                system("cls");
                printf("\nERROR: EMAIL INVALIDO, INGRESE NUEVAMENTE: ");
                fflush(stdin);
                gets(m.email);
                valem = validaEmail(m.email);
            }

            printf("\nDOMICILIO: ");
            fflush(stdin);
            gets(m.domicilio);

            printf("\nT. CELULAR: ");
            fflush(stdin);
            scanf("%s",m.movil);

            printf("\nESTADO DE BAJA ACTUAL: [%d]", c.baja);
            printf("\n\nMODIFICAR BAJA 1/0: ");
            scanf("%d", &m.baja);

            while(m.baja < 0 || m.baja > 1)
            {
                system("cls");
                printf("\nMODIFICAR BAJA 1/0: ");
                scanf("%d", &m.baja);
            }

            return m;
        }
    }
    while(op == 's');

    if(op=='n')
    {
        system("cls");
        printf("\nUSTED HA ELEGIDO NO CONTINUAR.");
        c.id = -1;
        return m;
    }
}

int copiarBajas2Arr(stCliente c[],int v)  /// esta funcion copia a un arreglo los clientes cuya baja = 1.
{
    FILE *pArch=fopen(FILECL,"rb");
    stCliente aux;

    if (pArch)
    {
        while (fread(&aux,sizeof(stCliente),1,pArch) > 0)
        {
            if (aux.baja == 1)
            {
                c[v]=aux;
                v++;
            }
        }
        fclose(pArch);
    }

    return v;
}

int posMenorEmail(stCliente c[], int v, int pos) // pos menor email =(arreglo clientes,validos,pos inicio)
{
    int i=pos;
    int posMenor=i;
    char minEmail[30];

    strcpy(minEmail, c[i].email);

    i++;

    while(i<v)
    {
        if (strcmp(c[i].email, minEmail) < 0)
        {
            strcpy(minEmail, c[i].email);
            posMenor=i;
        }
        i++;
    }

    return posMenor;
}

void ordenarArrClientes(stCliente c[],int v,char criterio) //(arreglo de clientes, validos,criterio de ordenamiento)
{
	int i=0;
    int posMenor;
    stCliente aux;

    while (i<v)
    {
    	switch (criterio)
		{
			case '1':
				posMenor=posMenorDNI(c,v,i);
				break;

			case '2':
				posMenor=posMenorApellido(c,v,i);
				break;

			case '3':
				posMenor=posMenorEmail(c,v,i);
				break;

			default:
				printf("\nERROR");
		}
		aux=c[i];
		c[i]=c[posMenor];
		c[posMenor]=aux;
		i++;
	}

}

void listarClientesEnAlta()	// lista clientes en alta, dando opcion de elegir criterio de ordenamiento
{
	stCliente c[500];
	int i,v=0,totalPags,pag;
	char opcion;

	v=copiarAltas2Arr(c,v);

	printf("\n\n\t\t\t\t<<<<---LISTAR CLIENTES ACTIVOS--->>>");
	printf("\n\n");

	if (v==0)
	{
		printf("\n\n\n\n\t\t\t\t\tSIN CLIENTES ACTIVOS\n\n\n");
		system("pause");
	}
	else
	{
		printf("\n\tSELECCIONAR CRITERIO.");
		printf("\n\t---------------------");
		printf("\n\n\t[1] - POR DNI");
		printf("\n\n\t[2] - POR APELLIDO\n\n\n");
		printf("\n\t-----------------------------------------------------------------------\n\n");
		printf("\tCOMICOS CUBICOS. TM - 2020 \t\t[Esc] - VOLVER AL MENU CLIENTES\n");
		opcion=getch();

		if (opcion=='1' || opcion=='2')
		{
			ordenarArrClientes(c,v,opcion); // ordena el arreglo por el metodo elegido

			totalPags=v/5+1;
			if (v%5==0)	//en caso de que justo  sea divisible por 5
			{
				totalPags=totalPags-1;
			}

			pag=0;

			do
			{
				system("cls");

				printf("\n\n\t\t\t\t\t<<<<---LISTADO DE CLIENTES ACTIVOS--->>>\n\n\n\n");
				if (pag<0)
				{
					pag=totalPags-1;
				}
				else
				{
					if (pag+1>totalPags)
					{
						pag=0;
					}
				}

				i=pag*5;
				printf("\n\n\t\t\tAPELLIDO, NOMBRE  |  DNI  |  E-MAIL  |  DOMICILIO  |  MOVIL  |  CONDICION\n");
				printf("\t\t------------------------------------------------------------------------------------------\n");
				while(i<(pag+1)*5 && i<v)
				{
					mostrarCliente(c[i]);
					i++;
				}
				printf("\n\n\n\n\t\t------------------------------------------------------------------------------------------\n");
				printf("\t\t\t[4]-PAG. ANT.<<<		PAGINA %d/%d		>>>[6]-PAG. SIG.",pag+1,totalPags);
				printf("\n\n\t\t\t\t\t\t\t\t\t\t\t[ESC] SALIR\n");

				opcion=getch();
				if (opcion=='4')
				{
					pag=pag-1;
				}
				else
				{
					if(opcion=='6')
					{
						pag=pag+1;
					}
				}
			} while (opcion!=27);
		}
	}
}

int posMenorApellido (stCliente c[], int v, int pos)
{
    int i=pos;
    int posMenor=i;
    char minApellido[30];

    strcpy(minApellido, c[i].apellido);

    i++;

    while(i<v)
    {
        if (strcmp(c[i].apellido, minApellido) < 0)
        {
            strcpy(minApellido, c[i].apellido);
            posMenor=i;
        }
        i++;
    }

    return posMenor;

}

int posMenorDNI(stCliente c[], int v, int pos)
{
    int i=pos;
    int posMenor=i;
    i++;


    while(i<v)
    {
        if (c[i].dni < c[posMenor].dni)
        {
            posMenor=i;
        }
        i++;
    }


    return posMenor;
}

void listarClientesEnBaja()                      /// LISTAR BAJA ///
{
    stCliente c[100];
	int i,v=0,totalPags,pag;
	char opcion;

    v=copiarBajas2Arr(c, v);

	if (v==0)
	{
		printf("\n\n\n\n\t\t\t\t\tSIN CLIENTES INACTIVOS\n\n\n");
		system("pause");
	}
	else
	{
		ordenarArrClientes(c,v,'3');

		totalPags=v/5+1;
		if (v%5==0)	//en caso de que justo  sea divisible por 5
		{
			totalPags=totalPags-1;
		}

		pag=0;

		do
		{
			system("cls");

			printf("\n\n\t\t\t\t\t<<<<---LISTADO DE CLIENTES INACTIVOS--->>>\n\n\n\n");
			if (pag<0)
			{
				pag=totalPags-1;
			}
			else
			{
				if (pag+1>totalPags)
				{
					pag=0;
				}
			}

			i=pag*5;
			printf("\n\n\t\t\tNOMBRE Y APELLIDO  |  DNI  |  E-MAIL  |  DOMICILIO  |  MOVIL  |  CONDICION\n");
			printf("\t\t------------------------------------------------------------------------------------------\n");
			while(i<(pag+1)*5 && i<v)
			{
				mostrarCliente(c[i]);
				i++;
			}
			printf("\n\n\n\n\t\t------------------------------------------------------------------------------------------\n");
			printf("\t\t\t[4]-PAG. ANT.<<<		PAGINA %d/%d		>>>[6]-PAG. SIG.",pag+1,totalPags);
			printf("\n\n\t\t\t\t\t\t\t\t\t\t\t[ESC] SALIR\n");

			opcion=getch();
			if (opcion=='4')
			{
				pag=pag-1;
			}
			else
			{
				if(opcion=='6')
				{
					pag=pag+1;
				}
			}
		} while (opcion!=27);
	}
}

int buscaCliente(int dni)  /// funcion usada en el menu clientes para buscar un cliente por dni.
{
    FILE *pArch=fopen(FILECL,"rb");
    stCliente c;
    int id=-1;

    if (pArch)
    {
        while (fread(&c,sizeof(stCliente),1,pArch)>0)
        {
            if (c.dni == dni)
            {
                id=c.id;
            }
        }
        fclose(pArch);
    }

    return id;
}

int copiarAltas2Arr (stCliente c[],int v)  /// esta funcion copia a un arreglo los clientes cuya baja = 0.
{
    FILE *pArch=fopen(FILECL,"rb");
    stCliente aux;

    if (pArch)
    {
        while (fread(&aux,sizeof(stCliente),1,pArch) > 0)
        {
        	if (aux.baja == 0)
            {
            	c[v]=aux;
                v++;
            }
        }
        fclose(pArch);
    }

    return v;
}

void mostrarClienteEspecifico()
{
	int idCliente;

	printf("\t\t\t\t<<<<---BUSCAR UN CLIENTE--->>>");
	printf("\n\n\tINGRESE DNI DE CLIENTE A BUSCAR : \n");

	idCliente=validaDNI();

	if (idCliente!=-1)
	{
		system("cls");
		printf("\n\n\t\t\t\t\t\tCLIENTE ENCONTRADO\n\n");
		printf("\n\n\t\t\tAPELLIDO, NOMBRE  |  DNI  |  E-MAIL  |  DOMICILIO  |  MOVIL  |  CONDICION\n");
		printf("\t\t------------------------------------------------------------------------------------------\n");
		mostrarCliente(copiaCliente(idCliente));
	}
}

/// FUNCIONES CONSUMOS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

stConsumos cargarConsumo()
{
    stConsumos c,aux;
    int dni, mes, dia, consumo;


    do
    {
        system("cls");
        printf("\n\nINGRESE DNI DEL USER A DAR CONSUMO: ");
        scanf("%d",&dni);

        if (buscaCliente(dni)==-1)
        {
            printf("\nEL CLIENTE NO EXISTE EN ARCHIVO.\n");
            system("pause");
        }
    }
    while(buscaCliente(dni)==-1);

    mostrarCliente(copiaCliente(buscaCliente(dni)));

    mes = validaMes();

    dia = validaDia(mes);

    if (buscaConsumo(buscaCliente(dni),mes,dia)!=-1)
    {
        system("cls");
        c=copiaConsumo(buscaConsumo(buscaCliente(dni),mes,dia));

        mostrarUnConsumo(c);

        printf("\nEL CONSUMO DEL CLIENTE EN LA FECHA ESPECIFICADA YA EXISTE.\n\n");
        printf("\nINGRESE CANTIDAD DE DATOS A AGREGAR (MBs) :");
        scanf("%d",&consumo);
        system("cls");
        printf("\n\n\n\n\n\n");
        printf("\n\n\n\n\n\n");
        printf("\t\t\t\t\tCONSUMO MODIFICADO CORRECTAMENTE!\n\n");
        printf("\n\n\n\n");
        printf("\n\n\n\n");
        printf("\n\n\n\n");

        c.datosConsumidos=c.datosConsumidos+consumo;
    }
    else
    {
        c.anio=YEAR;
        c.mes=mes;
        c.dia=dia;
        c.baja=0;
        c.id=nuevoIdConsumos();
        c.idCliente=buscaCliente(dni);

        printf("\nINGRESE LA CANTIDAD DE DATOS CONSUMIDOS (MBs) :");
        scanf("%d",&c.datosConsumidos);
    }

	return c;
}

int nuevoIdConsumos() // comprueba el ultimo ID para asignar uno nuevo.
{
    int id;
    stConsumos c;
    FILE *pArchConsumos = fopen(FILECO, "rb");

    if(pArchConsumos)
    {
        fseek(pArchConsumos, sizeof(stConsumos)*(-1), SEEK_END);
        if(fread(&c, sizeof(stConsumos), 1, pArchConsumos) > 0)
        {
            id = c.id;
        }
        fclose(pArchConsumos);
    }
    return id+1;
}

void guardarConsumo(stConsumos c)
{
    if(buscaConsumo(c.idCliente, c.mes, c.dia)!= -1)
    {
        modificaConsumo(c);
    }
    else
    {
        guardaNuevoConsumo(c);
    }
}

void guardaNuevoConsumo(stConsumos c)
{
    FILE *pArch=fopen(FILECO,"ab");

    if (pArch)
    {
        fwrite(&c,sizeof(stConsumos),1,pArch);
        fclose(pArch);
    }
}

void modificaConsumo(stConsumos c) /// Modifica el consumo que se pasa por parametro
{
    FILE *pArch = fopen(FILECO, "r+b");
    stConsumos aux;
    int flag = 0;

    if (pArch)
    {
        while(flag == 0 && fread(&aux, sizeof(stConsumos), 1, pArch) > 0)
        {
            if(c.idCliente == aux.idCliente && c.dia == aux.dia && c.mes == aux.mes)
            {
                fseek(pArch, sizeof(stConsumos)*(-1), SEEK_CUR);
                fwrite(&c, sizeof(stConsumos), 1, pArch);
                flag = 1;
            }
        }

        fclose(pArch);
    }
}

void mostrarUnConsumo(stConsumos c)
{
	stCliente cliente=copiaCliente(c.idCliente);
	printf("\n\t\t\t %s , %s ",cliente.apellido,cliente.nombre);
	printf("| %d ",cliente.dni);
    printf("| %d/%d/%d ",c.dia,c.mes,c.anio);
    printf("| %d MBs.",c.datosConsumidos);
    printf("| %s ",(c.baja)? "INACTIVO":"ACTIVO");
    printf("\n\t\t\t---------------------------------------------------------------------");

}

void listarConsumos()
{
    stConsumos c[1500];
    int v=0, i=0,mes,dia,pag,totalPags;
    char opcion;

    system("cls");
	printf("\n\tINGRESE DIA Y MES DEL CONSUMO QUE DESEA LISTAR :");
	printf("\n");

	mes=validaMes();

    dia=validaDia(mes);

    v = copiarConsumos2Arreglo(c,v,mes,dia);

    if (v==0)
	{
		printf("\n\n\n\n\t\t\t\t\tSIN CONSUMOS A LA FECHA ( %d / %d)\n\n\n",dia,mes);
		system("pause");
	}
	else
	{
		ordenararrConsumosXidCliente(c,v);

		totalPags=v/5+1;
		if (v%5==0)	//en caso de que justo  sea divisible por 5
		{
			totalPags=totalPags-1;
		}

		pag=0;

		do
		{
			system("cls");

			printf("\n\n\n\n\t\t\t\t\t CONSUMOS CON FECHA ( %d/%d/%d ) \n\n\n",dia,mes,YEAR);

			if (pag<0)
			{
				pag=totalPags-1;
			}
			else
			{
				if (pag+1>totalPags)
				{
					pag=0;
				}
			}

			i=pag*5;
			printf("\n\n\t\t\tAPELLIDO, NOMBRE  |  DNI  |  FECHA  |  DATOS CONSUMIDOS  |  ESTADO\n");
			printf("\t\t--------------------------------------------------------------------------------\n");
			while(i<(pag+1)*5 && i<v)
			{
				mostrarUnConsumo(c[i]);
				i++;
			}
			printf("\n\n\n\n\t\t------------------------------------------------------------------------------------------\n");
			printf("\n\t\t\t[4]-PAG. ANT.<<<		PAGINA %d/%d		>>>[6]-PAG. SIG.",pag+1,totalPags);
			printf("\n\n\t\t\t\t\t\t\t\t\t\t\t[ESC] SALIR\n");

			opcion=getch();
			if (opcion=='4')
			{
				pag=pag-1;
			}
			else
			{
				if(opcion=='6')
				{
					pag=pag+1;
				}
			}
		} while (opcion!=27);
	}
}

int copiarConsumos2Arreglo(stConsumos c[],int v,int mes,int dia)
{
    FILE *pArch=fopen(FILECO,"rb");
    stConsumos aux;

    if (pArch)
    {
        while (fread(&aux,sizeof(stConsumos),1,pArch) > 0)
        {
        	if(aux.mes==mes && aux.dia==dia)
            {
                c[v]=aux;
                v++;
            }
        }
        fclose(pArch);
    }

    return v;
}

void ordenararrConsumosXidCliente(stConsumos c[], int v)
{
    int i=0;
    int posMenor;
    stConsumos aux;

    while(i<v-1)
    {
        posMenor=posMenorId(c,v,i);
        aux=c[i];
        c[i]=c[posMenor];
        c[posMenor]=aux;
        i++;
    }
}

int posMenorId(stConsumos c[], int v, int pos)  /// BUSCAR MENOR ID ///
{
    int i=pos;
    int posMenor=i;
    i++;


    while(i<v)
    {
        if (c[i].idCliente < c[posMenor].idCliente)
        {
            posMenor=i;
        }
        i++;
    }
    return posMenor;
}

void menuDarDeBajaConsumo()
{
    stConsumos c;
    char opcion;
    int idCliente, id, dia, mes;

    idCliente=validaDNI();

    mes=validaMes();

    dia=validaDia(mes);

    id=buscaConsumo(idCliente,mes,dia);

    if (id!=-1)
    {
        c = copiaConsumo(id);

        if(c.baja == 1)
        {
            printf("\n\nDICHO CONSUMO YA SE ENCUENTRA DADO DE BAJA.");
        }
        else
        {
            mostrarUnConsumo(c);

            printf("\nDESEA DAR DE BAJA?(S/N)\n");
            fflush(stdin);
            opcion = getch();

            if (opcion == 's')
            {
                c.baja = 1;
                modificaConsumo(c);
                system("cls");

            }
        }
    }
    else
    {
        printf("\nEL CONSUMO CORRESPONDIENTE A ESA FECHA Y DNI, NO EXISTE.");
    }
}

stConsumos copiaConsumo(int id)	//devuelve un consumo del archivo, se le pasa el id del consumo
{
    stConsumos c,aux;
    FILE *pArch=fopen(FILECO,"rb");

    if (pArch)
    {
        while (fread(&aux,sizeof(stConsumos),1,pArch) > 0)
        {
            if (aux.id == id)
            {
                c=aux;
            }
        }
        fclose(pArch);
    }

    return c;
}

int buscaConsumo(int idCliente,int mes,int dia) // devuelve el id del consumo
{
    FILE *pArch=fopen(FILECO,"rb");
    stConsumos c;
    int id=-1;

    if (pArch)
    {
        while (fread(&c,sizeof(stConsumos),1,pArch)>0)
        {
            if (c.idCliente==idCliente && c.mes==mes && c.dia==dia)
            {
                id=c.id;
            }
        }
        fclose(pArch);
    }

    return id;
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

/// CARGA ALEATORIA CONSUMOS //////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menuCargaAleatoriaConsumoAnual()
{
    int idCliente, v = 0;
    stConsumos arrConsumos[366];

    idCliente = validaDNI();

    if (idCliente != -1)
    {
    	system("cls");
    	printf("\n\t\t\tCARGANDO CLIENTE  [");

    	v = arrConsumosAnual(idCliente, arrConsumos, v);

		guardarArrDeConsumos(arrConsumos, v);

		printf("]");
    	printf("\n\n\n\n");
		printf("\n\n\n\n\n");
		puts("\t\t\t\t-----------------------------------------------");
		printf("\n\t\t\t\t\tEL CLIENTE FUE CARGADO EXITOSAMENTE\n\n\n\t\t");
		puts("\t\t-----------------------------------------------");
		printf("\n\n\n\n\n");
		printf("\n\n\n\n\n");
		printf("\n\n\n\n\n");
		system("pause");
    }
}

int arrConsumosAnual(int idCliente, stConsumos arrConsumos[], int v)
{

    int d, m, id;

    for (m=1; m<13; m++)
    {
    	printf("#");
        int diasMax = 31;

        if (m == 2)
        {
            diasMax = diasMax-2;
        }
        else
        {
            if (m == 4 || m == 6 || m == 9 || m == 11)
            {
                diasMax = diasMax-1;
            }
        }

        for (d = 1; d < diasMax+1; d++)
        {
            id = buscaConsumo(idCliente, m, d);

             if(id != -1)
            {
                arrConsumos[v] = copiaConsumo(id);
                arrConsumos[v].datosConsumidos = arrConsumos[v].datosConsumidos + rand()%(200)+0;
            }
            else
            {
                arrConsumos[v].id = nuevoIdConsumos()+v;
                arrConsumos[v].idCliente = idCliente;
                arrConsumos[v].anio = 2020;
                arrConsumos[v].mes = m;
                arrConsumos[v].dia = d;
                arrConsumos[v].datosConsumidos = rand()%(200)+0;
                arrConsumos[v].baja = 0;
            }
            v++;
        }
    }
    return v;
}

void guardarArrDeConsumos(stConsumos arrConsumos[],int v)
{
    int i;

    for (i=0; i<v; i++)
    {
    	if (i%20==0)
    	{
    		printf("#");
    	}
    	guardarConsumo(arrConsumos[i]);
    }
}

void modificarUNConsumo()
{
    stConsumos c;
    int idCliente, mes, dia;
    int idtemp = -1;
    char baja;


	printf("\n\n\tINGRESE DNI DEL CLIENTE: \n\n\t");
    idCliente = validaDNI();
    mes = validaMes();
    dia = validaDia(mes);

    idtemp = buscaConsumo(idCliente, mes, dia);

    if(idtemp != -1)
    {
		c = copiaConsumo(idtemp);

		system("cls");
		printf("\n\n");
		printf("\n\tCONSUMO A MODIFICAR:\n");

		mostrarUnConsumo(c);

		printf("\n\n");
		printf("\n\tINGRESE DATOS CONSUMIDOS: ");
		scanf("%d", &c.datosConsumidos);

		printf("\n\tDAR DE BAJA? (S/N) :");
		baja=getch();

		if (baja=='s')
		{
			c.baja=1;
		}
		else
		{
			c.baja=0;
		}

		modificaConsumo(c);

		system("cls");

		printf("\n\n\t\tCONSUMO MODIFICADO\n\n");
		mostrarUnConsumo(c);
	}
    else
    {
		printf("\nCONSUMO INEXISTENTE!\n");
    }

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

void cargarArrConsumo(int a[]) // carga el arreglo de consumos por mes
{
	int i,m,nClientes;

	nClientes=nuevoId();

	for (m=1;m<13;m++)	//	inicializacion
	{
		a[m]=0;
	}

	for (i=0;i<nClientes;i++)
	{
		for (m=1;m<13;m++)
		{
			a[m]=a[m]+devolverTotalMes(i,m);
		}
	}
}

