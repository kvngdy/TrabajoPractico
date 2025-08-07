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
                                        int fecha; 
    int CodigoDeVendedor;
    int CodigoDeProducto;
    int monto; 
};
bool esBisiesto(int año)
{
    return (año % 4 == 0 && año % 100 != 0) || (año % 400 == 0);
}

bool verificarFecha(int fecha)
{
    if (fecha < 19000101 || fecha > 20991231) 
    {
        return false;
    }
    int año = fecha / 10000;
    int mes = (fecha / 100) % 100;
    int dia = fecha % 100;

    if (mes < 1 || mes > 12)
    {
        return false;
    }
    int diasEnMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes == 2 && esBisiesto(año))
    {
        diasEnMes[1] = 29;
    }
    if (dia < 1 || dia > diasEnMes[mes - 1])
    {
        return false;
    }
    return true;
}

int cargarFecha()
{
    int control = 0;
    int fecha;
    do
    {
        if (control == 0)
        {
            cout << "dame la fecha en AAAAMMDD: ";
        }
        else
        {
            cout << "ERROR EN EL FORMATO\n";
            cout << "dame la fecha en AAAAMMDD: ";
        }

        cin >> fecha;

        control = 1;

    } while (!verificarFecha(fecha));

    return fecha;
}

// donando por un anonimo generoso de vendedores!

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

Venta cargarVenta(Vendedor vendedores[], int tamaño, int fecha)
{
    Venta Nventa;
    int control = 0;
    Nventa.fecha = fecha;

    do
    {
        if (control == 0)
        {
            cout << "\ndame el codigo de vendedor: ";
        }
        else
        {
            cout << "\ncodigo de vendedor inexistente \n";
            cout << "dame el codigo de vendedor: ";
        }

        cin >> Nventa.CodigoDeVendedor;
        control = 1;
    } while (!verificarCodigoVendedor(Nventa.CodigoDeVendedor, vendedores, tamaño));

    cout << "dame el codigo de producto: ";
    cin >> Nventa.CodigoDeProducto;

    control = 0;
    do
    {
        if (control == 0)
        {
            cout << "\nDame el monto de la venta: " ;
        }
        else
        {
            cout << "\nEl monto de la venta No pude ser 0 ni negativo" << endl;

            cout << "Dame el monto de la venta: ";
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
        FILE *archivo = fopen("vendedores.exe", "rb");
        if (archivo == NULL){
            
        }
    }

    fread(sucursales, sizeof(Sucursal), cantidadSucursales, archivo); // solo pera recorrer las surcursales que ocupan el primer espacio de bits
    fread(vendedores, sizeof(Vendedor), cantidadVendedores, archivo);
    fclose(archivo);
}

void escribirVenta(Venta nVenta, int numeroVenta)
{
    FILE *archivo;
    if (numeroVenta == 0)
    {
        archivo = fopen("ventas_diarias.dat", "wb"); // sobre escribe el archivo si existe
    }
    else
    {
        archivo = fopen("ventas_diarias.dat", "ab");
    }

    if (archivo != NULL)
    {
        fwrite(&nVenta, sizeof(nVenta), 1, archivo);
        cout << "\nVenta guardada...\n";
        fclose(archivo);
    }
    else
    {
        cout << "ERROR no se pudo guardar la venta" << endl;
        escribirVenta(nVenta, numeroVenta); // trata de ejecutarlo de nuevo
    }
}

void leer()

{
    FILE *archivo = fopen("ventas_diarias.dat", "rb");
    int tamaño;
    fseek(archivo, -(int)sizeof(int), SEEK_END);
    fread(&tamaño, sizeof(int), 1, archivo);
    cout << "\nEl tamaño es: " << tamaño << endl;
    fseek(archivo, 0, SEEK_SET);
    Venta ventas[tamaño];
    fread(ventas, sizeof(Venta), tamaño, archivo);

    cout << "Ventas del dia de hoy:" << endl;
    for (int i = 0; i < tamaño; i++)
    {
        cout << "-CodigoDeVendedor: " << ventas[i].CodigoDeVendedor << " // monto: " << ventas[i].monto << endl;
    }
}
int main()
{
    int tamañoVentasMax = 1000;
    Venta nVenta;
    int fecha = cargarFecha();
    int cantidadVendedores = 15;

    Vendedor vendedores[cantidadVendedores];
    cargarVendedores(vendedores, cantidadVendedores, 3); // traemos datos
    int i = 0;
    char cargarOtraVenta = 'y';

    do
    {
        nVenta = cargarVenta(vendedores, cantidadVendedores, fecha);
        escribirVenta(nVenta, i);
        cout << "\n¿Quieres ingresar otra venta?(y/n): ";
        cin >> cargarOtraVenta;
        i++;
    } while (i <= tamañoVentasMax && cargarOtraVenta == 'y');
    FILE *archivo = fopen("ventas_diarias.dat", "ab");
    fwrite(&i, sizeof(i), 1, archivo);
    fclose(archivo);
    if (i == tamañoVentasMax)
    {
        cout << "\n Ya hiciste las "<< tamañoVentasMax << "ventas de hoy, ahora a descansar" << endl;
    }
    
    leer(); //mostramos un resumen de lac ventas de hoy 
    cout << "\nTotal de ventas: " << i;
    return 0;
}