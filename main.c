// main.c
#include <gtk/gtk.h>
#include "user.h"

void on_signup_button_clicked(GtkWidget *widget, gpointer data) {
    signup();
}

void on_login_button_clicked(GtkWidget *widget, gpointer data) {
    login();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window, *signup_button, *login_button, *vbox;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "User Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    signup_button = gtk_button_new_with_label("Signup");
    g_signal_connect(signup_button, "clicked", G_CALLBACK(on_signup_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), signup_button, TRUE, TRUE, 0);

    login_button = gtk_button_new_with_label("Login");
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), login_button, TRUE, TRUE, 0);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

