#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include <ctype.h>
#include "spass.h"
#include "repeatedpass.h"
#include "emptyentries.h"
#include "sgpass.h"

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *savebutton;
GtkWidget *label;
GtkWidget *infolabel;
GtkWidget *entrypass;
GtkWidget *entryloc;
GtkBuilder *builder;

char *passcp;
char *entryloctext;

//this is to make vscode ignore errors on this function
#ifndef __INTELLISENSE__
void savefile(char *path, char *pass)
{
    char *encryptedpass = (char *)malloc(sizeof(char) * strlen(pass));
    FILE *f = fopen(path, "w");
    for (int i = 0; i < strlen(pass); i++)
    {
        encryptedpass[i] = pass[i] + ENC_KEY;
    }
    fprintf(f, "%s %ld", encryptedpass, strlen(pass) + ENC_KEY);
    fclose(f);
    free(encryptedpass);
}
#endif

void chkifexists(char *path, char *pass)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        savefile(path, pass);
    }
    else
    {
        opennreppasspopup(path, pass);
    }
}

void createspasswindow(){
    passcp = "";
    entryloctext = "";
    builder = gtk_builder_new_from_file("UI/spasswindows/savepasswindow.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "savepasswindow"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);
    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    savebutton = GTK_WIDGET(gtk_builder_get_object(builder, "generatepassbutton"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
    infolabel = GTK_WIDGET(gtk_builder_get_object(builder, "infolabel"));
    entrypass = GTK_WIDGET(gtk_builder_get_object(builder, "entrypass"));
    entryloc = GTK_WIDGET(gtk_builder_get_object(builder, "entryloc"));
    gtk_widget_show(window);
    gtk_main();
}

void checkfornonalpha(char *text, GtkEntry *e){
    for(int i = 0; i < strlen(text); i++){
        if(!isalpha(text[i])){
            char *textcp = (char *) malloc(sizeof(char)*strlen(text));
            strcpy(textcp, text);
            textcp[strlen(textcp)-1] = '\0';
            gtk_entry_set_text(e, (const gchar *) textcp);
            free(textcp);
        }
    }
}

void on_entrypass_changed(GtkEntry *e){
    passcp = (char *) gtk_entry_get_text(GTK_ENTRY(e));
    checkfornonalpha(passcp, e);
}

void on_entryloc_changed(GtkEntry *e){
    entryloctext = (char *) gtk_entry_get_text(GTK_ENTRY(e));
    checkfornonalpha(entryloctext, e);
}

void on_savebutton_clicked_2(GtkButton *b){
    if ((strcmp(passcp, "") || strcmp(entryloctext, "")) || (strcmp(passcp, "") && strcmp(entryloctext, "")))
    {
        char *path = (char *) malloc(sizeof(char) * (strlen(entryloctext) + strlen(PASSW_FILE_DIR)+ strlen("/") + strlen(PASSW_FILE_EXT)));
        strcpy(path, PASSW_FILE_DIR);
        strcat(path, "/");
        strcat(path, entryloctext);
        strcat(path, PASSW_FILE_EXT);
        char *pass = (char *) malloc(sizeof(char)*(strlen(passcp)+1));
        strcpy(pass, passcp);
        pass[strlen(pass)-1] = '\0';
        gtk_widget_destroy(GTK_WIDGET(window));
        chkifexists(path, pass);
        return;
    }
    openemptyepopup();
}