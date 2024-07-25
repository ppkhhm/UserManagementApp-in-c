#ifndef USER_H
#define USER_H

#include <gtk/gtk.h>

// Structure to store user information
typedef struct {
    char user_id[50];
    char password[50];
    char name[100];
    char email[100];
} User;

// Function declarations for signup and login
void signup();
void login();
void display_user_info(User user);

#endif

