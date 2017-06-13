#include <iostream>
#include <cstdlib> //random numbers
#include <ctime> //random numbers
#include <algorithm>
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
        bool hasChildren;
        void printBoard();
        bool moveNorth();
        bool moveSouth();
        bool moveWest();
        bool moveEast();
        bool isEqualTo(TileSet *setToTest);
        int mbDistance();
        int distanceToGoal(int position, int value);
        void generateChildren();
        TileSet* moves[4];
        TileSet* parent;
};

class TreeSearch{
    private:
        TileSet originalSet;
    public:
        TreeSearch(TileSet tile);

};

class Node{
    private:
        TileSet nodeSet;
    public:
        Node(TileSet tileSet);
        Node* parent;
        Node* children[4];
        void solve();
};

TileSet* generateChild(TileSet* toCopy){
    TileSet* newTile = new TileSet(*toCopy);
    return newTile;
};

bool TileSet::isEqualTo(TileSet* testToSet){
    int i;
    for(i=0;i<9;i++){
        if(this->tiles[i]!=testToSet->tiles[i]){
            return false;
        }
    }
    cout << "found equivalent" << endl;
    return true;
}

int traverse(TileSet* top){
    queue<TileSet*> nodes;
    queue<TileSet*> tempQ;
    queue<TileSet*> tempR;
    queue<TileSet*> tempE;
    queue<TileSet*> best;
    TileSet* current;
    TileSet* temp;
    nodes.push(top);
    int j = 0;
    bool push = true;
    int i,bestDistance;
    bestDistance = 99;
    int moves = 0;
    current = nodes.front();
    nodes.size();
    while(current->mbDistance()!=0){

        current->printBoard();
        //cin.ignore();

        cout << endl << nodes.size() << "   " << best.size() << endl;
        if(best.size()==0){
            current = nodes.front();
            nodes.pop();
            bestDistance = 99;
            if(current->moveEast()){
                push = true;
                tempE = nodes;
                while(tempE.size()!=0){
                    if(current->isEqualTo(tempE.front())){
                        push = false;
                    }
                    tempE.pop();
                }
                if(push){
                    nodes.push(generateChild(current));
                }
                current->moveWest();
            }
            if(current->moveWest()){
                push = true;
                    tempE = nodes;
                while(tempE.size()!=0){
                    if(current->isEqualTo(tempE.front())){
                        push = false;
                    }
                    tempE.pop();
                }
                if(push){
                    nodes.push(generateChild(current));
                }
                current->moveEast();
            }
            if(current->moveNorth()){
                push = true;
                tempE = nodes;
                while(tempE.size()!=0){
                    if(current->isEqualTo(tempE.front())){
                        push = false;
                    }
                    tempE.pop();
                }
                if(push){
                    nodes.push(generateChild(current));
                }
                current->moveSouth();
            }
            if(current->moveSouth()){
                push = true;
                tempE = nodes;
                while(tempE.size()!=0){
                    if(current->isEqualTo(tempE.front())){
                        push = false;
                    }
                    tempE.pop();
                }
                if(push){
                    nodes.push(generateChild(current));
                }
                current->moveNorth();
            }

            while(!nodes.empty()){
                temp = nodes.front();
                if(temp->mbDistance()<=bestDistance){
                    bestDistance = temp->mbDistance();
                    best.push(nodes.front());
                    tempQ.push(nodes.front());
                    nodes.pop();
                }
                else{
                    tempQ.push(nodes.front());
                    nodes.pop();
                }

            }
            while(!tempQ.empty()){
                    tempR.push(tempQ.front());
                    tempQ.pop();
            }
            while(!tempR.empty()){
                    nodes.push(tempR.front());
                    tempR.pop();
            }
        }
        else{
            current = best.front();
            best.pop();
            if(current->moveEast()){
                if(current->mbDistance()<bestDistance){
                    bestDistance = current->mbDistance();
                    best.push(generateChild(current));
                }
                else{
                    nodes.push(generateChild(current));
                }
                current->moveWest();
            }
            if(current->moveWest()){
                if(current->mbDistance()<bestDistance){
                    bestDistance = current->mbDistance();
                    best.push(generateChild(current));
                }
                else{
                    nodes.push(generateChild(current));
                }
                current->moveEast();
            }
            if(current->moveNorth()){
                if(current->mbDistance()<bestDistance){
                    bestDistance = current->mbDistance();
                    best.push(generateChild(current));
                }
                else{
                    nodes.push(generateChild(current));
                }
                current->moveSouth();
            }
            if(current->moveSouth()){
                if(current->mbDistance()<bestDistance){
                    bestDistance = current->mbDistance();
                    best.push(generateChild(current));
                }
                else{
                    nodes.push(generateChild(current));
                }
                current->moveNorth();
            }
        }

        moves ++;
    }
    current->printBoard();
    return moves;
};


int main(){
    srand(time(0));//random number seed

    TileSet tileSet0;
    TileSet* tileSet1 = &tileSet0;
    tileSet1->printBoard();
    TileSet* first = tileSet1;
    cout << traverse(first);

    //return 0;
}


TileSet::TileSet(){
    emptyPosition = 8;
    int i;
    for(i=0;i<4;i++){
        moves[i] = NULL;
    }
    parent = NULL;
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
    cout << endl << "Manhattan Distance: " << this->mbDistance() << endl;
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

int TileSet::mbDistance(){
    int manhattanDistance = 0;
    int i = 0;
    for(i=0;i<9;i++){
        manhattanDistance =  manhattanDistance + distanceToGoal(i, tiles[i]);
    }
    return manhattanDistance;
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

void TileSet::generateChildren(){
    TileSet newTile;
    int i,j;
    for(i=0;i<4;i++){
        newTile.emptyPosition = this->emptyPosition;
        for(j=0;j<9;j++){
            newTile.tiles[j] = tiles[j];
        }
        newTile.parent = this;
        moves[i] = &newTile;
        //children[i].printBoard();
    }
    if(moves[0]->moveEast()){
        moves[0];
        //moves[0]->printBoard();
    }
    else{
        moves[0] = NULL;
    }
    if(moves[1]->moveWest()){
        moves[1];
        //moves[1]->printBoard();
    }
    else{
        moves[1] = NULL;
    }
    if(moves[2]->moveNorth()){
        moves[2];
        //moves[2]->printBoard();
    }
    else{
        moves[2] = NULL;
    }
    if(moves[3]->moveSouth()){
        moves[3];
        //moves[3]->printBoard();

    }
    else{
        moves[3] = NULL;
    }
    this->hasChildren = true;
    /*int bestMove = 999;
    int nextMove;
    for(i=0;i<4;i++){
        if(moves[i]!=NULL){
            if(bestMove>moves[i]->mbDistance()){
                bestMove = moves[i]->mbDistance();
                nextMove = i;
            }
        }
    }
    children[1].solve();*/


}
TreeSearch::TreeSearch(TileSet tile){
    originalSet = tile;
}

Node::Node(TileSet tile){
    nodeSet = tile;
    int i;
    for(i=0;i<3;i++){
        /*children[i]->nodeSet = nodeSet;*/
    }
    /*children[0]->nodeSet.moveNorth();
    children[1]->nodeSet.moveSouth();
    children[2]->nodeSet.moveEast();
    children[3]->nodeSet.moveWest();*/
}

void Node::solve(){

    children[0]->nodeSet.printBoard();
}
