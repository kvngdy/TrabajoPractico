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
bool verificarCodigoVendedor(int codigo)
{
    return true;
}

Venta cargarVenta()
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
    } while (!verificarCodigoVendedor(Nventa.CodigoDeVendedor));

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
// donando por un anonimo generozo de vendedores
bool CodigoDeVendedorRepetido(int n_codigo, Vendedor vendedores[], int tamaño)
{
    for (int i = 0; i < tamaño; i++)
    {
        if (vendedores[i].CodigoDeVendedor == n_codigo)
        {
            return true;
        }
    }
    return false;
}
void cargarVendedores(Vendedor vendedores[], int cantidadVendedores, int cantidadSucursales)
{
    Sucursal sucursales[cantidadSucursales];
    FILE *archivo = fopen("vendedores.dat", "rb");
    if (archivo == NULL)
    {
        cout << "No se pudo abrir el archivo.";
    }

    fread(sucursales, sizeof(Sucursal), 3, archivo);
    fread(vendedores, sizeof(Vendedor), 4, archivo);
    fclose(archivo);

    cout << "\n Vendedores \n";
    for (int i = 0; i < 4; i++)
    {
        cout << "\n  Vendedor " << i + 1 << ": \n"
             << vendedores[i].Nombre;
        cout << " - Codigo: " << vendedores[i].CodigoDeVendedor;
        cout << " - Sucursal: " << vendedores[i].CodigoDeSucursal;
    }
}

int main()
{
    int cantidadVendedores = 3;
    int tamañoVentasMax = 3; //!!debe ser 1000
    Venta ventasDia[tamañoVentasMax];
    Vendedor vendedores[cantidadVendedores];
    cargarVendedores(vendedores, cantidadVendedores, 3);

    int i = 1;
    int cargarOtraVenta = 1;
    do
    {
        cargarVenta();

        cout << "ingrese un 1 si quiere ingresar otra venta\n";
        cin >> cargarOtraVenta;
        i++;
    } while (i <= 1000 && cargarOtraVenta == 1);

    return 0;
}
