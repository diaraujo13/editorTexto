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
        w->filename = NULL;
        w->texto = NULL;

        GtkWidget *barra_menu;

    /*-------- ITENS DO MENU ---------------------*/
        GtkWidget *arquivo, *editar, *busca, *ajuda, *inserir, *mm_item;
    /*--------  UM SUBMENU QUE É ANEXADO A CADA ITEM DE MENU-------------*/
        GtkWidget *arquivo_sub, *editar_sub, *busca_sub, *ajuda_sub, *inserir_sub, *mm_sub;
    /*---------  ITENS QUE SERÃO ANEXADO AO SUBMENU CRIADO PARA O RESPECTIVO ITEM DE MENU DA BARRA DE MENU---------*/
        GtkWidget *novo, *abrir, *salvar, *salvar_como, *inserir_final, *inserir_comeco, *inserir_cursor, *sair;
        GtkWidget *desfazer,*avancar, *cortar, *copiar, *colar,  *fonte, *maiuscula, *minuscula;
        GtkWidget *procurar, *substituir;
        GtkWidget *sobre, *doc;
    /*--------- SEPARADOR HORIZONTAL DOS MENU ITEM ------------*/
        GtkWidget *sep, *sep2;
    /* ---------- CRIAÇÃO DA BARRA DE FERRAMENTAS E SEUS ITENS ------*/
        GtkWidget *barra_ferramenta;
        GtkToolItem *novo_ferramenta,*abrir_ferramenta,
                    *salvar_ferramenta,
                    *inserir_ferramenta,
                    *separador_ferramenta,
                    *copiar_ferramenta,
                    *recortar_ferramenta,
                    *colar_ferramenta;

        GtkAccelGroup *grupo_atalho;
        GtkWidget *vertical_layout;
        GtkWidget *barra_rolagem;

        gtk_init(&argc, &argv);

        w -> janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW (w->janela), "Novo documento");
        gtk_window_maximize(GTK_WINDOW (w->janela));




