# rmit-draughts

**Team Members:**
- Jayden Joyce: s3543824
- Derrick Phung: s3546900

**Enable C++**
- source /opt/rh/devtoolset-6/enable

**Compile**
- g++ -Wall -pedantic -std=c++14 main_noncurses.cpp model/model.cpp nc_controller/command.cpp nc_controller/controller.cpp ncview/add_player_window.cpp ncview/game_window.cpp ncview/main_menu.cpp ncview/menu.cpp ncview/player_selection_window.cpp ncview/ui.cpp ncview/window.cpp -o draught
