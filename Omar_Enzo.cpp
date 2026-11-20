#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    char dato;
    Nodo* sig;
};

// ---------- Operaciones Pila ----------
void push(Nodo*& tope, char c) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = c;
    nuevo->sig = tope;
    tope = nuevo;
}

char pop(Nodo*& tope) {
    if (tope == nullptr) return '\0';
    Nodo* temp = tope;
    char c = temp->dato;
    tope = tope->sig;
    delete temp;
    return c;
}

// ---------- Operaciones Cola ----------
void insertar(Nodo*& cab, Nodo*& fin, char c) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = c;
    nuevo->sig = nullptr;
    if (cab == nullptr) {
        cab = nuevo;
        fin = nuevo;
    } else {
        fin->sig = nuevo;
        fin = nuevo;
    }
}

char extraer(Nodo*& cab, Nodo*& fin) {
    if (cab == nullptr) return '\0';
    Nodo* temp = cab;
    char c = temp->dato;
    cab = cab->sig;
    if (cab == nullptr) fin = nullptr;
    delete temp;
    return c;
}

void destruirPila(Nodo*& tope) {
    while (tope != nullptr) {
        pop(tope);
    }
}

void destruirCola(Nodo*& cab, Nodo*& fin) {
    while (cab != nullptr) {
        extraer(cab, fin);
    }
}

// ==========================================
// FUNCIÓN BOOLEANA SI-SI
// ==========================================
bool esPalindromo(Nodo*& tope, Nodo*& cab, Nodo*& fin) {
    bool resultado = true;

    while (tope != nullptr && cab != nullptr) {
        char letraPila = pop(tope);
        char letraCola = extraer(cab, fin);
        if (letraPila != letraCola) {
            resultado = false;
        }
    }

    if (tope != nullptr || cab != nullptr) {
        resultado = false;
    }

    destruirPila(tope);
    destruirCola(cab, fin);
    return resultado;
}

bool esVocal(char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

bool contieneDiptongo(Nodo*& tope) {
    bool resultado = false;
    bool vocalAnterior = false;

    while (tope != nullptr) {
        char letra = pop(tope);
        if (esVocal(letra) && vocalAnterior) {
            resultado = true;
        }
        vocalAnterior = esVocal(letra);
    }

    return resultado;
}

// ---------- MAIN ----------
int main() {
    Nodo* tope = nullptr;
    Nodo* cab = nullptr;
    Nodo* fin = nullptr;

    string palabra = "RADAR"; // Cambia a "AGUA" para probar el falso

    // Llenamos ambas estructuras con la misma palabra
    for (char c : palabra) {
        push(tope, c);
        insertar(cab, fin, c);
    }

    cout << "Palabra analizada: " << palabra << endl;
    bool resultado = esPalindromo(tope, cab, fin);

    if (resultado) {
        cout << "Resultado: TRUE → Es palíndromo" << endl;
    } else {
        cout << "Resultado: FALSE → No es palíndromo" << endl;
    }

    Nodo* topeDiptongo = nullptr;
    string palabraDiptongo = "CUIDADO";
    for (char c : palabraDiptongo) {
        push(topeDiptongo, c);
    }

    cout << "Palabra analizada: " << palabraDiptongo << endl;
    if (contieneDiptongo(topeDiptongo)) {
        cout << "Resultado: TRUE → Contiene diptongo" << endl;
    } else {
        cout << "Resultado: FALSE → No contiene diptongo" << endl;
    }

    return 0;
}