#include "Map.h"
#include <queue>

Map::Map()
{
    this->root = nullptr;
}
Map::~Map()
{
    // TODO: Free any dynamically allocated memory if necessary
    //deleteTree(root);
}

void Map::deleteTree(MapNode *node){
    if (node == nullptr)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node->isle;
    delete node;
}

void Map::initializeMap(std::vector<Isle *> isles)
{
    // TODO: Insert innitial isles to the tree
    // Then populate with Goldium and Einstainium items
    for(Isle *isle: isles){
        insert(isle);
        isleList.push_back(isle);
        rebalanceCounter = 0;
    }
    rebalanceCounter = 0;
    populateWithItems();
  
}

MapNode *Map::rotateRight(MapNode *current)
{
    // TODO: Perform right rotation according to AVL
    // return necessary new root
    // Use std::cerr << "[Right Rotation] " << "Called on invalid node!" << std::endl;
    if (!current || !current->left) {
        std::cerr << "[Right Rotation] " << "Called on invalid node!" << std::endl;
        return current;
    }

    MapNode* a = current->left;
    MapNode* d = a->right;

    a->right = current;
    current->left = d;
    current->height = std::max(height(current->left), height(current->right)) + 1;
    a->height = std::max(height(a->left), height(a->right)) + 1;

    return a;
}

MapNode *Map::rotateLeft(MapNode *current)
{
    // TODO: Perform left rotation according to AVL
    // return necessary new root
    // Use std::cerr << "[Left Rotation] " << "Called on invalid node!" << std::endl;
    if (!current || !current->right) {
        std::cerr << "[Left Rotation] " << "Called on invalid node!" << std::endl;
        return current;
    }

    MapNode* a = current->right;
    MapNode* d = a->left; 

    current->right = d;
    a->left = current;

    current->height = std::max(height(current->left), height(current->right)) + 1;
    a->height = std::max(height(a->left), height(a->right)) + 1;

    return a;
}

int Map::calculateMinMapDepthAccess(int playerDepth, int totalShaperTreeHeight, int totalMapDepth)
{
    return (int)totalMapDepth * ((double)playerDepth / totalShaperTreeHeight);
}

int Map::height(MapNode *node)
{
    // TODO: Return height of the node
    if (node == nullptr) {
        return -1; 
    }
    return node->height;
}

int Map::getBalance(MapNode *node)
{
    if (node == nullptr) {
        return 0; 
    }

    return height(node->left) - height(node->right);
}

MapNode *Map::insert(MapNode *node, Isle *isle)
{
    MapNode *newNode = nullptr;

    // TODO: Recursively insert isle to the tree
    // returns inserted node

    if (node == nullptr) {
        newNode = new MapNode(isle);  
        return newNode;
    }

    if (isle->getName() < node->isle->getName()) {
        node->left = insert(node->left, isle);  
    }
    else if (isle->getName() > node->isle->getName()) {
        node->right = insert(node->right, isle);  
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && isle->getName() < node->left->isle->getName()) {
        rebalance = true;
        return rotateRight(node);
    }

    if (balance < -1 && isle->getName() > node->right->isle->getName()) {
        rebalance = true;
        return rotateLeft(node);
    }

    if (balance > 1 && isle->getName() > node->left->isle->getName()) {
        node->left = rotateLeft(node->left);
        rebalance = true;
        return rotateRight(node);
    }

    if (balance < -1 && isle->getName() < node->right->isle->getName()) {
        node->right = rotateRight(node->right);
        rebalance = true;
        return rotateLeft(node);
    }

    return node;
}

void Map::insert(Isle *isle)
{
    root = insert((root), isle);
    if(rebalance == true){
        rebalanceCounter++;
        if(rebalanceCounter % 3 == 0){
            populateWithItems();
            dropItemBFS();
        }
    }
    rebalance = false;

    // you might need to insert some checks / functions here depending on your implementation
}


MapNode* Map::remove(MapNode* node, Isle* isle) {
    if (node == nullptr) {
        return nullptr;
    }

    if (isle->getName() > node->isle->getName()) { 
        node->right = remove(node->right, isle);
    }
    
    else if (isle->getName() < node->isle->getName()) { 
        node->left = remove(node->left, isle);
    }
    
    else { 
        
        if (node->left != nullptr) { 
            MapNode* p = node->left;

            while (p->right != nullptr) {
                p = p->right;
            }

            node->isle = p->isle; 
          
            node->left = remove(node->left, p->isle); 
        }
      
        else if (node->right != nullptr) {
            return node->right;
        }
     
        else {
            return nullptr;
        }
    }


    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        rebalance = true;
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        rebalance = true;
        return rotateLeft(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        rebalance = true;
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        rebalance = true;
        return rotateLeft(node);
    }

    return node;
}


void Map::remove(Isle *isle)
{
    root = remove((root), isle);
    // you might need to insert some checks / functions here depending on your implementation
    if(rebalance == true){
        rebalanceCounter++;
        if(rebalanceCounter % 3 == 0){
            populateWithItems();
            dropItemBFS();
        }
    }
    rebalance = false;
}

void Map::preOrderItemDrop(MapNode *current, int &count)
{
    // TODO: Drop EINSTEINIUM according to rules
    // Use std::cout << "[Item Drop] " << "EINSTEINIUM dropped on Isle: " << current->isle->getName() << std::endl;
    if(current == nullptr){
        return;
    }

    count++;
    if (count % 5 == 0) { 
        std::cout << "[Item Drop] EINSTEINIUM dropped on Isle: " << current->isle->getName() << std::endl;
        current->isle->setItem(EINSTEINIUM); 
    }

    preOrderItemDrop(current->left, count);
    preOrderItemDrop(current->right, count);
}

