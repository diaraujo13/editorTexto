/*  
    main.c

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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "main.h"

int main (int argc, char *argv[]){
                /* g_slice_new aloca uma quantidade dinâmica de memória que será utilizada pela struct */
        Janela_Buffer *w = g_slice_new(Janela_Buffer);

        GtkWidget *barra_menu;

    /*-------- ITENS DO MENU ---------------------*/
        GtkWidget *arquivo, *editar, *busca, *ajuda, *inserir, *mm_item;
    /*--------  UM SUBMENU QUE É ANEXADO A CADA ITEM DE MENU-------------*/
        GtkWidget *arquivo_sub, *editar_sub, *busca_sub, *ajuda_sub, *inserir_sub, *mm_sub;
    /*---------  ITENS QUE SERÃO ANEXADO AO SUBMENU CRIADO PARA O RESPECTIVO ITEM DE MENU DA BARRA DE MENU---------*/
        GtkWidget *novo, *abrir, *salvar, *salvar_como, *inserir_final, *inserir_comeco, *inserir_cursor, *sair;
        GtkWidget *desfazer,*avancar, *cortar, *copiar, *colar, *selecionar, *fonte, *cor, *maiuscula, *minuscula;
        GtkWidget *procurar, *substituir;
        GtkWidget *sobre, *doc;
    /*--------- SEPARADOR HORIZONTAL DOS MENU ITEM ------------*/
        GtkWidget *sep, *sep2;
    /* ---------- CRIAÇÃO DA BARRA DE FERRAMENTAS E SEUS ITENS ------*/
        GtkWidget *barra_ferramenta;
        GtkToolItem *novo_ferramenta,
                    *abrir_ferramenta,
                    *salvar_ferramenta,
                    *inserir_ferramenta,
                    *separador_ferramenta,
                    *copiar_ferramenta,
                    *recortar_ferramenta,
                    *colar_ferramenta;

    /*--------- CRIAÇÃO DOS 'ACCELERATORS GROUP' PARA CADA ITEM DO MENU ---------*/
        GtkAccelGroup *grupo_atalho;
    /*--------- LAYOUT ---------------*/
        GtkWidget *vertical_layout;
        GtkWidget *barra_rolagem;
    /*--------- TEXT VIEW --------------*/
        GtkWidget *field_text;


    /*--------- VARIAVEIS DE CONTROLE ---*/
        char *url_arquivo=NULL;



        gtk_init(&argc, &argv);

        w -> janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW (w->janela), "Novo documento");
        gtk_window_maximize(GTK_WINDOW (w->janela));

        /*
            88b           d88 88888888888 888b      88 88        88 88888888ba        db        88888888ba
            888b         d888 88          8888b     88 88        88 88      "8b      d88b       88      "8b
            88`8b       d8'88 88          88 `8b    88 88        88 88      ,8P     d8'`8b      88      ,8P
            88 `8b     d8' 88 88aaaaa     88  `8b   88 88        88 88aaaaaa8P'    d8'  `8b     88aaaaaa8P'
            88  `8b   d8'  88 88"""""     88   `8b  88 88        88 88""""""8b,   d8YaaaaY8b    88""""88'
            88   `8b d8'   88 88          88    `8b 88 88        88 88      `8b  d8""""""""8b   88    `8b
            88    `888'    88 88          88     `8888 Y8a.    .a8P 88      a8P d8'        `8b  88     `8b
            88     `8'     88 88888888888 88      `888  `"Y8888Y"'  88888888P" d8'          `8b 88      `8b

        */

        /* Criação da barra de menu. */
        barra_menu = gtk_menu_bar_new();
        /* Criação de um grupo de atalhos. Ele identifica os atalhos já padrões */
        grupo_atalho = gtk_accel_group_new();

        arquivo = gtk_menu_item_new_with_mnemonic ("_Arquivo");
        editar =  gtk_menu_item_new_with_mnemonic ("_Editar");
        busca =   gtk_menu_item_new_with_mnemonic ("_Buscar");
        ajuda =   gtk_menu_item_new_with_mnemonic ("A_juda");

        gtk_menu_shell_append(GTK_MENU_SHELL(barra_menu), arquivo);
        gtk_menu_shell_append(GTK_MENU_SHELL(barra_menu), editar);
        gtk_menu_shell_append(GTK_MENU_SHELL(barra_menu), busca);
        gtk_menu_shell_append(GTK_MENU_SHELL(barra_menu), ajuda);

        arquivo_sub = gtk_menu_new();
        editar_sub  = gtk_menu_new();
        busca_sub   = gtk_menu_new();
        ajuda_sub   = gtk_menu_new();

        gtk_menu_item_set_submenu(GTK_MENU_ITEM(arquivo), arquivo_sub);
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(editar), editar_sub);
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(busca), busca_sub);
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(ajuda), ajuda_sub);
        /*


                    ,adPPYYba, 8b,dPPYba,  ,adPPYb,d8 88       88 88 8b       d8  ,adPPYba,
                    ""     `Y8 88P'   "Y8 a8"    `Y88 88       88 88 `8b     d8' a8"     "8a
                    ,adPPPPP88 88         8b       88 88       88 88  `8b   d8'  8b       d8
                    88,    ,88 88         "8a    ,d88 "8a,   ,a88 88   `8b,d8'   "8a,   ,a8"
                    `"8bbdP"Y8 88          `"YbbdP'88  `"YbbdP'Y8 88     "8"      `"YbbdP"'
                                                   88
                                                   88
        */
        //CRIAÇÃO DOS MENU ITENS DENTRO DO SUBMENU DOS ITENS DE MENU DA BARRA DE MENU
        //DEPOIS "ANEXA-OS" AO 'MENU', JÁ QUE ESSE É UM FILHO DE MENU_SHELL

        novo = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW, grupo_atalho);
        abrir = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, grupo_atalho);
        salvar = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE, grupo_atalho);
        salvar_como = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS, grupo_atalho);
        inserir = gtk_menu_item_new_with_label("Inserir texto");
        sep = gtk_separator_menu_item_new();
        sair =  gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, grupo_atalho);

        //Quando o item de menu for clicado, uma função será chamada.
        //Esse tipo de função é conhecida como <callback>
        g_signal_connect(G_OBJECT(abrir), "activate", G_CALLBACK(abrir_arquivo), (gpointer) w);

        //Criação de um item de menu especial, que possuirá um menu embutido dentro dele.
        //Dessa maneira, aparecerá uma seta indicando que o item de menu possui um menu.
        inserir_sub = gtk_menu_new();
        inserir_final = gtk_menu_item_new_with_label("Ao final");
        inserir_comeco = gtk_menu_item_new_with_label("Ao inicio");
        inserir_cursor = gtk_menu_item_new_with_label ("Ao cursor");
        gtk_menu_shell_append (GTK_MENU_SHELL(inserir_sub), inserir_comeco);
        gtk_menu_shell_append (GTK_MENU_SHELL(inserir_sub), inserir_final);
        gtk_menu_shell_append (GTK_MENU_SHELL(inserir_sub), inserir_cursor);
        gtk_menu_item_set_submenu (GTK_MENU_ITEM(inserir), inserir_sub);

        //Anexação dos itens de menu no nosso submenu "Arquivo"
        // Barra de menu -> Menu Item -> SubMenu -> Menu Item
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), novo);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), abrir);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), salvar);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), salvar_como);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), inserir);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), sep);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), sair);

        /*
                                    88 88
                                    88 ""   ,d
                                    88      88
                 ,adPPYba,  ,adPPYb,88 88 MM88MMM ,adPPYYba, 8b,dPPYba,
                a8P_____88 a8"    `Y88 88   88    ""     `Y8 88P'   "Y8
                8PP""""""" 8b       88 88   88    ,adPPPPP88 88
                "8b,   ,aa "8a,   ,d88 88   88,   88,    ,88 88
                 `"Ybbd8"'  `"8bbdP"Y8 88   "Y888 `"8bbdP"Y8 88


        */

        //Instanciando dos Itens de Menu para o submenu do Item de Menu "Editar";
        //Para se anexar Itens de Menu é necessário ter um Menu ou uma derivada;
        sep2        =   gtk_separator_menu_item_new();
        desfazer    =   gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDO, grupo_atalho);
        avancar     =   gtk_image_menu_item_new_from_stock(GTK_STOCK_REDO, grupo_atalho);
        copiar      =   gtk_image_menu_item_new_from_stock (GTK_STOCK_COPY, grupo_atalho);
        cortar      =   gtk_image_menu_item_new_from_stock (GTK_STOCK_CUT, grupo_atalho);
        colar       =   gtk_image_menu_item_new_from_stock (GTK_STOCK_PASTE, grupo_atalho);
        fonte       =   gtk_image_menu_item_new_from_stock(GTK_STOCK_SELECT_FONT, grupo_atalho);
        cor         =   gtk_image_menu_item_new_from_stock (GTK_STOCK_SELECT_COLOR, grupo_atalho);

        // Criação de um submenu em um item de menu
        mm_item     =   gtk_menu_item_new_with_label ("Caixa Alta/Baixa");
        mm_sub = gtk_menu_new();
        maiuscula = gtk_menu_item_new_with_label ("Caixa Alta");
        minuscula = gtk_menu_item_new_with_label ("Caixa Baixa");
        gtk_menu_shell_append(GTK_MENU_SHELL(mm_sub), maiuscula);
        gtk_menu_shell_append(GTK_MENU_SHELL(mm_sub), minuscula);
        gtk_menu_item_set_submenu (GTK_MENU_ITEM(mm_item), mm_sub);

        //Adiciona os Itens de Menu no Submenu
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), desfazer);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), avancar);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), copiar);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), cortar);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), colar);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), sep2);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), fonte);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), cor);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), mm_item);


        /*

                88
                88
                88
                88,dPPYba,  88       88 ,adPPYba,  ,adPPYba, ,adPPYYba,
                88P'    "8a 88       88 I8[    "" a8"     "" ""     `Y8
                88       d8 88       88  `"Y8ba,  8b         ,adPPPPP88
                88b,   ,a8" "8a,   ,a88 aa    ]8I "8a,   ,aa 88,    ,88
                8Y"Ybbd8"'   `"YbbdP'Y8 `"YbbdP"'  `"Ybbd8"' `"8bbdP"Y8

        */
        //Instanciação dos Itens de Menu do Submenu do Item de Menu "Busca"
        procurar = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND, grupo_atalho);
        substituir = gtk_image_menu_item_new_from_stock(GTK_STOCK_FIND_AND_REPLACE, grupo_atalho);

        gtk_menu_shell_append(GTK_MENU_SHELL(busca_sub), procurar);
        gtk_menu_shell_append(GTK_MENU_SHELL(busca_sub), substituir);
    /*


                           88                      88
                           ""                      88
                                                   88
                ,adPPYYba, 88 88       88  ,adPPYb,88 ,adPPYYba,
                ""     `Y8 88 88       88 a8"    `Y88 ""     `Y8
                ,adPPPPP88 88 88       88 8b       88 ,adPPPPP88
                88,    ,88 88 "8a,   ,a88 "8a,   ,d88 88,    ,88
                `"8bbdP"Y8 88  `"YbbdP'Y8  `"8bbdP"Y8 `"8bbdP"Y8
                          ,88
                        888P"

    */
        //Instanciação dos Itens de Menu do Submenu do Item de Menu "Ajuda"
        sobre = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, grupo_atalho);
        doc = gtk_image_menu_item_new_from_stock(GTK_STOCK_HELP, grupo_atalho);

