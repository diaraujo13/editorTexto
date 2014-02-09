/* Include Guards;
   Condição para verificar se o header já foi incluído.
   Isso evita dele ser colocado duas vezes no código. */
#ifndef MAIN_H_INCLUDED /* Código só será importado se ele não estiver definido */
#define MAIN_H_INCLUDED /* Caso não esteja definido, então "define" */
    typedef struct {

    GtkWidget* janela;
    GtkTextBuffer *buffer_text;

} Janela_Buffer;


    /* Protótipos de funções dos respectivos itens de cada menu! */
    /* Menu Arquivo */
    static void abrir_arquivo (GtkWidget *widget, Janela_Buffer *dado);
    static void salvar_arquivo (GtkWidget *widget);
    static void sair_app ();
    static void imprimir ();
    /* Menu Editar*/
    void copiar();
    void colar ();
    static void desfazer(GtkWidget *widget, Janela_Buffer *dado);
    static void refazer (GtkWidget *widget, Janela_Buffer *dado);
    static void mudarFonte(GtkWidget *widget, Janela_Buffer *dado);
    static void mudarCor (GtkWidget *widget, Janela_Buffer *dado);
    static void uppercase (GtkWidget *widget, Janela_Buffer *dado);
    static void lowcase (GtkWidget *widget, Janela_Buffer *dado);

    /* Menu Busca */
    void procurarProximo(GtkWidget *widget, GtkTextBuffer *buffer_text);
    void procurarAnterior(GtkWidget *widget, GtkTextBuffer *buffer_text);
    void procurarPalavra(GtkWidget *widget, GtkTextBuffer *buffer_text);

    /* Menu Ajuda */
    static void exibirSobre(GtkWidget *widget, Janela_Buffer *dado);

#endif /* Fim da verificação :-) */
