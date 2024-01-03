// Desenvolvido por Bernardo Leris, Iago Carvalho Souto, Andre Ulhoa e Pedro Igor Martins

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// Função para verificar se é seguro atribuir uma cor a um vértice
bool isSafe(size_t v, int c, const vector<vector<int>>& graph, const vector<int>& color) {
    for (size_t i = 0; i < graph.size(); i++) {
        // Verifica se o vértice v está conectado a i e se i tem a mesma cor c
        if (graph[v][i] && c == color[i]) {
            return false; // Não é seguro
        }
    }
    return true; // É seguro
}

// Função para coloração por força bruta usando backtracking
bool bruteForce(const vector<vector<int>>& graph, vector<int>& color, size_t v, int numColors) {
    if (v == graph.size()) {
        return true; // Todos os vértices foram coloridos
    }

    for (int c = 1; c <= numColors; c++) {
        if (isSafe(v, c, graph, color)) {
            color[v] = c;

            // Chama recursivamente a próxima iteração
            if (bruteForce(graph, color, v + 1, numColors)) {
                return true; // A coloração foi bem-sucedida
            }

            color[v] = 0; // Desfaz a atribuição se não foi bem-sucedida
        }
    }

    return false; // Não foi possível colorir o grafo
}

// Função para coloração heurística
int heuristic(const vector<vector<int>>& graph, vector<int>& color) {
    int c = 0;

    while (find(color.begin(), color.end(), -1) != color.end()) {
        for (size_t i = 0; i < graph.size(); i++) {
            if (color[i] == -1) {
                if (isSafe(i, c, graph, color)) {
                    color[i] = c;
                }
            }
        }
        c++;
    }

    return c; // Retorna a quantidade de cores usadas
}

// Função principal para chamar a abordagem de coloração selecionada
int callFunctions(const vector<vector<int>>& graph, vector<int>& color, int method) {
    size_t numVertices = graph.size();
    int numColors = 0;

    auto start = high_resolution_clock::now();

    if (method == 1) {
        // Chama a heurística
        numColors = heuristic(graph, color);
    } else if (method == 2) {
        // Chama a abordagem de força bruta
        while (!bruteForce(graph, color, 0, numColors)) {
            numColors++;
        }
    } else {
        cerr << "Metodo invalido. Escolha 1 para heuristica ou 2 para forca bruta." << endl;
        return -1;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Imprime as cores atribuídas aos roteadores
    cout << "Frequencias atribuidas aos roteadores:" << endl;
    for (size_t i = 0; i < numVertices; i++) {
        cout << "Roteador " << i + 1 << ": Frequencia " << color[i] << endl;
    }

    // Imprime o tempo de execução
    cout << "Tempo de execucao: " << duration.count() << " milliseconds" << endl;

    return numColors;
}

// Função para ler o grafo de um arquivo
vector<vector<int>> readGraphFromFile(const string& filePath) {
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        exit(EXIT_FAILURE);
    }

    int numVertices;
    file >> numVertices;

    // Inicializa uma matriz de adjacência para representar o grafo
    vector<vector<int>> graph(numVertices, vector<int>(numVertices, 0));

    // Preenche a matriz de adjacência com os valores do arquivo
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            file >> graph[i][j];
        }
    }

    file.close();

    return graph;
}

int main() {
    string filePath;
    
    filePath = "test.txt";

    // Lê o grafo a partir do arquivo
    vector<vector<int>> graph = readGraphFromFile(filePath);

    // Vetor para armazenar as cores
    vector<int> color(graph.size(), -1);

    int method;
    cout << "Escolha o metodo de execucao (1 para heuristica, 2 para forca bruta): ";
    cin >> method;

    int numColors = callFunctions(graph, color, method);

    if (numColors != -1) {
        cout << "\nNumero minimo de frequencias necessarias: " << numColors << endl;
    }

    return 0;
}