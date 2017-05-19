#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define RUTAPEDIDOS "Pedidos.dat"

#include "Consola.h"
#include "Clientes.h"
#include "Articulos.h"

typedef struct
{
	int nCliente;
	int nArticulo;
	float pvp;
	int cantidad;
}PEDIDO;

void fFormularioPedido();
void fAgregarPedido();
int fPedirCliente(FILE *pf,int linea);
int fPedirArticulo(FILE *pf,int linea);