/*


        `7MMM.     ,MMF'`7MM"""YMM  `7MN.   `7MF'`7MMF'   `7MF'`7MM"""Yp,      db      `7MM"""Mq.
          MMMb    dPMM    MM    `7    MMN.    M    MM       M    MM    Yb     ;MM:       MM   `MM.
          M YM   ,M MM    MM   d      M YMb   M    MM       M    MM    dP    ,V^MM.      MM   ,M9
          M  Mb  M' MM    MMmmMM      M  `MN. M    MM       M    MM"""bg.   ,M  `MM      MMmmdM9
          M  YM.P'  MM    MM   Y  ,   M   `MM.M    MM       M    MM    `Y   AbmmmqMA     MM  YM.
          M  `YM'   MM    MM     ,M   M     YMM    YM.     ,M    MM    ,9  A'     VML    MM   `Mb.
        .JML. `'  .JMML..JMMmmmmMMM .JML.    YM     `bmmmmd"'  .JMMmmmd9 .AMA.   .AMMA..JMML. .JMM.


*/

        /* Criação da barra de menu. */
        barra_menu = gtk_menu_bar_new();
        /* Criação de um grupo de atalhos. Ele identifica os atalhos já padrões */
        grupo_atalho = gtk_accel_group_new();
        /* Adiciona esse grupo de atalhos na janela principal. */
        gtk_window_add_accel_group(GTK_WINDOW(w->janela), grupo_atalho);

        /* Cada item de menu que será exibido na barra de menu.
           Criado com um mnemonic, teclado de atalho para abrir o menu
           e acessado através de ALT+ <tecla que procede o underline> */
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

        novo = gtk_image_menu_item_new_from_stock (GTK_STOCK_NEW, grupo_atalho);
        abrir = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, grupo_atalho);
        salvar = gtk_image_menu_item_new_from_stock (GTK_STOCK_SAVE, grupo_atalho);
        salvar_como = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS, grupo_atalho);
        inserir = gtk_menu_item_new_with_label("Inserir texto");
        sep = gtk_separator_menu_item_new();
        sair =  gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, grupo_atalho);

        /*
        Quando o item de menu for clicado, uma função será chamada.
        Esse tipo de função é conhecida como <callback>
        */
        g_signal_connect(G_OBJECT(novo), "activate", G_CALLBACK(criar_arquivo), (gpointer) w);
        g_signal_connect(G_OBJECT(abrir), "activate", G_CALLBACK(abrir_arquivo), (gpointer) w);
        g_signal_connect(G_OBJECT(salvar), "activate", G_CALLBACK(salvar_arquivo), (gpointer) w);
        g_signal_connect(G_OBJECT(sair), "activate", G_CALLBACK(on_window_delete_event), (gpointer) w);

        /*
        Criação de um item de menu especial, que possuirá um menu embutido dentro dele.
        Dessa maneira, aparecerá uma seta indicando que o item de menu possui um menu.
        */
        inserir_sub = gtk_menu_new();

        inserir_final = gtk_menu_item_new_with_label("Ao final");
        inserir_comeco = gtk_menu_item_new_with_label("Ao inicio");
        inserir_cursor = gtk_menu_item_new_with_label ("Ao cursor");

        gtk_menu_shell_append (GTK_MENU_SHELL(inserir_sub), inserir_comeco);
        gtk_menu_shell_append (GTK_MENU_SHELL(inserir_sub), inserir_final);
        gtk_menu_shell_append (GTK_MENU_SHELL(inserir_sub), inserir_cursor);
        gtk_menu_item_set_submenu (GTK_MENU_ITEM(inserir), inserir_sub);



        /*Anexação dos itens de menu no nosso submenu "Arquivo"
         Barra de menu -> Menu Item -> SubMenu -> Menu Item
        */
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), novo);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), abrir);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), salvar);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), salvar_como);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), inserir);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), sep);
        gtk_menu_shell_append(GTK_MENU_SHELL(arquivo_sub), sair);

        g_signal_connect(G_OBJECT(inserir_comeco), "activate", G_CALLBACK(inserir_no_comeco), (gpointer) w);
        g_signal_connect(G_OBJECT(inserir_final), "activate", G_CALLBACK(inserir_no_final), (gpointer) w);
        g_signal_connect(G_OBJECT(inserir_cursor), "activate", G_CALLBACK(inserir_no_cursor), (gpointer) w);

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

        /*
        Instanciando dos Itens de Menu para o submenu do Item de Menu "Editar";
        Para se anexar Itens de Menu é necessário ter um Menu ou uma derivada;
        */
        sep2        =   gtk_separator_menu_item_new();
        desfazer    =   gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDO, grupo_atalho);
        avancar     =   gtk_image_menu_item_new_from_stock(GTK_STOCK_REDO, grupo_atalho);
        copiar      =   gtk_image_menu_item_new_from_stock (GTK_STOCK_COPY, grupo_atalho);
        cortar      =   gtk_image_menu_item_new_from_stock (GTK_STOCK_CUT, grupo_atalho);
        colar       =   gtk_image_menu_item_new_from_stock (GTK_STOCK_PASTE, grupo_atalho);
        fonte       =   gtk_image_menu_item_new_from_stock(GTK_STOCK_SELECT_FONT, grupo_atalho);

        /* Anexo cada item para cada função quando receberem um evento de <active> */
        g_signal_connect(G_OBJECT(fonte), "active", G_CALLBACK(mudar_fonte), (gpointer) w);

         /* Criação de um submenu em um item de menu /*/
        mm_item     =   gtk_menu_item_new_with_label ("Caixa Alta/Baixa");
        mm_sub = gtk_menu_new();
        maiuscula = gtk_menu_item_new_with_label ("Caixa Alta");
        minuscula = gtk_menu_item_new_with_label ("Caixa Baixa");
        gtk_menu_shell_append(GTK_MENU_SHELL(mm_sub), maiuscula);
        gtk_menu_shell_append(GTK_MENU_SHELL(mm_sub), minuscula);
        gtk_menu_item_set_submenu (GTK_MENU_ITEM(mm_item), mm_sub);

        /*/Adiciona os Itens de Menu no Submenu/*/
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), desfazer);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), avancar);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), copiar);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), cortar);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), colar);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), sep2);
        gtk_menu_shell_append(GTK_MENU_SHELL(editar_sub), fonte);
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
        /*/Instanciação dos Itens de Menu do Submenu do Item de Menu "Busca"/*/
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
        /*/Instanciação dos Itens de Menu do Submenu do Item de Menu "Ajuda"/*/
        sobre = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, grupo_atalho);
        doc = gtk_image_menu_item_new_from_stock(GTK_STOCK_HELP, grupo_atalho);

        g_signal_connect(G_OBJECT(sobre), "activate", G_CALLBACK(exibirSobre), NULL);

        gtk_menu_shell_append(GTK_MENU_SHELL(ajuda_sub), sobre);
        gtk_menu_shell_append(GTK_MENU_SHELL(ajuda_sub), doc);


