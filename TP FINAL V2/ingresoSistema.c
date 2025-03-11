#include <stdlib.h>
#include <stdio.h>
#include "paciente.h"
#include "empleado.h"
#include "ingresoSistema.h"
#include "string.h"
#include "menuDios.h"


UsuarioPaciente ingresarUsuarioPaciente()
{
    UsuarioPaciente usuarioP;
    UsuarioPaciente aux;
    int i=3;
    FILE*archi=fopen("UsuariosPacientes.txt","r");
    int flag = 0;
    char dni[8];

    if(archi)
    {

        while(flag == 0 && i >=0 && i<=3)
        {

            printf("INICIO DE SESION PACIENTE\n ");
            printf("-------------------------\n ");
            printf("USUARIO: ");
            fflush(stdin);
            gets(aux.usuarioPaciente);

            printf("CONTRASENIA: ");
            fflush(stdin);
            gets(aux.contrasenia);
            printf("-------------------------\n ");

            while(fread(&usuarioP,sizeof(UsuarioPaciente),1,archi))
            {
                if(strcmp(aux.usuarioPaciente,usuarioP.usuarioPaciente) == 0 && strcmp(aux.contrasenia,usuarioP.contrasenia)==0)
                {

                    flag = 1;

                    break;

                }
            }
            if (flag==0)
            {
                printf("TE QUEDAN %i INTENTOS\n",i);
                printf("LA CONTRASENIA O EL USUARIO ES INVALIDO, INTENTE DE NUEVO...\n");
                flag = 0;
                i--;
                rewind(archi);
            }
        }
        fclose(archi);
    }

    if (flag == 1)
    {
        return aux;
    }
    else
    {
        printf("Inicio de sesion fallido. Cerrando el programa...\n");
        exit(EXIT_FAILURE);
    }
}


UsuarioEmpleado ingresarUsuarioEmpleado()
{
    UsuarioEmpleado aux;
    UsuarioEmpleado usuarioE;
    int i = 3;
    FILE *archi = fopen("UsuariosEmpleados.txt", "r");
    int flag = 0;

    if (archi)
    {
        while (i > 0 && flag == 0)
        {
            printf("INICIO DE SESION EMPLEADO\n ");
            printf("-------------------------\n ");
            printf("USUARIO: ");
            fflush(stdin);
            gets(aux.usuarioEmpleado);

            printf("CONTRASENIA: ");
            fflush(stdin);
            gets(aux.contraEmpleado);
            printf("-------------------------\n ");

            fseek(archi, 0, SEEK_SET);

            while (fread(&usuarioE, sizeof(UsuarioEmpleado), 1, archi) && flag == 0)
            {
                if (strcmp(aux.usuarioEmpleado, usuarioE.usuarioEmpleado) == 0 && strcmp(aux.contraEmpleado, usuarioE.contraEmpleado) == 0)
                {
                    flag = 1;
                    aux=usuarioE;
                }
            }

            if (flag == 0)
            {
                printf("TE QUEDAN %i INTENTOS\n", (i-1));
                printf("LA CONTRASENIA O EL USUARIO ES INVALIDO, INTENTE DE NUEVO...\n");
                i--;
                rewind(archi);
            }
        }
        fclose(archi);
    }

    if (flag == 1)
    {
        return aux;
    }
    else
    {
        printf("Inicio de sesion fallido. Cerrando el programa...\n");
        exit(EXIT_FAILURE);
    }
}
void menuPaciente(nodoarbol*arbol)
{

    UsuarioPaciente usuario=ingresarUsuarioPaciente();
    int eleccion=0;

    do
    {
        if(usuario.nivel !=2 && usuario.nivel!=1)
        {
            system("cls");
            printf("MENU PACIENTE.-\n");
            printf("1:VER INGRESOS.-\n");
            printf("2:CAMBIAR CONTRASENIA.-\n");
            printf("3:SALIR.-\n");
            printf("Seleccione la opcion que desea utilizar.\n");
            fflush(stdin);
            scanf("%i",&eleccion);
             system("cls");
            switch(eleccion)
            {
            case 1:
                mostrarEstudioPaciente(arbol,usuario);
                break;
            case 2:
                cambiarContraseniaPacientes("UsuariosPacientes.txt",usuario);
                break;
            case 3:
                printf("Saliendo del menu paciente.-\n");
                system("pause");
                break;
            }
        }
        else
        {
            printf("Error al ingresar el usuario.\n");
            break;
        }
    }while(eleccion !=3);
}
void menuEmpleado(nodoarbol*arbol)
{
    UsuarioEmpleado empleado = ingresarUsuarioEmpleado();
    int eleccion = 0;


    do
    {
        if (empleado.nivel == 1) ///administrativo
        {
            system("cls");
            printf("Tareas administrativas.\n");
            printf("1: CARGAR PACIENTE.-\n");
            printf("2: CARGAR INGRESO.-\n");
            printf("3: MODIFICAR PRACTICAS.-\n");
            printf("4: MOSTRAR EMPLEADOS LABORATORIO.-\n");
            printf("5: MOSTRAR PACIENTES LABORATORIO.-\n");
            printf("6: CAMBIAR CONTRASENIA.-\n");
            printf("7: SALIR.-\n");
            printf("Seleccione la opcion que desea utilizar.\n");

            fflush(stdin);
            scanf("%i", &eleccion);
            system("cls");

            switch (eleccion)
            {
            case 1:

                cargaEnArchivo("pacientes.txt");


                break;
            case 2:
               arbol=pasarArchPacienteToArbol("pacientes.txt",arbol);
               agregarIngreso("ingresos.txt",arbol);

                break;

            case 3:



                break;
            case 4:

                mostrarArchEmpleados("empleadosLab.txt");
                system("pause");
                break;
            case 5:
                mostrarArchPacientes("pacientes.txt");
                system("pause");
                break;
            case 6:
                cambiarContraseniaEmpleados("UsuariosEmpleados.txt","empleadosLab.txt", empleado);
            break;
            case 7:
                printf("Saliendo del menu paciente.-\n");
                system("pause");
                return; // Salir del bucle y la función
            }
        }
        else if (empleado.nivel == 2) ///nivel 2 tecnico bioquimico
        {
            system("cls");
            printf("Tareas de laboratorio.\n");
            printf("1: CARGAR RESULTADO\n");
            printf("2: MODIFICAR RESULTADO\n");
            printf("3: VER PRACTICAS\n");
            printf("4: CAMBIAR CONTRASENIA\n");
            printf("5: SALIR\n");
            printf("Seleccione la opcion que desea utilizar.\n");

            fflush(stdin);
            scanf("%i", &eleccion);
            system("cls");

            switch (eleccion)
            {
            case 1:
                // cargar RESULTADO
                break;
            case 2:
                // MODIFICAR RESULTADO
                break;
            case 3:
                mostrarArchPracticas("practicasLab.dat");
                system("pause");
                break;
            case 4:
                cambiarContraseniaEmpleados("UsuariosEmpleados.txt","empleadosLab.txt", empleado);
                break;
            case 5:
                printf("Saliendo del menu paciente.-\n");
                system("pause");
                return; // Salir del bucle y la función
            }
        }
        else
        {
            break;
        }

    } while (1);
}

