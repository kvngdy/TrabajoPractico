# TrabajoPractico
Trabajo practico general numero 1, Algoritmos y estructuras de datos.

#Guia#
Trabajo Práctico Grupal – Gestión de Ventas Diarias - 2025
Modalidad:
Grupos de 5 estudiantes.
Entrega: Código C++ dividido en tres archivos .cpp distintos + informe + video muestra como funciona
Descripción del Proyecto
La empresa "Ventas Rápidas SA" quiere informatizar su sistema de ventas diarias.
El programa debe permitir:
Registrar vendedores, indicando también a qué sucursal pertenecen.
Registrar las ventas del día.
Guardar y leer toda la información de ventas en archivos.
Analizar y mostrar resultados basados en el archivo de ventas. 
Hay 15 vendedores y 3 sucursales
Requerimientos
1. Registro de Vendedores y Sucursales (registro.cpp)
Permitir cargar:
Código de vendedor (único)
Nombre del vendedor
Nombre de la sucursal
Guardar todos los vendedores en el archivo vendedores.dat.
✅ Tip: Validar que no se repita el código de vendedor.
2. Registro de Ventas Diarias (ventas.cpp)
Permitir cargar hasta 1000 ventas por día.
Debe cargar la fecha en formato AAAAMMDD.
Cada venta debe registrar:
Código de vendedor
Código de producto
Monto de la venta
Guardar todas las ventas en ventas_diarias.dat.
✅ Tip: Validar que el vendedor exista al momento de registrar la venta.
3. Análisis de Ventas (analisis.cpp)
Desde el archivo ventas_diarias.dat, el sistema debe:
Determinar el vendedor que más dinero generó (mostrar su nombre y monto total).
Determinar la sucursal que más dinero generó (sumando las ventas de todos los vendedores de esa sucursal).
Mostrar un ranking de los productos más vendidos (por cantidad de veces que se vendió cada código de producto).
✅ Tip:
Agrupar ventas por vendedor y sucursal usando corte de control o acumulación.
Para ranking de productos, contar ocurrencias y luego ordenar.
Entregables
3 archivos .cpp principales (registro.cpp, ventas.cpp, analisis.cpp) + main.cpp.
Archivos .dat generados (vendedores.dat, ventas_diarias.dat).
Informe breve explicando:
Cómo dividieron las responsabilidades en módulos.
Cómo resolvieron la validación y almacenamiento.
Estructura de Carpetas
/TrabajoPractico/
  registro.cpp
  ventas.cpp
  analisis.cpp
 
 -- Ejecutando el código se debe generar estos archivos -- 
  vendedores.dat
  ventas_diarias.dat

