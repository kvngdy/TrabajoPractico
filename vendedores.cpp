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
	//char n_nombre[32];
	int n_codigoDeSucursal;

	cout << "Ingresar Nombre de sucursal: ";
	cin >> NuevoSucursal.Nombre;

	do {
		cout << "Ingresar Codigo de sucursal: ";
		cin >> n_codigoDeSucursal;
		if (CodigoDeSucursalRepetido(n_codigoDeSucursal, sucursales)) {
			cout << "CC3digo repetido. Ingrese otro.\n";
		}
	} while (CodigoDeSucursalRepetido(n_codigoDeSucursal, sucursales));

	NuevoSucursal.CodigoDeSucursal = n_codigoDeSucursal;
	//strcpy(NuevoSucursal.Nombre, n_nombre);
	//error //NuevoSucursal.Nombre = n_nombre;

	return NuevoSucursal;
}

bool CodigoDeVendedorRepetido(int n_codigo, Vendedor vendedores[]) {
	for (int i = 0; i < 4; i++) {
		if (vendedores[i].CodigoDeVendedor == n_codigo) {
			return true;
		}
	}
	return false;
}

Vendedor cargarVendedor(Vendedor vendedores[], Sucursal sucursales[]) {
	Vendedor NuevoVendedor;
	//char n_nombre[32];
	int n_codigoDeVendedor;
	int n_codigoDeSucursal;

	cout << "Ingrese nombre del Vendedor: ";
	cin >> NuevoVendedor.Nombre;

	do {
		cout << "Ingresar Codigo de Vendedor: ";
		cin >> n_codigoDeVendedor;
		if (CodigoDeVendedorRepetido(n_codigoDeVendedor, vendedores)) {
			cout << "CC3digo de vendedor repetido. Ingrese otro.\n";
		}
	} while (CodigoDeVendedorRepetido(n_codigoDeVendedor, vendedores));

	NuevoVendedor.CodigoDeVendedor = n_codigoDeVendedor;

	//strcpy(NuevoVendedor.Nombre, n_nombre);
	//error //NuevoVendedor.Nombre = n_nombre;

	cout << "Ingrese Codigo de Sucursal (elija uno de los siguientes):\n";
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
		fwrite(vendedores, sizeof(Vendedor), 4, archivo);
		fclose(archivo);
		cout << "Archivo creado exitosamente.";
	} else {
		cout << "No se pudo crear el archivo.";
	}

	/*
	Sucursal prueba_sucursales[3];
	Vendedor prueba_vendedores[4];
	FILE* prueba_archivo = fopen("vendedores.dat", "rb");
	if (prueba_archivo == NULL) {
		cout << "No se pudo abrir el archivo.";
	}
	fread(prueba_sucursales, sizeof(Sucursal), 3, prueba_archivo);
	fread(prueba_vendedores, sizeof(Vendedor), 4, prueba_archivo);
	fclose(archivo);

	cout << "\n Sucursales \n";
	for (int i = 0; i < 3; i++) {
		cout << " Sucursal " << i + 1 << ": \n" << sucursales[i].Nombre;
		cout << " -Codigo: " << sucursales[i].CodigoDeSucursal << endl;
	}

	cout << "\n Vendedores \n";
	for (int i = 0; i < 4; i++) {
		cout << "\n  Vendedor " << i + 1 << ": \n" << vendedores[i].Nombre;
		cout << " - Codigo: " << vendedores[i].CodigoDeVendedor;
		cout << " - Sucursal: " << vendedores[i].CodigoDeSucursal;
	}
	*/
}

int main() {
	// cargar 3 sucursales
	
	Sucursal sucursales[3];

	for (int i = 0; i < 3; i++) {
		sucursales[i] = cargarNuevoSucursal(sucursales);
	}

	// cargar 4 vendedores
	int tamaño = 2;
	Vendedor vendedores[tamaño];

	for (int i = 0; i < tamaño; i++) {
		vendedores[i] = cargarVendedor(vendedores, sucursales);
	}

	/*
		cout << "Prueba \n";

		for (int i = 0; i < 3; i++) {
			cout << "Sucursal: " << sucursales[i].Nombre << " - Codigo: " << sucursales[i].CodigoDeSucursal << endl;
		}

		for (int i = 0; i < 4; i++) {
			cout << "Vendedor: " << vendedores[i].Nombre << " - Codigo: " << vendedores[i].CodigoDeVendedor
			     << " - Sucursal: " << vendedores[i].CodigoDeSucursal << endl;
		}
	*/
	
	CrearArchivo(sucursales,vendedores);
	return 0;
}

// CAMBIAR TODOS LOS CUATROS POR UN QUINCE !!!