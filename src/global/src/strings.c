// #include "../headers/strings.h"
// #include <stdio.h>
// #include <string.h>
// #include "../../helper/formater.c"
// #include "../../helper/boxer.c"

// OsTrademark os_inf = {
//     .ascii_art_name =
//         "  ______ _______ ___   _     ______   ______  _____  ______ _     _ _______\n"
//         "   ____/ |______ |  \\  |     |_____] |_____/    |   |  ____ |_____|    |\n"
//         "  /_____ |______ |   \\_|     |_____] |     \\_ __|__ |_____| |     |    |\n",
//     .asii_art_logo =

//         "                                                         mrrm\n"
//         "                                                         rrrr\n"
//         "                                                         mrrrr\n"
//         "                                                        rrrrrm\n"
//         "                                                        mrrrrrr\n"
//         "                                                       mrrrrrrrr\n"
//         "                                                      rrrrrrrrrrr\n"
//         "                                                     rrrrrrrrrrrrrm\n"
//         "                         mrrr                      rrrrrrrrrrrrrrrrrr                      rrr\n"
//         "                         rrrrrr                  rrrrrrrrrrrrrrrrrrrrrr                 rrrrrrm\n"
//         "                           rrrrrrrrm       imrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrmm      mmrrrrrrrr\n"
//         "                            rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
//         "                             rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
//         "                              rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
//         "                              rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
//         "                               rrrrrrrrrrrrrrrrrrrrrr              rrrrrrrrrrrrrrrrrrrrrr\n"
//         "                               rrrrrrrrrrrrrrrrrm                      rrrrrrrrrrrrrrrrrr\n"
//         "                               rrrrrrrrrrrrrrr                           mrrrrrrrrrrrrrrr\n"
//         "                               rrrrrrrrrrrrrr                              rrrrrrrrrrrrrr\n"
//         "                              rrrrrrrrrrrrr                                 rrrrrrrrrrrrrm\n"
//         "                              rrrrrrrrrrrr                                    rrrrrrrrrrrr\n"
//         "                             rrrrrrrrrrrr                                      rrrrrrrrrrrr\n"
//         "                            rrrrrrrrrrrrr                                      rrrrrrrrrrrrr\n"
//         "                          mrrrrrrrrrrrrr                                        rrrrrrrrrrrrrm\n"
//         "                        rrrrrrrrrrrrrrrr                                        rrrrrrrrrrrrrrrr\n"
//         "                    rrrrrrrrrrrrrrrrrrrr                                        rrrrrrrrrrrrrrrrrrrm\n"
//         "                mrrrrrrrrrrrrrrrrrrrrrrr                                        rrrrrrrrrrrrrrrrrrrrrrrm\n"
//         "\n"
//         "\n"
//         "\n"
//         "                     rrrrrrrrrrrr   mrrrrrrrrrrrrr  rrrrm rrrrrrrrrrrr  rrrr      rrrrmrrrrrrrrrrrrr\n"
//         "                     rrrmrrrrrrrrr  mrrrrrrrrrrrrrr rrrrmrrrrrrrrrrrrm  rrrr      rrrrmrrrrrrrrrrrrr\n"
//         "                     rrrm     mrrri mrrrr      mrrr rrrrirrrrm          rrrmiiiiiirrrrr    mrrrr\n"
//         "                     rrrrrrrrrrrrrrrmrrrrrrrrrrrrrr rrrrmrrrrm     mrrm rrrrrrrrrrrrrrr    mrrrr\n"
//         "                     rrrm       rrrrmrrrrrrmrrrrrr  rrrrirrrrm     mrrm rrrr      rrrrr    rrrrr\n"
//         "                     rrrrrrrrrrrrrrrmrrrr      rrrr rrrrirrrrrrrrrrmrrm rrrr      rrrrr    mrrrr\n"
//         "                     rrrrrrrrrrrrrr mrrrr       rrrmrrrri  rrrrrrrrrrrm rrrm      rrrrm    mrrrm\n",
//     .version = "0.0.1",
//     .name = "Zen BrightOS Administrator Pro",
//     .id = "brightos",
//     .home_url = "TBA",
//     .support_url = "TBA",
//     .created_at = "2024-04-20",
//     .updated_at = "2024-04-20",
//     .author = {
//         .name = "Quoc Doan",
//         .username = "Mudoker",
//         .email = "huuquoc7603@gmail.com",
//         .sid = "S3927776",
//     },
//     .init = "BrightOS> ",
// };

// Acknowledgement ack = {
//     .school = "RMIT University",
//     .course = "EEET2490: Embedded System: OS and Interfacing",
//     .lecturer = "Mr Linh T.D.",
//     .submitted_by = "Quoc Doan",
//     .declaration = "I declare that in submitting all work for this assessment I have read, understood and agree to the content and expectations of the Assessment declaration.",
// };

// void OS_Greet()
// {
//     int color = 33;
//     char *color_string = "yellow";

//     format_and_print(os_inf.asii_art_logo, color_string, 0, 0);
//     printf("\n");

//     // OS Information
//     print_in_box("OS Information");
//     printf("\033[0;%dmID\033[0m           : %s\n", color, os_inf.id);
//     printf("\033[0;%dmOS Name\033[0m      : %s\n", color, os_inf.name);
//     printf("\033[0;%dmVersion\033[0m      : %s\n", color, os_inf.version);
//     printf("\033[0;%dmHome URL\033[0m     : %s\n", color, os_inf.home_url);
//     printf("\033[0;%dmSupport URL\033[0m  : %s\n", color, os_inf.support_url);
//     printf("\033[0;%dmCreated At\033[0m   : %s\n", color, os_inf.created_at);
//     printf("\033[0;%dmLast Updated\033[0m : %s\n", color, os_inf.updated_at);

//     printf("\n");

//     // Author Information
//     print_in_box("Author Information");
//     printf("\033[0;%dmName\033[0m     : %s\n", color, os_inf.author.name);
//     printf("\033[0;%dmUsername\033[0m : %s\n", color, os_inf.author.username);
//     printf("\033[0;%dmSID\033[0m      : %s\n", color, os_inf.author.sid);
//     printf("\033[0;%dmEmail\033[0m    : %s\n", color, os_inf.author.email);

//     printf("\n");

//     // Copyright
//     print_in_box("Acknowledgement");
//     printf("School of Science, Engineering and Technology\n\n");
//     printf("\033[0;%dmSchool\033[0m     : %s\n", color, ack.school);
//     printf("\033[0;%dmCourse\033[0m     : %s\n", color, ack.course);
//     printf("\033[0;%dmLecturer\033[0m   : %s\n", color, ack.lecturer);
//     printf("\033[0;%dmSubmitted by\033[0m: %s\n\n", color, ack.submitted_by);
//     printf("\033[3m%s\033[0m\n", ack.declaration);

//     printf("\n%s", os_inf.ascii_art_name);
//     printf("\n %s @2024. All rights reserved.\n\n", os_inf.author.username);

//     return;
// }