void menu()
{
    int eleccion = 0;
    empleados_laboratorio empleado;
    nodoarbol* arbol=inicArbol();


    do
    {
        printf("Laboratorio de analisis clinico\n\n\n");
        printf("------------------------------------\n");
        printf("1: Iniciar sesion.\n");
        printf("2: Crear usuario.\n");
        printf("3: Salir.\n");
    printf("------------------------------------\n");
        printf("Seleccione la opcion que desea utilizar.\n");

        fflush(stdin);
        scanf("%i", &eleccion);
        system("cls");
        switch (eleccion)
        {
        case 1:
        {
            int eleccion2 = 0;
            printf("1: Iniciar sesion paciente.\n");
            printf("2: Iniciar sesion empleado.\n");
            printf("3: Salir.\n");
            printf("Seleccione la opcion que desea utilizar.\n");

            fflush(stdin);
            scanf("%i", &eleccion2);
            system("cls");


            switch (eleccion2)
            {
            case 1:
                menuPaciente(arbol);
                break;
            case 2:
                menuEmpleado(arbol);
                break;
            case 3:
                break;
            default:
                printf("Elección no válida. Intente de nuevo.\n");
            }
        }
        break;
        case 2:
            printf("Ingrese contrasenia del laboratorio.\n");
            fflush(stdin);
            char contra[8];
            gets(contra);
            if(strcmp(contra,"labcom7")==0)
            {
                agregarEmpleados("empleadosLab.txt",empleado);
                break;
            }else
            {system("cls");
                printf("Contrasenia del laboratorio incorrecta.\n");
                system("pause");
                system("cls");
            break;

            }
        case 3:
            printf("Cerrando programa, hasta pronto.-\n");

            break;
        case 99:
            menuDios();
            break;
        default:
            printf("Elección no válida. Intente de nuevo.\n");
        }

    }
    while (eleccion!=3);
}
//
///
