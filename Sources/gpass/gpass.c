#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "gpass.h"
#include "showpass.h"
#include "sgpass.h"
#include "opennullppopup.h"

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *generatepassbutton;
GtkWidget *label;
GtkWidget *entry;
GtkBuilder *builder;

char *size;
int savepass;

void createpass(char *pass, int n) {
    srand(time(NULL));
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    for(int i = 0; i < n; i++){
        int r = rand() % sizeof(letters);
        pass[i] = letters[r]; 
    }
    pass[n-1] = '\0';
}

void creategpasswindow(){
    size = "";
    savepass = 0;
    builder = gtk_builder_new_from_file("UI/gpasswindows/generatepasswindow.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "generatepasswindow"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    generatepassbutton = GTK_WIDGET(gtk_builder_get_object(builder, "generatepassbutton"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry"));
    gtk_widget_show(window);
    gtk_main();
}

void on_entry_changed(GtkEntry *e){
    size = (char *) gtk_entry_get_text(GTK_ENTRY(e));
    for(int i = 0; i < strlen(size); i++){
        if(!isdigit(size[i])){
            char *text = (char *) malloc(sizeof(char)*strlen(size));
            strcpy(text, size);
            text[strlen(size)-1] = '\0';
            gtk_entry_set_text(e, (const gchar *) text);
            free(text);
        }
    }
}

void on_check_toggled(GtkCheckButton *cb){
    if(savepass == 0){
        savepass = 1;
    }
    else {
        savepass = 0;
    }
}

void on_generatepassbutton_clicked(GtkButton *b){
    int i_size = atoi(size); 
    char *pass = (char *) malloc(sizeof(char)*(i_size+1));
    if(!(i_size <= 0)){
        createpass(pass, i_size);
        gtk_widget_destroy(GTK_WIDGET(window));
        if(savepass == 0)
            createshowpasswindow(pass, i_size);
        else
            createsgpasswindow(pass);
    }
    else {
        opennullppopup();
    }
}