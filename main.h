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