//        g_signal_connect(G_OBJECT(sobre))

        gtk_menu_shell_append(GTK_MENU_SHELL(ajuda_sub), sobre);
        gtk_menu_shell_append(GTK_MENU_SHELL(ajuda_sub), doc);


    /*
        888888888888 ,ad8888ba,     ,ad8888ba,   88          88888888ba        db        88888888ba
             88     d8"'    `"8b   d8"'    `"8b  88          88      "8b      d88b       88      "8b
             88    d8'        `8b d8'        `8b 88          88      ,8P     d8'`8b      88      ,8P
             88    88          88 88          88 88          88aaaaaa8P'    d8'  `8b     88aaaaaa8P'
             88    88          88 88          88 88          88""""""8b,   d8YaaaaY8b    88""""88'
             88    Y8,        ,8P Y8,        ,8P 88          88      `8b  d8""""""""8b   88    `8b
             88     Y8a.    .a8P   Y8a.    .a8P  88          88      a8P d8'        `8b  88     `8b
             88      `"Y8888Y"'     `"Y8888Y"'   88888888888 88888888P" d8'          `8b 88      `8b
    */


 	barra_ferramenta = gtk_toolbar_new ();

    //CRIA CADA BOTÃO DA BARRA DE FERRAMENTA COM UM RESPECTIVO ICONE (STOCK)
    novo_ferramenta     =   gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
    abrir_ferramenta    =   gtk_tool_button_new_from_stock (GTK_STOCK_OPEN);
    salvar_ferramenta   =   gtk_tool_button_new_from_stock (GTK_STOCK_SAVE);
    inserir_ferramenta  =   gtk_tool_button_new_from_stock (GTK_STOCK_EDIT);
    copiar_ferramenta   =   gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
    recortar_ferramenta =   gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
    colar_ferramenta    =   gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	separador_ferramenta= gtk_separator_tool_item_new();

	g_signal_connect(G_OBJECT(abrir_ferramenta), "clicked", G_CALLBACK(abrir_arquivo), (gpointer) w);
    //SE NÃO FOR POSSÍVEL EXIBIR TODOS OS ÍCONES NA BARRA DE TAREFAS
    //UMA SETA SERÁ MOSTRADO NO FINAL
    gtk_toolbar_set_show_arrow(GTK_TOOLBAR(barra_ferramenta), TRUE);

    gtk_toolbar_set_style(GTK_TOOLBAR(barra_ferramenta), GTK_TOOLBAR_ICONS);

    //ADICIONA ESSES BOTÕES NA BARRA DE FERRAMENTAS
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), novo_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), abrir_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), salvar_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), inserir_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), separador_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), copiar_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), recortar_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), colar_ferramenta, -1);

    //ADICIONA EVENTOS
	//g_signal_connect(G_OBJECT(novo_ferramenta), "clicked", G_CALLBACK(abrir_novo), )

    /*-----------------------------------------------------------------------------------------------------------------*/
    /*--------------------------------------------------------------------------------------------------------------*/
    /*------------ TEXTVIEW & TEXTBUFFER -------------------------------------------------------------------------*/


        field_text = gtk_text_view_new();

        barra_rolagem = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(barra_rolagem), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

        gtk_container_add (GTK_CONTAINER(barra_rolagem), field_text);
        // Instanciando um GtkTextBuffer para manipularo  texto presente no GtkWidget *field_text;
        w -> buffer_text = gtk_text_view_get_buffer(GTK_TEXT_VIEW(field_text));


    /*--------------------------------------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------------------------------*/
    /*----------- ORGANIZAÇÃO DOS ITENS NA VERTICAL BOX LAYOUT E ANEXANDO-O AO CONTAINER PRINCIPAL -----------------*/

    vertical_layout = gtk_vbox_new(FALSE, 0);

    gtk_box_pack_start(GTK_BOX(vertical_layout), barra_menu, FALSE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vertical_layout), barra_ferramenta, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vertical_layout), barra_rolagem, TRUE , TRUE, 0);

    gtk_container_add(GTK_CONTAINER(w->janela), vertical_layout);
    g_signal_connect(G_OBJECT(w->janela), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(w->janela);

    gtk_main();

    return 0;
}