/*


        MMP""MM""YMM   .g8""8q.     .g8""8q. `7MMF'      `7MM"""Yp,      db      `7MM"""Mq.
        P'   MM   `7 .dP'    `YM. .dP'    `YM. MM          MM    Yb     ;MM:       MM   `MM.
             MM      dM'      `MM dM'      `MM MM          MM    dP    ,V^MM.      MM   ,M9
             MM      MM        MM MM        MM MM          MM"""bg.   ,M  `MM      MMmmdM9
             MM      MM.      ,MP MM.      ,MP MM      ,   MM    `Y   AbmmmqMA     MM  YM.
             MM      `Mb.    ,dP' `Mb.    ,dP' MM     ,M   MM    ,9  A'     VML    MM   `Mb.
           .JMML.      `"bmmd"'     `"bmmd"' .JMMmmmmMMM .JMMmmmd9 .AMA.   .AMMA..JMML. .JMM.

*/


 	barra_ferramenta = gtk_toolbar_new ();

    /*/CRIA CADA BOTÃO DA BARRA DE FERRAMENTA COM UM RESPECTIVO ICONE (STOCK)/*/
    novo_ferramenta     =   gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
    abrir_ferramenta    =   gtk_tool_button_new_from_stock (GTK_STOCK_OPEN);
    salvar_ferramenta   =   gtk_tool_button_new_from_stock (GTK_STOCK_SAVE);
    inserir_ferramenta  =   gtk_tool_button_new_from_stock (GTK_STOCK_EDIT);
    copiar_ferramenta   =   gtk_tool_button_new_from_stock (GTK_STOCK_COPY);
    recortar_ferramenta =   gtk_tool_button_new_from_stock (GTK_STOCK_CUT);
    colar_ferramenta    =   gtk_tool_button_new_from_stock (GTK_STOCK_PASTE);
	separador_ferramenta= gtk_separator_tool_item_new();

    g_signal_connect(G_OBJECT(novo_ferramenta), "clicked", G_CALLBACK(criar_arquivo), (gpointer) w);
	g_signal_connect(G_OBJECT(abrir_ferramenta), "clicked", G_CALLBACK(abrir_arquivo), (gpointer) w);
    g_signal_connect(G_OBJECT(salvar_ferramenta), "clicked", G_CALLBACK(salvar_arquivo), (gpointer) w);
    g_signal_connect(G_OBJECT(inserir_ferramenta), "clicked", G_CALLBACK(tst), (gpointer) w);
    g_signal_connect(G_OBJECT(copiar_ferramenta), "clicked", G_CALLBACK(tsta), (gpointer) w);


    /*/SE NÃO FOR POSSÍVEL EXIBIR TODOS OS ÍCONES NA BARRA DE TAREFAS
    //UMA SETA SERÁ MOSTRADO NO FINAL/*/
    gtk_toolbar_set_show_arrow(GTK_TOOLBAR(barra_ferramenta), TRUE);

    gtk_toolbar_set_style(GTK_TOOLBAR(barra_ferramenta), GTK_TOOLBAR_ICONS);

    /* Adiciona cada botão já configurado, na barra de ferramentas.
       Segue a ordem de inserção. s*/
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), novo_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), abrir_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), salvar_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), inserir_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), separador_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), copiar_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), recortar_ferramenta, -1);
    gtk_toolbar_insert (GTK_TOOLBAR(barra_ferramenta), colar_ferramenta, -1);



