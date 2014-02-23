/*
    main.h

    Copyright (C) 2014 Izaias Araújo <izaiasousa@gmail.com>

    Este arquivo é parte do programa e-Text

    e-Text é um software livre; você pode redistribuí-lo e/ou
    modificá-lo dentro dos termos da Licença Pública Geral GNU como
    publicada pela Fundação do Software Livre (FSF); na versão 2 da
    Licença, ou (na sua opinião) qualquer versão.

    Este programa é distribuído na esperança de que possa ser  útil,
    mas SEM NENHUMA GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer
    MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

    Você deve ter recebido uma cópia da Licença Pública Geral GNU
    junto com este programa, se não, escreva para a Fundação do Software
    Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef MAIN_H_INCLUDED /* Código só será importado se ele não estiver definido */
#define MAIN_H_INCLUDED /* Caso não esteja definido, então "define" */

    typedef struct {

        GtkWidget           *janela;
        GtkTextBuffer       *buffer_text;
        GtkWidget           *text_view;
        char                *filename;
        char                *texto;
    } Janela_Buffer;



/* Protótipos de funções dos respectivos itens de cada menu! */
/* Operação com Arquivos */

    void tst (GtkWidget *widget, Janela_Buffer *dado);

    void tsta (GtkWidget *widget, Janela_Buffer *dado);
    gboolean buffer_modificado (Janela_Buffer *w);
    void defina_buffer_salvo (Janela_Buffer *w, char *caminho_arquivo);
    void defina_buffer_modificado (GtkWidget *widget, Janela_Buffer *w);
    gboolean possui_filename (Janela_Buffer *w);
    gboolean caixa_confirmacao (Janela_Buffer *w);
    void salvar (char* nome_arquivo, char* conteudo, Janela_Buffer *w);
    void salvar_arquivo (GtkWidget *widget, Janela_Buffer *dado);
    void dialogo_salvar(Janela_Buffer *dado, char* texto);

    void on_window_delete_event (GtkWidget *widget, Janela_Buffer *dado);

    void criar_arquivo (GtkWidget *widget, Janela_Buffer *dado);
    void abrir_arquivo (GtkWidget *widget, Janela_Buffer *dado);


    void inserir_no_comeco ( GtkWidget *widget, Janela_Buffer *dado);
    void inserir_no_final ( GtkWidget *widget, Janela_Buffer *dado);
    void inserir_no_cursor ( GtkWidget *widget, Janela_Buffer *dado);



 /* Menu Editar */
    void copiar(GtkWidget *widget, Janela_Buffer *dado);
    void colar (GtkWidget *widget, Janela_Buffer *dado);
    static void desfazer(GtkWidget *widget, Janela_Buffer *dado);
    static void refazer (GtkWidget *widget, Janela_Buffer *dado);

    void mudar_fonte( GtkWidget *widget, Janela_Buffer *dado);
    static void uppercase (GtkWidget *widget, Janela_Buffer *dado);
    static void lowcase (GtkWidget *widget, Janela_Buffer *dado);

 /* Menu Busca */
    void procurarProximo(GtkWidget *widget, GtkTextBuffer *buffer_text);
    void procurarAnterior(GtkWidget *widget, GtkTextBuffer *buffer_text);
    void procurarPalavra(GtkWidget *widget, GtkTextBuffer *buffer_text);

/* Menu Ajuda */
    void exibirSobre(GtkWidget *widget);
    void exibirAjuda(GtkWidget *widget);

/* Miscelânea */
    void mostrar_erro (GtkWidget *widget, GError *erro);

/*
    Cores utilizadas.
    Cada nível de cor RGB é definida através de sua intensidade, que varia de 0 a 65535.
*/

    GdkColor branco;
    GdkColor cinza_claro;

#endif /* Fim da verificação :-) */
