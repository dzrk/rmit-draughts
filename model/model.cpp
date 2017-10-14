#include "model.h"
//source /opt/rh/devtoolset-6/enable
Cell BOARD_STATE[BOARD_HEIGHT][BOARD_WIDTH] =
{
    { EMPTY, P1, EMPTY, P1, EMPTY, P1, EMPTY, P1},
    { P1, EMPTY, P1, EMPTY, P1, EMPTY, P1, EMPTY},
    { EMPTY, P1, EMPTY, P1, EMPTY, P1, EMPTY, P1},
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    { P2, EMPTY, P2, EMPTY, P2, EMPTY, P2, EMPTY},
    { EMPTY, P2, EMPTY, P2, EMPTY, P2, EMPTY, P2},
    { P2, EMPTY, P2, EMPTY, P2, EMPTY, P2, EMPTY}
};

std::unique_ptr<draughts::model::model> draughts::model::model::instance =
nullptr;

draughts::model::model::model(void) 
{
}

draughts::model::model * draughts::model::model::get_instance(void)
{
    if(instance == nullptr)
    {
        instance = std::unique_ptr<model>(new model);   
    }
    return instance.get();    
}

int draughts::model::model::get_player_score(int playernum)
{
    std::map<int, int>::iterator it;
    
    it = m_scores.find(playernum);
    if(it != m_scores.end())
        return it->second;
    return 0;
}

void draughts::model::model::start_game(int plr1, int plr2)
{
    players.push_back(plr1);
    players.push_back(plr2);
    current_player = players[0];
    m_token.insert(std::pair<int,char>(plr1,X_TOKEN));
    m_token.insert(std::pair<int,char>(plr2,O_TOKEN));

    //intialise board
    for (int x = 0; x < BOARD_HEIGHT; x++)
    {
        for (int y = 0; y < BOARD_WIDTH; y++)
        {
            if(BOARD_STATE[x][y] == EMPTY){
                Cell cell = EMPTY;
                std::cout << cell_to_char(cell);

            }else if(BOARD_STATE[x][y] == P1){
                Cell cell = P1;
                std::cout << cell_to_char(cell);

            }else if(BOARD_STATE[x][y] == P2){
                Cell cell = P2;

                std::cout << cell_to_char(cell);

            }
        }
        std::cout << std::endl;
    }

    

}

int draughts::model::model::get_winner()
{
    return EOF;
}

std::string draughts::model::model::get_player_name(int id)
{
    std::map<int, std::string>::iterator it;
    
    it = m_players.find(id);
    if(it != m_players.end())
        return it->second;
    return "";
}

char draughts::model::model::get_token(int x ,int y)
{
    int row = x - 1;
    int column = y - 1;
    if(BOARD_STATE[row][column] == EMPTY){
        Cell cell = EMPTY;
        return cell_to_char(cell);
    }else if(BOARD_STATE[row][column] == P1){
        Cell cell = P1;
        return cell_to_char(cell);
    }else if(BOARD_STATE[row][column] == P2){
        Cell cell = P2;
        return cell_to_char(cell);
        
    }
    return '\0';
}

void draughts::model::model::make_move(int playernum,
        int startx, int starty, int endx, int endy)
{
    current_token = pid_to_token(playernum);
    normal_moves.clear();
    jump_moves.clear();
    get_legal_moves(startx, starty);
    std::map<int,int>::iterator it;



    if (jump_moves.size() > 0){
        it = jump_moves.find(endx);
        if(it != jump_moves.end())
            it->second;
        //actually move
    }else if(normal_moves.size() > 0){

    }else{

    }


    
}
void draughts::model::model::actually_move(int x_start, int y_start, int x_end, int y_end){

}

void draughts::model::model::add_player(const std::string& p)
{
    int map_size = m_players.size();
    m_players.insert(std::pair<int,std::string>(map_size,p));
    
}

bool draughts::model::model::player_exists(const std::string& pname)
{
    std::map<int, std::string>::iterator it;
    for(it = m_players.begin(); it != m_players.end(); it++){
        if(it->second == pname){ //returns value
            return true;
        }
    }
    return false;
}

int draughts::model::model::get_current_player(void)
{
    return current_player;
}

std::map<int, std::string> draughts::model::model::get_player_list(void) 
    const
{
//    std::map<int, std::string> nameslist;
//    return nameslist;
    return m_players;
}

void draughts::model::model::delete_instance(void)
{
    instance.reset(nullptr);
}


int draughts::model::model::get_width()
{
    return BOARD_WIDTH;
}

int draughts::model::model::get_height()
{
    return BOARD_HEIGHT;
}

draughts::model::model::~model(void)
{
}

void draughts::model::model::legal_board(void)
{
    for (int x = 0; x < BOARD_HEIGHT; x++)
    {
        for (int y = 0; y < BOARD_WIDTH; y++)
        {
            if (((x+y) % 2) == 0) {
                board[x][y] = WHITE;

            }
            else
            {
                board[x][y] = BLACK;
            }
        }
    }
}

