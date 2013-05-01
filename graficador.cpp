/* Angel Carriola 28/04/2013
   Graficador de ecuaciones en la forma y = ax^n+bx+c,
   posibilidad de cambiar el rango de impresión y la escala para el eje Y
*/

// principalmente para graficar
#include <cstdio> // printf(), scanf()
#include <cstdlib> // abs(), itoa()
#include <cmath> // pow()
// principalmente para imprimir la ecuación simplificada
#include <iostream> // std::cout, std::cin
#include <string> // std::string

using namespace std;

// Calcula el lugar donde se encuentra el cuadrante respecto al punto (x,y),
// se numeran de 0 a 3 (0 es el primer cuadrante)
int obtenerCuadrante(int x, int y) {
    int cuadrante;
    if ( x > 0 && y > 0 )
        cuadrante = 0;
    if ( x < 0 && y > 0 )
        cuadrante = 1;
    if ( x < 0 && y < 0 )
        cuadrante = 2;
    if ( x > 0 && y < 0 )
        cuadrante = 3;
    return cuadrante;
}

// Devuelve una cadena vacia si el termino es 1 o 0 ya que multiplican a X, por lo que no se necesitan.
// si devolverSignoPositivo, entonces dolverá un signo + si n>0 o n es 1
// si devolverSoloSignoNegativo, solo devolverá el signo - cuando n = -1
string obtenerSalidaDeTermino(int termino, bool devolverSignoPositivo, bool devolverSoloSignoNegativo) {
    string resultado;
    char sTermino[20];
    resultado = itoa(termino, sTermino, 10);
    if ( termino == 1 || termino == 0 )
        resultado = "";
    if ( devolverSignoPositivo ) {
        if ( termino > 1 )
            resultado =  "+" + resultado;
        if ( termino == 1 )
            resultado = "+";
    }
    if ( devolverSoloSignoNegativo ) {
        if ( termino == -1 )
            resultado = "-";
    }
    return resultado;
}

