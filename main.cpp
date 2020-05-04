#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "funciones_lara.h"

using namespace std;

int main()
{
    int op;
    bool entrar=true;

    while(entrar)
    {
        system("cls");
        op=menuI();

        switch(op)
        {
        case (1):
        {
            menuII();
        } break;
        case (2):
        {
            cout<<"todavia no se creo la opcion."<<endl;
            system("pause");
        } break;
        case (3):
        {
            cout<<"todavia no se creo la opcion."<<endl;
            system("pause");
        } break;
        case (4):
        {
            cout<<"todavia no se creo la opcion."<<endl;
            system("pause");
        } break;
        case (5):
        {
            cout<<"todavia no se creo la opcion."<<endl;
            system("pause");
        } break;
        case (0):
        {
            entrar=false;
        }
        break;
        default:{
            cout<<"Opcion incorrecta vuelva a intetarlo."<<endl;
            system("pause");
        }break;

        };

    }

    return 0;
}
