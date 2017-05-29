#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define RUTARESUMEN "Archivo\\Resumen.dat"
#define IVA 21

#include <stdio.h>
#include <time.h>
#include <string.h>

#include "Articulos.h"
#include "Clientes.h"
#include "Pedidos.h"
#include "Menu.h"

typedef struct
{
	int nFactura;
	int nCliente;
	float baseImponible;
	float iva;
}FACTURACION;

void fCabeceraFactura();
void fCabeceraResumen(char * fecha);
void fAgregarFactura();
void fInformeResumen(char *fecha,FILE *cpf);
int fCalcularTamanoFicheroResumen(FILE * pf);
void fImprimirCabeceraFactura(FILE *pf,CLIENTE regCliente,PEDIDO regPedido, char *fecha, int nFactura);
void fImprimirPiePaginaFactura(FILE *pf,float total, int Lineas);
void fImprimirCabeceraResumen(FILE *pf, CLIENTE regCliente, FACTURACION regFactura, char *fecha, int nFactura);
void fImprimirPiePaginaResumen(FILE *pf, float total, int Lineas);