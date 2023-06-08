//
// Created by DANILIAMMO on 06.06.23.
//

#include <gtk/gtk.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

GtkWidget *headerbar;
GtkWidget *box;
GtkWidget *height;
GtkWidget *weight;


/* Функция-обработчик события insert-text для поля ввода */
void on_insert_text(GtkEditable *editable, const gchar *text, gint length, const gint *position, gpointer)
{
    /* Проверяем каждый введенный символ на соответствие допустимым символам */
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(text[i]) && text[i] != ',' ||
            (text[i] == '-' && *position == 0))
        {
            /* Отклоняем ввод, если в нем содержатся недопустимые символы */
            g_signal_stop_emission_by_name(editable, "insert-text");
            return;
        }
    }
}

char* CalculateBMIStatus(float BMI)
{

    if(BMI >= 0)
    {
        if(BMI <= 16)
        {
            return "Severe thinness";
        }
    }

    if(BMI >= 16)
    {
        if(BMI <= 17)
        {
            return "Moderate thinness";
        }
    }

    if(BMI >= 17)
    {
        if(BMI <= 18.5)
        {
            return "Underweight"; // Маленький BMI
        }
    }

    if(BMI >= 18.5)
    {
        if(BMI <= 25)
        {
            return "Normal"; // Нормальный BMI
        }
    }

    if(BMI >= 25)
    {
        if(BMI <= 30)
        {
            return "Overweight";
        }
    }

    if(BMI >= 30)
    {
        if(BMI <= 35)
        {
            return "Obese Class I";
        }
    }

    if(BMI >= 35)
    {
        if(BMI <= 40)
        {
            return "Obese Class II";
        }
    }

    if(BMI >= 40)
    {
        return "Obese Class III";
    }

}

float CalculateBMI(GtkWidget *height_widget, GtkWidget *weight_widget)
{
    const char* height_text = gtk_entry_get_text(GTK_ENTRY(height_widget));
    const char* weight_text = gtk_entry_get_text(GTK_ENTRY(weight_widget));
    float height;
    float bmi;
    float weight;

    weight = atof(weight_text);
    height = atof(height_text);

    bmi = weight / (height * height);
    printf("Your BMI is %f\n", bmi);
    if (!isnan(bmi))
    {
        return bmi;
    } else
    {
        return 0;
    }
}

void on_button_clicked()
{
    float bmi = CalculateBMI(height, weight);
    char bmi_text[256] = "Your BMI is %.2f";

    // Проверяем наличие bmi_label в контейнере
    GList *children = gtk_container_get_children(GTK_CONTAINER(box));
    GtkLabel *bmi_label = NULL;

    while (children != NULL && bmi_label == NULL)
    {
        GtkWidget *child = GTK_WIDGET(children->data);
        if (GTK_IS_LABEL(child))
        {
            const gchar *label_text = gtk_label_get_text(GTK_LABEL(child));
            if (g_str_has_prefix(label_text, "Your BMI is "))
            {
                bmi_label = GTK_LABEL(child);
            }
        }
        children = g_list_next(children);
    }

    printf(CalculateBMIStatus(bmi), "\n");

    // Если bmi_label уже есть в контейнере, то обновляем его текст
    if (bmi_label != NULL)
    {
        sprintf(bmi_text, "Your BMI is %.2f", bmi);
        gtk_label_set_text(bmi_label, bmi_text);
    }
    else // Иначе создаем новый bmi_label и добавляем его в контейнер
    {
        sprintf(bmi_text, "Your BMI is %.2f", bmi);
        bmi_label = GTK_LABEL(gtk_label_new(bmi_text));
        gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(bmi_label), FALSE, FALSE, 20);
        gtk_widget_show_all(box);
    }
}

void add_elements(GtkWidget *window)
{

    /* Создаем новую заголовочную панель */
    headerbar = gtk_header_bar_new();

    /* Устанавливаем кнопку закрытия окна на заголовочной панели */
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);

    /* Устанавливаем название приложения на заголовочной панели */
    gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "Калькулятор ИМТ");

    /* Устанавливаем подзаголовок на заголовочной панели */
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar), "Узнайте нормальный ли у вас ИМТ");

    /* Устанавливаем заголовочную панель на окно */
    gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);



    /* Создаем контейнер */
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    /* Добавляем контейнер в окно */
    gtk_container_add(GTK_CONTAINER(window), box);



    /* Создаем первое поле для ввода */
    height = gtk_entry_new();
    gtk_widget_set_name(height, "gray-entry"); // добавляем CSS-класс

    /* Устанавливаем текст по умолчанию */
    gtk_entry_set_placeholder_text(GTK_ENTRY(height), "Рост (в метрах)");

    /* Устанавливаем размеры виджета */
    gtk_widget_set_size_request(height, 400, 50);

    /* Выравниваем по центру */
    gtk_widget_set_halign(height, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(height, GTK_ALIGN_CENTER);

    /* Добавляем обработчик события insert-text для поля ввода */
    g_signal_connect(G_OBJECT(height), "insert-text", G_CALLBACK(on_insert_text), NULL);

    /* Добавляем первое поле для ввода в контейнер */
    gtk_box_pack_start(GTK_BOX(box), height, FALSE, FALSE, 20);

    /* Создаем второе поле для ввода */
    weight = gtk_entry_new();
    gtk_widget_set_name(weight, "gray-entry"); // добавляем CSS-класс

    /* Устанавливаем текст по умолчанию */
    gtk_entry_set_placeholder_text(GTK_ENTRY(weight), "Вес (в килограммах)");

    /* Устанавливаем размеры виджета */
    gtk_widget_set_size_request(weight, 400, 50);

    /* Выравниваем по центру */
    gtk_widget_set_halign(weight, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(weight, GTK_ALIGN_CENTER);

    /* Добавляем обработчик события insert-text для поля ввода */
    g_signal_connect(G_OBJECT(weight), "insert-text", G_CALLBACK(on_insert_text), NULL);

    /* Добавляем второе поле для ввода в контейнер */
    gtk_box_pack_start(GTK_BOX(box), weight, FALSE, FALSE, 20);



    /* Создаем кнопку */
    GtkWidget *calculate_button = gtk_button_new_with_label("Узнать ИМТ");

    /* Добавляем CSS-класс */
    gtk_widget_set_name(calculate_button, "blue-button");

    /* Устанавливаем размеры виджета */
    gtk_widget_set_size_request(calculate_button, 400, 50);

    /* Выравниваем по центру */
    gtk_widget_set_halign(calculate_button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(calculate_button, GTK_ALIGN_CENTER);

    /* Добавляем обработчик события clicked для кнопки */
    g_signal_connect(G_OBJECT(calculate_button), "clicked", G_CALLBACK(on_button_clicked), NULL);

    /* Добавляем кнопку в контейнер */
    gtk_box_pack_start(GTK_BOX(box), calculate_button, FALSE, FALSE, 20);

}
