#include "./global.h"

OsTrademark OS_INF = {
    .ascii_art_name = "  ______ _______ ___   _     ______   ______  _____  "
                      "______ _     _ _______\n"
                      "   ____/ |______ |  \\  |     |_____] |_____/    |   |  "
                      "____ |_____|    |\n"
                      "  /_____ |______ |   \\_|     |_____] |     \\_ __|__ "
                      "|_____| |     |    |\n",
    .ascii_art_logo =

        "                                                         mrrm\n"
        "                                                         rrrr\n"
        "                                                         mrrrr\n"
        "                                                        rrrrrm\n"
        "                                                        mrrrrrr\n"
        "                                                       mrrrrrrrr\n"
        "                                                      rrrrrrrrrrr\n"
        "                                                     rrrrrrrrrrrrrm\n"
        "                         mrrr                      rrrrrrrrrrrrrrrrrr "
        "                     rrr\n"
        "                         rrrrrr                  "
        "rrrrrrrrrrrrrrrrrrrrrr                 rrrrrrm\n"
        "                           rrrrrrrrm       "
        "imrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrmm      mmrrrrrrrr\n"
        "                            "
        "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                             "
        "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                              "
        "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                              "
        "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrrrrrrrrrr              "
        "rrrrrrrrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrrrrrm                     "
        " rrrrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrrr                        "
        "   mrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrr                         "
        "     rrrrrrrrrrrrrr\n"
        "                              rrrrrrrrrrrrr                           "
        "      rrrrrrrrrrrrrm\n"
        "                              rrrrrrrrrrrr                            "
        "        rrrrrrrrrrrr\n"
        "                             rrrrrrrrrrrr                             "
        "         rrrrrrrrrrrr\n"
        "                            rrrrrrrrrrrrr                             "
        "         rrrrrrrrrrrrr\n"
        "                          mrrrrrrrrrrrrr                              "
        "          rrrrrrrrrrrrrm\n"
        "                        rrrrrrrrrrrrrrrr                              "
        "          rrrrrrrrrrrrrrrr\n"
        "                    rrrrrrrrrrrrrrrrrrrr                              "
        "          rrrrrrrrrrrrrrrrrrrm\n"
        "                mrrrrrrrrrrrrrrrrrrrrrrr                              "
        "          rrrrrrrrrrrrrrrrrrrrrrrm\n"
        "\n"
        "\n"
        "\n"
        "                     rrrrrrrrrrrr   mrrrrrrrrrrrrr  rrrrm "
        "rrrrrrrrrrrr  rrrr      rrrrmrrrrrrrrrrrrr\n"
        "                     rrrmrrrrrrrrr  mrrrrrrrrrrrrrr "
        "rrrrmrrrrrrrrrrrrm  rrrr      rrrrmrrrrrrrrrrrrr\n"
        "                     rrrm     mrrri mrrrr      mrrr rrrrirrrrm        "
        "  rrrmiiiiiirrrrr    mrrrr\n"
        "                     rrrrrrrrrrrrrrrmrrrrrrrrrrrrrr rrrrmrrrrm     "
        "mrrm rrrrrrrrrrrrrrr    mrrrr\n"
        "                     rrrm       rrrrmrrrrrrmrrrrrr  rrrrirrrrm     "
        "mrrm rrrr      rrrrr    rrrrr\n"
        "                     rrrrrrrrrrrrrrrmrrrr      rrrr "
        "rrrrirrrrrrrrrrmrrm rrrr      rrrrr    mrrrr\n"
        "                     rrrrrrrrrrrrrr mrrrr       rrrmrrrri  "
        "rrrrrrrrrrrm rrrm      rrrrm    mrrrm\n",
    .version = "0.0.1",
    .name = "Zen BrightOS Administrator Pro",
    .id = "brightos",
    .home_url = "TBA",
    .support_url = "TBA",
    .created_at = "2024-04-20",
    .updated_at = "2024-04-20",
    .author =
        {
            .name = "Quoc Doan",
            .username = "Mudoker",
            .email = "huuquoc7603@gmail.com",
            .sid = "S3927776",
        },
    .init = "BrightOS> ",
};

Acknowledgement ACK = {
    .school = "RMIT University",
    .course = "EEET2490: Embedded System: OS and Interfacing",
    .lecturer = "Mr Linh T.D.",
    .submitted_by = "Quoc Doan",
    .declaration = "I declare that in submitting all work for this assessment "
                   "I have read, understood and agree to the content and "
                   "expectations of the Assessment declaration.",
};

Color COLOR = {.RED = "\033[0;31m",
               .GREEN = "\033[0;32m",
               .YELLOW = "\033[0;33m",
               .BLUE = "\033[0;34m",
               .PURPLE = "\033[0;35m",
               .CYAN = "\033[0;36m",
               .WHITE = "\033[0m",
               .BLACK = "\033[0;30m",
               .RED_BG = "\033[41m",
               .GREEN_BG = "\033[42m",
               .YELLOW_BG = "\033[43m",
               .BLUE_BG = "\033[44m",
               .PURPLE_BG = "\033[45m",
               .CYAN_BG = "\033[46m",
               .WHITE_BG = "\033[47m",
               .BLACK_BG = "\033[40m",
               .RESET = "\x1b[49m"};

Styler STYLER = {
    .BOLD_ON = "\033[1m",
    .ITALIC_ON = "\033[3m",
    .UNDERLINE_ON = "\033[4m",
    .BOLD_OFF = "\033[22m",
    .ITALIC_OFF = "\033[23m",
    .UNDERLINE_OFF = "\033[24m",
};

OsConfig OS_CONFIG = {.PRIMARY_COLOR = "\033[0;33m",
                      .SECONDARY_COLOR = "\033[0m",
                      // reset background color
                      .BACKGROUND_COLOR = "\x1b[49m",
                      .SUCCESS = "\033[0;32m",
                      .ERROR = "\033[0;31m",
                      .THEME = (char *)0};

BaudRateConfig BAUD_RATE_CONFIG = {.ibrd = 26, .fbrd = 3};

int DATA_BITS_CONFIG = 8;
int IS_REINIT_UART = 0;
int STOP_BIT_CONFIG = 1;
char *PARITY_CONFIG = "none";
char *HANDSHAKE_CONFIG = "RTS/CTS";
