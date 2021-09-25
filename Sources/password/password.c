#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "password.h"
#include "passnullinc.h"

GtkWidget *window;
GtkWidget *label;
GtkWidget *button;
GtkWidget *entry;
GtkBuilder *builder;

char *content;

void createpasswindow(){
    content = "";
    builder = gtk_builder_new_from_file("UI/passwordwindows/passwordwindow.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "passwordwindow"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "enterbutton"));
    entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry"));
    gtk_widget_show(window);
    gtk_main();
}

#ifndef __INTELLISENSE__
void on_enterbutton_clicked(GtkButton *b){
    content = (char *) gtk_entry_get_text(GTK_ENTRY(entry));
    FILE *f = fopen("temp/access.txt", "w");
    if(strcmp(content, PASSWD) != 0){
        gtk_widget_destroy(GTK_WIDGET(window));
        opennipasspopup();
    }
    else {
        char accesstxt[] = "access";
        for(int i = 0; i < 6; i++){
            fprintf(f, "%c", accesstxt[i]+ENC_KEY);
        }
        fclose(f);
        gtk_widget_destroy(GTK_WIDGET(window));
    }
}
#endif