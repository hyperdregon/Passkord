#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "opennullppopup.h"

GtkWidget *window;
GtkWidget *label;
GtkWidget *button;
GtkBuilder *builder;

void opennullppopup(){
    builder = gtk_builder_new_from_file("UI/gpasswindows/popups/nullpassword.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "nullpasswindow"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "okbutton"));
    gtk_widget_show(window);
    gtk_main();
}

void on_okbutton_clicked(GtkButton *b){
    gtk_widget_destroy(GTK_WIDGET(window));
}