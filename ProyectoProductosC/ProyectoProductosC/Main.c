#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include "Articulos.h"
#include "Clientes.h"
#include "Pedidos.h"

void main()
{
	fExisteFicheroArticulos();
	fExisteFicheroClientes();
	void(*ptrMenuClientes[4])() = { fAltaCliente,fBajaCliente,fModificarCliente,fInformeCliente };
	void(*ptrMenuArticulos[4])() = {fAltaArticulo, fBajaArticulo, fModificarArticulo, fInformeArticulo};
	system("cls");
	int opc;
	opc = fMenu("\t\tMENU DE FACTURACION\n\n1.-Clientes\n2.-Articulos\n3.-Pedidos\n4.-Facturacion\n5.-Salir\nEleccion: ",1,5);
	while (opc != 5)
	{
		switch (opc)
		{
		case 1:
			system("cls");
			opc = fMenu("\t\tMENU DE CLIENTES\n\n1.-Altas\n2.-Bajas\n3.-Modificar\n4.-Consultar\n5.-Salir\nEleccion: ", 1, 5);
			while (opc != 5)
			{
				(*ptrMenuClientes[opc - 1])();
				opc = fMenu("\t\tMENU DE CLIENTES\n\n1.-Altas\n2.-Bajas\n3.-Modificar\n4.-Consultar\n5.-Salir\nEleccion: ", 1, 5);
			}
			break;
		case 2:
			system("cls");
			opc = fMenu("\t\tMENU DE ARTICULOS\n\n1.-Altas\n2.-Bajas\n3.-Modificar\n4.-Consultar\n5.-Salir\nEleccion: ", 1, 5);
			while (opc != 5)
			{
				(*ptrMenuArticulos[opc - 1])();
				opc = fMenu("\t\tMENU DE ARTICULOS\n\n1.-Altas\n2.-Bajas\n3.-Modificar\n4.-Consultar\n5.-Salir\nEleccion: ", 1, 5);
			}
			break;
		case 3:
			fAgregarPedido();
			break;
		case 4:
			break;
		}
		opc = fMenu("\t\tMENU DE FACTURACION\n\n1.-Clientes\n2.-Articulos\n3.-Pedidos\n4.-Facturacion\n5.-Salir\nEleccion: ", 1, 5);
	}
}