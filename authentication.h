#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

int load_users(const char *filename);
int authenticate_user();
char get_logged_in_user_role();

#endif
