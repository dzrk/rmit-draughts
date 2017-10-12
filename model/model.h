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
const char WHITE = 'w';
const char BLACK = 'b';

const char X_TOKEN = 'x'; // player 1 is X
const char O_TOKEN = 'o'; // player 2 is O
const char X_KING = 'X';
const char O_KING = 'O';
const char BLANK = ' ';

typedef enum cell
{
    EMPTY,
    P1,
    P2,
    P1_KING,
    P2_KING
} Cell;


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
            char cell_to_char(Cell v);
            
        private:
            std::map<int, std::string> m_players; // pid, players
            std::map<int, int> m_scores; //pid, score
            char board[BOARD_HEIGHT][BOARD_WIDTH];
            int current_player;
            std::vector<int> players;

        };
    }
}
