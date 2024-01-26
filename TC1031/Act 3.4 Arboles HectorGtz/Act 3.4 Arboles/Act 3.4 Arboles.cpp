#include <iostream>
#include <fstream>
using namespace std;

// Definición de un nodo del árbol binario de búsqueda
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Función para insertar un nodo en el árbol
TreeNode* insertNode(TreeNode* root, int value) {
    if (root == nullptr) {
        return new TreeNode(value);
    }
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    }
    else {
        root->right = insertNode(root->right, value);
    }
    return root;
}

// Función para recorrer el árbol en orden y actualizar contadores
void inOrderTraversal(TreeNode* root, int& counter, int& realCounter, int& nodeCounter) {
    if (root != nullptr) {
        inOrderTraversal(root->left, counter, realCounter, nodeCounter);
        counter = counter + root->data - 1;
        if (nodeCounter != 0) {
            realCounter = realCounter + counter;
        }
        nodeCounter++;
        inOrderTraversal(root->right, counter, realCounter, nodeCounter);
    }
}

int main() {
    int nodeCounter = 0;
    int realCounter = 0;
    int counter = 1;
    int numLists = 0;
    TreeNode* root = nullptr;

    ifstream file("BST_NUMBERS.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo de lectura" << endl;
        return 1;
    }

    int number;
    int count = 0;
    while (file >> number) {
        if (count == 0) {
            numLists = number;
        }
        else {
            root = insertNode(root, number);
        }
        count++;
    }
    file.close();

    cout << "RECORRIDO INORDEN" << endl;
    cout << "NUMERO DE LISTAS A COMPARAR: " << numLists << endl;
    inOrderTraversal(root, counter, realCounter, nodeCounter);
    cout << "Comparaciones totales: " << realCounter << endl;

    return 0;  // Se corrigió el espacio en blanco no estándar aquí
}
