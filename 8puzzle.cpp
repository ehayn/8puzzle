#include <iostream>
#include <cstdlib> //random numbers
#include <ctime> //random numbers
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class TileSet{
    private:
        int goalState[9];
        int tiles[9];
        int emptyPosition;
    public:
        TileSet();
        TileSet(const TileSet& toCopy);
        ~TileSet();
        void printBoard();
        bool moveNorth();
        bool moveSouth();
        bool moveWest();
        bool moveEast();
        bool isEqualTo(TileSet* setToTest);
        int hFunction();
        int distanceToGoal(int position, int value);
};

//this is for generating nodes
TileSet* generateChild(TileSet* toCopy){
    TileSet* newTile = new TileSet(*toCopy);
    return newTile;
};

//function takes in original board and solves it.  Keeps track of best possible moves and already visited nodes.
//Will choose a move from the best possible move(lowest heuristic, and will only save moves that don't match already visited nodes.
int solve(TileSet* toSolve){
    int moves = 0;//moves to solve
    int bestH = 99;
    int i = 0;
    TileSet* current;//current node I'm looking at
    TileSet* temp;
    bool push; //decide whether to push or not
    vector<TileSet*> nodes;
    vector<TileSet*> best;
    vector<TileSet*> visited;
    vector<TileSet*>::iterator it;
    nodes.push_back(toSolve);
    current = nodes.front();
    while(current->hFunction()!=0){
        temp = generateChild(current);
        if(temp->moveEast()){
            //cout << "in east" << endl;
            push = true;
            for(it = nodes.begin(); it != nodes.end(); ++it){
                if((*it)->isEqualTo(temp)){
                    push = false;
                }
            }
            for(it = visited.begin(); it != visited.end(); ++it){
                if((*it)->isEqualTo(temp)){
                    push = false;
                }
            }
            if(push){
                nodes.push_back(generateChild(temp));
                //temp->printBoard();
            }
            temp->moveWest();
        }
        if(temp->moveWest()){
            //cout << "in west" << endl;
            push = true;
            for(it = nodes.begin(); it != nodes.end(); ++it){
                if((*it)->isEqualTo(temp)){
                    push = false;
                }
            }
            for(it = visited.begin(); it != visited.end(); ++it){
                if((*it)->isEqualTo(temp)){
                    push = false;
                }
            }
            if(push){
                nodes.push_back(generateChild(temp));
                //temp->printBoard();
            }
            temp->moveEast();
        }
        if(temp->moveNorth()){
            //cout << "in north" << endl;
            push = true;
            for(it = nodes.begin(); it != nodes.end(); ++it){
                if((*it)->isEqualTo(temp)){
                    push = false;
                }
            }
            for(it = visited.begin(); it != visited.end(); ++it){
                if((*it)->isEqualTo(temp)){
                    push = false;
                }
            }
            if(push){
                nodes.push_back(generateChild(temp));
                //temp->printBoard();
            }
            temp->moveSouth();
        }
        if(temp->moveSouth()){
            //cout << "in south" << endl;
            push = true;
            for(it = nodes.begin(); it != nodes.end(); ++it){
                if((*it)->isEqualTo(temp)){
                    push = false;
                }
            }
            for(it = visited.begin(); it != visited.end(); ++it){
                if((*it)->isEqualTo(temp)){
                    push = false;
                }
            }
            if(push){
                nodes.push_back(generateChild(temp));
                //temp->printBoard();
            }
            temp->moveNorth();
        }
        it = nodes.begin();
        visited.push_back(*it);
        nodes.erase(it);
        for(i=0;i<9;i++){
            for(it = nodes.begin(); it != nodes.end(); ++it){
                if((*it)->hFunction()==i){
                    best.push_back(*it);
                }
            }
        }

        nodes.swap(best);
        best.clear();
        current = nodes.front();
        //cout << nodes.size() << endl;
        //current->printBoard();
        //cin.ignore();
        moves ++;
    }
    cout << "Final Board:"<<endl;
    current->printBoard();
    return moves;
};

void playGame(){
    TileSet* toSolve;
    TileSet tileSet1;
    toSolve = &tileSet1;
    cout << endl << "Original Board:" << endl;
    tileSet1.printBoard();
    cout << "Moves taken: " << solve(toSolve) << endl<< endl;
};

int main(){
    srand(time(0));//random number seed
    bool keepGoing = true;
    int x;
    while(keepGoing){
        cout << "Enter '1' to generate and solve an 8Puzzle" << endl;
        cout << "Enter '2' to exit: ";
        cin >> x;
        if(x==1){
            playGame();
        }
        else if(x==2){
            keepGoing = false;
        }
        else{
            keepGoing = true;
        }

    }

    return 0;
}

//check if board is equal to another
bool TileSet::isEqualTo(TileSet* testToSet){
    int i;
    for(i=0;i<9;i++){
        if(this->tiles[i]!=testToSet->tiles[i]){
            return false;
        }
    }
    return true;
}



