#include <iostream>
#include <cstring>
using namespace std;

struct Sucursal
{
	char Nombre[32];
	int CodigoDeSucursal;
};

struct Vendedor
{
	char Nombre[32];
	int CodigoDeVendedor;
	int CodigoDeSucursal;
};

struct Venta
{
	int fecha; // AAAAMMDD
	int CodigoDeVendedor;
	int CodigoDeProducto;
	int monto; // en centavos
};

void MostrarMayorVendedor(int TotalDeCadaVendedor[], int cantidadDeVendedores, Vendedor vendedores[])
{
	int mayorMonto = TotalDeCadaVendedor[0];
	bool alguienVendio = mayorMonto > 0;

	for (int i = 0; i < cantidadDeVendedores; i++)
	{
		if (TotalDeCadaVendedor[i] > mayorMonto)
		{
			mayorMonto = TotalDeCadaVendedor[i];
			alguienVendio = true;
		}
	}

	if (!alguienVendio)
	{
		cout << "ERROR: NingC:n vendedor realizC3 ventas." << endl;
	}
	else
	{
		cout << "El/los mayor(es) vendedor(es) vendieron $";
		cout << (mayorMonto / 100) << "," << (mayorMonto % 100) << endl;

		for (int i = 0; i < cantidadDeVendedores; i++)
		{
			if (TotalDeCadaVendedor[i] == mayorMonto)
			{
				cout << "- " << vendedores[i].Nombre << endl;
			}
		}
	}
}

void MostrarMayorSucursal(int TotalDeCadaSucursal[], int cantidadDeSucursales, Sucursal sucursales[])
{
	int mayorMonto = TotalDeCadaSucursal[0];
	bool alguienVendio = mayorMonto > 0;

	for (int i = 0; i < cantidadDeSucursales; i++)
	{
		if (TotalDeCadaSucursal[i] > mayorMonto)
		{
			mayorMonto = TotalDeCadaSucursal[i];
			alguienVendio = true;
		}
	}

	if (!alguienVendio)
	{
		cout << "ERROR: NingC:n vendedor realizC3 ventas." << endl;
	}
	else
	{
		cout << "La/las sucursal(es) con mayores ventas vendieron $";
		cout << (mayorMonto / 100) << "," << (mayorMonto % 100) << endl;

		for (int i = 0; i < cantidadDeSucursales; i++)
		{
			if (TotalDeCadaSucursal[i] == mayorMonto)
			{
				cout << "- " << sucursales[i].Nombre << endl;
			}
		}
	}
}

void JuntarVentasAlTotalVendedores(Vendedor vendedores[], int cantidadDeVendedores, int TotalDeCadaVendedor[], Venta ventas[], int cantidadDeVentas)
{
	for (int i = 0; i < cantidadDeVendedores; i++)
	{
		TotalDeCadaVendedor[i] = 0;
	}

	for (int i = 0; i < cantidadDeVentas; i++)
	{
		for (int j = 0; j < cantidadDeVendedores; j++)
		{
			if (ventas[i].CodigoDeVendedor == vendedores[j].CodigoDeVendedor)
			{
				TotalDeCadaVendedor[j] += ventas[i].monto;
				break;
			}
		}
	}
}

int ObtenerCodigoDeSucursalDelVendedor(int codigo, Vendedor vendedores[], int cantidadDeVendedores)
{
	for (int i = 0; i < cantidadDeVendedores; i++)
	{
		if (vendedores[i].CodigoDeVendedor == codigo)
		{
			return vendedores[i].CodigoDeSucursal;
		}
	}
	return -1; // No encontrado
}

void JuntarVentasAlTotalSucursales(Sucursal sucursales[], int cantidadDeSucursales, int TotalDeCadaSucursal[], Venta ventas[], int cantidadDeVentas, Vendedor vendedores[], int cantidadDeVendedores)
{
	for (int i = 0; i < cantidadDeSucursales; i++)
	{
		TotalDeCadaSucursal[i] = 0;
	}

	for (int i = 0; i < cantidadDeVentas; i++)
	{
		int codSucursal = ObtenerCodigoDeSucursalDelVendedor(ventas[i].CodigoDeVendedor, vendedores, cantidadDeVendedores);

		for (int j = 0; j < cantidadDeSucursales; j++)
		{
			if (sucursales[j].CodigoDeSucursal == codSucursal)
			{
				TotalDeCadaSucursal[j] += ventas[i].monto;
				break;
			}
		}
	}
}

