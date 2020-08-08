
/******************************************************************************
KALAH GAME IMPLEMENTATION USING MINMAXAB AND ALPHABETASEARCH ALGORITHMS
*******************************************************************************/


#include<ctime>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include<cstdlib>

using namespace std;

int total_nodes,expanded_node_count,game_path_length;
const int SIZE = 6;

class Kalah
{
    public:
    int Player_A[SIZE],
        Player_B[SIZE],
        store_A,
        store_B,
        slots,
        maxWinNumber;

    int *pointer;

    Kalah();
    Kalah(Kalah *);
    void display();
    void operator=(Kalah);
    char move_decider(int, char);
    char move_generator_A(int);
    char move_generator_B(int);
    char result();

};

/******************************************************************************
Kalah(): A default constructor that initializes all the data members of the
         Kalah Class.
         Each pit of Player A and Player B are initialized to having 6 stones
         stores of both players initialized to 0
         max number of stones that a person needs to be considered as having
         a winning chance is assigned to 36
parameters used: no
returns : constructor does not have a return type.
*******************************************************************************/

Kalah::Kalah()
{
    for(int i = 0 ; i < SIZE; i++)
    {
        Player_A[i] = 6;
        Player_B[i] = 6;
    }

    store_A = store_B = 0;
    slots = 5;

    pointer = NULL;
    maxWinNumber = 36;
}


/******************************************************************************
Kalah(): A copy constructor that is used to initialize an object of class Kalah
         with another object. Copies the kalah value from one object to another
parameters used: no
returns : constructor does not have a return type.
*******************************************************************************/

Kalah::Kalah(Kalah *b)
{
    for(int i = 0; i < SIZE; i++)
    {
        this->Player_A[i] = b->Player_A[i];
        this->Player_B[i] = b->Player_B[i];
    }

    this->store_A = b->store_A;
    this->store_B = b->store_B;
}

/******************************************************************************
dislay(): This function displays the Kalah board
parameters used: No parameters used
returns : Returns no values
*******************************************************************************/

void Kalah::display()
{
    cout << endl;
    cout << "\t\tPLAYER A";
    cout << endl << endl;
    cout << " \t | ";

    for(int i = 0 ; i < SIZE; i++)
        cout  << i << setw(2) << "|" << " ";

    cout << "--------------> Pit Numbers of A" << endl;
    cout << "\t=========================";
    cout << endl;
    cout << "\t" << "|";
    cout << setw(2);


    for(int i = (SIZE - 1) ; i >= 0 ; i--)
        cout << Player_A[i] << setw(2) << "|" << " ";

    cout << endl;
    cout << "\t=========================";

    cout << endl;
    cout << "store_A" << "\t\t\t\t   store_B" <<endl;
    cout << "------"  << "\t\t\t\t   ------";
    cout << endl;
    cout <<"|" << setw(3) << store_A << " |"; // Fourth Line
    cout <<"\t\t\t\t   |" << setw(3) << store_B << " |" << endl;
    cout << "------"  << "\t\t\t\t   ------";
    cout << endl;
    cout << "\t=========================";
    cout << endl;
    cout << "\t" << "|";
    cout << setw(2);

    for(int i = 0 ; i < SIZE; i++)
        cout << Player_B[i] << setw(2) << "|" << " ";

    cout << endl;
    cout << "\t=========================";
    cout << endl;
    cout << " \t | ";

     for(int i = 0 ; i < SIZE; i++)
        cout  << i << setw(2) << "|" << " ";

    cout << "--------------> Pit Numbers of B";
    cout << endl << endl;
    cout << "\t\tPLAYER B";
    cout << endl << endl << endl << endl;
}

/******************************************************************************
operater=(Kalah k): This is an operator overloading function that overloads the '='
parameters used: Object of type Kalah
returns : Returns no values
*******************************************************************************/

