Trabalho Prático Grafos
Professor: Ricardo Terra
Alunos: Bernardo Leris, Iago Carvalho Souto, Andre Ulhoa e Pedro Igor Martins


Nosso trabalho envolve a resolução do problema de interferência entre roteadores Wi-Fi, comumente enfrentado em redes sem fio densamente povoadas, e utilizando a heurística ingênua da coloração de grafos. Nesta abordagem, cada roteador é representado como um vértice no grafo, com arestas conectando roteadores que podem causar interferência. A heurística consiste em atribuir canais diferentes aos roteadores, equivalendo à coloração de vértices de forma que roteadores adjacentes não compartilhem o mesmo canal.

- A heurística funciona da seguinte forma:

Inicialização: Inicia-se com a cor 0 (c = 0). A cor de cada vértice é armazenada no vetor color, onde -1 indica que o vértice ainda não foi colorido.

Enquanto houver vértices não coloridos (-1 no vetor color):

Itera-se sobre todos os vértices do grafo (for (size_t i = 0; i < graph.size(); ++i)).
Se o vértice i ainda não foi colorido (color[i] == -1):
	Verifica se é possível atribuir a cor c ao vértice i usando a função isValid(i, graph, color, c).
Se for possível, atribui a cor c ao vértice i (color[i] = c).
Próxima cor e repetição: Incrementa-se a cor (c++) e o processo se repete até que todos os vértices estejam coloridos.

Retorno: A função retorna o número total de cores usadas.

- Algoritmo de força bruta:

Condição de Parada: A função graphColoringUtil é uma função recursiva que tenta colorir os vértices do grafo. A primeira verificação é se o índice v (representando o vértice atual) atingiu o tamanho do grafo (v == graph.size()). Se sim, isso significa que todos os vértices foram coloridos, e a função retorna true, indicando que uma solução válida foi encontrada.

Loop de Cores: Para o vértice atual v, a função utiliza um loop de 1 até numColors para tentar atribuir cada cor possível. A variável c representa a cor atual sendo testada.

Verificação de Segurança (isSafe): Antes de atribuir a cor c ao vértice v, verifica-se se essa atribuição é segura usando a função isSafe(v, c, graph, color). Essa função verifica se a cor c pode ser atribuída ao vértice v sem violar a regra de não ter vértices adjacentes com a mesma cor.

Atribuição e Chamada Recursiva: Se a atribuição da cor c for segura, ela é realizada (color[v] = c), e a função é chamada recursivamente para o próximo vértice (graphColoringUtil(graph, color, v + 1, numColors)).

Backtracking: Se a chamada recursiva retorna true, isso significa que a atribuição da cor levou a uma solução válida. A função retorna true. Se a chamada recursiva retorna false, a cor atribuída a v é revertida para 0 (color[v] = 0), e o loop continua com a próxima cor.

Retorno Final: Se nenhum conjunto de cores é encontrado após tentar todas as combinações, a função retorna false, indicando que não há uma solução válida com o número de cores especificado.

Em resumo, o algoritmo explora todas as combinações possíveis de cores, para os vértices, utilizando recursão e backtracking para encontrar uma solução válida.

Para iniciar a aplicação, é necessário executar o código, o qual inclui a leitura de um arquivo denominado "test.txt". Este arquivo está localizado na pasta do trabalho e contém informações cruciais, como o número de vértices de um grafo e sua matriz correspondente, em que o 0 correponde a não existência de conexões entre os vértices e o 1 a conexão entre eles, utilizados para a realização dos testes necessários. Ao iniciar o sistema, serão apresentadas opções para executá-lo usando a heurística ou a força bruta, permitindo assim a comparação entre os dois algoritmos.