void cargarDatosVendedores(Vendedor vendedores[], int cantidadVendedores, Sucursal sucursales[], int cantidadSucursales)
{
	FILE *archivo = fopen("vendedores.dat", "rb");
	if (archivo == NULL)
	{
		cout << "No se pudo abrir el archivo vendedores.dat." << endl;
		exit(1);
	}

	fread(sucursales, sizeof(Sucursal), cantidadSucursales, archivo);
	fread(vendedores, sizeof(Vendedor), cantidadVendedores, archivo);
	fclose(archivo);
}

void cargarDatosVentas(Venta ventas[], int cantidadDeVentas)
{
	FILE *archivo = fopen("ventas_diarias.dat", "rb");
	if (archivo == NULL)
	{
		cout << "No se pudo abrir el archivo ventas_diarias.dat." << endl;
		exit(1);
	}

	fread(ventas, sizeof(Venta), cantidadDeVentas, archivo);
	fclose(archivo);
}

void OrdenarVentasPorCodigo(Venta ventas[], int cantidadDeVentas)
{
	for (int i = 0; i < cantidadDeVentas - 1; i++)
	{
		for (int j = 0; j < cantidadDeVentas - i - 1; j++)
		{
			if (ventas[j].CodigoDeProducto > ventas[j + 1].CodigoDeProducto)
			{
				Venta temp = ventas[j];
				ventas[j] = ventas[j + 1];
				ventas[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < cantidadDeVentas; i++)
	{
		cout << ventas[i].CodigoDeProducto << endl;
	}
}

void MostrarMejorProducto(Venta ventas[], int cantidadDeVentas)
{
	int supraContador = 1;
	int contador = 1;
	int codigoAnterior = ventas[0].CodigoDeProducto;
	int codigoActual = ventas[0].CodigoDeProducto; // esto no importa q valor tiene ahora
	int codigoGanador = ventas[0].CodigoDeProducto;

	for (int i = 0; i < cantidadDeVentas; i++)
	{
		codigoActual = ventas[i].CodigoDeProducto;

		if (codigoActual == codigoAnterior)
		{
			// es el mismo producto
			contador++;
		}
		else
		{
			// hubo un cambio de producto
			if (contador > supraContador)
			{
				supraContador = contador;
				codigoGanador = codigoAnterior;
			}
			contador = 1;
		}
		codigoAnterior = codigoActual;
	}
	cout << "El producto que mas veces se vendio es: " << endl;
	cout << codigoGanador << ", " << supraContador << " veces";
}

int obtenerCantidadDeVentas()
{
	FILE *archivo = fopen("ventas_diarias.dat", "rb");
	int cantidad;
	fseek(archivo, -sizeof(int), SEEK_END);
	fread(&cantidad, sizeof(int), 1, archivo);
	fclose(archivo);
	return cantidad - 1;
}

int main()
{
	int cantidadSucursales = 3;
	int cantidadDeVendedores = 4;
	Sucursal sucursales[cantidadSucursales];
	Vendedor vendedores[cantidadDeVendedores];

	cargarDatosVendedores(vendedores, cantidadDeVendedores, sucursales, cantidadSucursales);

	int cantidadDeVentas = obtenerCantidadDeVentas();
	Venta ventas[cantidadDeVentas];
	cargarDatosVentas(ventas, cantidadDeVentas);

	int TotalDeCadaVendedor[cantidadDeVendedores];
	int TotalDeCadaSucursal[cantidadSucursales];

	JuntarVentasAlTotalVendedores(vendedores, cantidadDeVendedores, TotalDeCadaVendedor, ventas, cantidadDeVentas);
	JuntarVentasAlTotalSucursales(sucursales, cantidadSucursales, TotalDeCadaSucursal, ventas, cantidadDeVentas, vendedores, cantidadDeVendedores);

	MostrarMayorVendedor(TotalDeCadaVendedor, cantidadDeVendedores, vendedores);
	MostrarMayorSucursal(TotalDeCadaSucursal, cantidadSucursales, sucursales);

	OrdenarVentasPorCodigo(ventas, cantidadDeVentas);
	MostrarMejorProducto(ventas, cantidadDeVentas);
	return 0;
}