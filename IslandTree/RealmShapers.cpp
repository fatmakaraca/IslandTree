#include "RealmShapers.h"
#include <cmath>
#include <algorithm>

ShaperTree::ShaperTree()
{
}

ShaperTree::~ShaperTree()
{
    // TODO: Free any dynamically allocated memory if necessary
}

void ShaperTree::initializeTree(std::vector<RealmShaper *> shapers)
{
    // TODO: Insert innitial shapers to the tree
    for (RealmShaper *shaper : shapers) {
        insert(shaper); 
    }
}

int ShaperTree::getSize()
{
    // TODO: Return number of shapers in the tree
    return realmShapers.size();
    return 0;
}


std::vector<RealmShaper *> ShaperTree::getTree()
{
    return realmShapers;
}

bool ShaperTree::isValidIndex(int index)
{
    bool isValid = false;

    // TODO: Check if the index is valin in the tree
    if (index >= 0 && index < realmShapers.size()){
        isValid = true;
    }
      
    return isValid;
}

void ShaperTree::insert(RealmShaper *shaper)
{
    // TODO: Insert shaper to the tree
    realmShapers.push_back(shaper);

}

int ShaperTree::remove(RealmShaper *shaper)
{
    // TODO: Remove the player from tree if it exists
    // Make sure tree protects its form (complate binary tree) after deletion of a node
    // return index if found and removed
    int index = findIndex(shaper);
    if(index != -1){
        realmShapers.erase(realmShapers.begin() + index);
        return index;
    }
    // else
    return -1;
}

int ShaperTree::findIndex(RealmShaper *shaper)
{
    // return index in the tree if found
    for(int i = 0; i < realmShapers.size(); ++i){
        if (realmShapers[i] == shaper)
        {
            return i;
        }
    }
    // else
    return -1;
}

int ShaperTree::getDepth(RealmShaper *shaper)
{
    // return depth of the node in the tree if found
    int index = findIndex(shaper);
    if(index != -1){
        return static_cast<int>(std::ceil(std::log2(index + 2))) - 1;
    }
    // else
    return -1;
}

int ShaperTree::getDepth()
{
    // return total|max depth|height of the tree
    if(!realmShapers.empty()){
        return static_cast<int>(std::ceil(std::log2(realmShapers.size() + 1)));
    }
    return 0;
}

RealmShaper ShaperTree::duel(RealmShaper *challenger, bool result)
{
    // TODO: Implement duel logic, return the victor
    // Use   std::cout << "[Duel] " << victorName << " won the duel" << std::endl;
    // Use   std::cout << "[Honour] " << "New honour points: ";
    // Use   std::cout << challengerName << "-" << challengerHonour << " ";
    // Use   std::cout << opponentName << "-" << opponentHonour << std::endl;
    // Use   std::cout << "[Duel] " << loserName << " lost all honour, delete" << std::endl;
    
    
    if (challenger == realmShapers[0]) {
        return *challenger;
    }
    RealmShaper *opponent = getParent(challenger);
    RealmShaper *winner;
    RealmShaper *loser;
    if (result){
        winner = challenger;
        loser = opponent;

        challenger->gainHonour();
        opponent->loseHonour();
        replace(challenger, opponent);
        std::cout << "[Duel] " << challenger->getName() << " won the duel" << std::endl;
        std::cout << "[Honour] " << "New honour points: ";
        std::cout << challenger->getName() << "-" << challenger->getHonour() << " ";
        std::cout << opponent->getName() << "-" << opponent->getHonour() << std::endl;

        if(opponent->getHonour() <= 0){
            std::cout << "[Duel] " << opponent->getName() << " lost all honour, delete" << std::endl;
            remove(opponent);
        }

        return *winner;

        
    }else {
        winner = opponent;
        loser = challenger;

        challenger->loseHonour();
        opponent->gainHonour();
        std::cout << "[Duel] " << challenger->getName() << " lost the duel" << std::endl;
        std::cout << "[Honour] " << "New honour points: ";
        std::cout << challenger->getName() << " - " << challenger->getHonour() << " ";
        std::cout << opponent->getName() << " - " << opponent->getHonour() << std::endl;
        if(challenger->getHonour() <= 0){
            std::cout << "[Duel] " << challenger->getName() << " lost all honour, delete" << std::endl;
            remove(challenger);
        }
        
        return *winner;
        
    }
    return *winner;
}

