#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "spass.h"
#include "repeatedpass.h"
#include "sgpass.h"

GtkWidget *window;
GtkWidget *label;
GtkWidget *yesbutton;
GtkWidget *nobutton;
GtkBuilder *builder;

char *pathcp;
char *passcp;

void opennreppasspopup(char *path, char *pass){
    pathcp = path;
    passcp = pass;
    builder = gtk_builder_new_from_file("UI/spasswindows/popups/repeatedpasswindow.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "repeatedpasswindow"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    yesbutton = GTK_WIDGET(gtk_builder_get_object(builder, "yesbutton"));
    nobutton = GTK_WIDGET(gtk_builder_get_object(builder, "nobutton"));
    gtk_widget_show(window);
    gtk_main();
}

void on_yesbutton_clicked(GtkButton *b){
    savefile(pathcp, passcp);
    gtk_widget_destroy(GTK_WIDGET(window));
}

void on_nobutton_clicked(GtkButton *b){
    gtk_widget_destroy(GTK_WIDGET(window));
}