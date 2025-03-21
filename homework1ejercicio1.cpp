#include <ostream>
#include <iostream>

// a. Crear una función que dado un valor entero “n”, positivo y mayor a uno, devuelva una matriz cuadrada con valores como en los siguientes ejemplos para n=2 y n=3:

void creamatriznxn(int n) {
    if (n < 1) {
        return; // no se puede crear matriz con n=0 o negativo
    }
    int cont = 1;// inicializamos contador
    int matriz[n][n]; //crea matriz de tamano nxn

    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {  // con 2 fors anidados vamos llenando la matriz en orden, incrementando el contador en cada vuelta (este es el que le asigna el numero a su posicion respectiva)
            matriz[i][j] = cont++;
            std::cout << matriz[i][j] << " "; // asigna valor e imprime 
        }
        std::cout << std::endl;// ir a la siguiente linea cuando se termina la fila
    }
}



// b. Proveer un código que imprima el contenido de la matriz, utilizando un único ciclo for, desde el mayor valor al menor, es decir, para el ejemplo de Para 𝑀2:

void contenidomatriz(int n){
    int temp = n-1;
    int valor = n*n;
    while(temp>=0){
        for(int i=n-1; i>=0; i--){
            std::cout << "[" << temp << "]" << "[" << i << "]" << "=" << valor << " ";
            std::cout << std::endl;
            valor--;
        }
        temp--;
    }
}
// sin while y 1 solo for
// inicializamos valor con el numero maximo qu vendria a ser nxn
// usamos un unico for que va desde 0 a nxn(abarca todos los valores de la matriz)
// este es el que se va a imprimir con sus respectivas posiciones [i][j], lo decrementamos en cada vuelta hasta llegar al primer valor, valor=1
void contenidomatriz(int n) {
    int valor = n* n;
    for (int k=0; k<n*n; k++) {
        int i = (n*n-1-k) / n;  //calcula la fila de atrás hacia adelante
        int j = (n*n-1-k) % n;  //calcula la columna de atrás hacia adelante
        std::cout << "[" << i << "][" << j << "] = " << valor-- << std::endl; // en orden decreciente, va imprimiendo los valores con sus posiciones
    } // decrementamos valor en cada vuelta
}


int main() { 
    int n;
    std::cout << "ingrese un numero ";
    std::cin >> n;
    std::cout << std::endl;
    creamatriznxn(n); 
    contenidomatriz(n);
    return 0;
}


