// rmit-draughts
// https://github.com/dzrk/rmit-draughts
// **Team Members:**
// - Jayden Joyce: s3543824
// - Derrick Phung: s3546900
#include "window.h"
#pragma once
namespace draughts
{
    namespace ncview
    {
        class add_player_window : public window
        {
            public:
            virtual void activate(void) override;
            virtual ~add_player_window(void){}
        };
    }
}
