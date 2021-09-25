#ifndef SPASS_H_
#define SPASS_H_

void createspasswindow();
void chkifexists(char *path, char *pass);
void savefile(char *path, char *pass);
void writewarningmsg();
void checkfornonalpha(char *text, GtkEntry *e);

#endif 

