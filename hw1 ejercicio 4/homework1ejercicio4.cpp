#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

// 4. Recursión y ejecución en tiempo de compilación:
// a. Se requiere el código de una función recursiva que compare dos variables que contengan texto e indique mediante una variable bool si son iguales (true si son
// iguales, false si no lo son). Explique su elección entre los tipos string y char* (lea el siguiente item de este ejercicio antes de elegir el tipo de variable) y demuestre
// la funcionalidad de su código con un texto de, al menos, 64 caracteres.

//usar string es mas comodo y facil para una funcion recursiva
bool soniguales(std::string texto1, std::string texto2){
    if((texto1.length() != texto2.length())){
        return false; // si tienen distinta longitud ya sabemos que no son iguales
    }
    if(texto1.length() == 0 && texto2.length()==0){
        return true; //caso base-> comparo recursivamente todos los caracteres y todos pasaron la prueba de ser iguales
    }
    int largo = texto1.length()-1;
    if(texto1.at(largo)==texto2.at(largo)){ // compara de atras para adelante
        texto1.pop_back();
        texto2.pop_back(); // si son iguales los saca y vuelve a llamae a la funcion hasta que los textos queden vacios y confirme que si son iguales
        return soniguales(texto1, texto2);
    }
    return false;//caso contario, no pasaron la prueba
}    


// b. El componente high_resolution_clock de <chrono> permite calcular el tiempo de ejecución de un proceso al hacer:
// Utilice esté código y las modificaciones necesarias que crea conveniente para verificar cuanto tiempo toma la ejecución del código del ejercicio 4.1.

// -- > en el main

// c. Modifique el código del ejercicio 4.1 para que la comparación de los textos se realice en tiempo de compilación y obtenga el tiempo de ejecución. Compare
// este tiempo con el obtenido en el ejercicio 4.2 y justifique brevemente la diferencia (puede escribir su conclusión como un comentario al final del código de este item).

// para constrexpr usamos *char
constexpr bool soniguales2(const char* texto1, const char* texto2){
    if (*texto1 != *texto2) {
        return false; //compara el caracter actual y si es distinto devuelve false
    }
    if (*texto1 == '\0') {  //Si llegamos al final de ambas cadenas
        return true;
    }
    return soniguales2(texto1 + 1, texto2 + 1); // avanzamos en ambas cadenas hasta llegar hasta el final
}

//se realiza la comparación en tiempo de compilación 
constexpr bool resultado = soniguales2(
    "Te invitamos el miércoles 26 de marzo a las 17:30 horas, de forma virtual o presencial en el aula B107 del Campus Victoria. Una vez que completes el formulario de registro, obtendrás más información sobre el encuentro:",
    "Te invitamos el miércoles 26 de marzo a las 17:30 horas, de forma virtual o presencial en el aula B107 del Campus Victoria. Una vez que completes el formulario de registro, obtendrás más información sobre el encuentro:"
);

int main() {
    // 4 a:
    std::string texto1 = "Te invitamos el miércoles 26 de marzo a las 17:30 horas, de forma virtual o presencial en el aula B107 del Campus Victoria. Una vez que completes el formulario de registro, obtendrás más información sobre el encuentro:";
    std::string texto2 = "Te invitamos el miércoles 26 de marzo a las 17:30 horas, de forma virtual o presencial en el aula B107 del Campus Victoria. Una vez que completes el formulario de registro, obtendrás más información sobre el encuentro:";
    std::cout << soniguales(texto1,texto2) << std::endl; // imprime true en este caso

    // 4b: tiempo de ejecucion
    auto startTimeb = std::chrono::high_resolution_clock::now();
    soniguales(texto1,texto2);
    auto endTimeb = std::chrono::high_resolution_clock::now(); // cuenta cuanto tarda en correr soniguales
    auto elapsedTimeb = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimeb - startTimeb); // calcula cuantos nanosegundos tardo
    std::cout << "A miProcesoAMedir le tomó: "<< elapsedTimeb.count() << " nanosegundos" << std::endl;

    // 4 c:
    auto startTimec = std::chrono::high_resolution_clock::now();
    auto endTimec = std::chrono::high_resolution_clock::now();
    auto elapsedTimec = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimec - startTimec);

    std::cout << "Resultado (tiempo de compilación): " << std::boolalpha << resultado << std::endl;
    std::cout << "A miProcesoAMedir le tomó: " << elapsedTimec.count() << " nanosegundos" << std::endl;

    return 0;
}
// string no se puede evaluar con constexpr pero char si

//En 4b, la comparación se ejecuta en tiempo de ejecución, por lo que el procesador debe evaluar cada carácter y recorrer ambas cadenas, lo que toma un tiempo medible en nanosegundos
//En 4c el compilador resuelve la igualdad de las cadenas antes de generar el código ejecutable. cuando el codigo se corre en tiempo de complilacion tarda significativamente menos que en el 4B

