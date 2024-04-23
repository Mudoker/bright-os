#include "os.h"
#include "../global/global.h"
#include "../helper/styler/styler.h"

void os_greet() {
  uart_puts("\n");

  // Print OS logo
  char *os_logo = str_format(OS_INF.ascii_art_logo, COLOR.YELLOW, 0);
  uart_puts(os_logo);
  uart_puts("\n");

  // Print OS Information box
  print_in_box("OS Information");
  uart_puts("\n");

  // Format and print "ID" title
  char *id_title = str_format("ID           : ", COLOR.YELLOW, 0);
  uart_puts(id_title);
  uart_puts(OS_INF.id);
  uart_puts("\n\0");

  // Format and print "OS Name" title
  char *name_title = str_format("OS Name      : ", COLOR.YELLOW, 0);
  uart_puts(name_title);
  uart_puts(OS_INF.name);
  uart_puts("\n");

  // Format and print "Version" title
  char *version_title = str_format("Version      : ", COLOR.YELLOW, 0);
  uart_puts(version_title);
  uart_puts(OS_INF.version);
  uart_puts("\n");

  // Format and print "Home URL" title
  char *home_url_title = str_format("Home URL     : ", COLOR.YELLOW, 0);
  uart_puts(home_url_title);
  uart_puts(OS_INF.home_url);
  uart_puts("\n");

  // Format and print "Support URL" title
  char *sup_url_title = str_format("Support URL  : ", COLOR.YELLOW, 0);
  uart_puts(sup_url_title);
  uart_puts(OS_INF.support_url);
  uart_puts("\n");

  // Author Information
  print_in_box("Author Information");
  uart_puts("\n");

  // Print author name
  char *author_name = str_format("Author       : ", COLOR.YELLOW, 0);
  uart_puts(author_name);
  uart_puts(OS_INF.author.name);
  uart_puts("\n");

  // Print author username
  char *username = str_format("Username     : ", COLOR.YELLOW, 0);
  uart_puts(username);
  uart_puts(OS_INF.author.username);
  uart_puts("\n");

  // Print author SID
  char *sid = str_format("SID          : ", COLOR.YELLOW, 0);
  uart_puts(sid);
  uart_puts(OS_INF.author.sid);
  uart_puts("\n");

  // Print author email
  char *email = str_format("Email        : ", COLOR.YELLOW, 0);
  uart_puts(email);
  uart_puts(OS_INF.author.email);
  uart_puts("\n");

  // Copyright
  print_in_box("Acknowledgement");
  uart_puts("School of Science, Engineering and Technology\n\n");

  // Print school name (RMIT SSET)
  char *school = str_format("School       : ", COLOR.YELLOW, 0);
  uart_puts(school);
  uart_puts(ACK.school);
  uart_puts("\n");

  // Print course name (Embedded Systems 3)
  char *course = str_format("Course       : ", COLOR.YELLOW, 0);
  uart_puts(course);
  uart_puts(ACK.course);
  uart_puts("\n");

  // Print lecturer name (Mr. Linh T.D.)
  char *lecturer = str_format("Lecturer     : ", COLOR.YELLOW, 0);
  uart_puts(lecturer);
  uart_puts(ACK.lecturer);
  uart_puts("\n");

  // Print submitted by
  char *submitted_by = str_format("Submitted by : ", COLOR.YELLOW, 0);
  uart_puts(submitted_by);
  uart_puts(ACK.submitted_by);
  uart_puts("\n\n");

  // Print declaration
  uart_puts(ACK.declaration);
  uart_puts("\n");

  // Print OS logo
  char *os_name = str_format(OS_INF.ascii_art_name, COLOR.YELLOW, 0);
  uart_puts(os_name);
  uart_puts("\n");

  uart_puts("@2024. All rights reserved.\n\n");
}