string ecuacionConFormato;
int main(int fromX, int toX, int fromY, int toY, int ec_A, int ec_B, int ec_C, int ec_N, int escalaY) {

    // variables para definir el rango de la gráfica y los valores dela ecuación
    //int fromX=-30, toX=30, fromY=-50, toY=50, ec_A, ec_B, ec_C, ec_N, escalaY = 1;

    fromX = isnan(fromX) ? fromX : -30; toX = isnan(toX) ? toX : 30;
    fromY = isnan(fromY) ? fromY : -50; toY = isnan(toY) ? toY : 50;
    escalaY = isnan(escalaY) ? escalaY : 4;

    string leerRango, leerEscala, leerEcuacion = "s";

    cout << "Ecuacion en la forma y = Ax^n + Bx + C\n\n";

    // Si el usuario ya uso el programa en la misma ejecucion, se le pregunta si desea definir nuevamente la ecuacion
    if (ecuacionConFormato != "") {
        cout << "Ya a definido la ecuacion " << ecuacionConFormato << ", desea definirla de nuevo? (s/n)\n";
        cin >> leerEcuacion;
    }
    if (leerEcuacion == "s") {
        // lee los valores para la ecuación
        cout << "A = "; cin >> ec_A;
        cout << "B = "; cin >> ec_B;
        cout << "C = "; cin >> ec_C;
        cout << "n = "; cin >> ec_N;
    }

    printf("\n\nDesea definir el rango de la grafica? (s/n)\n (El rango predeterminado es [%i, %i][%i, %i])\n", fromX, toX, fromY, toY);
    cin >> leerRango;

    // lee los valores para el rango de impresión de la gráfica si el usuario lo desea
    if (leerRango == "s") {
        cout << "\nDefina el rango de la grafica (\"desde\" debe ser negativo o cero y \"hasta\"  debe ser positivo o cero)\n";
        cout << "\nPara el rango de X: \n";
        cout << "desde = "; cin >> fromX;
        cout << "hasta = "; cin >> toX;
        cout << "\nPara el rango de Y: \n";
        cout << "desde = "; cin >> fromY;
        cout << "hasta = "; cin >> toY;
    }

    printf("\n\nDesea definir la escala para Y? (s/n)\n (La escala predeterminada es %i)\n", escalaY);
    cin >> leerEscala;

    if (leerEscala == "s") {
        cout << "\nEscala para Y (debe ser un entero positivo): "; cin >> escalaY;
    }

    // define los cuatro cuadrantes de la gráfica respecto al rango leído, pues es un plano cartesiano
    char *cuadrante1[toX][toY];
    char *cuadrante2[-fromX][toY];
    char *cuadrante3[-fromX][-fromY];
    char *cuadrante4[toX][-fromY];

    // De aquí hasta el primer "for" solo se da formato a la ecuación ingresada por el usuario,
    // para que pueda visualizarla de forma simplificada
    string oec_A = obtenerSalidaDeTermino(ec_A, false, true),
        oec_B = obtenerSalidaDeTermino(ec_B, true, true),
        oec_C = obtenerSalidaDeTermino(ec_C, true, true),
        oec_N = obtenerSalidaDeTermino(ec_N, false, false);

    if ( oec_C == "+" )
        oec_C = oec_C + "1";
    if ( ec_C == 0 )
        oec_C = "";

    string oec_AXN, oec_BX;
    oec_AXN = oec_A + (ec_A == 0 ? "" : (ec_N == 0 ? "1" : "x" ))
        + (ec_N == 1 || ec_N == 0 || ec_A == 0 ? "" : "^" + oec_N );
    oec_BX = oec_B + (ec_B == 0 ? "" : "x");

    ecuacionConFormato = oec_AXN + oec_BX + oec_C;

    cout << "\n\n////////////////////////////////////////////////////////////////////////\n";
    cout << "La grafica de y = " << ecuacionConFormato;
    printf(", con el rango de impresion [%i, %i][%i, %i] \ny escala %i para Y es: \n", fromX, toX, fromY, toY, escalaY);
    cout << "////////////////////////////////////////////////////////////////////////\n\n";
    // Fin de la simplificación visual de la ecuación

    for(int i = fromX; i <= toX; i++) {
        int x = i;
        // Se calcula el valor de y respecto a la ecuacion con expresion en x
        float fY = ec_A*pow(x,ec_N) + ec_B*x + ec_C;
        int y = fY / escalaY;
        if ( fY != (int)fY || x > toX || x < fromX ||  y > toY || y < fromY || x == 0 || y == 0 )
            continue;
        // Se rescatan los valores originales del punto (x, y) antes de ajustarse para posicionarse en su cuadrante correspondiente
        int realX = x, realY = y;
        // obtiene el numero del cuadrante donde se encuentra el punto (x,y)
        int cuadrante = obtenerCuadrante(x, y);
        // Arregla las coordenas x, y para almacenarse en los arreglos de forma equivalente como el ejemplo:
        // cuadrante1 {{0,1,2,3,4}, {0,1,2,3,4}} - el punto (1,4) se posiciona en cuadrante[0, 0]
        if ( x < 0 )
            x = -fromX+x;
        if ( y > 0 )
            y = toY-y;
        if ( y < 0 )
            y = -y;
        if ( x != 0 )
            x--;
        if ( y != 0 )
            y--;
        // Guarda la ubicación del punto en su cuadrante correspondiente
        //if ( i == -fromX+1 )
            //printf("(%i,%i), (%i,%i)\n", x, y, realX, realY);
        switch(cuadrante) {
            case 0: cuadrante1[x][y] = "punto"; break;
            case 1: cuadrante2[x][y] = "punto"; break;
            case 2: cuadrante3[x][y] = "punto"; break;
            case 3: cuadrante4[x][y] = "punto"; break;
        }
    }
    cout << "\n\n";

    // imprime cuadrante 1 y 2
    for (int j = 0; j < toY; j++) {
        // cuadrante 2
        for (int p = 0; p < -fromX; p++) {
            char *r = cuadrante2[p][j];
            cout << (r=="punto"?' ':'@');
        }
        // eje del origen
        cout << "|";
        // cuadrante 1
        for (int p = 0; p < toX; p++) {
            char *r = cuadrante1[p][j];
            cout << (r=="punto"?' ':'@');
        }
        cout << "\n";
    }
    // imprime el eje de las abscisas (se suma 1 por el espacio de más de el origen)
    for (int i = 0; i < -fromX+toX + 1; i++)
        cout << "-";
    cout << "\n";
    // imprime cuadrante 3 y 4
    for (int j = 0; j < -fromY; j++) {
        // cuadrante 3
        for (int p = 0; p < -fromX; p++) {
            char *r = cuadrante3[p][j];
            cout << (r=="punto"?' ':'@');
        }
        // eje del origen
        cout << "|";
        // cuadrante 4
        for (int p = 0; p < toX; p++) {
            char *r = cuadrante4[p][j];
            cout << (r=="punto"?' ':'@');
        }
        cout << "\n";
    }

    string reiniciar;
    cout << "\n\nVolver a empezar? (s/n)\n";
    cin >> reiniciar;

    if (reiniciar == "s") {
        system("cls");
        main(fromX, toX, fromY, toY, ec_A, ec_B, ec_C, ec_N, escalaY);
    }
    else
        system("exit");

    return 0;
}
