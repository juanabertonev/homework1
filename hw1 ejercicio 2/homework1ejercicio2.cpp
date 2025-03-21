#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept> // Para atrapar el std::runtime_error

// 2. En muchos sistemas, es importante registrar todo lo que sucede mientras están en funcionamiento. 
//Para ello, se utiliza un sistema de log que almacena los eventos relevantes. 
//Cada evento recibe una etiqueta que indica su nivel de importancia o gravedad. 
//Las etiquetas más comunes son: DEBUG, INFO, WARNING, ERROR y CRITICAL.


// a. En este ejercicio, se pide crear un sistema log que permite agregar entradas a un
// archivo mediante el llamado a una función logMessage 
// Donde NivelSeveridad corresponderá con unas de las leyendas previamente
// mencionadas. El formato esperado en una línea del archivo de log es el siguiente:
// [ERROR] <Mensaje>
// [INFO] <Mensaje>
// etc.
// Verifique su funcionamiento con al menos una entrada de cada tipo.

void logMessage(std::string mensaje, std::string etiqueta){
    std::ofstream outFile("archivo_logmessage.txt", std::ios::app); // modo append
    if (outFile.is_open()) { // Escribe por línea de texto
        outFile << "[" << etiqueta << "]" << " <" << mensaje << ">" << std::endl; // escribe etiqueta y mensaje
        outFile.close(); // Cerrar el archivo!!!
        std::cout << "mensaje registrado.\n";
    } else{
        std::cerr << "Error abriendo el archivo!\n";
    }
}


// b. En un proyecto usualmente se solicitan cambios para mejorar o agregar funcionalidad.
// Para el caso del código del ejercicio 2.a, se requiere tener la habilidad de agregar
// mensajes personalizados para registrar otro tipo de eventos. Los requisitos son los
// siguientes:

// i. Todos los nuevos mensajes deben ser invocados con logMessage.
void logMessage(std::string mensaje, std::string etiqueta){
    std::ofstream outFile("archivo_logmessage.txt", std::ios::app); // modo append
    if (outFile.is_open()) { // Escribe por línea de texto
        outFile << "[" << etiqueta << "]" << " <" << mensaje << ">" << std::endl; // escribe etiqueta y mensaje
        outFile.close(); // Cerrar el archivo!!!
        std::cout << "mensaje registrado.\n";
    } else{
        std::cerr << "Error abriendo el archivo!\n";
    }
}

// ii. Se requiere la posibilidad de registrar errores, indicando el mensaje de error, el
// archivo y la línea de código donde sucedió este error, es decir:
// logMessage(String Mensage_de_Error, String Archivo, Int Línea_de_Código)
void logMessage(std::string Mensaje_de_Error, std::string Archivo, int Linea_de_Código){
    std::ofstream outFile("archivo_logmessage.txt", std::ios::app); // modo append
    if (outFile.is_open()) { // Escribe por línea de texto
        outFile << "[ERROR]" << " <" << Mensaje_de_Error << ">" << " Archivo: " << Archivo << " Linea donde sucedio el error: " << Linea_de_Código << std::endl;
        outFile.close(); // Cerrar el archivo!!!
        std::cout << "Error registrado.\n";
    } else{
        std::cerr << "No se pudo abrir el archivo \n";
    
    }    
}

// iii. Se requiere la posibilidad de registrar un mensaje de “Acceso de Usuario” a la
// aplicación. Este mensaje debe tener una leyenda nueva: [SECURITY]. La misma
// debe ser ingresada de la siguiente manera:
// logMessage(String Mensaje_De_Acceso, String Nombre_de_Usuario)
// Los mensajes de acceso pueden ser: Access Granted, Access Denied, etc.

void logMessage(std::string Mensaje_De_Acceso, std::string Nombre_de_Usuario){
    std::ofstream outFile("archivo_logmessage.txt", std::ios::app); // modo append
    if (outFile.is_open()) { // Escribe por línea de texto
        outFile << "[SECURITY]" << " Nombre de usuario: " << Nombre_de_Usuario << " <" << Mensaje_De_Acceso << ">" << std::endl; // escribe en el archivo
        outFile.close(); // Cerrar el archivo!!!
        std::cout << "mensaje de acceso registrado.\n";
    } else{
        std::cerr << "No se pudo abrir el archivo \n";
    
    }     
}

// iv. Se requiere un código que pruebe que el sistema verifica la funcionalidad
// requerida y que además demuestre que puede capturar un error en runtime,
// crear una entrada en el log y después detener la ejecución del programa y salir
// del mismo con un código de error (return 1). 

int main(){
    // 2 a:
    logMessage("DEBUG", "virus detectado");
    logMessage("INFO", "bateria baja");
    logMessage("WARNING", "sobrecalentamiento de disco duro");
    logMessage("ERROR", "codigo fallo en correr");
    logMessage("CRITICAL", "manana haran 40 grados");

    // 2 b ii:
    //simulación de error
    logMessage("Acceso inválido", "main.cpp", 42);

    // 2 b iii:
    logMessage("Access Granted", "juana7"); // simulacion de accesso otorgado

    // 2 b iv:
    try {
        int x = 10, y = 0;
        if (y == 0){// Arroja un error con el texto dado.
            throw std::runtime_error("ERROR"); // division por 0
        }
        int result = x / y;// nunca se corre porqe tiro error ya
    } catch (const std::runtime_error& e) { // Captura la excepcion
        logMessage(e.what(),__FILE__, __LINE__ - 4); // lo registra con nuestra funcion registraerrores
        return 1;
    } 
    return 0;// no funciono bien (no registro el error)
}

