// login.c
#include <gtk/gtk.h>
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_user_info(User user) {
    GtkWidget *window, *label, *vbox;
    char info[300]; // Increased buffer size

    snprintf(info, sizeof(info), "User ID: %s\nName: %s\nEmail: %s", user.user_id, user.name, user.email);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "User Information");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    label = gtk_label_new(info);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
    gtk_main();
}

void on_login_submit_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const char *user_id = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *password = gtk_entry_get_text(GTK_ENTRY(entries[1]));

    User user;
    FILE *file = fopen("users.dat", "rb");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.user_id, user_id) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            gtk_main_quit();
            display_user_info(user);
            return;
        }
    }
    fclose(file);

    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Invalid User ID or Password");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void login() {
    GtkWidget *window, *grid, *submit_button;
    GtkWidget *user_id_entry, *password_entry;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *user_id_label = gtk_label_new("User ID:");
    GtkWidget *password_label = gtk_label_new("Password:");

    user_id_entry = gtk_entry_new();
    password_entry = gtk_entry_new();

    gtk_grid_attach(GTK_GRID(grid), user_id_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), user_id_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 1, 1);

    GtkWidget *entries[] = {user_id_entry, password_entry};

    submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_login_submit_clicked), entries);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 2, 2, 1);

    gtk_widget_show_all(window);
    gtk_main();
}