/*
        MMP""MM""YMM `7MM"""YMM  `YMM'   `MP'MMP""MM""YMM     `7MMF'   `7MF'`7MMF'`7MM"""YMM `7MMF'     A     `7MF'
        P'   MM   `7   MM    `7    VMb.  ,P  P'   MM   `7       `MA     ,V    MM    MM    `7   `MA     ,MA     ,V
             MM        MM   d       `MM.M'        MM             VM:   ,V     MM    MM   d      VM:   ,VVM:   ,V
             MM        MMmmMM         MMb         MM              MM.  M'     MM    MMmmMM       MM.  M' MM.  M'
             MM        MM   Y  ,    ,M'`Mb.       MM              `MM A'      MM    MM   Y  ,    `MM A'  `MM A'
             MM        MM     ,M   ,P   `MM.      MM               :MM;       MM    MM     ,M     :MM;    :MM;
           .JMML.    .JMMmmmmMMM .MM:.  .:MMa.  .JMML.              VF      .JMML..JMMmmmmMMM      VF      VF
*/

        /* Criação do TextView */
        w->text_view= gtk_text_view_new();
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(w->text_view), GTK_WRAP_WORD);

        barra_rolagem = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(barra_rolagem), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
        gtk_container_add (GTK_CONTAINER(barra_rolagem), w->text_view);

        /* Instanciando um GtkTextBuffer para manipular o  texto presente no GtkWidget *field_text; */
        w -> buffer_text = gtk_text_view_get_buffer(GTK_TEXT_VIEW(w->text_view));
        g_signal_connect(G_OBJECT(w->buffer_text), "changed", G_CALLBACK(defina_buffer_modificado), (gpointer) w);

/*

            `7MMF'            db   `YMM'   `MM' .g8""8q. `7MMF'   `7MF'MMP""MM""YMM
              MM             ;MM:    VMA   ,V .dP'    `YM. MM       M  P'   MM   `7
              MM            ,V^MM.    VMA ,V  dM'      `MM MM       M       MM
              MM           ,M  `MM     VMMP   MM        MM MM       M       MM
              MM      ,    AbmmmqMA     MM    MM.      ,MP MM       M       MM
              MM     ,M   A'     VML    MM    `Mb.    ,dP' YM.     ,M       MM
            .JMMmmmmMMM .AMA.   .AMMA..JMML.    `"bmmd"'    `bmmmmd"'     .JMML.

*/

    vertical_layout = gtk_vbox_new(FALSE, 0);



    branco.red = 16448;
    branco.green = 16448;
    branco.blue = 16448;

    cinza_claro.red = 20000;
    cinza_claro.green = 20000;
    cinza_claro.blue =20000;



    gtk_widget_modify_bg (barra_menu, GTK_STATE_NORMAL, &branco);
    gtk_widget_modify_bg (barra_ferramenta, GTK_STATE_NORMAL, &cinza_claro );
    gtk_widget_modify_bg (w->janela, GTK_STATE_NORMAL, &cinza_claro );

    gtk_box_pack_start(GTK_BOX(vertical_layout), barra_menu, FALSE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vertical_layout), barra_ferramenta, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vertical_layout), barra_rolagem, TRUE , TRUE, 0);

    gtk_container_add(GTK_CONTAINER(w->janela), vertical_layout);

    /* Antes da janela ser destruída, há uma verificação sobre o arquivo, se ele está salvo ou não.*/
    g_signal_connect(G_OBJECT(w->janela), "delete-event", G_CALLBACK(on_window_delete_event), (gpointer) w);

    gtk_widget_show_all(w->janela);

    gtk_main();

    return EXIT_SUCCESS;
}

/*
                                                    ,og.  ,
                                                           "  `6o"
        `7MM"""YMM `7MMF'   `7MF'`7MN.   `7MF' .g8"""bgd   .g8""8q. `7MM"""YMM   .M"""bgd
          MM    `7   MM       M    MMN.    M .dP'     `M .dP'    `YM. MM    `7  ,MI    "Y
          MM   d     MM       M    M YMb   M dM'       ` dM'      `MM MM   d    `MMb.
          MM""MM     MM       M    M  `MN. M MM          MM        MM MMmmMM      `YMMNq.
          MM   Y     MM       M    M   `MM.M MM.         MM.      ,MP MM   Y  , .     `MM
          MM         YM.     ,M    M     YMM `Mb.     ,' `Mb.    ,dP' MM     ,M Mb     dM
        .JMML.        `bmmmmd"'  .JML.    YM   `"bmmmd'    `"bmmd"' .JMMmmmmMMM P"Ybmmd"
                                                  bog
                                                   od
*/


