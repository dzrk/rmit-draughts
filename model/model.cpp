#include "model.h"

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
//    diff = endy-starty
//    int direction = 1;
//    if playernum == player1{
//        direction = direction * -1;
//
//    char start_token = get_token(startx-1,starty-1);
//    if(start_token == X_TOKEN && playernum == players[0]){
//        // valid
//    }else if start_token == O_TOKEN && playernum == players[1]{
//        // valid
//    }else{
//        // invalid
//    }
//    if valid{
//        char end_token = get_token(endx-1, endy-1);
//        if(diff == 2 || diff = -2{
//            jump
//        }else if(diff == 1 || diff = -1){
//            normal move
//        }else{
//            invalid move
//        }
//    }
    // check valid token for playernum
    // check if move possible
    // if possible set current_player to next player if p[0] -> p[1] vice versa
    // else current_player attempts again
    
//    char start_token = get_token(startx-1,starty-1);
//    char end_token = get_token(endx-1, endy-1);
    BOARD_STATE[startx-1][starty-1] = EMPTY;
    BOARD_STATE[endx-1][endy-1] = P1;

    
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
char draughts::model::model:: cell_to_char(Cell v)
{
    switch (v)
    {
        case EMPTY:
            return BLANK;
        case P1:
            return X_TOKEN;
        case P2:
            return O_TOKEN;
        default:
            return '\0';
    }
}