TileSet::TileSet(){
    emptyPosition = 8;
    int i;
    bool hasChildren = false;
    i = 0;

    //Build the initial board and goal state
    while(i<9){
        tiles[i] = i+1;
        goalState[i] = i+1;
        i++;
    }
    tiles[8]=0;
    goalState[8]=0;

    i = 100;
    //randomize start state
    int direction;
    while(i>0){
        direction = rand() % 4;
        if(direction==0){
            moveNorth();
        }
        if(direction==1){
            moveSouth();
        }
        if(direction==2){
            moveEast();
        }
        if(direction==3){
            moveWest();
        }
        i--;
    }
}
TileSet::TileSet(const TileSet& toCopy){
    int i,j;
    for(i=0;i<4;i++){
        this->emptyPosition = toCopy.emptyPosition;
        for(j=0;j<9;j++){
            this->tiles[j] = toCopy.tiles[j];
        }
    }
};

TileSet::~TileSet(){
};

void TileSet::printBoard(){
    int i;
    for(i=0;i<9;i++){
        cout << tiles[i] << "    ";
        if(i==2){
            cout << endl;
        }
        if(i==5){
            cout << endl;
        }
    }
    cout << endl << "heuristic: " << this->hFunction() << endl;
    //break after print
    cout << endl << endl;
}

bool TileSet::moveNorth(){
    if(emptyPosition<3){
        return false;
    }
    else{
        swap(tiles[emptyPosition-3], tiles[emptyPosition]);
        emptyPosition = emptyPosition - 3;
        return true;
    }
}

bool TileSet::moveSouth(){
    if(emptyPosition>5){
        return false;
    }
    else{
        swap(tiles[emptyPosition+3], tiles[emptyPosition]);
        emptyPosition = emptyPosition + 3;
        return true;
    }
}

bool TileSet::moveEast(){
    if((emptyPosition==2)||(emptyPosition==5)||(emptyPosition==8)){
        return false;
    }
    else{
        swap(tiles[emptyPosition+1], tiles[emptyPosition]);
        emptyPosition = emptyPosition + 1;
        return true;
    }
}

bool TileSet::moveWest(){
    if((emptyPosition==0)||(emptyPosition==3)||(emptyPosition==6)){
        return false;
    }
    else{
        swap(tiles[emptyPosition-1], tiles[emptyPosition]);
        emptyPosition = emptyPosition - 1;
        return true;
    }
}

//calculate heuristic
int TileSet::hFunction(){
    int i;
    int total = 0;
    for(i=0;i<8;i++){
        if(this->tiles[i]==i+1){
            total;
        }
        else{
            total = total + 1;
        }
    }
    return total;
}

int TileSet::distanceToGoal(int position, int value){
    int result = 0;
    if(value==1){
        if((position==1)||(position==3)){
            result = 1;
            return result;
        }
        else if((position==2)||(position==4)||(position==6)){
            result = 2;
            return result;
        }
        else if((position==5)||(position==7)){
            result = 3;
            return result;
        }
        else if((position==8)){
            result = 4;
            return result;
        }
        else{
            return result;
        }
    }
    else if(value==2){
        if((position==0)||(position==2)||(position==4)){
            result = 1;
            return result;
        }
        else if((position==3)||(position==5)||(position==7)){
            result = 2;
            return result;
        }
        else if((position==6)||(position==8)){
            result = 3;
            return result;
        }
        else{
            return result;
        }
    }
    else if(value==3){
        if((position==1)||(position==5)){
            result = 1;
            return result;
        }
        else if((position==0)||(position==4)||(position==8)){
            result = 2;
            return result;
        }
        else if((position==3)||(position==7)){
            result = 3;
            return result;
        }
        else if((position==6)){
            result = 4;
            return result;
        }
        else{
            return result;
        }
    }
    else if(value==4){
        if((position==0)||(position==4)||(position==6)){
            result = 1;
            return result;
        }
        else if((position==1)||(position==5)||(position==7)){
            result = 2;
            return result;
        }
        else if((position==2)||(position==8)){
            result = 3;
            return result;
        }
        else{
            return result;
        }
    }
    else if(value==5){
        if((position==1)||(position==3)||(position==5)||(position==7)){
            result = 1;
            return result;
        }
        else if((position==0)||(position==2)||(position==6)||(position==8)){
            result = 2;
            return result;
        }
        else{
            return result;
        }
    }
    else if(value==6){
        if((position==2)||(position==4)||(position==8)){
            result = 1;
            return result;
        }
        else if((position==1)||(position==3)||(position==7)){
            result = 2;
            return result;
        }
        else if((position==0)||(position==6)){
            result = 3;
            return result;
        }
        else{
            return result;
        }
    }
    else if(value==7){
        if((position==3)||(position==7)){
            result = 1;
            return result;
        }
        else if((position==0)||(position==4)||(position==8)){
            result = 2;
            return result;
        }
        else if((position==1)||(position==5)){
            result = 3;
            return result;
        }
        else if((position==2)){
            result = 4;
            return result;
        }
        else{
            return result;
        }
    }
    else if(value==8){
        if((position==4)||(position==6)||(position==8)){
            result = 1;
            return result;
        }
        else if((position==1)||(position==3)||(position==5)){
            result = 2;
            return result;
        }
        else if((position==0)||(position==2)){
            result = 3;
            return result;
        }
        else{
            return result;
        }
    }
    else{
        return result;
    }

}
