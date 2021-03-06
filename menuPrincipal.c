//gcc -Wall -g -o tutorial main.c `pkg-config --cflags --libs gtk+-2.0` -export-dynamic

#include <stdlib.h>
#include <gtk/gtk.h>
#include"cadastroUsuario.c"
#include"cadastroQuarto.c"

GtkBuilder      *builder;

void on_wMenuPrincipal_destroy(GtkObject *object, gpointer user_data){
	gtk_main_quit ();
}
void  on_miQuartoCadastrar_activate(GtkObject *object, gpointer user_data){
	cadastroQuarto();
}

void on_miClienteCadastrar_activate (GtkObject *object, gpointer user_data){
	cadastroUsuario();
}
 
int main (int argc, char *argv[]){
//int menuPrincipal(){

    GtkWidget       *window;

    gtk_init (&argc,&argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "menuPrincipal.glade", NULL); //Carrega as informações do projeto glade para o GtkBuilder
    window = GTK_WIDGET(gtk_builder_get_object (builder, "wMenuPrincipal"));   //Retorna o objeto Window, para mostrá-lo mais tarde
    gtk_builder_connect_signals (builder, NULL); //Conecta todos os eventos dentro do projeto do glade.
 
   //g_object_unref (G_OBJECT (builder)); //Exclui o GtkBuilder, pois não iremos mais usá-lo nesse exemplo.
 
    gtk_widget_show_all(window);   //Mostra a janela com seus objetos
    gtk_main ();
 
    return 0;
}
