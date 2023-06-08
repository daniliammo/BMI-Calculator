//
// Created by DANILIAMMO on 06.06.23.
//

#include <gtk/gtk.h>

GtkWidget *create_window()
{
    GtkWidget *window;

    /* Создаем новое окно */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /* Устанавливаем заголовок окна */
    gtk_window_set_title(GTK_WINDOW(window), "BMI Calculator");

    /* Устанавливаем размеры окна */
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 700);

    /* Устанавливаем позицию окна по центру экрана */
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    return window;
}