char draughts::model::model::cell_to_char(Cell v)
{
    switch (v)
    {
        case EMPTY:
            return BLANK;
        case P1:
            return X_TOKEN;
        case P2:
            return O_TOKEN;
        case P1_KING:
            return X_KING;
        case P2_KING:
            return O_KING;
        default:
            return '\0';
    }
}

bool draughts::model::model::boundary_check(int x_coord, int y_coord)
{
    if(x_coord > BOARD_WIDTH || x_coord < BOARD_WIDTH_MIN)
    {
        return false;
    }
    
    if(y_coord > BOARD_HEIGHT || y_coord < BOARD_HEIGHT_MIN)
    {
        return false;
    }
    
    return true;
}

char draughts::model::model::pid_to_token(int playernum)
{
    std::map<int,char>::iterator it;
    it = m_token.find(playernum);
    if (it != m_token.end())
        return it->second;
    return '\0';

}

bool draughts::model::model::can_move(int x_start, int y_start, int x_end, int y_end)
{
    char pos_start = get_token(x_start, y_start);
    char pos_end = get_token(x_end, y_end);

    if(boundary_check(x_end, y_end) == false) // check if destination is on the board 
        return false;
    if(pos_end != EMPTY) // end destination already contains a piece - can jump?
        return false;
    if(current_token == X_TOKEN){ // checks if chosen piece is the players piece 
        if(pos_start == P1 && x_end > x_start){ // x pieces can only move down
            return false;    
        }
        return true; // legal move
    }else if(current_token == O_TOKEN){
        if(pos_start == P2 && x_start > x_end) // o pieces can only move up
            return false; 
        return true; // legal move
    }

} // needs else to remove warning

bool draughts::model::model::can_jump(int x_start, int y_start, int x_mid, int y_mid, int x_end, int y_end){
    char pos_start = get_token(x_start, y_start);
    char pos_mid = get_token(x_mid, y_mid);
    char pos_end = get_token(x_end, y_end);

    if(pos_end != EMPTY)
        return false;   // end destination already contains a piece

    if(current_token == X_TOKEN){
        if(pos_start == P1 && x_end > x_start) // x can only move down
            return false;
        if(pos_mid != P2 && pos_mid != P2_KING)
            return false;
        return true;
    }else{
        if(pos_start == P2 && x_start > x_end) // o can only move up
            return false;
        if(pos_mid != P1 && pos_mid != P1_KING)
            return false;
        return true;
    }

}

void draughts::model::model::check_jumps(int x_start, int y_start){
    int x_up_up = x_start + 2;
    int x_down_down = x_start - 2;
    int y_up_up = y_start + 2;
    int y_down_down = y_start - 2;
    int x_up = x_start + 1;
    int x_down = x_start - 1;
    int y_up = y_start + 1;
    int y_down = y_start - 1;

    if(can_jump(x_start, y_start, x_up, y_up, x_up_up, y_up_up))
        jump_moves.insert(std::pair<int,int>(x_up_up, y_up_up));          // 2,2
    if(can_jump(x_start, y_start, x_up, y_down, x_up_up, y_down_down))
        jump_moves.insert(std::pair<int,int>(x_up_up, y_down_down));           // 2,-2
    if(can_jump(x_start, y_start, x_down, y_up, x_down_down, y_up_up))
        jump_moves.insert(std::pair<int,int>(x_down_down, y_up_up));      // -2,2
    if(can_jump(x_start, y_start, x_down, y_down, x_down_down, y_down_down))
        jump_moves.insert(std::pair<int,int>(x_down_down, y_down_down));  // -2,-2
}

void draughts::model::model::check_moves(int x_start, int y_start){
    int x_up = x_start + 1;
    int x_down = x_start - 1;
    int y_up = y_start + 1;
    int y_down = y_start - 1;

    if(can_move(x_start, y_start, x_up, y_up))
        normal_moves.insert(std::pair<int,int>(x_up, y_up));        // 1,1
    if(can_move(x_start, y_start, x_up, y_down))
        normal_moves.insert(std::pair<int,int>(x_up, y_down));      // 1,-1
    if(can_move(x_start, y_start, x_down, y_up))
        normal_moves.insert(std::pair<int,int>(x_down, y_up));      // -1,1
    if(can_move(x_start, y_start, x_down, y_down))
        normal_moves.insert(std::pair<int,int>(x_down, y_down));    // -1,-1
}

void draughts::model::model::get_legal_moves(int x_start, int y_start){
    char KING;
    if(current_token == X_TOKEN){
        KING = P1_KING;
    }else{
        KING = P2_KING;
    }
    check_jumps(x_start, y_start);
    //check for jump first
    if(jump_moves.size() == 0){
        check_moves(x_start, y_start);
    }
    

}