// rmit-draughts
// https://github.com/dzrk/rmit-draughts
// **Team Members:**
// - Jayden Joyce: s3543824
// - Derrick Phung: s3546900
#include "ncview/ui.h"
#include "nc_controller/controller.h"
#include "model/model.h"

int main(void)
{
    draughts::ncview::ui * view = draughts::ncview::ui::get_instance();
    atexit(draughts::ncview::ui::delete_instance);
    atexit(draughts::nc_controller::controller::delete_instance);
    atexit(draughts::model::model::delete_instance);
    view->main_menu();
}
