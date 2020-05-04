#ifndef FUNCIONES_LARA_H_INCLUDED
#define FUNCIONES_LARA_H_INCLUDED
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
///////STRUCTURAS//////
struct platos
{
    int id;
    char nombre[50];
    float costo_de_preparacion;
    float valor_de_venta;
    int tiempo_de_preparacion;
    int id_restaurante;
    int comision_restaurante;
    int id_categoria;
    bool estado;
};
////////////prototipos///////////////
bool baja_logica();
void listar_todos_los_platos();
void platos_por_restaurant();
int validacion_plato(int);
void mostrare(struct platos);
struct platos copypage_platos();
bool cargar_plato(struct platos *);
void guardar_plato(struct platos *);
void mostrar_plato();
int posicion_plato(int);
int menuI();
void menuII();
////////MOSTRAR O LISTAR//////////////
void mostrare(struct platos mostrare)
{

    cout << "ID: " << mostrare.id << endl;
    cout << "NOMBRE: " << mostrare.nombre << endl;
    cout << "COSTO DE PREPARACION: $" << mostrare.costo_de_preparacion << endl;
    cout << "VALOR DE VENTA: $" << mostrare.valor_de_venta << endl;
    cout << "TIEMPO DE PREPARACION: mnts" << mostrare.tiempo_de_preparacion << endl;
    cout << "ID RESTAURANTE: " << mostrare.id_restaurante << endl;
    cout << "COMISION RESTAURANTE: %" << mostrare.comision_restaurante << endl;
    cout << "ID CATEGORIA: " << mostrare.id_categoria << endl;
    if(mostrare.estado)
    {
        cout << "-HAY STOCK-" << endl;
    }
    else
    {
        cout << "-NO HAY STOCK-" << endl;
    }

}
///////CARGA/////
bool cargar_plato(struct platos *registro)
{
    system("cls");
    cout << "ID: ";
    cin>>registro->id;
    int ids=registro->id;
    if(registro->id<0)
    {
        cout << "el numero no puede ser menor a cero. " << endl;
        system("pause");
        return false;
    }
    if(validacion_plato(ids)>0)
    {
        system("cls");
        cout << "Este numero ya se encuentra en uso." << endl;
        system("pause");
        return false;
    }
    cout << "NOMBRE: ";
    cin.ignore();
    cin.getline(registro->nombre,50);

    cout << "COSTO DE PREPARACION: ";
    cin>>registro->costo_de_preparacion;
    if(registro->costo_de_preparacion<0)
    {
        cout << "el numero no puede ser menor a cero. ";
        system("pause");
        return false;
    }
    cout << "VALOR DE VENTA: ";
    cin>>registro->valor_de_venta;
    if(registro->valor_de_venta < 0 || registro->valor_de_venta < registro->costo_de_preparacion)
    {
        cout << "el numero no puede ser menor a cero, o a su costo de preaparacion. ";
        system("pause");
        return false;
    }
    cout << "TIEMPO DE PREPARACION: ";
    cin>>registro->tiempo_de_preparacion;
    if(registro->tiempo_de_preparacion<0)
    {
        cout << "el numero no puede ser menor a cero. ";
        system("pause");
        return false;
    }
    cout << "ID RESTAURANTE: ";
    cin>>registro->id_restaurante;
    if(registro->id_restaurante<0)
    {
        cout << "el numero no puede ser menor a cero. ";
        system("pause");
        return false;
    }
    cout << "COMISION RESTAURANTE: ";
    cin>>registro->comision_restaurante;
    if(registro->comision_restaurante < 0 && registro->comision_restaurante <100 )
    {
        cout << "La comision debe ser entre 0 y 100. ";
        system("pause");
        return false;
    }
    cout << "ID CATEGORIA: ";
    cin>>registro->id_categoria;
    if(registro->id_categoria<0)
    {
        cout << "el numero no puede ser menor a cero. ";
        system("pause");
        return false;
    }
    registro->estado=true;
    system("pause");
    cin.ignore();
    return true;
}