void Kalah::operator=(Kalah k)
{
    for(int i = 0; i < SIZE; i++)
    {
        Player_A[i] = k.Player_A[i];
        Player_B[i] = k.Player_B[i];

    }

    store_A = k.store_A;
    store_B = k.store_B;
    slots = 5;
    pointer = NULL;
    maxWinNumber = 36;

}

char Kalah::move_decider(int hole_num,char player)
{
    if(player == 'A')
        return (move_generator_A(hole_num));
    else
        return (move_generator_B(hole_num));
}


/******************************************************************************
move_generator_A(): This function helps generate moves for Player A
                    If last stone lands in Player A's store, Player A gets another
                    chance. If player A's stone lands in an empty hole in Player A's
                    holes, player A captures all player B's stone from the opposite
                    hole. If the above two special scenarios are not encountered,
                    the moves are normal.
parameters used: Hole number from which the player should start playing
returns : Returns the next player that gets a chance after A's move.
          In most cases, B gets a turn. When A's stone lands in its store, A
          is returned, meaning, A gets an extra move
*******************************************************************************/

char Kalah::move_generator_A(int hole_num)
{
    int current_Position = hole_num;
    pointer = Player_A;

    int stoneCount = pointer[current_Position];

    pointer[current_Position] = 0;
    int opPosition, opStones;

    current_Position++;

    while(stoneCount > 0)
    {
        //last stone lands in Player A's store
        if(stoneCount >= 1 && current_Position == 6 )
        {
            stoneCount--;
            store_A ++;

            if(stoneCount == 0)
                return 'A'; // giving A another chance as last stone falls in A's store
        }

        else if(current_Position >= 0 && current_Position <= 5)
        {
            if(stoneCount == 1)
            {
                stoneCount--;

                opPosition = slots - current_Position;

                if(pointer[current_Position] == 0 && Player_B[opPosition] > 0)
                {
                    pointer = Player_B;
                    opStones = pointer[opPosition];
                    pointer[opPosition] = 0;

                    store_A += opStones + 1;

                    if(stoneCount == 0)
                        return 'B';
                }

                else
                {
                    pointer[current_Position]++;

                    if(stoneCount == 0)
                        return 'B';
                }
            }

            else if(stoneCount > 1)
            {
                stoneCount--;

                pointer[current_Position]++;
            }
        }

        else if(current_Position > 6 && current_Position <= 12)
        {
            pointer = Player_B;
            stoneCount--;

            pointer[current_Position-7]++;

            if(stoneCount == 0)
                return 'B';
        }

        //skip Player B's store
        else if(current_Position >= 12)
        {
            current_Position = -1;
            pointer = Player_A;
        }

        current_Position++;
    }
    return 'B';
}

/******************************************************************************
move_generator_B(): This function helps generate moves for Player B
                    If last stone lands in Player B's store, Player B gets another
                    chance. If player B's stone lands in an empty hole in Player B's
                    holes, player B captures all player A's stone from the opposite
                    hole. If the above two special scenarios are not encountered,
                    the moves are normal.
parameters used: Hole number from which the player should start playing
returns : Returns the next player that gets a chance after B's move.
          In most cases, A gets a turn. When B's stone lands in its store, B
          is returned, meaning, B gets an extra move
*******************************************************************************/
char Kalah::move_generator_B(int hole_num)
{
    int current_Position = hole_num;
    pointer = Player_B;

    int stoneCount = pointer[current_Position];

    pointer[current_Position] = 0;
    int opPosition, opStones;

    current_Position++;

    while(stoneCount > 0)
    {
        //last stone lands in Player B's store
        if(stoneCount >= 1 && current_Position == 6)
        {
            stoneCount--;
            store_B++;

            if(stoneCount == 0)
                return 'B'; // giving B another chance as last stone falls in B's store
        }

        else if(current_Position >= 0 && current_Position <= 5)
        {
            if(stoneCount == 1)
            {
                stoneCount--;

                opPosition = slots - current_Position;

                if(pointer[current_Position] == 0)
                {
                    pointer = Player_A;
                    opStones = pointer[opPosition];
                    pointer[opPosition] = 0;

                    store_B += opStones + 1;

                    if(stoneCount == 0)
                        return 'A';
                }

                else
                {
                    pointer[current_Position]++;

                    if(stoneCount == 0)
                        return 'A';
                }
            }

            else if(stoneCount > 1)
            {
                stoneCount--;

                pointer[current_Position]++;
            }
        }

        else if(current_Position > 6 && current_Position <= 12)
        {
            pointer = Player_A;
            stoneCount--;

            pointer[current_Position-7]++;

            if(stoneCount == 0)
                return 'A';
        }

        else if(current_Position >= 12)
        {
            current_Position = -1;
            pointer = Player_B;
        }

        current_Position++;
    }
    return 'A';
}


