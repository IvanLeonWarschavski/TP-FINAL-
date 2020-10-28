#include "stCliente.h"
#include "stConsumos.h"
#define FILECL "clientes.bin"
#define FILECO "consumos.bin"

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

        printf("\n\n\nNOMBRE: ");
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
