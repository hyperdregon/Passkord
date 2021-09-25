#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sys/stat.h>
#include "main.h"
#include "gpass.h"
#include "spass.h"
#include "sgpass.h"
#include "searchpass.h"
#include "password.h"

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *generatepassword;
GtkWidget *savepassword;
GtkWidget *listpassword;
GtkBuilder *builder;

#ifndef __INTELLISENSE__
int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    mkdir("temp", S_IRWXU);
    createpasswindow();
    char *access = (char *) malloc(sizeof(char)*6);
    FILE *f = fopen("temp/access.txt", "r");
    if(f != NULL)
        fscanf(f, "%s", access);
        for(int i = 0; i < 6; i++){
            access[i]-=ENC_KEY;
        }
        if(strcmp(access, "access") == 0){
            fclose(f);
            free(access);
            remove("temp/access.txt");
            remove("temp");
            mkdir(PASSW_FILE_DIR, S_IRWXU);
            builder = gtk_builder_new_from_file("UI/mainwindow.glade");
            window = GTK_WIDGET(gtk_builder_get_object(builder, "mainwindow"));
            g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
            gtk_builder_connect_signals(builder, NULL);
            fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
            generatepassword = GTK_WIDGET(gtk_builder_get_object(builder, "generatepassword"));
            savepassword = GTK_WIDGET(gtk_builder_get_object(builder, "savepassword"));
            listpassword = GTK_WIDGET(gtk_builder_get_object(builder, "listpassword"));
            gtk_widget_show(window);
            gtk_main();
        }
    return EXIT_SUCCESS;
}
#endif

void on_GeneratePassword_clicked(GtkButton *b){
    creategpasswindow();
}

void on_SavePassword_clicked(GtkButton *b){
    createspasswindow();
}

void on_ListPassword_clicked(GtkButton *b){
    createsearchpasswindow();
}
