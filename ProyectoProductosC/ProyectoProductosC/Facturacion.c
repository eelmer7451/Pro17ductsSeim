#include "Facturacion.h"

void fCabeceraFactura()
{
	system("cls");
	printf("\n%43sNombre: \n", "");
	printf("%43sDomicilio: \n", "");
	printf("%43sC.P.: \n%50s\n", "","");
	printf("Fecha: %36sNº Factura:\n", "");
	printf("%12s  %23s  %10s  %10s  %10s\n%50s", "Nº Articulo", "Denominacion", "P.V.P.", "Cantidad", "Importe","");
}

void fCabeceraResumen(char* fecha)
{
	system("cls");
	printf("\t\tLISTADO RESUMEN DE FACTURACION DEL %s\n\n",fecha);
	printf("%15s  %10s  %10s  %15s  %10s\n\n\n\n\n\n","Nº Factura","Cliente","N.I.F.","Base Imponible","IVA");
}

void fAgregarFactura()
{
	FILE *cpf, *apf, *ppf, *rpf, *fpf;
	CLIENTE regCliente;
	ARTICULO regArticulo;
	FACTURACION regFactura;
	PEDIDO regPedido;
	time_t t = time(NULL);
	char  archivoFactura[80]="",fecha[12]="",del[100]="del ";
	struct tm tm = *localtime(&t);
	float total=0;
	int tamArchivoPedidos, sw=1,numLineas=0,nCliente;
	sw = fExisteFicheroPedidos();
	if (sw == 0)
		return;
	sprintf(fecha, "%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
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
	fread(&regPedido, sizeof(regPedido), 1, ppf);
	fCabeceraFactura();
	nCliente = regPedido.nCliente;
	sw = 0;
	while (!feof(ppf))
	{
		if (nCliente == regPedido.nCliente)
		{
			fseek(cpf, nCliente * sizeof(regCliente), SEEK_SET);
			fread(&regCliente, sizeof(regCliente), 1, cpf);
			strcpy(archivoFactura, "Facturas\\");
			strcat(archivoFactura, regCliente.nif);
			strcat(archivoFactura, "_");
			strcat(archivoFactura, fecha);
			strcat(archivoFactura, ".dat");
			fpf = fopen(archivoFactura, "ab+");
			if (fpf == NULL)
			{
				printf("Error al abrir el archivo de Factura.");
				getch();
				fclose(cpf);
				fclose(apf);
				fclose(ppf);
				fclose(rpf);
				return;
			}
			if (sw == 0)
			{
				fImprimirCabeceraFactura(fpf, regCliente, regPedido, fecha, regFactura.nFactura);
				sw = 1;
			}
			GoToXY(53, 1);
			printf("%s", regCliente.nombre);
			GoToXY(53, 2);
			printf("%s", regCliente.domicilio);
			GoToXY(48, 3);
			printf("%s  Municipio: %s", regCliente.codigoPostal, regCliente.municipio);
			GoToXY(7, 5);
			printf("%s",fecha);
			GoToXY(55, 5);
			printf("%d", regFactura.nFactura);
			GoToXY(0, numLineas + 8);
			fseek(apf, sizeof(regArticulo)*regPedido.nArticulo, SEEK_SET);
			fread(&regArticulo, sizeof(regArticulo), 1, apf);
			printf("%10d  %23s  %8.2f  %12d  %9.2f\n", regPedido.nArticulo, regArticulo.denominacion, regPedido.pvp, regPedido.cantidad, regPedido.cantidad*regPedido.pvp);
			fprintf(fpf,"%12d  %20s  %6.2f  %8d  %7.2f\n", regPedido.nArticulo, regArticulo.denominacion, regPedido.pvp, regPedido.cantidad, regPedido.cantidad*regPedido.pvp);
			total += regPedido.cantidad*regPedido.pvp;
			numLineas++;
			fread(&regPedido, sizeof(regPedido), 1, ppf);
			fclose(fpf);
		}
		else
		{
			fpf = fopen(archivoFactura, "ab+");
			if (fpf == NULL)
			{
				printf("Error al abrir el archivo de Factura.");
				getch();
				fclose(cpf);
				fclose(apf);
				fclose(ppf);
				fclose(rpf);
				return;
			}
			regFactura.iva = total - total*0.79;
			regFactura.baseImponible = total*0.79;
			regFactura.nCliente = nCliente;
			fwrite(&regFactura, sizeof(regFactura), 1, rpf);
			GoToXY(49, numLineas + 9);
			printf("Base Imp.:   %.2f\n", total*0.79);
			GoToXY(49, numLineas + 10);
			printf("IVA:         %.2f\n", total - total*0.79);
			GoToXY(49, numLineas + 11);
			printf("TOTAL:       %.2f\n", total);
			fImprimirPiePaginaFactura(fpf, total, numLineas);
			getch();
			fwrite(&regFactura, sizeof(regFactura), 1, rpf);
			fseek(ppf, sizeof(regPedido)*numLineas, SEEK_SET);
			fread(&regPedido, sizeof(regPedido), 1, ppf);
			nCliente = regPedido.nCliente;
			numLineas = 0;
			total = 0;
			sw = 0;
			regFactura.nFactura = fCalcularTamanoFicheroResumen(rpf);
			system("cls");
			fCabeceraFactura();
			fclose(fpf);
		}
	}
	fpf = fopen(archivoFactura, "ab+");
	if (fpf == NULL)
	{
		printf("Error al abrir el archivo de Factura.");
		getch();
		fclose(cpf);
		fclose(apf);
		fclose(ppf);
		fclose(rpf);
		return;
	}
	regFactura.iva = total - total*0.79;
	regFactura.baseImponible = total*0.79;
	regFactura.nCliente = nCliente;
	fwrite(&regFactura, sizeof(regFactura), 1, rpf);
	GoToXY(49, numLineas + 9);
	printf("Base Imp.:   %.2f\n", total*0.79);
	GoToXY(49, numLineas + 10);
	printf("IVA:         %.2f\n", total - total*0.79);
	GoToXY(49, numLineas + 11);
	printf("TOTAL:       %.2f\n", total);
	fImprimirPiePaginaFactura(fpf, total,numLineas);
	getch();
	fclose(rpf);
	fclose(fpf);
	fInformeResumen(fecha,cpf);
	fclose(ppf);
	fclose(cpf);
	fclose(apf);
	strcat(del, RUTAPEDIDOS);
	system(del);
	getch();
}

void fInformeResumen(char* fecha, FILE *cpf)
{
	FILE *pf;
	FACTURACION regFactura;
	CLIENTE regCliente;
	char del[100] = "del ";
	float totalBase = 0, totalIva = 0;
	pf = fopen(RUTARESUMEN, "rb");
	if (pf == NULL)
	{
		printf("Error al abrir el archivo de facturacion.");
		getch();
		return;
	}
	fread(&regFactura, sizeof(regFactura), 1, pf);
	fCabeceraResumen(fecha);
	while (!feof(pf))
	{
		fseek(cpf, regFactura.nCliente * sizeof(regCliente), SEEK_SET);
		fread(&regCliente, sizeof(regCliente), 1, cpf);
		printf("%15d  %10s  %10s  %15.2f  %10.2f\n\n\n\n\n\n", regFactura.nFactura, regCliente.nombre, regCliente.nif, regFactura.baseImponible, regFactura.iva);
		totalBase += regFactura.baseImponible;
		totalIva += regFactura.iva;
		fread(&regFactura, sizeof(regFactura), 1, pf);
	}
	printf("\n\n%33sTotales: %.2f  %.2f", "", totalBase, totalIva);
	getch();
	fclose(pf);
	strcat(del, RUTARESUMEN);
	system(del);
	getch();
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

void fImprimirCabeceraFactura(FILE * pf, CLIENTE regCliente, PEDIDO regPedido, char *fecha,int nFactura)
{
	fprintf(pf,"\n%33sNombre: %s\n", "",regCliente.nombre);
	fprintf(pf,"%33sDomicilio: %s\n", "",regCliente.domicilio);
	fprintf(pf,"%33sC.P.: %s\n%33sMunicipio: %s\n\n", "", regCliente.codigoPostal, "",regCliente.municipio);
	fprintf(pf,"Fecha: %s%26sNº Factura: %d\n\n", fecha, "",nFactura);
	fprintf(pf,"%10s  %20s  %6s  %8s  %7s\n", "Nº Articulo", "Denominacion", "P.V.P.", "Cantidad", "Importe");
}

void fImprimirPiePaginaFactura(FILE * pf, float total)
{
	fprintf(pf,"\n%33sBase Imp.:   %.2f\n","", total*0.79);
	fprintf(pf,"%33sIVA:         %.2f\n","", total - total*0.79);
	fprintf(pf,"%33sTOTAL:       %.2f\n","", total);
}

void fImprimirCabeceraResumen(FILE * pf, CLIENTE regCliente, FACTURACION regFactura, char * fecha, int nFactura)
{
	fprintf(pf,"\n\t\tLISTADO RESUMEN DE FACTURACION DEL %s\n\n", fecha);
	fprintf(pf,"%15s  %10s  %10s  %15s  %10s\n\n\n\n\n\n", "Nº Factura", "Cliente", "N.I.F.", "Base Imponible", "IVA");
}

void fImprimirPiePaginaResumen(FILE * pf, float total)
{
	fprintf(pf, "\nTOTALES %.2f  %.2f\n", total*0.79, total*0.21);
}
