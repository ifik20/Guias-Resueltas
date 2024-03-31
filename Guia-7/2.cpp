#include <iostream>
#include <fstream>
#include "listasutil.hpp"
#include "listas.hpp"
#include "listasord.hpp"
#include "listasordUni.hpp"
#include "rwstring.hpp"

using namespace std; 

struct ventas{
    string modelo; 
    int cantidad; 
}; 
struct ciudad{
    string city;
    int totalVentas = 0; 
    int totalCantidad = 0; 
    Nodo<ventas>* listaVentas = nullptr;   
}; 
struct registro{
    string ciudad; 
    string modelo; 
    int cantidad;  
}; 

const int dimCiudad {12};  
const int dimModelo {10}; 

ostream& operator << (ostream& os, const ciudad& ord)
{
    os<<"Ciudad: "<<ord.city<< "\t"<<"Ventas: "<<ord.totalVentas<< "\t"<<"Cantidad Unidades: "<<ord.totalCantidad;
    return os;
}

ostream& operator << (ostream& os, const ventas& ord)
{
    os<<"Modelo: "<<ord.modelo<< "\t \t"<<ord.cantidad; 
    return os; 
}

fstream& operator >> (fstream& fs, registro& ord)
{
    ord.ciudad = readstring(fs, dimCiudad);
    ord.modelo = readstring(fs, dimModelo); 
    fs.read(reinterpret_cast<char*> (&ord.cantidad), sizeof (ord.cantidad)); 
    return fs; 
}

int ordenarlista(ciudad a, ciudad b)
{
    return a.city.compare(b.city);
}

int main()
{
    Nodo<ciudad>* lista = nullptr; 
    fstream archivo; 
    ventas vent; 
    registro reg;
    ciudad ciu;
    Nodo<ciudad>* punteroCiudad;   

    archivo.open("G07E02.bin", ios :: in | ios :: binary); 
    if (!archivo)
    {
        cout<<"ERROR: No se puede abrir el archivo."; 
        return EXIT_FAILURE;
    }

    while (archivo >> reg) //Hago todo junto para hacer una sola lectura del archivo.
    {
        ciu.city = reg.ciudad; 
        punteroCiudad = insertar_unico(ciu, lista, ordenarlista);
        punteroCiudad->dato.totalVentas++; 
        punteroCiudad->dato.totalCantidad += reg.cantidad; 
        vent.modelo = reg.modelo; 
        vent.cantidad = reg.cantidad; 
        agregar(punteroCiudad->dato.listaVentas, vent);  
    }
    archivo.close(); //Cierro archivo, ya no lo necesito, cargue todos mis datos ya. 

    cout<<"Listado de ciudades con total de ventas y cantidad de unidades: "<<endl; 
    mostrar(lista); 
    cout<<"Fin de la lista"<<endl; 
    
    cout<<"==================================="<<endl; 
    cout<<endl<<"Ingrese ciudad a consultar ventas: "<<endl; 
    
    while(cin >> ciu.city)
    {
        if (ciu.city == "EOF") 
        break;

        punteroCiudad = buscar(ciu, lista, ordenarlista);
        if (punteroCiudad != nullptr)
        {
            cout<<"Ventas realizadas en "<<ciu.city<<": "<<endl; 
            cout<<"Modelo \t \t"<<"      "<<"Cantidad"<<endl; 
            mostrar(punteroCiudad -> dato.listaVentas);
            cout<<endl;  
        }else{
            cout<<"No hay ventas registradas en esta ciudad. "<<endl; 
        }
    cout<<endl<<"Ingrese ciudad a consultar ventas: "<<endl;
    } 
    cin.clear(); 

    int cantminima; 
    cout<<"==================================="<<endl; 
    cout<<endl<<"Ingrese ciudad a consultar ventas: "<<endl;
    if (cin >> ciu.city)
    if (ciu.city == "EOF"){
        return EXIT_FAILURE;
    } 
        cout<<"Ingrese cantidad minima de ventas: "<<endl; 
    while (cin >> cantminima)
    {
        punteroCiudad = buscar(ciu, lista, ordenarlista); 
        if (punteroCiudad != nullptr)
        {
            Nodo<ventas>* punteroVenta = punteroCiudad->dato.listaVentas; 
            int cantSuperar = 0; 
            while (punteroVenta != nullptr)
            {
                if(punteroVenta->dato.cantidad > cantminima)
                cantSuperar++; 
                punteroVenta=punteroVenta->sig; 
            }
            cout<<"Ventas realizadas en "<<ciu.city<<"mayores a "<<cantminima<<": "<<endl; 
            cout<< cantSuperar; 
            cout<<endl;  
        }else{
            cout<<"No hay ventas registradas en esta ciudad. "<<endl; 
        }
    cout<<endl<<"Ingrese ciudad a consultar ventas: "<<endl;
    if (cin >> ciu.city)
        cout<<"Ingrese cantidad minima de ventas: "<<endl;
    }
}