/******************************************************************************
result(): This function checks the result of the game. If A has more than 36
          stones, A wins. If B has more than 36 stones, B wins.
parameters used: No parameters
returns : Returns A if Player A wins, B if player B wins, N if no win yet.
*******************************************************************************/

char Kalah::result()
{
    int empty_pits_A = 0,
        empty_pits_B = 0;

    for(int i = 0; i < SIZE; i++)
    {
        if(Player_A[i]==0)
            empty_pits_A++;

        if(Player_B[i]==0)
            empty_pits_B++;
    }

    if(empty_pits_A == 6)
    {
        for(int i = 0 ; i < SIZE; i++)
        {
            store_B += Player_B[i];
            Player_B[i] = 0;
        }

        cout << "Player A ran out of all the stones! All the pits in A are empty! " << endl;
    }

    if( empty_pits_B == 6)
    {
        for(int i = 0 ; i < SIZE ; i++)
        {
            store_A += Player_A[i];
            Player_A[i] = 0;
        }

        cout << "Player B ran out of all the stones! All the pits in B are empty! " << endl;
    }

    //if Player A has more than 36 stones, Player A wins
    if(store_A > maxWinNumber)
        return 'A';

    //if Player B has more than 36 stones, Player B wins
    else if(store_B > maxWinNumber)
        return 'B';

    else
        return 'N';
}




class KalahFlow
{

public:

    char player;
    Kalah current_status;
    int heuristic;
    KalahFlow * successors[SIZE];
    int successor_count;

    KalahFlow(char);
    void current_player_status(Kalah);
    bool is_deep_enough(int, int);
    void generate_successors();
    int myEvaluationFunction1();
    int myEvaluationFunction2();
    int myEvaluationFunction3();
    int myEvaluationFunction4();

};

/******************************************************************************
KalahFlow(): A parameterized constructor that is used to initialize an object of class
             KalahFlow.
parameters used: player
returns : constructor does not have a return type.
*******************************************************************************/

KalahFlow::KalahFlow(char player)
{
    this->player = player;
    heuristic = -2000;
    successor_count = 0;

    for(int i = 0; i < SIZE; i++)
        successors[i] = NULL;
}

/******************************************************************************
current_player_status(): copies the current status of the player into the current_status
object of type Kalah
parameters used: Kalah k
returns : returns nothing
*******************************************************************************/

void KalahFlow::current_player_status(Kalah k)
{
    for(int i = 0; i < SIZE; i++)
    {
        this->current_status.Player_A[i] = k.Player_A[i];
        this->current_status.Player_B[i] = k.Player_B[i];
    }

    this->current_status.store_A = k.store_A;
    this->current_status.store_B = k.store_B;
}

/******************************************************************************
is_deep_enough(): This function checks if the depth is 2 or 4, which gives true for
                  is_deep_enough for the algorithms. If it is not deep enough,
                  we generate one more ply of the tree by calling the generate_successors()
                  function
parameters used: the current depth passed by the functions, the selected maximum depth that the
                 ply can be generated up to
returns : If the depth is greater than or equal to the selected depth, the function returns
          true. Otherwise, false is returned
*******************************************************************************/

bool KalahFlow::is_deep_enough(int depth, int selected)
{
    if(heuristic != -2000)
        return heuristic;

    if(depth >= selected || current_status.result() != 'N' )
        return true;

    else
    {
        expanded_node_count++;
        generate_successors();
        return false;
    }
}