/* Chamada para criar um novo arquivo. Checa, primeiramente, se há algum arquivo aberto */
void criar_arquivo (GtkWidget *widget, Janela_Buffer *dado){


    if (gtk_text_buffer_get_modified(dado->buffer_text)==TRUE){
      if (caixa_confirmacao(dado)){
          salvar_arquivo(widget, dado);
      }
    }


    GtkTextIter inicio;
    GtkTextIter final;

    gtk_text_buffer_get_start_iter (dado->buffer_text, &inicio);
    gtk_text_buffer_get_end_iter (dado->buffer_text, &final);

    gtk_text_buffer_delete (dado->buffer_text, &inicio, &final);

    /*dado->buffer_text = gtk_text_view_get_buffer(GTK_TEXT_VIEW(dado->text_view));
    */

    gtk_text_buffer_set_text(dado->buffer_text, "", -1);
    defina_buffer_modificado(widget, dado);

    g_free(dado->texto);
    g_free(dado->filename);

    dado->texto = NULL;
    dado->filename = NULL;

}

/* Chamada para abrir um arquivo que o usuário selecionará
pela caixa de dialógo (GtkFileChooserDialog) e então
carregá-lo no buffer do TextView. */

void abrir_arquivo (GtkWidget *widget, Janela_Buffer *dado){

    GtkWidget   *abrir_dialogo;
    gchar       *texto_arquivo;
    /* Verificar se o arquivo foi aberto com sucesso! */
    gboolean resultado;


    abrir_dialogo = gtk_file_chooser_dialog_new("Abrir arquivo", GTK_WINDOW(dado->janela), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancelar", GTK_RESPONSE_CANCEL, "Abrir", GTK_RESPONSE_ACCEPT,  NULL );

    if (gtk_dialog_run (GTK_DIALOG(abrir_dialogo)) == GTK_RESPONSE_ACCEPT ){
        dado->filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(abrir_dialogo));

        gtk_widget_destroy(abrir_dialogo);

        /* Pega o conteúdo do arquivo e coloca-o na variável texto_arquivo.
           Retorna um valor booleano, dependendo do sucesso em passar o conteúdo para a variável.
           Se não conseguir, a última variável receberá um de erro.
        */
        resultado = g_file_get_contents(dado->filename, &texto_arquivo, NULL , NULL);

        gtk_widget_set_sensitive (dado->text_view, FALSE);
        gtk_text_buffer_set_text(dado->buffer_text, texto_arquivo,-1);
        gtk_widget_set_sensitive (dado->text_view, TRUE);

        defina_buffer_salvo (dado, dado->filename);
    }else{
         gtk_widget_destroy(abrir_dialogo);
    }

}

/* Se o buffer for salvo em disco, então defina como FALSE */
void defina_buffer_salvo (Janela_Buffer *w, char *caminho_arquivo){
    gtk_text_buffer_set_modified(w->buffer_text, FALSE);
    w->filename = caminho_arquivo;
    gtk_window_set_title(GTK_WINDOW(w->janela), w->filename);
}

/* Chamado quando o texto do GtkBufferText foi "changed" para definir como verdadeiro
    em seu método gtk_text_buffer_set_modified */
void defina_buffer_modificado (GtkWidget *widget, Janela_Buffer *w){
    gtk_text_buffer_set_modified(w->buffer_text, TRUE);
    gtk_window_set_title(GTK_WINDOW(w->janela), "****");
}

/* Verifica se o arquivo aberto possui um caminho.
   Caso o seu caminho estaja vazio, então retorna falso, signficando que ele é um arquivo novo. */
