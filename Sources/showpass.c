#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>
#include "showpass.h"

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *label;
GtkWidget *passbutton;
GtkWidget *infolabel;
GtkBuilder *builder;

const char *option;
char *passcp;
int sizepasscp;
int showingpass;

void addtexttopasslabel(){
    char *temp = (char *) malloc(sizeof(char)*(sizepasscp+1000));
    for(int i = 0, j = 0, k = 0; k < sizepasscp; i++, j++){
        if(j == 182){
            temp[i] = '\n';
            j = 0;
            continue;
        }
        temp[i] = passcp[k];
        temp[i+1] = '\0';
        k++;
    }
    char *pass = (char *) malloc(sizeof(char)*strlen(temp));
    strcpy(pass, temp);
    free(temp);
    gtk_button_set_label(GTK_BUTTON(passbutton), (const gchar *) pass);
    free(pass);
}

void createshowpasswindow(char *pass, int sizepass){
    showingpass = 0;
    passcp = (char *) malloc(sizeof(char)*strlen(pass));
    strcpy(passcp, pass);
    sizepasscp = sizepass;
    builder = gtk_builder_new_from_file("UI/showpasswindow.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "showpasswindow"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    passbutton = GTK_WIDGET(gtk_builder_get_object(builder, "passbutton"));
    infolabel = GTK_WIDGET(gtk_builder_get_object(builder, "infolabel"));
    gtk_widget_show(window);
    gtk_main();
}

void on_passbutton_clicked(GtkButton *b){
    GtkClipboard *cb = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
    gtk_clipboard_set_text(cb, passcp, strlen(passcp));
    gtk_label_set_text(GTK_LABEL(infolabel), (const gchar *) "(Password copied!)");
}

void on_showpasswindow_focus_in_event(){
    if(showingpass == 0){
        addtexttopasslabel();
        showingpass = 1;
    }
}