/******************************************************************************
generate_successors(): generates successors(child node) when the deep enough function
                       is satisfied to evaluate the future moves of the opponent based on
                       the present state of the board. This root node has child branches
                       which ends in the heuristic value of the end leaf node. Here the leaf
                       node is the value of number of stones in the pit at a given board state.
parameters used: no parameters used
returns : returns nothing
*******************************************************************************/

void KalahFlow::generate_successors()
{
    char player_temp;

    if(player == 'A')
        player_temp = 'B';

    else
        player_temp = 'A';

    for(int i = 0; i < SIZE; i++)
    {
        successor_count++;

        successors[i] = new KalahFlow(player_temp);

        if(current_status.Player_A[i]!=0 && player == 'A')
            successors[i]->current_status = current_status;

        else if(current_status.Player_B[i]!=0 && player == 'B')
            successors[i]->current_status = current_status;

        else
            successors[i] = NULL;

        if(successors[i]!=NULL)
        {
            total_nodes++;

            successors[i]->current_status.move_decider(i,successors[i]->player);
        }
    }
}

/******************************************************************************
my_evaluation_function1():used to estimate the value or goodness of a position at leaf node
parameters used: no parameters
returns : returns the terminal value
*******************************************************************************/

int KalahFlow::myEvaluationFunction1()
{
    int terminal_value;

    if(player == 'A')
    {
        int empty_pits_A = 0;

        for(int i = 0 ; i < 6 ; i++)
        {
            if(current_status.Player_A[i] == 0)
                empty_pits_A++;
        }

        if(empty_pits_A == 6)
            terminal_value = 2000;
    }
    else if(player == 'B')
    {
        int empty_pits_B = 0;

        for(int i = 0 ; i < 6 ; i++)
        {
            if(current_status.Player_B[i] == 0)
                empty_pits_B++;
        }
        if(empty_pits_B == 6)
            terminal_value = -2000;
    }

    heuristic = terminal_value;

    return terminal_value;
}

/******************************************************************************
my_evaluation_function2():used to estimate the value or goodness of a position at leaf node
parameters used: no parameters
returns : returns the terminal value
*******************************************************************************/

int KalahFlow::myEvaluationFunction2()
{

int terminal_value;
    if(player == 'A')
        terminal_value = current_status.store_A - current_status.store_B;

    else if(player == 'B')
        terminal_value = current_status.store_A - current_status.store_B;

    heuristic = terminal_value;

    return terminal_value;

}

/******************************************************************************
my_evaluation_function3():used to estimate the value or goodness of a position at leaf node
parameters used: no parameters
returns : returns the terminal value
*******************************************************************************/

int KalahFlow::myEvaluationFunction3()
{
    int p0 = current_status.store_A;
    int p1 = current_status.store_B;
    int terminal_value;

    if(player == 'A')
    {
        if(p0 != 0)
            terminal_value = (current_status.store_A/current_status.store_B);

        else
            return -1;
    }

    else if(player == 'B')
    {
        if(p1 !=0)
            terminal_value = (current_status.store_B/ current_status.store_A);

        else
            return -1;

    heuristic = terminal_value;
    return terminal_value;
}
}

/******************************************************************************
my_evaluation_function4():used to estimate the value or goodness of a position at leaf node
parameters used: no parameters
returns : returns the terminal value
*******************************************************************************/

int KalahFlow::myEvaluationFunction4()
{
    int terminal_value;
    if (player == 'A'){
        int stones_of_A = 0;
        for(int i=0; i<6; i++) {
            if (current_status.Player_A[i]==0) stones_of_A++;
            else if(current_status.Player_A[i]==i) terminal_value = 1500;
            else if(current_status.Player_A[i]<i) terminal_value = 800;
            else
                terminal_value = 500;
        }
        if(stones_of_A == 6)
            terminal_value = 1000; }
    if (player == 'B'){
        int stones_of_B = 0;
        for(int i=0; i<6; i++) {
            if (current_status.Player_A[i]==0) stones_of_B++;
            else if(current_status.Player_A[i]==i) terminal_value = 1500;
            else if(current_status.Player_A[i]<i) terminal_value = 800;
            else
                terminal_value = 500;
        }
        if(stones_of_B == 6)
            terminal_value = 1000; }
    heuristic = terminal_value;
    return terminal_value;

}

