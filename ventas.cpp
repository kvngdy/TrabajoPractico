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
    int fecha; //! AAAAMMDD
    int CodigoDeVendedor;
    int CodigoDeProducto;
    int monto; //??dos espacios de deciamal hay que mostrar con coma de dos espacios (dividir en 100)
};
bool verificarFecha(int fecha)
{
    // verificar
    return true; // correcto
}
// donando por un anonimo generozo de vendedores
bool verificarCodigoVendedor(int codigo, Vendedor vendedores[], int tamaño)
{
    for (int i = 0; i < tamaño; i++)
    {
        if (vendedores[i].CodigoDeVendedor == codigo)
        {
            return true;
        }
    }
    return false;
}

Venta cargarVenta(Vendedor vendedores[], int tamaño)
{
    Venta Nventa;
    int control = 0;
    do
    {
        if (control == 0)
        {
            cout << "dame la fecha en AAAAMMDD" << endl;
        }
        else
        {
            cout << "ERROR EN EL FORMATO" << endl;
            cout << "dame la fecha en AAAAMMDD" << endl;
        }

        cin >> Nventa.fecha;
        control = 1;

    } while (!verificarFecha(Nventa.fecha));

    control = 0;
    do
    {
        if (control == 0)
        {
            cout << "dame el codigo de vendedor" << endl;
        }
        else
        {
            cout << "codigo de vendedor inexistente" << endl;
            cout << "dame el codigo de vendedor" << endl;
        }

        cin >> Nventa.CodigoDeVendedor;
        control = 1;
        cout << vendedores[1].CodigoDeVendedor << endl;
    } while (!verificarCodigoVendedor(Nventa.CodigoDeVendedor, vendedores, tamaño));
    // while (0);

    cout << "dame el codigo de producto" << endl;
    cin >> Nventa.CodigoDeProducto;

    control = 0;
    do
    {
        if (control == 0)
        {
            cout << "dame el monto de la venta" << endl;
        }
        else
        {
            cout << "El monto de la venta No pude ser 0 ni negativo" << endl;
            cout << "dame el monto de la venta" << endl;
        }

        cin >> Nventa.monto;
        control = 1;
    } while (Nventa.monto <= 0);

    return Nventa;
}

void cargarVendedores(Vendedor vendedores[], int cantidadVendedores, int cantidadSucursales)
{
    Sucursal sucursales[cantidadSucursales];
    FILE *archivo = fopen("vendedores.dat", "rb");
    if (archivo == NULL)
    {
        cout << "No se pudo abrir el archivo.";
    }

    fread(sucursales, sizeof(Sucursal), cantidadSucursales, archivo); // solo pera recorrer las surcursales que ocupan el primer espacio de bits
    fread(vendedores, sizeof(Vendedor), cantidadVendedores, archivo);
    fclose(archivo);

    // solo lectura de control
    cout << "\n Vendedores \n";
    for (int i = 0; i < cantidadVendedores; i++)
    {
        cout << "\n  Vendedor " << i + 1 << ": \n"
             << vendedores[i].Nombre;
        cout << " - Codigo: " << vendedores[i].CodigoDeVendedor;
        cout << " - Sucursal: " << vendedores[i].CodigoDeSucursal;
    }
    cout << endl;
}

void escribirVenta(Venta nVenta)
{
    FILE *archivo = fopen("ventas_diarias.dat", "wb");

    if (archivo != NULL)
    {
        fwrite(&nVenta, sizeof(nVenta), 1, archivo);
        cout << "venta guardadad" << endl;
        fclose(archivo);
    }
    else
    {
        cout << "ERRROR no se pudo guardar la venta" << endl;
        escribirVenta(nVenta);
    }
}

void leer(int tamaño)
{
    Venta ventas[tamaño];
    FILE *archivo = fopen("ventas_diarias.dat", "rb");
    fread(ventas, sizeof(Venta), tamaño, archivo);

    cout << "Ventas del dia de hoy" << endl;
    for (int i = 0; i < tamaño; i++)
    {
        cout << "cp " << ventas[i].CodigoDeVendedor << " monto " << ventas[i].monto << endl;
    }
}
int main()
{
    int tamañoVentasMax = 3; //!!debe ser 1000
    Venta nVenta;

    int cantidadVendedores = 2;

    Vendedor vendedores[cantidadVendedores];
    cargarVendedores(vendedores, cantidadVendedores, 3); // traemos datos
leer(4);
    int i = 1;
    int cargarOtraVenta = 1;
    do
    {
        nVenta = cargarVenta(vendedores, cantidadVendedores);
        escribirVenta(nVenta);
        cout << "ingrese un 1 si quiere ingresar otra venta\n";
        cin >> cargarOtraVenta;
        i++;
    } while (i <= tamañoVentasMax && cargarOtraVenta == 1);
    leer(i);
    return 0;
}
