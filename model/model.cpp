#include "model.h"
// source /opt/rh/devtoolset-6/enable
Cell side[BOARD_HEIGHT][BOARD_WIDTH] =
{
    { EMPTY, P1, EMPTY, EMPTY, EMPTY, P2, EMPTY, P2},
    { P1, EMPTY, P1, EMPTY, EMPTY, EMPTY, P2, EMPTY},
    { EMPTY, P1, EMPTY, EMPTY, EMPTY, P2, EMPTY, P2},
    { P1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, P2, EMPTY},
    { EMPTY, P1, EMPTY, EMPTY, EMPTY, P2, EMPTY, P2},
    { P1, EMPTY, P1, EMPTY, EMPTY, EMPTY, P2, EMPTY},
    { EMPTY, P1, EMPTY, EMPTY, EMPTY, P2, EMPTY, P2},
    { P1, EMPTY, P1, EMPTY, EMPTY, EMPTY, P2, EMPTY}
};
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


Point draughts::model::model::midpoint(const Point& a, const Point& b) {
    Point ret;
    ret.x = (a.x + b.x) / 2;
    ret.y = (a.y + b.y) / 2;
    return ret;
}
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
    m_token.insert(std::pair<int,char>(plr1, X_TOKEN));
    m_token.insert(std::pair<int,char>(plr2, O_TOKEN));


    

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
    int x_start = startx - 1;
    int y_start = starty - 1;
    int x_end = endx - 1;
    int y_end = endy - 1;
    std::cout << "player num: "<< playernum << std::endl;

    current_token = pid_to_token(playernum);        
    normal_moves.clear();
    jump_moves.clear();
    get_legal_moves(x_start, y_start);

    for(auto elem : normal_moves)
    {
       std::cout << "normal_moves: " << elem.first << " " << elem.second << "\n";
    }
    for(auto elem : jump_moves)
    {
       std::cout << "jump_moves: " << elem.first << " " << elem.second << "\n";
    }

    std::map<int,int>::iterator it;
    bool kill = false;
    bool moved = false;

    if (jump_moves.size() > 0)
    {
        it = jump_moves.find(x_end);
        if(it != jump_moves.end())
        {
            if(y_end == it->second)
            {
                kill = true;
                actually_move(x_start, y_start, x_end, y_end, kill);
                moved = true;
            }
        }
    }else if(normal_moves.size() > 0){
        it = normal_moves.find(x_end);
        if(it != normal_moves.end())
        {
            if(y_end == it->second)
            {
                actually_move(x_start, y_start, x_end, y_end, kill);
                moved = true;
            }
        }
    }else{
        std::cout << "invalid move" << std::endl;
    }
    if(kill == false && moved){
        if(current_player == players[0]){
            current_player = players[1];
            std::cout << "swapped " << std::endl;
            }else{
            current_player = players[0];
            std::cout << "swapped " << std::endl;

            }
    }


    
}
void draughts::model::model::actually_move(int x_start, int y_start, int x_end, int y_end, bool kill)
{
    Cell start_cell = BOARD_STATE[x_start][y_start];
    if(kill){
        Point start = { 
            x_start,
            y_start,
        };
        Point end = { 
            x_end,
            y_end,
        };
        Point mid = midpoint(start,end);
        BOARD_STATE[mid.x][mid.y] = EMPTY;
        BOARD_STATE[x_start][y_start] = EMPTY;
        BOARD_STATE[x_end][y_end] = start_cell;
    }else{
        BOARD_STATE[x_start][y_start] = EMPTY;
        BOARD_STATE[x_end][y_end] = start_cell;
    }
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
    char pos_start = get_token(x_start+1, y_start+1);
    char pos_end = get_token(x_end+1, y_end+1);

    if(boundary_check(x_end, y_end) == false){ // check if destination is on the board 
        return false;
        }
    if(pos_end != cell_to_char(EMPTY)){ // end destination already contains a piece - can jump?
        return false;
        }
    if(current_token == X_TOKEN){ // checks if chosen piece is the players piece 
        if(pos_start != cell_to_char(P1)){ // x pieces can only move down 
            return false;    
        }
        if(x_start > x_end)
            return false;
        return true; // legal move
    }else if(current_token == O_TOKEN){
        if(pos_start == P2) // o pieces can only move up
            return false; 
        if(x_start < x_end)
            return false;
        return true; // legal move
    }else{
        return false;
    }

} // needs else to remove warning