/******************************************************************************
AlphaBetaSearch(): Alpha Beta search algorithm implementation for Kalah Game
parameters used: an object of type KalahFlow, the current depth which is 0 during the initial call,
                 the current player, which was ‘A’ initially, alpha, beta, selectedDepth,
                 which can be 2 or 4, the maximum depth, evaluation_choice 1, 2 or 3
                 select from three possible evaluation function options.
returns : returns the best value
*******************************************************************************/

int AlphaBetaSearch(KalahFlow *alphabeta, int depth, char player, int alpha, int beta, int selected, int evaluation_choice)
{

    int bestValue = -100;
    int value;

    if(alphabeta->is_deep_enough(depth, selected))
    {
        if(evaluation_choice == 1)
            return alphabeta->myEvaluationFunction1();

        else if (evaluation_choice == 2)
            return alphabeta->myEvaluationFunction2();

        else if (evaluation_choice == 3)
            return alphabeta->myEvaluationFunction3();

        else
            return alphabeta->myEvaluationFunction4();
    }

    if (player == 'A' )

    {

        for (int i=0; i < 6; i++ )

        {

            if(alphabeta->successors[i]== NULL)

            continue;

            value = AlphaBetaSearch(alphabeta->successors[i], depth+1, alphabeta->player, alpha, beta, selected, evaluation_choice);

            if (bestValue > value)

            bestValue = max(bestValue,value);

            alpha=max(alpha,bestValue);

            if (beta <= alpha)

            break;  }

        alphabeta->heuristic = bestValue;

        return bestValue;

    }


    else

    {

        int bestValue = +100;

        int value;



        for(int i=0; i < 6; i++)

        {

            if(alphabeta->successors[i]== NULL)

            continue;

            value = AlphaBetaSearch(alphabeta->successors[i], depth+1, alphabeta->player, alpha, beta, selected, evaluation_choice);

            if (bestValue < value)

            bestValue = min( bestValue, value);

            beta = min( beta, bestValue);

            if (beta <= alpha)

            break;

        }

        alphabeta->heuristic = bestValue;

        return bestValue;

    }

}

/******************************************************************************
MinMaxAB(): MinMAxAB search algorithm implementation for Kalah Game
parameters used: an object of type KalahFlow, the current depth which is 0 during the initial call,
                 the current player, which was ‘A’ initially, Use-Threshold, Pass-Threshold value,
                 selectedDepth, which can be 2 or 4, the maximum depth, evaluation_choice-1, 2 or 3 – to
                 select from three possible evaluation function options.
returns : returns the best value
*******************************************************************************/

int MinMaxAB(KalahFlow *min_max,int depth, char player, int use_Threshold, int pass_Threshold, int selectedDepth, int evaluation_choice)
{
    int structure;
    int new_value;
    char new_Player;
    int result_successor = 0;

    if(min_max->is_deep_enough(depth, selectedDepth))
    {

        if(evaluation_choice == 1)
            structure = min_max->myEvaluationFunction1();

        else if (evaluation_choice == 2)
            structure = min_max->myEvaluationFunction2();

        else if (evaluation_choice == 3)
            structure = min_max->myEvaluationFunction3();

        else
            structure = min_max->myEvaluationFunction4();

        if(player == 'B')
            structure = -structure;

        min_max->heuristic = structure;

        return structure;
    }

    for(int i = 0 ; i < SIZE; i++)
    {
        if(min_max->successors[i] == NULL)
            continue;

        if(player == 'A')
            new_Player = 'B';

        else
            new_Player = 'A';

        result_successor = MinMaxAB(min_max->successors[i],depth+1,new_Player,-pass_Threshold,-use_Threshold, selectedDepth, evaluation_choice);

        new_value = -result_successor;

        if(new_value > pass_Threshold)
        {
            min_max->heuristic = i;
            pass_Threshold = new_value;
        }

        if(pass_Threshold >= use_Threshold)
        {
            result_successor = pass_Threshold;
            return result_successor;
        }
    }

    result_successor = pass_Threshold;

    return result_successor;
}