gboolean possui_filename (Janela_Buffer *w){

    if ( w->filename != NULL )
        return TRUE;
    else return FALSE;

}

/*
  Dialogo de confirmação, sendo chamado quando o usuário deseja sair do arquivo.
*/
gboolean caixa_confirmacao (Janela_Buffer *w){

    GtkWidget *dialogo;

    dialogo = gtk_dialog_new_with_buttons ("Arquivo não salvo. Deseja salvá-lo?",
                                        GTK_WINDOW(w->janela),
                                        GTK_DIALOG_MODAL,
                                       GTK_STOCK_YES, GTK_RESPONSE_ACCEPT,
                                       GTK_STOCK_NO, GTK_RESPONSE_CANCEL, NULL);

    gtk_window_set_gravity(GTK_WINDOW(dialogo), GDK_GRAVITY_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(dialogo), 450, 40);

    if (gtk_dialog_run(GTK_DIALOG(dialogo)) == GTK_RESPONSE_ACCEPT ){
            gtk_widget_destroy(dialogo);
            return TRUE;
    }else{
            gtk_widget_destroy(dialogo);
            return FALSE;
    }

}

/*
    Método que abstrai todas as operações de verificação sobre o arquivo,
    fazendo apenas a gravação de um conteúdo num arquivo. */
void salvar (char* nome_arquivo, char* conteudo, Janela_Buffer *w){


    printf("\n>>>>>>>>>> Salvar");

    gboolean resultado;

    resultado = g_file_set_contents(nome_arquivo, conteudo, -1, NULL);

    printf("%d", resultado);
    printf("\n>>>>>>>>>>Resultado");
    defina_buffer_salvo(w, nome_arquivo);

    printf("\n>>>>>>>>>>Já salvou Salvar");

}

void salvar_arquivo (GtkWidget *widget, Janela_Buffer *dado){

        char        *caminho_arquivo;
        gchar        *texto;
        GtkTextIter inicio;
        GtkTextIter final;

        gtk_text_buffer_get_start_iter (dado->buffer_text, &inicio);
        gtk_text_buffer_get_end_iter (dado->buffer_text, &final);

        /* Retorna uma cadeia de caracteres UTF-8 */
        texto = gtk_text_buffer_get_text (dado->buffer_text, &inicio, &final, FALSE);

        if (gtk_text_buffer_get_modified(dado->buffer_text) == TRUE){
            if (possui_filename(dado)==TRUE)
                salvar(dado->filename, texto, dado);
            else{

                dialogo_salvar(dado, texto);

            }
        }

}

/*
    Abre um dialogo aonde o usuário define o nome do arquivo e onde o salvará.
*/

void dialogo_salvar(Janela_Buffer *dado, char* texto){

    printf("\n>>>>>>>>>>Dialogo Salvar");
    GtkWidget *dialog;
    char *caminho_arquivo;

    dialog = gtk_file_chooser_dialog_new("Salvar arquivo", GTK_WINDOW(dado->janela), GTK_FILE_CHOOSER_ACTION_SAVE, "Cancelar", GTK_RESPONSE_CANCEL, "Salvar", GTK_RESPONSE_ACCEPT, NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT){
        /* Armazena aonde o arquivo será salvo */
        caminho_arquivo = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        dado->filename = caminho_arquivo;
        salvar(caminho_arquivo, texto, dado);
    }


    gtk_widget_destroy(dialog);

}

void tst (GtkWidget *widget, Janela_Buffer *dado){

    if (possui_filename (dado) == TRUE ){
        gtk_text_buffer_set_text(dado->buffer_text, dado->filename, -1);
    }

    if (possui_filename (dado) == FALSE ){
        gtk_text_buffer_set_text(dado->buffer_text, "NULO",  -1);
    }
}

void tsta (GtkWidget *widget, Janela_Buffer *dado){

    if (gtk_text_buffer_get_modified(dado->buffer_text) == TRUE ){

            gtk_text_buffer_set_text(GTK_TEXT_BUFFER(dado->buffer_text), "MODIFICADO", -1);
    }


    if (gtk_text_buffer_get_modified(dado->buffer_text) == FALSE ){

            gtk_text_buffer_set_text(GTK_TEXT_BUFFER(dado->buffer_text), "NAO MODIFICADO", -1);
    }
}