bool draughts::model::model::can_jump(int x_start, int y_start, int x_mid, int y_mid, int x_end, int y_end){
    char pos_start = get_token(x_start+1, y_start+1); // current player
    char pos_mid = get_token(x_mid+1, y_mid+1);  // enemy player
    char pos_end = get_token(x_end+1, y_end+1); // empty

    if(boundary_check(x_end, y_end) == false){ // check if destination is on the board 
        std::cout << "outside board" << x_end << ", "<< y_end<<std::endl;
        return false;
        }
    if(pos_end != cell_to_char(EMPTY)){
        std::cout << "cell not empty " << pos_end << std::endl;
        return false;   // end destination already contains a piece
        }
    if(current_token == X_TOKEN){
        if(pos_start != cell_to_char(P1)){ // token belongs to player
            std::cout << "not ur piece " << pos_start << std::endl;
            return false;
            }
        if(x_start > x_end){ // can only move down
            std::cout << "can only kill down " << std::endl;
            return false;
            }
        if(pos_mid != cell_to_char(P2) && pos_mid != cell_to_char(P2_KING)){ // must kill something
            std::cout << "NOTHING TO KILL " << pos_mid << std::endl;
            return false;
            }
        std::cout << "added jump " << x_end << ", " << y_end << std::endl;


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
    std::cout << "@@@@@@@@@@@@@@" << std::endl;

    if(can_move(x_start, y_start, x_up, y_up)){
        normal_moves.insert(std::pair<int,int>(x_up, y_up));        // 1,1
        std::cout << "added moves xup yup : " << x_up << " " << y_up << std::endl;
        }else{
        std::cout << "didnt add moves xup yup : " << x_up << " " << y_up << std::endl;
        std::cout << "start x,y: " << x_start;
        std::cout << ", " << y_start << std::endl;
        std::cout << "@@@@@@@@@@@@@@" << std::endl;


        }
    if(can_move(x_start, y_start, x_up, y_down)){
        normal_moves.insert(std::pair<int,int>(x_up, y_down));      // 1,-1
        std::cout << "added moves xup ydown: " << x_up << " " << y_down << std::endl;
                std::cout << "@@@@@@@@@@@@@@" << std::endl;

        }else{
        std::cout << "didnt add moves xup y_down : " << x_up << " " << y_down << std::endl;
        std::cout << "start x,y: " << x_start;
        std::cout << ", " << y_start << std::endl;
                std::cout << "@@@@@@@@@@@@@@" << std::endl;

        }
    if(can_move(x_start, y_start, x_down, y_up)){
        normal_moves.insert(std::pair<int,int>(x_down, y_up));      // -1,1
        std::cout << "added moves: " << x_down << " " << y_up << std::endl;
        }else{        
        std::cout << "didnt add moves x_down y_up : " << x_down << " " << y_up << std::endl;
        std::cout << "start x,y: " << x_start;
        std::cout << ", " << y_start << std::endl;
                std::cout << "@@@@@@@@@@@@@@" << std::endl;

        }
    if(can_move(x_start, y_start, x_down, y_down)){
        normal_moves.insert(std::pair<int,int>(x_down, y_down));    // -1,-1
        std::cout << "added moves: " << x_down << " " << y_down << std::endl;
        }else{
        std::cout << "didnt add moves x_down y_down : " << x_down << " " << y_down << std::endl;
        std::cout << "start x,y: " << x_start;
        std::cout << ", " << y_start << std::endl;
                std::cout << "@@@@@@@@@@@@@@" << std::endl;

        }
}

void draughts::model::model::get_legal_moves(int x_start, int y_start){
    char KING;
    if(current_token == X_TOKEN){
        KING = P1_KING;
    }else{
        KING = P2_KING;
    }
    check_jumps(x_start, y_start);
    std::cout << "jump size " << jump_moves.size() << std::endl;

    //check for jump first
    if(jump_moves.size() == 0){
        check_moves(x_start, y_start);
    }


}
