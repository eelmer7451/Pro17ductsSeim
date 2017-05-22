#include "Facturacion.h"

void fCabeceraFactura()
{
	GoToXY(0, 0);
	printf("\n%43sNombre: \n", "");
	printf("%43sDomicilio: \n", "");
	printf("%43sC.P.: \n%50s\n", "","");
	printf("Fecha: %36sNº Factura:\n", "");
	printf("%12s  %23s  %10s  %10s  %10s\n%50s", "Nº Articulo", "Denominacion", "P.V.P.", "Cantidad", "Importe","");
}

void fCabeceraResumen()
{
	system("cls");
	printf("\t\tLISTADO RESUMEN DE FACTURACION DEL ");
	printf("%15s  %10s  %10s  %15s  %10s\n\n\n\n\n\n","","","","","");
	printf("%29sTOTALES","");
}

void fAgregarFactura()
{
	FILE *cpf, *apf, *ppf, *rpf;
	CLIENTE regCliente;
	ARTICULO regArticulo;
	FACTURACION regFactura;
	PEDIDO regPedido;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int nCliente;
	int tamArchivoPedidos, sw=1,numLineas=0;
	cpf = fopen(RUTAFICHEROCLIENTES, "rb");
	if (cpf == NULL)
	{
		printf("Error al abrir el archivo clientes.");
		getch();
		return;
	}
	apf = fopen(RUTAARTICULOS, "rb");
	if (apf == NULL)
	{
		printf("Error al abrir el archivo articulos.");
		getch();
		fclose(cpf);
		return;
	}
	ppf = fopen(RUTAPEDIDOS, "rb");
	if (ppf == NULL)
	{
		printf("Error al abrir el archivo pedidos.");
		getch();
		fclose(cpf);
		fclose(apf);
		return;
	}
	rpf = fopen(RUTARESUMEN, "ab+");
	if (rpf == NULL)
	{
		printf("Error al abrir el archivo de facturacion.");
		getch();
		fclose(cpf);
		fclose(apf);
		fclose(ppf);
		return;
	}
	regFactura.nFactura = fCalcularTamanoFicheroResumen(rpf);
	tamArchivoPedidos = fCalcularTamanoFicheroPedidos(ppf);
	while (!feof(ppf))
	{
		fread(&regPedido, sizeof(regPedido), 1, ppf);
		fCabeceraFactura();
		nCliente = regPedido.nCliente;
		fseek(cpf, nCliente * sizeof(regCliente), SEEK_SET);
		fread(&regCliente, sizeof(regCliente), 1, cpf);
		GoToXY(53, 1);
		printf("%s", regCliente.nombre);
		GoToXY(53, 2);
		printf("%s", regCliente.domicilio);
		GoToXY(48, 3);
		printf("%s  Municipio: %s", regCliente.codigoPostal,regCliente.municipio);
		GoToXY(7, 5);
		printf("%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); 
		GoToXY(55,5);
		printf("%d", regFactura.nFactura);
		GoToXY(0, numLineas+8);
		//while (regPedido.nCliente == nCliente && !feof(ppf))
		//{
			fseek(apf, sizeof(regArticulo)*regPedido.nArticulo, SEEK_SET);
			fread(&regArticulo, sizeof(regArticulo), 1, apf);
			printf("%12d  %23s  %8.2f  %12d  %9.2f\n", regPedido.nArticulo, regArticulo.denominacion, regPedido.pvp, regPedido.cantidad, regPedido.cantidad*regPedido.pvp);
		//}
			numLineas++;
	}
	getch();
	fclose(cpf);
	fclose(apf);
	fclose(ppf);
	fclose(rpf);
}

int fCalcularTamanoFicheroResumen(FILE * pf)
{
	int tamArchivo, tamFinal, tamInicio;
	FACTURACION reg;
	fseek(pf, 0, SEEK_END);
	tamFinal = ftell(pf);
	fseek(pf, 0, SEEK_SET);
	tamInicio = ftell(pf);
	tamArchivo = (tamFinal - tamInicio) / sizeof(reg);
	return tamArchivo;
}