/*RealmShaper ShaperTree::duel(RealmShaper *challenger, bool result)
{
    if (challenger == realmShapers[0]) {
        return *challenger;
    }
    RealmShaper *opponent = getParent(challenger);
    
    
    
    // Kazanan ve kaybedeni belirle
    RealmShaper *winner = result ? challenger : opponent;
    RealmShaper *loser = result ? opponent : challenger;

    // Onur puanlarını güncelle
    winner->gainHonour();
    loser->loseHonour();

    // Kazanan ve kaybeden hakkında bilgi yazdır
    if(result){
        std::cout << "[Duel] " << winner->getName() << " won the duel" << std::endl;
    }else{
        std::cout << "[Duel] " << loser->getName() << " lost the duel" << std::endl;
    }
    
    std::cout << "[Honour] New honour points: " << winner->getName() << "-" << winner->getHonour() 
              << " " << loser->getName() << "-" << loser->getHonour() << std::endl;

    // Onuru sıfırlanan kaybedeni sil
    if (loser->getHonour() <= 0) {
        std::cout << "[Duel] " << loser->getName() << " lost all honour, delete" << std::endl;
        remove(loser);
    }

    // Kazananı döndür
    return *winner;
}*/


RealmShaper *ShaperTree::getParent(RealmShaper *shaper)
{
    RealmShaper *parent = nullptr;

    // TODO: return parent of the shaper
    int index = findIndex(shaper);
    if (index != -1 && index > 0) { 
        int parentIndex = (index - 1) / 2;
        parent = realmShapers[parentIndex]; 
    }

    return parent;
}

void ShaperTree::replace(RealmShaper *player_low, RealmShaper *player_high)
{
    // TODO: Change player_low and player_high's positions on the tree
    std::swap(realmShapers[findIndex(player_low)], realmShapers[findIndex(player_high)]);
}

RealmShaper *ShaperTree::findPlayer(RealmShaper shaper)
{
    RealmShaper *foundShaper = nullptr;

    // TODO: Search shaper by object
    // Return the shaper if found
    // Return nullptr if shaper not found

    for (RealmShaper* currentShaper : realmShapers) {
        if (*currentShaper == shaper) { 
            foundShaper = currentShaper;
            break;
        }
    }
    return foundShaper;
}

// Find shaper by name
RealmShaper *ShaperTree::findPlayer(std::string name)
{
    RealmShaper *foundShaper = nullptr;

    // TODO: Search shaper by name
    // Return the shaper if found
    // Return nullptr if shaper not found

    for (RealmShaper* currentShaper : realmShapers) {
        if (currentShaper->getName() == name) {
            foundShaper = currentShaper; 
            break;  
        }
    }

    return foundShaper;
}

void ShaperTree::inorderTraversal(const std::vector<RealmShaper>& tree, int index, std::vector<std::string>& result) {
    if (index >= tree.size()) {
        return;
    }

    
    inorderTraversal(tree, 2 * index + 1, result);
    result.push_back(tree[index].getName());
    inorderTraversal(tree, 2 * index + 2, result);
}

std::vector<std::string> ShaperTree::inOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement inOrderTraversal in tree
    // Add all to a string vector
    // Return the vector

    // Define and implement as many helper functions as necessary for recursive implementation

    // Note: Since SheperTree is not an binary search tree,
    // in-order traversal will not give rankings in correct order
    // for correct order you need to implement level-order traversal
    // still you are to implement this function as well

    std::vector<RealmShaper> realmShapersCopy;
    for (RealmShaper* shaper : realmShapers) {
        realmShapersCopy.push_back(*shaper); 
    }
    inorderTraversal(realmShapersCopy, index, result);
    
    return result;
}

void ShaperTree::preorderTraversal(const std::vector<RealmShaper>& tree, int index, std::vector<std::string>& result) {
    if (index >= tree.size()) {
        return;
    }

    result.push_back(tree[index].getName());
    preorderTraversal(tree, 2 * index + 1, result);
    preorderTraversal(tree, 2 * index + 2, result);
}

