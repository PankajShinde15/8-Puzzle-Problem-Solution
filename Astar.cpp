// A* Algorithm

#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct TreeNode // structure to create new node
{
    int mat[3][3];
    int fn;
    vector<TreeNode *> children;
};

struct TreeNode *CreateNewNode(int mat[3][3]); // Function to create new node
void addChild(TreeNode *node, int mat[3][3]);  // Function to add child nodes to parent node
TreeNode *root;
TreeNode *temp = root;
vector<TreeNode *> allNodes; // Keep track of all nodes
int flag1 = 0;
map<int, TreeNode *> openList; // Stores all possible nodes after moving tile
int cnt = 0;
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

// Function to find misplaced tiles
int calculateFn(int puzzle[3][3])
{
    int misplaced = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[i][j] != goal[i][j])
            {
                misplaced++;
            }
        }
    }
    return misplaced;
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

bool isVisited(TreeNode *node)
{
    int checkFlag = 0;
    for (int i = 0; i < allNodes.size(); i++)
    {
        if (checkFlag == 0)
        {
            checkFlag = 1;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (allNodes[i]->mat[j][k] != node->mat[j][k])
                    {
                        checkFlag = 0;
                        break;
                    }
                }
                if (checkFlag == 0)
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
    if (checkFlag == 0)
    {
        allNodes.push_back(node);
        return false;
    }
    return true;
}

// Function to move 0 upside
void up(TreeNode *temp, int puzzle[3][3], int posi, int posj)
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

    TreeNode *updatedPuzzle = CreateNewNode(newPuzzle);

    if (!isVisited(updatedPuzzle))
    {
        addChild(temp, newPuzzle);
        cnt++;
        openList.insert(pair<int, TreeNode *>(calculateFn(newPuzzle), updatedPuzzle));
    }
}

// Function to move 0 downside
void down(TreeNode *temp, int puzzle[3][3], int posi, int posj)
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

    TreeNode *updatedPuzzle = CreateNewNode(newPuzzle);

    if (!isVisited(updatedPuzzle))
    {
        addChild(temp, newPuzzle);
        cnt++;
        openList.insert(pair<int, TreeNode *>(calculateFn(newPuzzle), updatedPuzzle));
    }
}

// Function to move 0 to right
void right(TreeNode *temp, int puzzle[3][3], int posi, int posj)
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

    TreeNode *updatedPuzzle = CreateNewNode(newPuzzle);

    if (!isVisited(updatedPuzzle))
    {
        addChild(temp, newPuzzle);
        openList.insert(pair<int, TreeNode *>(calculateFn(newPuzzle), updatedPuzzle));
        cnt++;
    }
}

// Function to move 0 to left
void left(TreeNode *temp, int puzzle[3][3], int posi, int posj)
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

    TreeNode *updatedPuzzle = CreateNewNode(newPuzzle);

    if (!isVisited(updatedPuzzle))
    {
        addChild(temp, newPuzzle);
        openList.insert(pair<int, TreeNode *>(calculateFn(newPuzzle), updatedPuzzle));
        cnt++;
    }
}

// Function to explore all the possibilities by swapping zero
void swapZero(TreeNode *temp, int puzzle[3][3], int posi, int posj)
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
            up(temp, puzzle, posi, posj);
            down(temp, puzzle, posi, posj);
            right(temp, puzzle, posi, posj);
            left(temp, puzzle, posi, posj);
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
void printmat(TreeNode *node)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << node->mat[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to compare current state with goal state
bool compareWithGoal(TreeNode *node)
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
void checkAllPossibilties(TreeNode *temp, int *posi, int *posj)
{
    while (!compareWithGoal((*openList.begin()).second) && flag1 == 0)
    {
        TreeNode *minNode = (*openList.begin()).second;
        int p = (*openList.begin()).first;
        openList.clear();
        getPosZero(minNode->mat, posi, posj);
        cout << "\nNode: " << endl;
        printmat(minNode);
        cout << "fn = " << p - 1 << endl;
        swapZero(minNode, minNode->mat, *posi, *posj);

        for (int j = 0; j < minNode->children.size(); j++)
        {
            if (compareWithGoal(minNode->children[j]))
            {
                cout << "\nGoal State: " << endl;
                printmat(minNode->children[j]);
                cout << "fn = " << (*openList.begin()).first << endl;
                cout << "\nGoal is Reached!!\n";
                cout << "Total State Space = " << cnt << endl;
                flag1 = 1;
                break;
            }
        }
        cout << "\n";
        if (flag1 == 1)
        {
            break;
        }
    }
}

// Function to create a new node
TreeNode *CreateNewNode(int mat[3][3])
{
    TreeNode *newNode = new TreeNode();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            newNode->mat[i][j] = mat[i][j];
        }
    }
    newNode->fn = calculateFn(mat);
    return newNode;
}

// Function to add a child to a specific node
void addChild(TreeNode *node, int mat[3][3])
{
    TreeNode *newNode = CreateNewNode(mat);
    node->children.push_back(newNode);
}

void aStar(int puzzle[3][3], int posi, int posj)
{
    root = CreateNewNode(puzzle);

    temp = root;
    allNodes.push_back(temp);

    cout << "\nStart State (root): " << endl;
    for (int j = 0; j < 3; j++)
    {
        for (int k = 0; k < 3; k++)
        {
            cout << root->mat[j][k] << " ";
        }
        cout << endl;
    }
    if (compareWithGoal(root))
    {
        cout << "\nGoal State: " << endl;
        printmat(root);
        cout << "\nGoal is Reached!!\n";
        cout << "Total State Space = " << cnt << endl;
        return;
    }
    cout << "fn = " << calculateFn(puzzle) - 1 << endl;
    getPosZero(puzzle, &posi, &posj);
    swapZero(temp, puzzle, posi, posj);

    for (int i = 0; i < root->children.size(); i++)
    {
        if (compareWithGoal(root->children[i]))
        {
            cout << "\nGoal State: " << endl;
            printmat(root->children[i]);
            cout << "\nGoal is Reached!!\n";
            cout << "Total State Space = " << cnt << endl;
            break;
        }
    }
    cout << "\n";
    checkAllPossibilties(temp, &posi, &posj);
}

int main()
{
    int puzzle[3][3];
    int posi, posj;
    int choice;
    cout << "Enter Start State: " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> puzzle[i][j];
        }
    }

    cout << endl;
    Goal();
    aStar(puzzle, posi, posj);

    return 0;
}