/******************************************************************************
winner(): Prints the result of the winner, the computation time, memory consumed,
          number of nodes generated, number of nodes expanded and the total game path length
parameters used: result if A won the game or B, total time , object of type Kalah
returns : returns nothing
*******************************************************************************/

void winner(char result,int total_time, Kalah k)
{
    if(result == 'A')
        cout << "Player A won the GAME with " << k.store_A << " stones! " << endl << endl;

    else if(result == 'B')
        cout << "Player B won the GAME with " << k.store_B << " stones! " << endl << endl;

    cout << "******************************************************************************************************************" << endl;
    cout << "                                                 ***GAME OVER***                                                  " << endl ;
    cout << "******************************************************************************************************************" << endl << endl << endl;

    cout << "The program took " << "'" << (total_time)/double(CLOCKS_PER_SEC)<< "'" << " seconds of Execution time for the completed game! " << endl << endl;
    cout << "1 node takes 81 bytes of Memory "<<endl << endl;
    cout << "The algorithm takes : "<< "'" << (81* total_nodes) << "'" << " bytes = " << "'" << (81* total_nodes) / (1024) << "'" << " kb" << " of memory!" << endl << endl;
    cout << "The program generated " << "'" << total_nodes << "'" << " nodes for the completed game!" << endl << endl;
    cout << "The program expanded " << "'" << expanded_node_count << "'" << " nodes for the completed game!" << endl << endl;
    cout << "The total length of the Game path is " << "'" << game_path_length << "'" << " for the completed game! " << endl << endl;

}

