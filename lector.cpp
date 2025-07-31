#include <iostream>
#include <cstring>
using namespace std;

struct Sucursal {
	char Nombre[32];
	int CodigoDeSucursal;
};

struct Vendedor {
	char Nombre[32];
	int CodigoDeVendedor;
	int CodigoDeSucursal;
};

int main()
{
    Sucursal prueba_sucursales[3];
	Vendedor prueba_vendedores[4];
	FILE* prueba_archivo = fopen("vendedores.dat", "rb");
	if (prueba_archivo == NULL) {
		cout << "No se pudo abrir el archivo.";
	}
	fread(prueba_sucursales, sizeof(Sucursal), 3, prueba_archivo);
	fread(prueba_vendedores, sizeof(Vendedor), 4, prueba_archivo);
	fclose(prueba_archivo);

	cout << "\n Sucursales \n";
	for (int i = 0; i < 3; i++) {
		cout << " Sucursal " << i + 1 << ": \n" << prueba_sucursales[i].Nombre;
		cout << " -Codigo: " << prueba_sucursales[i].CodigoDeSucursal << endl;
	}

	cout << "\n Vendedores \n";
	for (int i = 0; i < 4; i++) {
		cout << "\n  Vendedor " << i + 1 << ": \n" << prueba_vendedores[i].Nombre;
		cout << " - Codigo: " << prueba_vendedores[i].CodigoDeVendedor;
		cout << " - Sucursal: " << prueba_vendedores[i].CodigoDeSucursal;
	}
    return 0;
}
