#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>
#include <algorithm>

#pragma once
const int BOARD_WIDTH = 8;
const int BOARD_WIDTH_MIN = 0;
const int BOARD_HEIGHT_MIN = 0;
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

struct Point
{
  int x;
  int y;    
};

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
            bool boundary_check(int,int);
            bool can_move(int,int,int,int); //  x1, y1, x2, y2 - checks specific move
            bool can_jump(int,int,int,int,int,int); // x1, y1, x2, y2 x3, y3 - checks specific jump
            char pid_to_token(int);
            void get_legal_moves(int,int);
            void check_moves(int,int); // runs can_move in every direction
            void check_jumps(int,int); // runs can_jump in every direction
            void actually_move(int,int,int,int,bool); // modifies the BOARD_STATE
            std::map<int, char> m_token; //pid, token
            Point midpoint(const Point&,const Point&);

        private:
            std::map<int, std::string> m_players; // pid, players
            std::map<int, int> m_scores; //pid, score
            char board[BOARD_HEIGHT][BOARD_WIDTH];
            std::vector<int> players;
            int current_player;
            std::vector<std::pair<int,int>> normal_moves; // moving one space
            std::vector<std::pair<int,int>> jump_moves; // moving two spaces
            char current_token;
        };
    }
}
