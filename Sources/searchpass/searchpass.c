#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "sgpass.h"
#include "searchpass.h"
#include "showpass.h"
#include "confirmdelpass.h"

GtkWidget *window;
GtkWidget *label;
GtkWidget *delpassbutton;
GtkWidget *showpassbutton;
GtkWidget *filechooser;
GtkBuilder *builder;

char *path;
char *dpass;
int sizepass;

#ifndef __INTELLISENSE__
void getcontentfile(){
    sizepass = 0;
    char *pass = (char *) malloc(sizeof(char)*50000);
    FILE *f = fopen(path, "r");
    fscanf(f, "%s %d", pass, &sizepass);
    sizepass-=ENC_KEY;
    dpass = (char *) malloc(sizeof(char)*sizepass);
    for(int i = 0; i < sizepass; i++){
        dpass[i] = pass[i]-ENC_KEY;
    }
    free(pass);
}
#endif

void createsearchpasswindow(){
    path = "";
    builder = gtk_builder_new_from_file("UI/searchpasswindows/searchpasswindow.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "searchpasswindow"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    delpassbutton = GTK_WIDGET(gtk_builder_get_object(builder, "deletepassbutton"));
    showpassbutton = GTK_WIDGET(gtk_builder_get_object(builder, "showpassbutton"));
    gtk_widget_set_sensitive(GTK_WIDGET(delpassbutton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(showpassbutton), FALSE);
    filechooser = GTK_WIDGET(gtk_builder_get_object(builder, "filechooser"));
    gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER(filechooser), "Passwords (DO NOT DELETE THIS FOLDER)/");
    gtk_widget_show(window);
    gtk_main();
}

void on_filechooser_file_set(GtkFileChooser *fc){
    path = (char *) gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filechooser));
    gtk_widget_set_sensitive(GTK_WIDGET(delpassbutton), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(showpassbutton), TRUE);
}

void on_deletepassbutton_clicked(GtkButton *b){
    gtk_widget_destroy(GTK_WIDGET(window));
    opennconfdppopup(path);
}

void on_showpassbutton_clicked(GtkButton *b){
    gtk_widget_destroy(GTK_WIDGET(window));
    getcontentfile();
    createshowpasswindow(dpass, sizepass);
}