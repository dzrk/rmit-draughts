// rmit-draughts
// https://github.com/dzrk/rmit-draughts
// **Team Members:**
// - Jayden Joyce: s3543824
// - Derrick Phung: s3546900
#include "menu.h"

#pragma once

namespace draughts
{
    namespace ncview
    {
        class main_menu : public menu
        {
            static const std::vector<std::string> strings;
            public:
                main_menu(void);
                virtual ~main_menu(void);
        };
    }
}
