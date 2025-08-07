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

bool CodigoDeSucursalRepetido(int n_codigo, Sucursal sucursales[]) {
	for (int i = 0; i < 3; i++) {
		if (sucursales[i].CodigoDeSucursal == n_codigo) {
			return true;
		}
	}
	return false;
}

Sucursal cargarNuevoSucursal(Sucursal sucursales[]) {
	Sucursal NuevoSucursal;
	int n_codigoDeSucursal;
	cout << "\nIngresar Nombre de sucursal: "  ;
	cin >> NuevoSucursal.Nombre;
	do {
		cout << "Ingresar Codigo de sucursal: ";
		cin >> n_codigoDeSucursal;
		if (CodigoDeSucursalRepetido(n_codigoDeSucursal, sucursales)) {
			cout << "\nCodigo repetido. Ingrese otro.\n";
		}
	} while (CodigoDeSucursalRepetido(n_codigoDeSucursal, sucursales));
	NuevoSucursal.CodigoDeSucursal = n_codigoDeSucursal;
	return NuevoSucursal;
}

bool CodigoDeVendedorRepetido(int n_codigo, Vendedor vendedores[]) {
	for (int i = 0; i < 15; i++) {
		if (vendedores[i].CodigoDeVendedor == n_codigo) {
			return true;
		}
	}
	return false;
}

Vendedor cargarVendedor(Vendedor vendedores[], Sucursal sucursales[]) {
	Vendedor NuevoVendedor;
	int n_codigoDeVendedor;
	int n_codigoDeSucursal;

	cout << "\nIngrese nombre del Vendedor: ";
	cin >> NuevoVendedor.Nombre;

	do {
		cout << "Ingresar Codigo de Vendedor: ";
		cin >> n_codigoDeVendedor;
		if (CodigoDeVendedorRepetido(n_codigoDeVendedor, vendedores)) {
			cout << "Codigo de vendedor repetido. Ingrese otro.\n";
		}
	} while (CodigoDeVendedorRepetido(n_codigoDeVendedor, vendedores));

	NuevoVendedor.CodigoDeVendedor = n_codigoDeVendedor;


	cout << "\nIngrese Codigo de Sucursal (elija uno de los siguientes):\n";
	for (int i = 0; i < 3; i++) {
		cout << "- " << sucursales[i].Nombre << " (" << sucursales[i].CodigoDeSucursal << ")\n";
	}

	do {
		cout << "Codigo: ";
		cin >> n_codigoDeSucursal;
		if (!CodigoDeSucursalRepetido(n_codigoDeSucursal, sucursales)) {
			cout << "Codigo de sucursal no existe, ingrese nuevamente una de las opciones.\n";
		}
	} while (!CodigoDeSucursalRepetido(n_codigoDeSucursal, sucursales));

	NuevoVendedor.CodigoDeSucursal = n_codigoDeSucursal;

	return NuevoVendedor;
}

void CrearArchivo(Sucursal sucursales[],Vendedor vendedores[]) {
	FILE* archivo = fopen("vendedores.dat", "wb");

	if (archivo != NULL) {
		fwrite(sucursales, sizeof(Sucursal), 3, archivo);
		fwrite(vendedores, sizeof(Vendedor), 15, archivo);
		fclose(archivo);
		cout << "Archivo creado exitosamente.";
	} else {
		cout << "No se pudo crear el archivo.";
	}

}

int main() {
	// cargar 3 sucursales
	
	Sucursal sucursales[3];

	for (int i = 0; i < 3; i++) {
		sucursales[i] = cargarNuevoSucursal(sucursales);
	}

	// cargar 15 vendedores
	int tamaño = 15;
	Vendedor vendedores[tamaño];

	for (int i = 0; i < tamaño; i++) {
		vendedores[i] = cargarVendedor(vendedores, sucursales);
	}

	
	CrearArchivo(sucursales,vendedores);
	return 0;
}