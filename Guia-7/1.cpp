#include <iostream>
#include <fstream>
#include "listasutil.hpp"
#include "listasordUni.hpp"
#include "rwstring.hpp"

using namespace std;

struct ventas
{
    string modelo;
    int cantidad;
};
const int dimModelo {10};

ostream& operator << (ostream& os, const ventas& ord)
{
     os<<"Modelo: " << ord.modelo << "\t \t" << " Cantidad: " << ord.cantidad;
     return os;
}

fstream& operator << (fstream& fs, const ventas& ord)
{
    writestring(fs, ord.modelo, dimModelo);
    fs.write(reinterpret_cast<const char* > (&ord.cantidad), sizeof (ord.cantidad));
    return fs;
}

fstream& operator >> (fstream& fs, ventas& ord)
{
    ord.modelo = readstring(fs, dimModelo);
    fs.read(reinterpret_cast<char *>(&ord.cantidad),sizeof (ord.cantidad));
    return fs;
}

int ordenarLista(ventas a, ventas b)
{
    return a.modelo.compare(b.modelo);
}

int main()
{
    Nodo<ventas>* lista = nullptr;
    Nodo<ventas>* puntero;
    ventas vta;
    ventas reg;
    fstream archivo;

    archivo.open("G07E01.bin", ios :: in | ios :: binary);
    if(!archivo){
        cout << "No se pudo abrir el archivo";
        return EXIT_FAILURE;
    }

    vta.cantidad = 0;
    while (archivo >> reg)
    {
        vta.modelo = reg.modelo;
        puntero = insertar_unico(vta, lista, ordenarLista);
        puntero->dato.cantidad += reg.cantidad;
    }
    archivo.close();

    cout<<"Listado de modelos con cantidades vendidas: "<<endl;
    mostrar(lista);
    cout<<"Fin de lista"<<endl;
    return 0;
}