/*---------------------------------------------------------------------------------------------------------------*/

static void abrir_arquivo (GtkWidget *widget, Janela_Buffer *dado){

    GtkWidget *abrir_dialogo;
    abrir_dialogo = gtk_file_chooser_dialog_new("Abrir arquivo", GTK_WINDOW(dado->janela), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancelar", GTK_RESPONSE_CANCEL, "Abrir", GTK_RESPONSE_ACCEPT,  NULL );

    if (gtk_dialog_run (GTK_DIALOG(abrir_dialogo)) == GTK_RESPONSE_ACCEPT ){
        int i, j = 0, k, contador = 0;
        char *file_path, *tmp, *file_name;
        file_path = gtk_file_chooser_get_filename_utf8(GTK_FILE_CHOOSER(abrir_dialogo));


        for (i = 0; i <= strlen(file_path); i++){
        if (file_path[i] == '.'){
                    int b = i-1;
                    for (j = b; j >= 0; j--){
                        if (file_path[j] != '\\'){
                            file_name [b-j] = file_path [j];
                            contador++;
                            continue;
                        }else
                            break;


                    }

                }
        }



        //for (k = strlen(file_name); k >= 0; k--)
//          //  tmp[strlen(file_name)-k] = file_name[k];
//        int w = 0;
//        int b = (int) strlen(file_name);
//        while (file_name[w]!='\0'){
//            tmp[w] = file_name[b-w];
//            w++;
//
//        }

		gtk_text_buffer_set_text(GTK_TEXT_BUFFER(dado->buffer_text), file_name,-1);
        gtk_window_set_title(GTK_WINDOW(dado->janela), file_name);
     //  mudarTexto(file_path);
    }

    gtk_widget_destroy(abrir_dialogo);
}
