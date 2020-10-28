#include "stConsumos.h"
#include "stCliente.h"
#define YEAR 2020

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
