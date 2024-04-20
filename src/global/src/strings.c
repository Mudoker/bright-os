#include "../headers/strings.h"
#include <stdio.h>
#include <string.h>

OsTrademark os_inf = {
    .ascii_art_name =
        "  ______ _______ ___   _     ______   ______  _____  ______ _     _ _______\n"
        "   ____/ |______ |  \\  |     |_____] |_____/    |   |  ____ |_____|    |\n"
        "  /_____ |______ |   \\_|     |_____] |     \\_ __|__ |_____| |     |    |\n",
    .asii_art_logo =

        "                                                         mrrm\n"
        "                                                         rrrr\n"
        "                                                        mrrrr\n"
        "                                                        rrrrrm\n"
        "                                                        mrrrrrr\n"
        "                                                       mrrrrrrrr\n"
        "                                                      rrrrrrrrrrr\n"
        "                                                     rrrrrrrrrrrrrm\n"
        "                         mrrr                      rrrrrrrrrrrrrrrrrr                      rrr\n"
        "                         rrrrrr                  rrrrrrrrrrrrrrrrrrrrrr                 rrrrrrm\n"
        "                           rrrrrrrrm       imrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrmm      mmrrrrrrrr\n"
        "                            rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                             rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                              rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                              rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrrrrrrrrrr              rrrrrrrrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrrrrrm                      rrrrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrrr                           mrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrr                              rrrrrrrrrrrrrr\n"
        "                              rrrrrrrrrrrrr                                 rrrrrrrrrrrrrm\n"
        "                              rrrrrrrrrrrr                                    rrrrrrrrrrrr\n"
        "                             rrrrrrrrrrrr                                      rrrrrrrrrrrr\n"
        "                            rrrrrrrrrrrrr                                      rrrrrrrrrrrrr\n"
        "                          mrrrrrrrrrrrrr                                        rrrrrrrrrrrrrm\n"
        "                        rrrrrrrrrrrrrrrr                                        rrrrrrrrrrrrrrrr\n"
        "                    rrrrrrrrrrrrrrrrrrrr                                        rrrrrrrrrrrrrrrrrrrm\n"
        "                mrrrrrrrrrrrrrrrrrrrrrrr                                        rrrrrrrrrrrrrrrrrrrrrrrm\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "                     rrrrrrrrrrrr   mrrrrrrrrrrrrr  rrrrm rrrrrrrrrrrr  rrrr      rrrrmrrrrrrrrrrrrr\n"
        "                     rrrmrrrrrrrrr  mrrrrrrrrrrrrrr rrrrmrrrrrrrrrrrrm  rrrr      rrrrmrrrrrrrrrrrrr\n"
        "                     rrrm     mrrri mrrrr      mrrr rrrrirrrrm          rrrmiiiiiirrrrr    mrrrr\n"
        "                     rrrrrrrrrrrrrrrmrrrrrrrrrrrrrr rrrrmrrrrm     mrrm rrrrrrrrrrrrrrr    mrrrr\n"
        "                     rrrm       rrrrmrrrrrrmrrrrrr  rrrrirrrrm     mrrm rrrr      rrrrr    rrrrr\n"
        "                     rrrrrrrrrrrrrrrmrrrr      rrrr rrrrirrrrrrrrrrmrrm rrrr      rrrrr    mrrrr\n"
        "                     rrrrrrrrrrrrrr mrrrr       rrrmrrrri  rrrrrrrrrrrm rrrm      rrrrm    mrrrm\n",
    .version = "0.0.1",
    .name = "Zen BrightOS Administrator Pro",
    .id = "brightos",
    .home_url = "TBA",
    .support_url = "TBA",
    .created_at = "2024-04-20",
    .updated_at = "2024-04-20",
    .author = {
        .name = "Quoc Doan",
        .username = "Mudoker",
        .email = "huuquoc7603@gmail.com",
        .sid = "S3927776",
    },
};

void print_in_box(const char *text)
{
    int length = strlen(text);
    int width = length + 4; // Width of the box
    int i, j;

    // Print the top of the box
    for (i = 0; i < width; i++)
    {
        printf("-");
    }
    printf("\n");

    // Print the sides of the box with text in the middle
    printf("| %s |\n", text);

    // Print the bottom of the box
    for (i = 0; i < width; i++)
    {
        printf("-");
    }
    printf("\n");
}

int main()
{
    // OS Information
    printf("%s", os_inf.asii_art_logo);
    printf("\n");
    print_in_box("OS Information");
    printf("ID           : %s\n", os_inf.id);
    printf("OS Name      : %s\n", os_inf.name);
    printf("Version      : %s\n", os_inf.version);
    printf("Home URL     : %s\n", os_inf.home_url);
    printf("Support URL  : %s\n", os_inf.support_url);
    printf("Created At   : %s\n", os_inf.created_at);
    printf("Last Updated : %s\n", os_inf.updated_at);

    printf("\n");

    // Author Information
    print_in_box("Author Information");
    printf("Name     : %s\n", os_inf.author.name);
    printf("Username : %s\n", os_inf.author.username);
    printf("SID      : %s\n", os_inf.author.sid);
    printf("Email    : %s\n", os_inf.author.email);
}