#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkWidget *window;
    // GObject *button;
	GError *error = NULL;
    
    gtk_init(&argc, &argv);

    // Carregar a interface gráfica do arquivo XML
    builder = gtk_builder_new(); 
	if (gtk_builder_add_from_file (builder, "interface.ui", &error) == 0) {
		g_printerr ("Error loading dice.ui file: %s\n", error->message);
		g_clear_error (&error);
		return 1;
	} 

    // Signal connections brought in from XML
	gtk_builder_connect_signals(builder, NULL);

    // Obter a janela principal da interface
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    /*GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(window); // 'window' é o widget da janela principal
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);*/

    // Conectar o sinal "destroy" da janela à função gtk_main_quit
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Exibir a janela
    gtk_widget_show(window);

    // Iniciar o loop principal da interface gráfica
    gtk_main();

    return 0;
}