// to Display the values by Post Order Method .. left - right - node
void Map::postOrderItemDrop(MapNode *current, int &count)
{
    // TODO: Drop GOLDIUM according to rules
    // Use  std::cout << "[Item Drop] " << "GOLDIUM dropped on Isle: " << current->isle->getName() << std::endl;
    if(current == nullptr){
        return;
    }

    postOrderItemDrop(current->left, count);
    postOrderItemDrop(current->right, count);
    count++;
    if(count % 3 == 0){
        std::cout << "[Item Drop] " << "GOLDIUM dropped on Isle: " << current->isle->getName() << std::endl;
        current->isle->setItem(GOLDIUM); 
    }
}

MapNode *Map::findFirstEmptyIsle(MapNode *node)
{
    // TODO: Find first Isle with no item
    if(node == nullptr){
        return node;
    }
    
    std::queue<MapNode*> q;
    q.push(node);

    while(!q.empty()) {
        MapNode* current = q.front();
        q.pop();
        if (current->isle->getItem() == EMPTY) {
            return current;
        }

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }

    }
    return nullptr;
}

void Map::dropItemBFS()
{
    // TODO: Drop AMAZONITE according to rules
    // Use std::cout << "[BFS Drop] " << "AMAZONITE dropped on Isle: " << targetNode->isle->getName() << std::endl;
    // Use std::cout << "[BFS Drop] " << "No eligible Isle found for AMAZONITE drop." << std::endl;
    MapNode* targetNode = findFirstEmptyIsle(root);
    if (targetNode != nullptr) {
        std::cout << "[BFS Drop] " << "AMAZONITE dropped on Isle: " << targetNode->isle->getName() << std::endl;
        targetNode->isle->setItem(AMAZONITE);  
    } else {
        std::cout << "[BFS Drop] " << "No eligible Isle found for AMAZONITE drop." << std::endl;
    }
}

void Map::displayMap()
{
    std::cout << "[World Map]" << std::endl;
    display(root, 0, 0);
}

int Map::getDepth(MapNode *node)
{
    // TODO: Return node depth if found, else
    if(node == nullptr){
        return 0;
    }
    int leftDepth = getDepth(node->left);
    int rightDepth = getDepth(node->right);
    return std::max(leftDepth, rightDepth) + 1;
}

// Function to calculate the depth of a specific node in the AVL tree
int Map::getIsleDepth(Isle *isle)
{
    // TODO: Return node depth by isle if found, else
    MapNode *node = findNode(*isle);
    if (node == nullptr) {
        return 0; 
    }
    int depth = getDepth(node);
    return getDepth() - depth;
}

int Map::getDepth()
{
    // TODO: Return max|total depth of tree
    return getDepth(root);
}

void Map::populateWithItems()
{
    // TODO: Distribute fist GOLDIUM than EINSTEINIUM
    int count = 0;
    postOrderItemDrop(root, count);
    count = 0;
    preOrderItemDrop(root, count);
}

Isle *Map::findIsle(Isle isle)
{
    // TODO: Find isle by value
    return findIsle(isle.getName());
}

Isle *Map::findIsle(std::string name)
{
    // TODO: Find isle by name
    MapNode *current = root;

    while (current != nullptr) {
        if (name == current->isle->getName()) {
            return current->isle;
        } 

        else if (name < current->isle->getName()) {
            current = current->left;
        } 

        else if (name > current->isle->getName()) {
            current = current->right;
        } 
        
    }
    return nullptr;
}

MapNode *Map::findNode(Isle isle)
{
    // TODO: Find node by value
    return findNode(isle.getName());
}

MapNode *Map::findNode(std::string name)
{
    // TODO: Find node by name
    MapNode *current = root;
    while (current != nullptr) {
        if (name == current->isle->getName()) {
            return current;  
        } else if (name < current->isle->getName()) {
            current = current->left;  
        } else if(name > current->isle->getName()) {
            current = current->right;  
        }
    }
    return nullptr;
}

void Map::display(MapNode *current, int depth, int state)
{
    // SOURCE:

    if (current->left)
        display(current->left, depth + 1, 1);

    for (int i = 0; i < depth; i++)
        printf("     ");

    if (state == 1) // left
        printf("   ┌───");
    else if (state == 2) // right
        printf("   └───");

    std::cout << "[" << *current->isle << "] - (" << current->height << ")\n"
              << std::endl;

    if (current->right)
        display(current->right, depth + 1, 2);
}

void Map::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output level by level
    if(root == nullptr){
        return;
    }
    std::ofstream file(filename);
    if(!file.is_open()){
        std::cerr << "File cannot opened"<< std::endl;
        return;
    }
    std::queue<MapNode*> q;
    q.push(root);
    while (!q.empty()) {
        MapNode *current = q.front();
        q.pop();
        file << current->isle->getName() << std::endl;
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    file.close();
}

void Map::inorderTraversal(MapNode *node, std::ofstream &outputFile) {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left, outputFile);

    outputFile << node->isle->getName() << std::endl;

    inorderTraversal(node->right, outputFile);
}

void Map::writeIslesToFile(const std::string &filename)
{
    // TODO: Write Isles to output file in alphabetical order
    // Use std::cout << "[Output] " << "Isles have been written to " << filename << " in in alphabetical order." << std::endl;
    std::ofstream outputFile(filename);
    if(!outputFile.is_open()){
        std::cerr << "File cannot opened"<< std::endl;
        return;
    }
    inorderTraversal(root, outputFile);
    outputFile.close();
    std::cout << "[Output] Isles have been written to " << filename << " in alphabetical order." << std::endl;
}