/*
   Método que invocado quando o usuário está prestes a sair do programa.
   Verifica se o arquivo está salvo ou não para, só então, finalizar o programa.
*/
void on_window_delete_event (GtkWidget *widget, Janela_Buffer *dado){

    if ((gtk_text_buffer_get_modified(dado->buffer_text)) == TRUE){
      if (caixa_confirmacao(dado)){
          salvar_arquivo(widget, dado);
      }
    }

    printf("Chegou antes do main quit");
    gtk_main_quit();

}

void exibirSobre(GtkWidget *widget){

        const gchar *comentario = "Simples e leve editor de texto para Windows.";

        /* Utilização de um widget GtkAboutDialog para mostrar informações sobre o programa */
        GtkWidget *sobre_dialogo = gtk_about_dialog_new();

        gtk_about_dialog_set_name (GTK_ABOUT_DIALOG(sobre_dialogo), "e-Text");
        gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(sobre_dialogo), "1.0.0");
        gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG(sobre_dialogo), "Copyright (C) 2014 ");
        gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG(sobre_dialogo), comentario);
        gtk_about_dialog_set_license (GTK_ABOUT_DIALOG (sobre_dialogo), "Licença Pública Geral GNU");


        gtk_dialog_run(GTK_DIALOG(sobre_dialogo));

        gtk_widget_destroy(sobre_dialogo);
}

/*
    Inserer um arquivo selecionado pelo usuário no começo do documento.
    É feita uma caixa de diálogo que permitirá ao usuário escolher o arquivo e,
    caso ele pressione <OK>, o conteúdo do arquivo selecionado será inserido no começo
    do GtkTextBuffer.
*/
void inserir_no_comeco ( GtkWidget *widget, Janela_Buffer *dado){

    GtkWidget   *abrir_dialogo;
    char        *filename;
    char        *texto;
    /* Verificar se o arquivo foi aberto com sucesso! */
    gboolean    resultado;
    /* Receberá a posição inicial */
    GtkTextIter  inicio;

    printf("\n>>>>>>>>>>>>>inserir_comeco");

    abrir_dialogo = gtk_file_chooser_dialog_new("Selecionar arquivo", GTK_WINDOW(dado->janela), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancelar", GTK_RESPONSE_CANCEL, "Abrir", GTK_RESPONSE_ACCEPT,  NULL );

    if (gtk_dialog_run (GTK_DIALOG(abrir_dialogo)) == GTK_RESPONSE_ACCEPT ){
        /* Como não alteraremos o caminho atual do arquivo no GtkTextBuffer,
           uma variável local guardará o caminho apenas para pegar o conteúdo */
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(abrir_dialogo));
        resultado = g_file_get_contents (filename, &texto, NULL, NULL);

        if(resultado){
            /* Caso o arquivo seja aberto com sucesso, adiciono no "Log"
               e com o GtkTextIter apontando para o início do documento
               é que eu insiro no GtkTextBuffer */
            printf("\nArquivo aberto com sucesso.");
            gtk_text_buffer_get_start_iter(dado->buffer_text, &inicio);
            gtk_text_buffer_insert(dado->buffer_text, &inicio, texto, -1);
        }else{
            printf("\nErro ao abrir arquivo.");
        }

        gtk_widget_destroy(abrir_dialogo);

    }else{
        printf("\nUsuário cancelou a caixa de diálogo, não fazendo nenhuma operação no caso e fecha a caixa.");
        gtk_widget_destroy(abrir_dialogo);
    }

    printf("\n>>>>>>>>>>>>>>>Método realizado com sucesso.");
}

