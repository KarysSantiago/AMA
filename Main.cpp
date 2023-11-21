#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
using namespace cv;
using namespace std;

int estandarizar(int n, int m) {
    float numero;
    float b = log10(2);
    string resultado;
    int estandar;
    char entero = 0;
    bool flag;
    if (m != n) {			// no es cuadrada
        if (m < n)		//m�s filas
            while (m < n) {
                m = m + 1;
            }
        else 		//m�s columnas
            while (n < m) {
                n = n + 1;
            }
    }
    //ya son cuadradas
    //m=n
    while (m % 2 != 0) {
        m++;
    }
    estandar = m;
    return estandar;
}
int getFilas(string text) {
    int filas = 0;
    string linea;
    ifstream archivo(text.c_str());
    while (getline(archivo, linea)) {
        filas++;
    }
    return filas;
}
int getColumnas(string text) {
    int columnas = 0;
    string linea;
    ifstream archivo(text.c_str());
    getline(archivo, linea);
    for (int i = 0; i < linea.length(); i++) {
        if (linea[i] == ',' || linea[i] == ' ')
            columnas++;
    }
    return columnas + 1;
}
void FuncionEvaluar() {
    string text1 = "MATRIZ_1.txt";
    string text2 = "MATRIZ_2.txt";
    string linea;
    int filas = 0, columnas = 0;
    vector <char> aux;
    float numero = 0;
    ifstream archivo(text1.c_str());
    printf("Este programa multiplica 2 matrices\n");
    int a, m1 = 0, n1 = 0, m2 = 0, n2 = 0, num1 = 0, num2 = 0;
    float** A, ** B, ** C;
    m1 = getColumnas("MATRIZ_1.txt");
    n1 = getFilas("MATRIZ_1.txt");
    m2 = getColumnas("MATRIZ_2.txt");
    n2 = getFilas("MATRIZ_2.txt");

    num1 = estandarizar(n1, m1);
    num2 = estandarizar(n2, m2);
    /*creacion de matrices*/
    if (num1 < num2)
        a = num2;
    else
        a = num1;
    A = (float**)malloc(a * sizeof(float*));
    B = (float**)malloc(a * sizeof(float*));
    C = (float**)malloc(a * sizeof(float*));

    for (int i = 0; i < a; i++) {
        A[i] = (float*)malloc(a * sizeof(float*));
        B[i] = (float*)malloc(a * sizeof(float*));
        C[i] = (float*)malloc(a * sizeof(float*));
    }
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            A[i][j] = 0;
            B[i][j] = 0;
        }
    }
    while (getline(archivo, linea)) {
        for (int i = 0; i < linea.length(); i++) {
            if (linea[i] >= 48 && linea[i] <= 57)
                aux.push_back(linea[i]);
            if (linea[i] == ',' || linea[i] == ' ' || i == linea.length() - 1) {
                //numero=0;
                for (int j = 0; j < aux.size(); j++) {
                    numero = numero + ((aux[aux.size() - 1 - j] - 48) * pow(10, j));
                }
                A[filas][columnas] = numero;
                cout << " num " << A[filas][columnas];
                numero = 0;
                aux.clear();
                columnas++;
            }
        }
        columnas = 0;
        filas++;
    }
    filas = 0;
    columnas = 0;
    ifstream archivo2(text2.c_str());
    while (getline(archivo2, linea)) {
        for (int i = 0; i < linea.length(); i++) {
            if (linea[i] >= 48 && linea[i] <= 57)
                aux.push_back(linea[i]);
            if (linea[i] == ',' || linea[i] == ' ' || i == linea.length() - 1) {
                //numero=0;
                for (int j = 0; j < aux.size(); j++) {
                    numero = numero + ((aux[aux.size() - 1 - j] - 48) * pow(10, j));
                }
                B[filas][columnas] = numero;
                numero = 0;
                aux.clear();
                columnas++;
            }
        }
        columnas = 0;
        filas++;
    }
    cout << "Matriz A" << endl;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++)
            cout << A[i][j] << "  ";
        printf("\n");
    }
    cout << "Matriz B" << endl;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++)
            cout << B[i][j] << "  ";
        printf("\n");
    }
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++) {
            C[i][j] = 0;
            for (int k = 0; k < a; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
    cout << "Matriz C" << endl;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < a; j++)
            cout << C[i][j] << "  ";
        printf("\n");
    }
}
int pendiente(vector<float>y, bool  indicador) {
    int a = 1, b = 1, n;
    float mayor, menor, pend;
    n = y.size();
    mayor = y[1];
    menor = y[1];
    for (int i = 2; i < n; i++) {
        pend = y[i] / i;
        if (pend < menor) {
            menor = pend;
            a = i;
        }
        if (pend > mayor) {
            mayor = pend;
            b = i;
        }
    }
    if (indicador == true)
        return  a;          //menor
    else
        return b;           //Mayor
}
float buscarMayor(vector<float>y, bool flag) {
    float  mayor;
    int a = 1, n = y.size();
    mayor = y[1];
    for (int i = 2; i < n; i++) {
        if (y[i] > mayor) {
            mayor = y[i];
            a = i;
        }
    }
    if (flag == 1)
        return  mayor;
    else
        return  a;
}
float buscarMenor(vector<float>y, bool flag) {
    float menor;
    float a = 1;
    int n = y.size();
    menor = y[1];
    for (int i = 2; i < n; i++) {
        if (y[i] < menor) {
            menor = y[i];
            a = i;
        }
    }
    if (flag == 1)
        return  menor;
    else
        return  a;
}
vector <float> compensarX(int ns) {
    vector<float>pixX;
    pixX.clear();
    for (int i = 0; i <= ns; i++)
        pixX.push_back(((i * 1244) / ns) + 98);
    return pixX;
}
vector <float> compensarY(float yinter, vector <float>y) {
    vector<float>pixY;
    pixY.clear();
    for (int i = 0; i < y.size(); i++)
        pixY.push_back(680 - ((y[i] * 64) / yinter));
    return pixY;
}
float intervaloY(vector <float>y, int ns) {
    float yinter, mayor;
    mayor = buscarMayor(y, 1);
    yinter = mayor / 9;
    if (yinter == 0)
        yinter = 0.00001;
    return yinter;
}
void graficarTn(Mat img, vector<float>pixX, vector<float>pixY, int a) {
    for (int i = 0; i < pixX.size() - 1; i++)
        line(img, Point(pixX[i], pixY[i]), Point(pixX[i + 1], pixY[i + 1]), Scalar(a, a, a), 2);
}
Mat creaMat(int ns, vector<float>y, bool flag) {
    float xinter, yinter, temp, parametro;
    string path;
    if(flag == false)
        path = "ola.png";
    else
        path = "ola2.png";
    Mat img = imread(path);
    xinter = 1;
    yinter = intervaloY(y, ns);
    //A(98,680), B(1342,680), C(1342,Parametro), D(98,Parametro)
    //Lineas hrizontals
    for (int i = 0; i <= 10; i++) {
        parametro = 680 - (64 * i);
        line(img, Point(98, parametro), Point(1342, parametro), Scalar(241, 135, 225), 1);
    }
    //lineas verticales
    for (int i = 0; i <= ns; i++) {
        parametro = ((i * 1244) / ns) + 98;
        if(i%5==0)
            line(img, Point(parametro, 690), Point(parametro ,40), Scalar(241, 135, 225), 1);
        else
            line(img, Point(parametro, 680), Point(parametro, 40), Scalar(226, 27, 197), 1);
    }
    for (int i = 0; i <= 10; i++)
        putText(img, to_string(yinter * i), Point(15, 679 - (63 * i)), FONT_HERSHEY_DUPLEX, 0.5, Scalar(255, 255, 255));
    for (int i = 0; i < ns; i+=5) {
        temp = 1244 / ns;
        putText(img, to_string(i), Point((97 + (temp*i)), 718), FONT_HERSHEY_DUPLEX, 0.4, Scalar(255, 255, 255));
        if (ns > 100)
            i += 5;
        if (ns > 200)
            break;
    }
    putText(img, to_string(ns), Point(1330, 718), FONT_HERSHEY_DUPLEX, 0.4, Scalar(255, 255, 255));
    return img;
}
void muestraMat(Mat img) {
    imshow("Grafica", img);
    waitKey(0);
}
vector<float>Parabola(int ns) {    //Vector familia de las parabolas
    vector<float>familia;
    for (int i = 0; i <= ns; i++)
        familia.push_back(i * i);         //Formula y=x(2)
    return familia;
}
vector<float>ln(int ns) {    //Vector familia de las logaritmicas
    vector<float>familia;
    familia.push_back(0);
    for (int i = 1; i <= ns; i++)
        familia.push_back(log10(i));         //Formula y=log10(x)
    return familia;
}
vector <float> GraphicLog(vector <float> tn) {
    vector <float>intentos;
    int a = tn.size() - 1;
    float aux;
    for (int i = 1; i <= a; i++) {
        aux = (pow(tn[i], 2) / i);
        intentos.push_back(pow((aux * a), 0.5));
    }
    return intentos;
}
vector <float> graficarO(int familia, vector <float>tn, float *k) {
    float mayor, Mpend, aux;
    int a;
    vector <float> puntosO;
    vector <float>  Vaux;
    puntosO.clear();
    switch (familia) {
    case 1:         //ctes
        mayor = buscarMayor(tn, 1);
        *k = mayor;
        for (int i = 0; i <= tn.size(); i++) {
            puntosO.push_back(mayor);
        }
        break;
    case 2:         //lineal
        a = pendiente(tn, false);
        Mpend = tn[a] / a;
        *k = Mpend;
        for (int i = 0; i < tn.size(); i++)
            puntosO.push_back(Mpend * i);
        break;
    case 3:         //parabolica
        *k = tn[1];
        for (int i = 0; i < tn.size(); i++)
            puntosO.push_back(tn[1] * (i * i));
        break;
    case 4:         //logaritmo
        Vaux = GraphicLog(tn);
        mayor = buscarMayor(Vaux, 0) + 1;
        aux = (pow(tn[mayor], 2) / mayor);
        *k = aux;
        for (int i = 0; i < tn.size(); i++)
            puntosO.push_back(pow((aux * i), 0.5));
        break;
    }
    return puntosO;
}
vector <float> graficarOmega(int familia, vector <float> tn, float *k) {
    float menor, mpend, aux;
    int a, n, b;
    n = tn.size() - 1;
    vector <float> puntosO;
    vector <float>  Vaux;
    switch (familia) {
    case 1:         //ctes
        menor = buscarMenor(tn, 1);
        *k = menor;
        for (int i = 0; i < tn.size(); i++) {
            puntosO.push_back(menor);
        }
        break;
    case 2:         //lineal
        a = pendiente(tn, true);
        mpend = tn[a] / a;
        *k = mpend;
        for (int i = 0; i < tn.size(); i++)
            puntosO.push_back(mpend * i);
        break;
    case 3:         //parabolica
        float b, c;
        a = pendiente(tn, true);
        b = (tn[a] / (a * a));
        c = (tn[n] / ((n) * (n)));
        if ((b * (n * n)) > (c * (n * n))) {
            for (int i = 0; i < tn.size(); i++)
                puntosO.push_back(c * (i * i));
            *k = c;
        }
        else {
            for (int i = 0; i < tn.size(); i++)
                puntosO.push_back(b * (i * i));
            *k = b;
        }
        break;
    case 4:         //logaritmo
        Vaux = GraphicLog(tn);
        menor = buscarMenor(Vaux, 0) + 1;
        aux = (pow(tn[menor], 2) / menor);
        for (int i = 0; i < tn.size(); i++)
            puntosO.push_back(pow((aux * i), 0.5));
        *k = aux;
        break;
    }
    return puntosO;
}
float sumatoria(vector<float>x) {
    int n = x.size();
    float suma = 0;
    for (int i = 0; i < n; i++) {
        suma = suma + x[i];
    }
    return suma;
}
vector<float> multiplicar(vector<float>x, vector<float>y) {
    //Suponiendo que los vectores tienen misma dimension
    vector<float>resultado;
    float aux, aux2;
    int a = x.size();
    for (int i = 0; i < a; i++) {
        aux = x[i];
        aux2 = y[i];
        resultado.push_back(aux * aux2);
    }
    return resultado;
}
float correlacion(vector<float>x, vector<float>y) {
    int n = y.size();
    vector<float>aux;
    float r, ProdPunt, p3, p4, p5, p6, q1, q2, q3;
    aux = multiplicar(x, y);
    ProdPunt = sumatoria(aux);
    p3 = sumatoria(x);
    p4 = sumatoria(y);
    aux.clear();
    aux = multiplicar(x, x);
    p5 = sumatoria(aux);
    aux.clear();
    aux = multiplicar(y, y);
    p6 = sumatoria(aux);
    q1 = (n * ProdPunt) - (p3 * p4);
    q2 = sqrt((n * p5) - pow(p3, 2));
    q3 = sqrt((n * p6) - pow(p4, 2));
    r = q1 / (q2 * q3);
    if (r < 0)
        return -1 * r;
    else
        return r;
}
void FindFamily(vector<float>y, int ns, int* familia) {
    float a, b, c, d;
    vector<float>aux;
    aux = Parabola(ns);
    a = correlacion(y, aux);
    aux.clear();
    aux = ln(ns);
    b = correlacion(y, aux);
    aux.clear();
    for (int i = 0; i <= ns; i++)
        aux.push_back(i);
    c = correlacion(y, aux);        //lineal
    aux.clear();
    aux.push_back(0);
    for (int i = 1; i < ns; i++)
        aux.push_back(1);
    aux.push_back(1.01);
    d = correlacion(y, aux);           //ctes1
    cout << "\nLos numeros de correlacion arrojados son:\n";
    cout << "Constantes: "<< d <<endl;
    cout << "Lineales: " << c << endl;
    cout << "Logaritmicas: " << b << endl;
    cout << "Parabolicas: " << a << endl;
    if (a > b) {
        if (a > c) {
            if (a > d) {
                cout << "Pertenece a la familia de las parabolas";
                *familia = 3;
            }
            else {
                cout << "Pertenece a la familia de las constantes";
                *familia = 1;
            }
        }
        else {
            if (c > d) {
                cout << "Pertenece a la familia de las lineales";
                *familia = 2;
            }
            else {
                cout << "Pertenece a la familia de las constantes";
                *familia = 1;
            }
        }
    }
    else {
        if (b > c) {
            if (b > d) {
                cout << "Pertenece a la familia de las logaritmicas";
                *familia = 4;
            }
            else {
                cout << "Pertenece a la familia de las constantes";
                *familia = 1;
            }
        }
        else {
            if (c > d) {
                cout << "Pertenece a la familia de las lineales";
                *familia = 2;
            }
            else {
                cout << "Pertenece a la familia de las constantes";
                *familia = 1;
            }
        }
    }
}
vector <float> CaptTiemp(int ns) {
    vector <float> tiempos;
    clock_t aux;
    float fin, a;
    tiempos.push_back(0);
    for (int i = 1; i <= ns; i++) {
        aux = clock();
        FuncionEvaluar();
        aux = clock() - aux;
        fin = ((float)(aux)) / CLOCKS_PER_SEC;
        tiempos.push_back(fin);
    }
    return tiempos;
}
vector <float> little(vector <float>y, int familia, bool flag) {
    float menor, a, pend, mayor, aux;
    int n = y.size() - 1;
    if (flag == 0) {
        if (familia != 2) {
            menor = buscarMenor(y, 1);
            for (int i = 0; i < y.size(); i++)
                if (menor >= 0.0002)
                    y[i] = y[i] - 0.0002;
            a = 0;
            if (familia != 1) {
                y[0] = 0;
                for (int i = 1; i <= n; i++) {
                    aux = ((y[n] - 0.0002) / (n * n)) * (i * i);
                    if (aux > 0)
                        y[i] = aux;
                    else
                        y[i] = 0;
                }
            }

        }
        else {
            a = pendiente(y, 1);
            menor = y[a];
            if (menor >= 0.0001)
                menor = menor - 0.0001;
            pend = menor / a;
            for (int i = 0; i < y.size(); i++)
                y[i] = pend * i;
        }
    }
    else {
        if (familia != 2) {
            a = 0;
            if (familia != 1) {
                a = 1;
                y[0] = 0;
            }
            for (int i = a; i < y.size(); i++)
                y[i] = y[i] + 0.0002;
        }
        else {
            a = pendiente(y, 0);
            mayor = y[a];
            mayor = mayor + 0.0002;
            pend = mayor / a;
            for (int j = 0; j < y.size(); j++) {
                aux = pend * j;
                y[j] = aux;
            }
        }
    }
    return y;
}
int main() {
    int familia, ns, opc, nueva = 0, opc2, ite;
    float xinter, yinter,Kmejor, Kpeor;
    vector<float>tiempo;
    vector<float>aux;
    vector<float>pixX;
    vector<float>pixY;
    pixX.clear();
    pixY.clear();
    cout << "Digite la cantidad de ejecuciones:   ";
    cin >> ns;
    tiempo = CaptTiemp(ns);
    Mat grafica2;
    Mat grafica = creaMat(ns, tiempo, false);
    xinter = 1;
    yinter = intervaloY(tiempo, ns);      //puede cambiar
    pixX = compensarX(ns);
    pixY = compensarY(yinter, tiempo);      //puede cambiar
    FindFamily(tiempo, ns, &familia);
    graficarTn(grafica, pixX, pixY, 255);
    muestraMat(grafica);
    cout << endl;
    cout << "Notacion asintotica:\n1.Big O\n2.Little O\n3.Big Omega\n4.Little Omega\n5.Big Theta\n6.Little Theta\nDigite la opcion deseada:  " << endl;
    cin >> opc;
    if (opc == 1 || opc == 2 || opc == 5 || opc == 6) {
        aux = graficarO(familia, tiempo, &Kpeor);
        if (opc == 2 || opc == 6)
            aux = little(aux, familia , 1);
        grafica2 = creaMat(ns, aux, true);
        yinter = intervaloY(aux, ns);
        pixY.clear();
        aux = compensarY(yinter, aux);
        pixY = compensarY(yinter, tiempo);
        graficarTn(grafica2, pixX, pixY, 255);
        graficarTn(grafica2, pixX, aux, 55);
    }
    if (opc == 3 || opc == 4 || opc == 5 || opc == 6) {
        aux = graficarOmega(familia, tiempo, &Kmejor);
        if (opc == 4 || opc == 6)
            aux = little(aux,familia, 0);
        if (opc == 4 || opc == 3)
            grafica2 = creaMat(ns, aux, true);
        if (opc==3 ||opc==4)
            graficarTn(grafica2, pixX, pixY, 255);
        aux = compensarY(yinter, aux);
        graficarTn(grafica2, pixX, aux, 55);
    }
    muestraMat(grafica2);
    cout << "Desea calcular el tiempo de ejecucion en x iteracion para la notacion seleccionada anteriormente?  1. Si   0. No   ";
    cin >> opc2;
    if (opc2 == 1) {
        cout << endl << "Digite la iteracion de la cual desea conocer cuanto tardara: ";
        cin >> ite;
        if (opc == 1 || opc == 2 || opc == 5 || opc == 6) {
            cout << endl << "Para el peor de los casos se tardara: ";
            if (opc == 2 || opc == 6) {
                switch (familia) {
                case 1:     //ctes
                    cout << Kpeor + 0.0002;
                    break;
                case 2:     //lineales
                    cout << Kpeor * ite;
                    break;
                case 3:     //PARABOLICA
                    cout << (Kpeor + 0.0002) * (ite * ite);
                    break;
                case 4:     //log
                    cout << pow(((Kpeor+ 0.0002) * ite), 0.5);
                    break;
                }
            }
            else {
                switch (familia) {
                case 1:     //ctes
                    cout << Kpeor;
                    break;
                case 2:     //lineales
                    cout << Kpeor * ite;
                    break;
                case 3:     //PARABOLICA
                    cout << Kpeor * (ite * ite);
                    break;
                case 4:     //log
                    cout << pow((Kpeor * ite), 0.5);
                    break;
                }
            }
        }
        if (opc == 3 || opc == 4 || opc == 5 || opc == 6) {
            cout << endl << "Para el mejor de los casos se tardara: ";
            if (opc == 4 || opc == 6) {
                switch (familia) {
                case 1:     //ctes
                    if (Kmejor >= 0.0002)
                        cout << Kmejor - 0.0002;
                    else
                        cout << "0";
                    break;
                case 2:     //lineales
                    if ((Kmejor-0.0002) * ite >= 0)
                        cout << (Kmejor - 0.0002) * ite;
                    else 
                        cout << "0";
                    break;
                case 3:     //PARABOLICA
                    if ((Kmejor - 0.0002) * (ite * ite) >= 0)
                        cout << (Kmejor - 0.0002) * (ite * ite);
                    else
                        cout << "0";
                    break;
                case 4:     //log
                    if (pow(((Kmejor - 0.0002) * ite), 0.5) >= 0)
                        cout << pow(((Kmejor - 0.0002) * ite), 0.5);
                    else
                        cout << "0";
                    break;
                }
            }
            else {
                switch (familia) {
                case 1:     //ctes
                    cout << Kmejor;
                    break;
                case 2:     //lineales
                    cout << Kmejor * ite;
                    break;
                case 3:     //PARABOLICA
                    cout << Kmejor * (ite * ite);
                    break;
                case 4:     //log
                    cout << pow((Kmejor * ite), 0.5);
                    break;
                }
            }
        }
    }
    return 0;
}