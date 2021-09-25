#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "sgpass.h"
#include "spass.h"
#include "emptyentries.h"

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *savebutton;
GtkWidget *label;
GtkWidget *entry;
GtkBuilder *builder;

char *passcp;
char *entrytext;

void createsgpasswindow(char *pass)
{
    entrytext = "";
    passcp = (char *) malloc(sizeof(char)*strlen(pass));
    strcpy(passcp, pass);
    builder = gtk_builder_new_from_file("UI/spasswindows/savegpasswindow.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "savegpasswindow"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    savebutton = GTK_WIDGET(gtk_builder_get_object(builder, "savebutton"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry"));
    gtk_widget_show(window);
    gtk_main();
}

void on_entry_changed_2(GtkEntry *e)
{
    entrytext = (char *) gtk_entry_get_text(GTK_ENTRY(e));
    for(int i = 0; i < strlen(entrytext); i++){
        if(!isalpha(entrytext[i])){
            char *text = (char *) malloc(sizeof(char)*strlen(entrytext));
            strcpy(text, entrytext);
            text[strlen(entrytext)-1] = '\0';
            gtk_entry_set_text(e, (const gchar *) text);
            free(text);
        }
    }
}

void on_savebutton_clicked(GtkButton *b)
{
    if (strcmp(entrytext, ""))
    {
        char *path = (char *)malloc(sizeof(char) * (strlen(entrytext) + strlen(PASSW_FILE_DIR) + strlen("/") + strlen(PASSW_FILE_EXT)));
        strcpy(path, PASSW_FILE_DIR);
        strcat(path, "/");
        strcat(path, entrytext);
        strcat(path, PASSW_FILE_EXT);
        gtk_widget_destroy(GTK_WIDGET(window));
        chkifexists(path, passcp);
        return;
    }
    openemptyepopup();
}