std::vector<std::string> ShaperTree::preOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement preOrderTraversal in tree
    // Add all to a string vector
    // Return the vector
    std::vector<RealmShaper> realmShapersCopy;
    for (RealmShaper* shaper : realmShapers) {
        realmShapersCopy.push_back(*shaper); 
    }
    preorderTraversal(realmShapersCopy, index, result);
    // Define and implement as many helper functions as necessary for recursive implementation
    return result;
}

void ShaperTree::postorderTraversal(const std::vector<RealmShaper>& tree, int index, std::vector<std::string>& result) {
    if (index >= tree.size()) {
        return;
    }

    postorderTraversal(tree, 2 * index + 1, result);
    postorderTraversal(tree, 2 * index + 2, result);
    result.push_back(tree[index].getName());
}

std::vector<std::string> ShaperTree::postOrderTraversal(int index)
{
    std::vector<std::string> result = {};
    // TODO: Implement postOrderTraversal in tree
    // Add all to a string vector
    // Return the vector
    std::vector<RealmShaper> realmShapersCopy;
    for (RealmShaper* shaper : realmShapers) {
        realmShapersCopy.push_back(*shaper); 
    }
    postorderTraversal(realmShapersCopy, index, result);
    // Define and implement as many helper functions as necessary for recursive implementation
    return result;
}

void ShaperTree::preOrderTraversal(int index, std::ofstream &outFile)
{
    // TODO: Implement preOrderTraversal in tree
    // write nodes to output file
    // Define and implement as many helper functions as necessary for recursive implementation
     std::vector<std::string> result = preOrderTraversal(index);

    if (!outFile.is_open()) {
        std::cerr << "File cannot be opened" << std::endl;
        return;
    }

    for (const std::string& name : result) {
        outFile << name << std::endl;
    }
    
}

void ShaperTree::breadthFirstTraversal(std::ofstream &outFile)
{
    // TODO: Implement level-order traversal
    // write nodes to output file

    // Define and implement as many helper functions as necessary
    int size = realmShapers.size();
    for (int i = 0; i < size; ++i) {
        outFile << realmShapers[i]->getName() << std::endl;
    }

}

void ShaperTree::displayTree()
{
    std::cout << "[Shaper Tree]" << std::endl;
    printTree(0, 0, "");
}

// Helper function to print tree with indentation
void ShaperTree::printTree(int index, int level, const std::string &prefix)
{
    if (!isValidIndex(index))
        return;

    std::cout << prefix << (level > 0 ? "   └---- " : "") << *realmShapers[index] << std::endl;
    int left = 2 * index + 1;  // TODO: Calculate left index
    int right = 2 * index + 2; // TODO: Calculate right index

    if (isValidIndex(left) || isValidIndex(right))
    {
        printTree(left, level + 1, prefix + (level > 0 ? "   │   " : "")); // ╎
        printTree(right, level + 1, prefix + (level > 0 ? "   │   " : ""));
    }
}

void ShaperTree::writeShapersToFile(const std::string &filename)
{
    // TODO: Write the shapers to filename output level by level
    // Use std::cout << "[Output] " << "Shapers have been written to " << filename << " according to rankings." << std::endl;
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "File cannot be opened: " << filename << std::endl;
        return;
    }
    for (RealmShaper* shaper : realmShapers)
    {
        if (shaper != nullptr) 
        {
            outFile << shaper->getName() << std::endl;
        }
    }

    outFile.close();
    std::cout << "[Output] " << "Shapers have been written to " << filename << " according to rankings." << std::endl;
    
}

void ShaperTree::writeToFile(const std::string &filename)
{
    // TODO: Write the tree to filename output pre-order
    // Use std::cout << "[Output] " << "Tree have been written to " << filename << " in pre-order." << std::endl;
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "File cannot be opened: " << filename << std::endl;
        return;
    }
    preOrderTraversal(0, outFile);
    outFile.close();
    std::cout << "[Output] " << "Tree have been written to " << filename << " in pre-order." << std::endl;
    
}


bool ShaperTree::contains(RealmShaper* realmShaper) {
    for (auto& shaper : realmShapers) {
        if (shaper == realmShaper) {
            return true;
        }
    }
    return false;
}