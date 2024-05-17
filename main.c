#include <gtk/gtk.h>

static void btn_click(GtkWidget *widget, gpointer data)
{
    GtkWidget *janela = (GtkWidget *)data;
    gtk_widget_destroy(janela);
}

static void max(GtkWidget *widget, gpointer data)
{
    GtkWidget *janela = (GtkWidget *)data;
    if(!gtk_window_is_maximized(GTK_WINDOW(janela))) {
        gtk_window_maximize(GTK_WINDOW(janela));
    } else {
        gtk_window_unmaximize(GTK_WINDOW(janela));
    }
}

static void min(GtkWidget *widget, gpointer data)
{
    GtkWidget *janela = (GtkWidget *)data;
    gtk_window_iconify(GTK_WINDOW(janela));
}

void pack_align(GtkBox *box, GtkWidget *widget, GtkAlign alignment) {
    gtk_box_pack_start(GTK_BOX(box), widget, FALSE, FALSE, 0);
    gtk_widget_set_halign(widget, alignment);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    // Carregar a imagem usando o pixbuf
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file("assets/img/image.png", &error);

    if (error != NULL)
    {
        g_error("Erro ao carregar a imagem: %s", error->message);
        g_error_free(error);
        return 1;
    }

    // Redimensionar o pixbuf para as dimensões desejadas
    GdkPixbuf *resized_pixbuf = gdk_pixbuf_scale_simple(pixbuf, 100, 55, GDK_INTERP_BILINEAR);

    // Criar o gtk_image com o pixbuf redimensionado
    GtkWidget *image = gtk_image_new_from_pixbuf(resized_pixbuf);

    // Criar a janela
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Pipo-15");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Criar os botões
    GtkWidget *button1 = gtk_button_new_with_label("Botão 1"),
    *button2 = gtk_button_new_with_label("Botão 2"),
    *button3 = gtk_button_new_with_label("Botão 3");

    gtk_widget_set_size_request(button1, 100, 55);

    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(btn_click), window);
    g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(max), window);
    g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(min), window);

    // criar a box dos botões de controle
    GtkWidget *cbtn = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), cbtn);

    // Criar um provedor de CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css", NULL); // Substitua "caminho/para/o/arquivo/estilos.css" pelo caminho real do seu arquivo CSS
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Adicionar os botões à caixa
    // packWidgetWithAlignment
    pack_align(GTK_BOX(cbtn), button1, GTK_ALIGN_START);
    pack_align(GTK_BOX(cbtn), button2, GTK_ALIGN_START);
    pack_align(GTK_BOX(cbtn), button3, GTK_ALIGN_START);
    pack_align(GTK_BOX(cbtn), image, GTK_ALIGN_START);

    // Exibir todos os elementos
    gtk_widget_show_all(window);

    // Liberar os pixbufs
    g_object_unref(pixbuf);
    g_object_unref(resized_pixbuf);

    gtk_main();

    return 0;
}