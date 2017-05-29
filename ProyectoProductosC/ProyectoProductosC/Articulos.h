#pragma once

#define RUTAARTICULOS "Archivo\\Articulos.dat"

#include "Consola.h"
#include "Menu.h"
#include <stdio.h>

typedef struct {
	int nArticulo;
	char denominacion[20];
	float precioCoste;
	float pvp;
	int estado;
}ARTICULO;

void fFormularioArticulo();
void fExisteFicheroArticulos();
int fCalcularTamanoFicheroArticulos(FILE *pf);
int fCalcularNumeroArticulo(FILE *pf);
void fAltaArticulo();
void fBajaArticulo();
void fModificarArticulo();
void fInformeArticulo();
int fPedirPosArticulo(FILE *pf);