//
// Created by DANILIAMMO on 06.06.23.
//

#include <gtk/gtk.h>

GtkWidget *create_window();
void add_elements(GtkWidget *window);


int main(int argc, char *argv[])
{
    GtkWidget *window;

    gtk_init(&argc, &argv);

    window = create_window();

    add_elements(window);

    /* Обрабатываем событие закрытия окна */
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /* Показываем все элементы интерфейса на экране */
    gtk_widget_show_all(window);

    /* Запускаем основной цикл GTK */
    gtk_main();
}
