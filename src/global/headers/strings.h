#ifndef STRINGS_H
#define STRINGS_H

// Author structure
typedef struct
{
    char *name;     // Author name
    char *username; // Author username
    char *email;    // Author email
    char *sid;      // Author student id
} Author;

// OS trademark structure
typedef struct
{
    char *ascii_art_name; // OS ascii art name
    char *asii_art_logo;  // OS logo
    char *name;           // OS name
    char *id;             // OS id
    char *home_url;       // OS home url (tba)
    char *support_url;    // OS support url (tba)
    char *version;        // OS version
    char *created_at;     // OS created date
    char *updated_at;     // OS updated date
    char *init;           // OS init (Initial text displayed in the console of the OS)
    Author author;        // OS author
} OsTrademark;

typedef struct
{
    char *name;         // Name of the command
    char *desc;         // Description of the command
    void (*func)(void); // Function pointer to the command
} Command;

typedef struct
{
    char *school;
    char *course;
    char *lecturer;
    char *submitted_by;
    char *declaration;
} Acknowledgement;

extern OsTrademark os_inf;
extern Acknowledgement ack;

#endif // STRINGS_H