/******************************************************************************
main():The program starts execution from this function main. It is the driver to
       integrate all the classes and functions defined above
parameters used: no parameters
*******************************************************************************/
int main()
{
    int choice, selectedDepth;
    int evaluation_choice;
    Kalah *kalah = new Kalah();


        cout << endl << endl;
        cout << "*****************************************************************************************************************" << endl;
        cout << "                                            YOU ARE NOW IN THE KALAH GAME ZONE!                                  " << endl ;
        cout << "*****************************************************************************************************************" << endl;
        cout << endl;
        cout << "                                    The game rules are as below:                              " << endl << endl;
        cout << " ** Kalah is played by two players on a board with two rows of 6 holes facing each other." << endl << endl;
        cout << " ** It has two KALAHS (Stores for each player.)" << endl << endl;
        cout << " ** The stones are called beans. At the beginning of the game, there are 6 beans in every hole. The KALAHS are empty." << endl << endl;
        cout << " ** The object of Kalah is to get as many beans into your own kalah by distributing them." << endl << endl;
        cout << " ** A player moves by taking all the beans in one of his 6 holes and distributing them counterclockwise," << endl;
        cout << "    by putting one bean in every hole including his, but excluding the opponent's kalah." << endl << endl;
        cout << " ** There are two special moves:" << endl << endl;
        cout << " ** Extra move: If the last bean is distributed into his own kalah, the player may move again. " << endl
             << "    He has to move again even if he does not want to." << endl << endl;
        cout << " ** Capture: If the last bean falls into an empty hole of the player and the opponent's hole above (or below) is not empty," << endl
             << "    the player puts his last bean and all the beans in his opponent's hole into his kalah. He has won all those beans." << endl << endl;
        cout << " ** The game ends if all 6 holes of one player become empty (no matter if it is this player's move or not)." << endl
             <<"     The beans in the other player's holes are given into this player's kalah." << endl << endl;
        cout << " ** The player who won more beans (at least 37) becomes the winner." << endl << endl;


        cout << " *****************************************************************************************************************" << endl;
        cout << "                                            ***KALAH BOARD DISPLAY***                                             " << endl ;
        cout << " *****************************************************************************************************************" << endl;

        kalah->display();

        cout << " You now have the below choices :" << endl << endl
             << "Choose your option :" << endl << endl;

        cout << " ** Choose 1 for MinMaxAB: " << endl;
        cout << " ** Choose 2 for AlphaBetaSearch: " << endl;
        cout << " ** Choose 3 to QUIT:" << endl;
        cin >> choice;

        cout << "Please enter the depth that you would want to check the results for: " << endl;
        cout << "2: Depth of 2" << endl;
        cout << "4: Depth of 4" << endl;
        cin >> selectedDepth;

        while(selectedDepth !=2 && selectedDepth !=4)
        {
            cout << "Invalid Depth! Please enter depth value 2 or 4!" << endl;
            cin >> selectedDepth;
        }

        cout << "Please enter the Evaluation function that you would want to check the results for: "<< endl;
        cout << "1: Evaluation Function 1 ( Vidhyashree Nagabhushana ) " << endl;
        cout << "2: Evaluation Function 2 ( Akshatha Jain ) " << endl;
        cout << "3: Evaluation Function 3 ( Akshatha Jain ) " << endl;
        cout << "4: Evaluation Function 4 ( Sahana Sreenath) " << endl;
        cin >> evaluation_choice;


        while(evaluation_choice < 1 || evaluation_choice > 4 )
        {
            cout << "Invalid selection! Please enter values 1, 2, 3 or 4!" << endl;
            cin >> evaluation_choice;
        }

        switch(choice)
        {
            case 1:
                {
                    cout << "Initial board " << endl;
                    kalah->display();

                    char result = kalah->result();

                    char player ='A';
                    int start_timer = clock();

                    while(result == 'N')
                    {
                        KalahFlow *min_max_ab = new KalahFlow(player);

                        min_max_ab->current_player_status( kalah );

                        cout << "It is player " << player << "'s turn!" << endl;

                        MinMaxAB(min_max_ab,0,player,2000,-2000,selectedDepth,evaluation_choice);

                        int pit = min_max_ab->heuristic;

                        if(player == 'A')
                            player = kalah->move_generator_A(pit);

                        else
                            player = kalah->move_generator_B(pit);

                        kalah->display();

                        result = kalah->result();

                        game_path_length++;
                    }

                    int stop_timer = clock();
                    kalah->display();
                    int total_time = stop_timer - start_timer;
                    winner(result, total_time, kalah );
                }

                break;

            case 2:
                {
                    cout << "Initial board " << endl;
                    kalah->display();

                    char result = kalah->result();

                    char player = 'A';
                    int start_timer = clock();

                    while(result == 'N')
                    {
                        KalahFlow *alpha_beta_flow = new KalahFlow(player);

                        alpha_beta_flow->current_player_status(kalah);

                        cout << "It is player " << player << "'s turn!" << endl;

                        AlphaBetaSearch(alpha_beta_flow,0,player,2000,-2000, selectedDepth,evaluation_choice);

                        int pit;

                        for(int i = 0; i < SIZE; i++)
                        {
                            if(alpha_beta_flow->successors[i] == NULL)
                                continue;

                            if(alpha_beta_flow->successors[i]->heuristic == alpha_beta_flow->heuristic)
                                pit = i;
                        }

                        if(player == 'A')
                            player = kalah->move_generator_A(pit);

                        else
                            player = kalah->move_generator_B(pit);

                        kalah->display();

                        result = kalah->result();

                        game_path_length++;
                    }

                    int stop_timer = clock();
                    kalah->display();
                    int total_time = stop_timer - start_timer;
                    winner(result,total_time, kalah);
                }

                break;

            case 3:
                cout <<"Thanks. See you again later........." << endl;
                return 0;
        }

    return 0;
}
