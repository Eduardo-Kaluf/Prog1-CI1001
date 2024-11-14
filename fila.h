// TAD fila
// Autor: Eduardo Kaluf, GRR 20241770

#ifndef FILA
#define FILA

// estrutura de um item da fila
struct nodo_t
{
  int valor ;			// valor do item
  struct nodo_t *prox ;	// próximo item
} ;

// estrutura de uma fila
struct fila_t
{
  struct nodo_t *prim ;	// primeiro item
  struct nodo_t *ult ;		// último item
  int tamanho ;		// número de itens da fila
} ;

// Cria uma fila vazia.
// Retorno: ponteiro p/ a fila ou NULL em erro.
struct fila_t *fila_cria ();

// Remove todos os itens da fila e libera a memória.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f);

// Nas operações insere/retira/consulta/procura, a fila inicia na
// posição 0 (primeiro item) e termina na posição TAM-1 (último item).

// Insere o item no início da fila
// Retorno: número de itens na fila após a operação ou -1 em erro.
int queue (struct fila_t *f, int valor);

// Retira o item da fila da posição indicada.
// se a posição for -1, retira do fim.
// Retorno: número de itens na fila após a operação ou -1 em erro.
int dequeue (struct fila_t *f, int *valor);

// Informa o tamanho da fila (o número de itens presentes nela).
// Retorno: número de itens na fila ou -1 em erro.
int fila_tamanho (struct fila_t *f);

// Retorna 1 se a fila é vazia.
// 0 caso exista algum elemento na fila.
int fila_vazia (struct fila_t *f);

// Imprime o conteúdo da fila do inicio ao fim no formato "item item ...",
// com um espaço entre itens, sem espaços antes/depois, sem newline.
void fila_imprime (struct fila_t *f);

#endif
