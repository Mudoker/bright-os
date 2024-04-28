#include "./global.h"

// OS trademark structure
Information OS_INFO = {
    .ASCII_ART_LOGO_TEXT =
        "  ______ _______ ___   _     ______   ______  _____  "
        "______ _     _ _______\n"
        "   ____/ |______ |  \\  |     |_____] |_____/    |   |  "
        "____ |_____|    |\n"
        "  /_____ |______ |   \\_|     |_____] |     \\_ __|__ "
        "|_____| |     |    |\n",
    .ASCII_ART_LOGO =

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
    .OS_VERSION = "0.0.1",
    .OS_NAME = "BrightOS Administrator Pro",
    .OS_ID = "brightos",
    .CREATED_AT = "2024-04-20",
    .UPDATED_AT = "2024-04-28",

    // Prompt text
    .PROMPT = "BrightOS> ",

    // Author
    .AUTHOR_NAME = "Quoc Doan",
    .AUTHOR_USERNAME = "Mudoker",
    .AUTHOR_EMAIL = "huuquoc7603@gmail.com",
    .AUTHOR_SID = "S3927776",
    .AUTHOR_GITHUB_URL = "https://github.com/Mudoker",

    // Acknowledgement
    .ACK_SCHOOL = "RMIT University",
    .ACK_COURSE = "EEET2490: Embedded System: OS and Interfacing",
    .ACK_LECTURER = "Mr Linh T.D.",
    .ACK_SUBMITTED_BY = "Quoc Doan",
    .ACK_DECLARATION =
        "I declare that in submitting all work for this assessment "
        "I have read, understood and agree to the content and "
        "expectations of the Assessment declaration.",
};

// Color configuration
Color COLOR = {
    .RED = "\033[0;31m",
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
    .CLEAR = "\x1b[49m",
};

// BrightOS theme configuration
Theme THEME = {
    .PRIMARY_COLOR = "\033[0;33m",
    .SECONDARY_COLOR = "\033[0m",
    .BACKGROUND_COLOR = "\x1b[49m",
    .SUCCESS_COLOR = "\033[0;32m",
    .ERROR_COLOR = "\033[0;31m",
};

// 115200 baud rate configuration for UART
BaudRateConfig BAUD_RATE_CONFIG = {
    .ibrd = 26,
    .fbrd = 3,
};

// State of the UART
int IS_REINIT_UART = 0;   // 0: Not reinit, 1: Reinit
int DATA_BITS_CONFIG = 8; // Data bits configuration (Default: 8 bits)
int STOP_BIT_CONFIG = 1;  // Stop bit configuration (Default: 1 bit)
int PARITY_CONFIG = 0;    // Parity configuration (Default: None)
int HANDSHAKE_CONFIG = 0; // Handshake configuration (Default: None)
