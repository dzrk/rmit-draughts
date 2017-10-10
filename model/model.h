#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>

#pragma once
const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;
const char WHITE_EMPTY = 'w';
const char BLACK_EMPTY = 'b';

namespace draughts
{
    namespace model
    {
        class model
        {
            static std::unique_ptr<model> instance;

            model(void);
            bool player_exists(const std::string&);

            public:
            void start_game(int, int);
            char get_token(int,int);
            void make_move(int, int, int, int, int);

            void add_player(const std::string& );
            int get_player_score(int);
            int get_current_player(void);
            std::string get_player_name(int);
            std::map<int, std::string> get_player_list(void) const;
            int get_winner();
            int get_width();
            int get_height();
            static model * get_instance(void);
            static void delete_instance(void);
            virtual ~model(void);
            void legal_board(void);
            
        private:
            std::map<int, std::string> m_players; // pid, players
            std::map<int, int> m_scores; //pid, score
            char board[BOARD_WIDTH][BOARD_HEIGHT];
            int current_player;

        };
    }
}