///////COSAS FILE/////////
int validacion_plato(int id) // se esta usando para la garga de platos.
{
    struct platos reg;
    FILE *p;
    p=fopen("archivo.dat","rb");
    if(p==NULL)
    {
        fclose(p);
        return-1;
    }
    while(fread(&reg,sizeof(platos),1,p)==1)
    {
        if(reg.id==id)
        {
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return-2;
}
void guardar_plato(struct platos *cargado)
{
    FILE *guardar;
    guardar = fopen("archivo.dat","ab");
    if(guardar == NULL)
    {
        cout << "ERROR EN GUARDAR PLATO." << endl;
        system("pause");
        return;
        fclose(guardar);
    }
    fwrite(cargado,sizeof(platos),1,guardar);
    cout<<"plato guardado con exito!"<<endl;
    fclose(guardar);
}
void mostrar_plato()
{
    int id;
    cout << "Ingresa El ID del producto que desea ver: ";
    cin>>id;
    cin.ignore();
    cout<<endl;
    struct platos reg;
    FILE *mostrar;
    mostrar = fopen("archivo.dat","rb");
    if(mostrar == NULL)
    {
        cout << "ERROR EN MOSTRAR PLATO." << endl;
        system("pause");
        fclose(mostrar);
        return;
    }
    while(fread(&reg,sizeof(platos),1,mostrar)==1)
    {
        if(reg.id == id && reg.estado == true)
        {
            mostrare(reg);
        }
        else if(reg.id == id && reg.estado == false)
        {
            cout<<"Este archivo fue dado de baja. consulte al soporte para volver a darlo de alta. Por que solo pidio la baja en su menu. "<<endl;

        }
    }
    system("pause");
    fclose(mostrar);
    return;

}
int posicion_plato(int id)
{
    int i=0;
    struct platos reg;
    FILE *p;
    p=fopen("archivo.dat","rb");
    if(p==NULL)
    {
        cout << "ERROR EN LA BUSQUEDA DE POSICION DE EL PLATO." << endl;
        system("pause");
        fclose(p);
        return-1;
    }
    while(fread(&reg,sizeof(platos),1,p)==1)
    {
        if(reg.id==id)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return-2;
}
struct platos copypage_platos(int ids)
{
    struct platos platico;
    long int pos=posicion_plato(ids);
    FILE *p;
    p=fopen("archivo.dat","rb");
    if(p==NULL)
    {
        cout<<"ERROR EN LA MODIFICACION DE PLATOS. " << endl;
        system("pause");
        fclose(p);
        platico.id=-1;
        return platico;
    }
    fseek(p,pos*sizeof(platos),SEEK_SET);
    fread(&platico,sizeof(platos),1,p);
    fclose(p);
    return platico;

};
void mod_platos()
{
    struct platos reg;
    int pos;
    int id;
    cout << "Modificando Datos ingrese id: ";
    cin>>id;
    pos=posicion_plato(id);

    FILE *p;
    p=fopen("archivo.dat","rb+");
    if(p==NULL)
    {
        cout<<"nope"<<endl;
        system("pause");
        fclose(p);
        return;
    }
    if(pos>=0)
    {
        reg=copypage_platos(id);
        mostrare(reg);
        cout<<"Modifique el precio: "<<endl;
        cin>>reg.valor_de_venta;
        cin.ignore();
        cout<<endl;
        cout<<"Modifique el tiempo de preparacion. "<<endl;
        cin>>reg.tiempo_de_preparacion;
        cin.ignore();
        fseek(p,pos*sizeof(platos),SEEK_SET);
        fwrite(&reg,sizeof(platos),1,p);
        mostrare(reg);
    }
    system("pause");
    fclose(p);
    return;
}
void platos_por_restaurant()
{
    struct platos reg;
    int id;
    cout<<"ingrese el id del restaurant: ";
    cin>>id;
    cin.ignore();
    FILE *p;
    p=fopen("archivo.dat","rb");
    if(p==NULL)
    {
        cout<<"No se encontro." << endl;
        system("pause");
        fclose(p);
        return;
    }
    cout<<"PLATOS DEL RESTAURANT: #"<< id <<endl;
    while(fread(&reg,sizeof(platos),1,p)==1)
    {
        if(reg.id_restaurante==id){
        cout<<"-------------------------"<<endl;
        mostrare(reg);

        }
    }
    system("pause");
    fclose(p);
    return;
}
void listar_todos_los_platos()
{
    struct platos reg;
    FILE *p;
    p=fopen("archivo.dat","rb");
    if(p==NULL)
    {
        cout<<"no se pudo encontrar el archivo: "<<endl;
        system("pause");
        return;
    }
    while(fread(&reg,sizeof(platos),1,p)==1)
    {
        cout<<"--------------------------------------"<<endl;
        mostrare(reg);
        cout<<"--------------------------------------"<<endl;
    }
    system("pause");
    fclose(p);
    return;
}
bool baja_logica()
{
    struct platos reg;
    int pos;
    int id;
    cout << "DANDO DE BAJA UN ARCHIVO. "<<endl;
    cout<<"ingrese el id de el archivo que desea dar de baja: ";
    cin>>id;
    pos=posicion_plato(id);
    FILE *p;
    p=fopen("archivo.dat","rb+");
    if(p==NULL)
    {
        cout<<"nope"<<endl;
        system("pause");
        fclose(p);
        return false;
    }
    if(pos>=0)
    {
        reg=copypage_platos(id);
        reg.estado=false;
        fseek(p,pos*sizeof(platos),SEEK_SET);
        fwrite(&reg,sizeof(platos),1,p);
        fclose(p);
        return true;
    }
    else
    {
        fclose(p);
        return false;
    }
}
//////////MENUS/////////////
int menuI()// MENU DE PRINCIPAL //
{
    int op;
    cout << "MENU PRINCIPAL." << endl;
    cout << "------------------------" << endl;
    cout << "1) PLATOS. " << endl;
    cout << "2) CLIENTES." << endl;
    cout << "3) PEDIDOS." << endl;
    cout << "4) REPORTES." << endl;
    cout << "5) CONFIGURACION." << endl;
    cout << "------------------------" << endl;
    cout << "0) SALIR" << endl;
    cin>>op;
    return op;
}
void menuII()// MENU DE PLATOS //
{
    struct platos cargado;
    while(true)
    {
        system("cls");
        int op;
        cout << "MENU PLATOS." << endl;
        cout << "------------------------" << endl;
        cout << "1) NUEVO PLATO. " << endl;
        cout << "2) MODIFICAR PLATO." << endl;
        cout << "3) LISTAR PLATO POR ID." << endl;
        cout << "4) PLATOS POR RESTAURANT." << endl;
        cout << "5) LISTAR TODOS LOS PLATOS." << endl;
        cout << "6) ELIMINAR PLATO." << endl;
        cout << "------------------------" << endl;
        cout << "0) SALIR" << endl;
        cin>>op;

        switch(op)
        {
        case (1):
        {
            system("cls");
            cout<<"CARGANDO PLATO. "<<endl;
            if(cargar_plato(&cargado))
            {
                guardar_plato(&cargado);
                system("pause");
            }

        }
        break;
        case (2):
        {
            system("cls");
            cout<<"MODIFICANDO COSTO DE VENTA Y TIEMPO DE PREPARACION. "<<endl;
            mod_platos();
        }
        break;
        case (3):
        {
            system("cls");
            cout<<"LISTANDO PLATO. "<<endl;
            mostrar_plato();
        }
        break;
        case (4):
        {
            system("cls");
            platos_por_restaurant();
        }
        break;
        case (5):
        {
            listar_todos_los_platos();
        }
        break;
        case (6):
        {
            if(baja_logica())
            {
                cout<<"El plato fue dado de baja con exito! "<<endl;
                system("pause");
            }
            else
            {
                cout<<"El plato No pudo darse de baja exitosamente. "<<endl;
                system("pause");
            }
        }
        break;
        case (0):
        {
            return;
        }
        break;
        default:{
        cout<<"Opcion incorrecta vuelva a intetarlo."<<endl;
        system("pause");
        }break;

        };

    }
}


#endif // FUNCIONES_LARA_H_INCLUDED
