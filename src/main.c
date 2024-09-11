#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

// Função de callback para fechar a janela
static void close_window(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

// Função de callback para destruir a janela
static void btn_click(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(GTK_WIDGET(data));
}

// Função de callback para maximizar a janela
static void max(GtkWidget *widget, gpointer data)
{
    GtkWidget *janela = (GtkWidget *)data;
    if(!gtk_window_is_maximized(GTK_WINDOW(janela))) {
        gtk_window_maximize(GTK_WINDOW(janela));
    } else {
        gtk_window_unmaximize(GTK_WINDOW(janela));
    }
}

// Função de callback para minimizar a janela
static void min(GtkWidget *widget, gpointer data)
{
    GtkWidget *janela = (GtkWidget *)data;
    gtk_window_iconify(GTK_WINDOW(janela));
}

int main(int argc, char *argv[]) {
    // Inicializar o GTK
    gtk_init(&argc, &argv);

    // Criar a janela
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "heheboy");
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);

    // Criar a WebView do WebKit2GTK
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    // Carregar uma página HTML local
    gchar *file_uri = g_strdup_printf("file://%s/view/index.html", g_get_current_dir());
    webkit_web_view_load_uri(webView, file_uri);

    // Criar um provedor de CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Carregar o arquivo CSS externo
    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "view/style/style.css", &error);
    if (error != NULL) {
        g_error("Erro ao carregar o arquivo CSS: %s", error->message);
        g_error_free(error);
        return 1;
    }

    // Criar os botões
    GtkWidget *button1 = gtk_button_new_with_label("close"),
              *button2 = gtk_button_new_with_label("max"),
              *button3 = gtk_button_new_with_label("min");

    // Conectar os botões às funções de callback
    g_signal_connect(button1, "clicked", G_CALLBACK(btn_click), window);
    g_signal_connect(button2, "clicked", G_CALLBACK(max), window);
    g_signal_connect(button3, "clicked", G_CALLBACK(min), window);

    // Criar a box dos botões de controle
    GtkWidget *cbtn = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(cbtn), button1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cbtn), button2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(cbtn), button3, FALSE, FALSE, 0);

    // Criar um layout para a janela
    GtkWidget *layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // Definir a expansão vertical e horizontal do elemento WebView
    gtk_widget_set_vexpand(GTK_WIDGET(webView), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(webView), TRUE);
    
    //add elements
    gtk_box_pack_start(GTK_BOX(layout), cbtn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(layout), GTK_WIDGET(webView), TRUE, TRUE, 0);

    // Adicionar o layout à janela
    gtk_container_add(GTK_CONTAINER(window), layout);

    // Exibir todos os elementos
    gtk_widget_show_all(window);

    // Iniciar o loop principal do GTK
    gtk_main();

    return 0;
}