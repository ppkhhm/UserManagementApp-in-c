// signup.c
#include <gtk/gtk.h>
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void on_signup_submit_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const char *user_id = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *password = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const char *name = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const char *email = gtk_entry_get_text(GTK_ENTRY(entries[3]));

    User user;
    strcpy(user.user_id, user_id);
    strcpy(user.password, password);
    strcpy(user.name, name);
    strcpy(user.email, email);

    FILE *file = fopen("users.dat", "ab");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }
    fwrite(&user, sizeof(User), 1, file);
    fclose(file);

    gtk_main_quit();
}

void signup() {
    GtkWidget *window, *grid, *submit_button;
    GtkWidget *user_id_entry, *password_entry, *name_entry, *email_entry;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Signup");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *user_id_label = gtk_label_new("User ID:");
    GtkWidget *password_label = gtk_label_new("Password:");
    GtkWidget *name_label = gtk_label_new("Name:");
    GtkWidget *email_label = gtk_label_new("Email:");

    user_id_entry = gtk_entry_new();
    password_entry = gtk_entry_new();
    name_entry = gtk_entry_new();
    email_entry = gtk_entry_new();

    gtk_grid_attach(GTK_GRID(grid), user_id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), user_id_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), email_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), email_entry, 1, 3, 1, 1);

    GtkWidget *entries[] = {user_id_entry, password_entry, name_entry, email_entry};

    submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_signup_submit_clicked), entries);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 4, 2, 1);

    gtk_widget_show_all(window);
    gtk_main();
}

