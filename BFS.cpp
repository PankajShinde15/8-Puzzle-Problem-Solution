// Breadth First Search

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node // structure to create new node
{
    int mat[3][3];
    vector<Node *> children;
};

struct Node *GetNewNode(int mat[3][3]);   // Function to create new node
void addChild(Node *node, int mat[3][3]); // Function to add child nodes to parent node

int cnt = 0;
Node *root;
Node *temp = root;
vector<Node *> allNodes; // Keep track of all nodes
int flag1 = 0;
queue<Node *> Queue;

int goal[3][3];
void Goal()
{
    cout << "Enter Goal State: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> goal[i][j];
        }
    }
}

// Function to get position of zero
void getPosZero(int puzzle[3][3], int *posi, int *posj)
{
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[i][j] == 0)
            {
                *posi = i;
                *posj = j;
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            break;
        }
    }
}

bool isVisited(Node *node)
{
    int flagCheck = 0;
    for (int i = 0; i < allNodes.size(); i++)
    {
        if (flagCheck == 0)
        {
            flagCheck = 1;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (allNodes[i]->mat[j][k] != node->mat[j][k])
                    {
                        flagCheck = 0;
                        break;
                    }
                }
                if (flagCheck == 0)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }
    if (flagCheck == 0)
    {
        allNodes.push_back(node);
        return false;
    }
    return true;
}

// Function to move 0 upside
void up(Node *temp, int puzzle[3][3], int posi, int posj)
{
    int newPuzzle[3][3];
    if (posi != 0)
    {

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                newPuzzle[i][j] = puzzle[i][j];
            }
        }
        int newPos = posi - 1;
        int temp = newPuzzle[newPos][posj];
        newPuzzle[newPos][posj] = 0;
        newPuzzle[posi][posj] = temp;
    }
    Node *updatedPuzzle = GetNewNode(newPuzzle);
    if (!isVisited(updatedPuzzle))
    {
        cout << "up" << endl;
        addChild(temp, newPuzzle);
        cnt++;
        Queue.push(updatedPuzzle);
    }
}
// Function to move 0 downside
void down(Node *temp, int puzzle[3][3], int posi, int posj)
{
    int newPuzzle[3][3];
    if (posi != 2)
    {

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                newPuzzle[i][j] = puzzle[i][j];
            }
        }
        int newPos = posi + 1;
        int temp = newPuzzle[newPos][posj];
        newPuzzle[newPos][posj] = 0;
        newPuzzle[posi][posj] = temp;
    }
    Node *updatedPuzzle = GetNewNode(newPuzzle);
    if (!isVisited(updatedPuzzle))
    {
        cout << "down" << endl;
        addChild(temp, newPuzzle);
        cnt++;
        Queue.push(updatedPuzzle);
    }
}
// Function to move 0 to right
void right(Node *temp, int puzzle[3][3], int posi, int posj)
{
    int newPuzzle[3][3];
    if (posj != 2)
    {

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                newPuzzle[i][j] = puzzle[i][j];
            }
        }
        int newPos = posj + 1;
        int temp = newPuzzle[posi][newPos];
        newPuzzle[posi][newPos] = 0;
        newPuzzle[posi][posj] = temp;
    }
    Node *updatedPuzzle = GetNewNode(newPuzzle);

    if (!isVisited(updatedPuzzle))
    {
        cout << "right" << endl;
        addChild(temp, newPuzzle);
        cnt++;
        Queue.push(updatedPuzzle);
    }
}
// Function to move 0 to left
void left(Node *temp, int puzzle[3][3], int posi, int posj)
{
    int newPuzzle[3][3];
    if (posj != 0)
    {

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                newPuzzle[i][j] = puzzle[i][j];
            }
        }
        int newPos = posj - 1;
        int temp = newPuzzle[posi][newPos];
        newPuzzle[posi][newPos] = 0;
        newPuzzle[posi][posj] = temp;
    }
    Node *updatedPuzzle = GetNewNode(newPuzzle);
    if (!isVisited(updatedPuzzle))
    {
        cout << "left" << endl;
        addChild(temp, newPuzzle);
        cnt++;
        Queue.push(updatedPuzzle);
    }
}
// Function to explore all the possibilities by swapping zero
void action(Node *temp, int puzzle[3][3], int posi, int posj)
{
    switch (posi)
    {
    case 0:
        switch (posj)
        {
        case 0:
            right(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);

            break;
        case 1:
            right(temp, puzzle, posi, posj);
            left(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);

            break;
        case 2:
            left(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);

            break;
        default:
            break;
        }
        break;
    case 1:
        switch (posj)
        {
        case 0:
            right(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);

            break;
        case 1:
            right(temp, puzzle, posi, posj);
            left(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);

            break;
        case 2:

            left(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);
            break;
        default:
            break;
        }
        break;

    case 2:
        switch (posj)
        {
        case 0:
            right(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);

            break;
        case 1:

            right(temp, puzzle, posi, posj);
            left(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);

            break;
        case 2:
            left(temp, puzzle, posi, posj);
            up(temp, puzzle, posi, posj);

            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}
// Function to print puzzle
void printmat(Node *node)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << node->mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// Function to compare current state with goal state
bool compareWithGoal(Node *node)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (node->mat[i][j] != goal[i][j])
            {

                return false;
            }
        }
    }

    return true;
}

// Function to display all possibilities after swapping zero
void checkAllPossibilties(Node *temp, int *posi, int *posj)
{
    while (!Queue.empty())
    {
        if (!compareWithGoal(Queue.front()) && flag1 == 0)
        {
            getPosZero(Queue.front()->mat, posi, posj);
            action(Queue.front(), Queue.front()->mat, *posi, *posj);

            for (int j = 0; j < Queue.front()->children.size(); j++)
            {
                printmat(Queue.front()->children[j]);
                if (compareWithGoal(Queue.front()->children[j]))
                {
                    cout << "Reached" << endl;
                    cout << "Total State Space=" << cnt;
                    flag1 = 1;
                    break;
                }

                if (flag1 == 1)
                {
                    break;
                }
            }
            cout << endl;
        }
        Queue.pop();
    }
}

// function to create new node
Node *GetNewNode(int mat[3][3])
{
    Node *newNode = new Node();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            newNode->mat[i][j] = mat[i][j];
        }
    }
    return newNode;
}

// function to add a child to a specific node
void addChild(Node *node, int mat[3][3])
{
    Node *newNode = GetNewNode(mat);
    node->children.push_back(newNode);
}

int main()
{
    int posi, posj;
    int puzzle[3][3];
    cout << "Enter Start State: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> puzzle[i][j];
        }
    }

    Goal();
    root = GetNewNode(puzzle);
    temp = root;
    allNodes.push_back(temp);

    cout << "root" << endl;
    for (int j = 0; j < 3; j++)
    {
        for (int k = 0; k < 3; k++)
        {
            cout << root->mat[j][k] << " ";
        }
        cout << endl;
    }
    cout << endl;
    getPosZero(puzzle, &posi, &posj);
    action(temp, puzzle, posi, posj);

    for (int i = 0; i < root->children.size(); i++)
    {
        printmat(root->children[i]);
    }
    cout << endl;
    checkAllPossibilties(temp, &posi, &posj);

    return 0;
}