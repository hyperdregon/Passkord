#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "confirmdelpass.h"
#include "searchpass.h"
#include "deleteddelpass.h"
#include "notdeleteddelpass.h"

GtkWidget *window;
GtkWidget *label;
GtkWidget *yesbutton;
GtkWidget *nobutton;
GtkBuilder *builder;

char *pathcp;

void opennconfdppopup(char *path){
    pathcp = (char *) malloc(sizeof(char)*strlen(path));
    strcpy(pathcp, path);
    builder = gtk_builder_new_from_file("UI/searchpasswindows/popups/confirmdelpass.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "confirmdelpass"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    yesbutton = GTK_WIDGET(gtk_builder_get_object(builder, "yesbutton"));
    nobutton = GTK_WIDGET(gtk_builder_get_object(builder, "nobutton"));
    gtk_widget_show(window);
    gtk_main();
}

void on_yesbutton_clicked_2(GtkButton *b){
    gtk_widget_destroy(GTK_WIDGET(window));
    if (remove(pathcp) == 0) {
        openddelppopup();
    } 
    else {
        opennddelppopup();
    }
}

void on_nobutton_clicked_2(GtkButton *b){
    gtk_widget_destroy(GTK_WIDGET(window));
    createsearchpasswindow();
}