/*
    Inserer um arquivo selecionado pelo usuário no final do documento.
    É feita uma caixa de diálogo que permitirá ao usuário escolher o arquivo e,
    caso ele pressione <OK>, o conteúdo do arquivo selecionado será inserido no final
    do GtkTextBuffer.
*/
void inserir_no_final ( GtkWidget *widget, Janela_Buffer *dado){

    GtkWidget   *abrir_dialogo;
    char        *filename;
    char        *texto;
    /* Verificar se o arquivo foi aberto com sucesso! */
    gboolean    resultado;
    /* Receberá a posição final */
    GtkTextIter  final;

    printf("\n>>>>>>>>>>>>>inserir_final");

    abrir_dialogo = gtk_file_chooser_dialog_new("Selecionar arquivo", GTK_WINDOW(dado->janela), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancelar", GTK_RESPONSE_CANCEL, "Abrir", GTK_RESPONSE_ACCEPT,  NULL );

    if (gtk_dialog_run (GTK_DIALOG(abrir_dialogo)) == GTK_RESPONSE_ACCEPT ){
        /* Como não alteraremos o caminho atual do arquivo no GtkTextBuffer,
           uma variável local guardará o caminho apenas para pegar o conteúdo */
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(abrir_dialogo));
        resultado = g_file_get_contents (filename, &texto, NULL, NULL);

        if(resultado){
            /* Caso o arquivo seja aberto com sucesso, adiciono no "Log"
               e com o GtkTextIter apontando para o final do documento
               é que eu insiro no GtkTextBuffer */
            printf("\nArquivo aberto com sucesso.");
            gtk_text_buffer_get_end_iter(dado->buffer_text, &final);
            gtk_text_buffer_insert(dado->buffer_text, &final, texto, -1);
        }else{
            printf("\nErro ao abrir arquivo.");
        }

        gtk_widget_destroy(abrir_dialogo);

    }else{
        printf("\nUsuário cancelou a caixa de diálogo, não fazendo nenhuma operação no caso e fecha a caixa.");
        gtk_widget_destroy(abrir_dialogo);
    }

    printf("\n>>>>>>>>>>>>>>>Método realizado com sucesso.");
}


/*
    Inserer um arquivo selecionado pelo usuário aonde o cursor está posicionado do documento.
    É feita uma caixa de diálogo que permitirá ao usuário escolher o arquivo e,
    caso ele pressione <OK>, o conteúdo do arquivo selecionado será inserido na posição do cursor
    do GtkTextBuffer.
*/
void inserir_no_cursor ( GtkWidget *widget, Janela_Buffer *dado){

    GtkWidget   *abrir_dialogo;
    char        *filename;
    char        *texto;
    /* Verificar se o arquivo foi aberto com sucesso! */
    gboolean    resultado;

    printf("\n>>>>>>>>>>>>>inserir_final");

    abrir_dialogo = gtk_file_chooser_dialog_new("Selecionar arquivo", GTK_WINDOW(dado->janela), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancelar", GTK_RESPONSE_CANCEL, "Abrir", GTK_RESPONSE_ACCEPT,  NULL );

    if (gtk_dialog_run (GTK_DIALOG(abrir_dialogo)) == GTK_RESPONSE_ACCEPT ){
        /* Como não alteraremos o caminho atual do arquivo no GtkTextBuffer,
           uma variável local guardará o caminho apenas para pegar o conteúdo */
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(abrir_dialogo));
        resultado = g_file_get_contents (filename, &texto, NULL, NULL);

        if(resultado){
            /* Caso o arquivo seja aberto com sucesso, adiciono uma mensagem no "Log"
               e entã adiciono o texto ao cursor */
            printf("\n (inserir_no_cursor) Arquivo aberto com sucesso.");
            gtk_text_buffer_insert_at_cursor(dado->buffer_text, texto, -1);
        }else{
            printf("\nErro ao abrir arquivo.");
        }

        gtk_widget_destroy(abrir_dialogo);

    }else{
        printf("\nUsuário cancelou a caixa de diálogo, não fazendo nenhuma operação no caso e fecha a caixa.");
        gtk_widget_destroy(abrir_dialogo);
    }

    printf("\n>>>>>>>>>>>>>>>(inserir_no_cursor) realizado com sucesso.");

}

void copiar(GtkWidget *widget, Janela_Buffer *dado){
}

void colar (GtkWidget *widget, Janela_Buffer *dado){
}

/*
    Abre uma caixa de escolha de fonte, utilizando o retorno como argumento para
    gtk_text_buffer_set_font
*/
void mudar_fonte( GtkWidget *widget, Janela_Buffer *dado){


}
