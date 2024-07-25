#include <emscripten.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>  // Add this line to include stdio.h

typedef struct {
    char user_id[50];
    char password[50];
    char name[100];
    char email[100];
} User;

// We'll use a simple array to store users. In a real application, you'd use a database.
#define MAX_USERS 100
User users[MAX_USERS];
int user_count = 0;

EMSCRIPTEN_KEEPALIVE
int signup(const char* user_id, const char* password, const char* name, const char* email) {
    if (user_count >= MAX_USERS) return 0; // Failed, too many users
    
    User new_user;
    strcpy(new_user.user_id, user_id);
    strcpy(new_user.password, password);
    strcpy(new_user.name, name);
    strcpy(new_user.email, email);
    
    users[user_count++] = new_user;
    return 1; // Success
}

EMSCRIPTEN_KEEPALIVE
char* login(const char* user_id, const char* password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].user_id, user_id) == 0 && strcmp(users[i].password, password) == 0) {
            // User found, return user data as a JSON string
            char* result = malloc(256); // Ensure this is large enough
            snprintf(result, 256, "{\"user_id\":\"%s\",\"name\":\"%s\",\"email\":\"%s\"}", 
                     users[i].user_id, users[i].name, users[i].email);
            return result;
        }
    }
    return NULL; // User not found or password incorrect
}

EMSCRIPTEN_KEEPALIVE
void free_string(char* ptr) {
    free(ptr);
}
