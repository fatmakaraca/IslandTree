#include "GameWorld.h"
#include "Map.h"
#include <algorithm>


GameWorld::GameWorld() : mapTree(), shaperTree() {}

void GameWorld::initializeGame(std::vector<Isle *> places, std::vector<RealmShaper *> players)
{
    shaperTree.initializeTree(players);
    mapTree.initializeMap(places);
}

Map& GameWorld::getMapTree()
{
    return mapTree;
}
ShaperTree& GameWorld::getShaperTree()
{
    return shaperTree;
}

bool GameWorld::hasAccess(RealmShaper *realmShaper, Isle *isle)
{
    bool hasAccess = false;

    // TODO: Check if the realmShaper has access to explore the isle
    // Get necessary depth values
    // Use mapTree.calculateMinMapDepthAccess
    // Use // std::cout << "[Access Control] " << "RealmShaper not found!" << std::endl;
    if (realmShaper == nullptr) {
        std::cout << "[Access Control] " << "RealmShaper not found!" << std::endl;
        return hasAccess;
    }
    MapNode* node = mapTree.findNode(*isle);
    if (node == nullptr) {
        return hasAccess;
    }
    int playerDepth = 0;
    int totalShaperTreeHeight = 0;
    int totalMapDepth = 0;
    playerDepth = shaperTree.getDepth(realmShaper);
    totalShaperTreeHeight = shaperTree.getDepth();
    totalMapDepth = mapTree.getDepth();
    int minMapDepthAccess = mapTree.calculateMinMapDepthAccess(playerDepth, totalShaperTreeHeight, totalMapDepth);
    int realmShaperAccessLevel = mapTree.getIsleDepth(isle); 

    if (realmShaperAccessLevel >= minMapDepthAccess) {
        hasAccess = true;
    }

    return hasAccess;
}

void GameWorld::exploreArea(RealmShaper *realmShaper, Isle *isle)
{
    // TODO:
    // Check if realmShaper has access
    // Use // std::cout << "[Explore Area] " << realmShaper->getName() << " does not have access to explore area " << *isle << std::endl;
    if(hasAccess(realmShaper, isle)==false){
        std::cout << "[Explore Area] " << realmShaper->getName() << " does not have access to explore area " << *isle << std::endl;
        return;
    }
    // If realmShaper has access
    // Visit isle, 
    // collect item, 
    // check overcrowding for Isle, 
    // delete Isle if necessary

    for (auto it = isle->visitorRealmShapers.begin(); it != isle->visitorRealmShapers.end();) {
        std::string visitorName = *it;
        RealmShaper* visitor = shaperTree.findPlayer(visitorName);
        
        if (!shaperTree.contains(visitor)) {
            isle->deleteRealmShaper(visitorName);
        } else {
            ++it;
        }
    }

    if(isle->overcrowding() == false){
        isle->addRealmShaper(realmShaper->getName());
        realmShaper->collectItem(isle->getItem());
        std::cout << "[Explore Area] " << realmShaper->getName() << " visited " << isle->getName() << std::endl;
        std::cout << "[Energy] " << realmShaper->getName() << "'s new energy level is " << realmShaper->getEnergyLevel() << std::endl;
       
        for (auto &otherIsle : mapTree.isleList) {
            if (otherIsle != isle) { 
                auto &visitors = otherIsle->visitorRealmShapers;
                auto it = std::find(visitors.begin(), visitors.end(), realmShaper->getName());
                if (it != visitors.end()) {
                    otherIsle->deleteRealmShaper(realmShaper->getName());
                }
            }
        }

        
    } else {
        isle->addRealmShaper(realmShaper->getName());
        realmShaper->collectItem(isle->getItem());
        std::cout << "[Explore Area] " << realmShaper->getName() << " visited " << isle->getName() << std::endl;
        std::cout << "[Energy] " << realmShaper->getName() << "'s new energy level is " << realmShaper->getEnergyLevel() << std::endl;
        
        mapTree.remove(isle);
        std::cout << "[Owercrowding] " << isle->getName() << " self-destructed, it will be removed from the map" << std::endl;
    }
    
    // Use // std::cout << "[Explore Area] " << realmShaper->getName() << " visited " << isle->getName() << std::endl;
    // Use // std::cout << "[Energy] " << realmShaper->getName() << "'s new energy level is " << realmShaper->getEnergyLevel() << std::endl;
    // Use // std::cout << "[Owercrowding] " << isle->getName() << " self-destructed, it will be removed from the map" << std::endl;

    // You will need to implement a mechanism to keep track of how many realm shapers are at an Isle at the same time
    // There are more than one ways to do this, so it has been left completely to you
    // Use shaperCount, but that alone will not be enough,
    // you will likely need to add attributes that are not currently defined
    // to RealmShaper or Isle or other classes depending on your implementation
}


void GameWorld::craft(RealmShaper *shaper, const std::string &isleName){
    // TODO: Check energy and craft new isle if possible
    // Use std::cout << "[Energy] " << shaperName << " has enough energy points: " << shaperEnergyLevel << std::endl;
    // Use std::cout << "[Craft] " << shaperName << " crafted new Isle " << isleName << std::endl;
    // Use std::cout << "[Energy] " << shaperName << " does not have enough energy points: " << shaperEnergyLevel << std::endl;
    //std::cout << "c1" << std::endl;
    
    if(shaper->hasEnoughEnergy() == true){
        std::cout << "[Energy] " << shaper->getName() << " has enough energy points: " << shaper->getEnergyLevel() << std::endl;
        std::cout << "[Craft] " << shaper->getName() << " crafted new Isle " << isleName << std::endl;
        Isle* isle = new Isle(isleName);
        mapTree.insert(isle);
        shaper->loseEnergy();
    }else{
        std::cout << "[Energy] " << shaper->getName() << " does not have enough energy points: " << shaper->getEnergyLevel() << std::endl;
    }
}

void GameWorld::displayGameState()
{
    //mapTree.displayMap();
    //shaperTree.displayTree();
}

// TODO: Implement functions to read and parse Access and Duel logs

void GameWorld::processGameEvents(const std::string &accessLogs, const std::string &duelLogs)
{
    // TODO:
    // Read logs
    // For every 5 access, 1 duel happens
    // If there are still duel logs left after every access happens duels happens one after other

    // This function should call exploreArea and craft functions

    // Use displayGameState();

    std::ifstream accessFile(accessLogs);  // Access log dosyasını açıyoruz
    if (!accessFile.is_open()) {
        std::cerr << "Access log file could not be opened!" << std::endl;
        return;
    }

    std::ifstream duelFile(duelLogs);
    if (!duelFile.is_open()) {
        std::cerr << "Duel log file could not be opened!" << std::endl;
        return;
    }

    std::string accessEvent;
    std::getline(accessFile, accessEvent);

    std::string duelEvent;

    std::getline(duelFile, duelEvent);
    
    int accessCounter = 0;
    int duelCounter = 0;

    while(std::getline(accessFile, accessEvent)){
        if (accessEvent.empty()) continue;
    
        std::istringstream accessDetails(accessEvent);
        std::string playerName, placeName;
        std::getline(accessDetails, playerName, ' ');
        std::getline(accessDetails, placeName);

        RealmShaper *player = shaperTree.findPlayer(playerName);
        Isle *place = mapTree.findIsle(placeName);
     
        if (!place)
        {
            craft(player, placeName);
        }

        if (player && place)
        {
            exploreArea(player, place);
        }
        accessCounter++;

        if (accessCounter % 5 == 0)
        {
            if (std::getline(duelFile, duelEvent))
            {
                std::istringstream duelDetails(duelEvent);
                std::string challengerName, resultStr;
                std::getline(duelDetails, challengerName, ' ');
                std::getline(duelDetails, resultStr);

                bool result = (resultStr == "   1");
                

                RealmShaper *challenger = shaperTree.findPlayer(challengerName);

                if (challenger)
                {
                    shaperTree.duel(challenger, result);
    
                }
                duelCounter++;
            }
        }
        displayGameState();

    }

    accessFile.close();

    while (std::getline(duelFile, duelEvent))
    {
        if (duelEvent.empty()) continue;
        std::istringstream duelDetails(duelEvent);
        std::string challengerName, resultStr;
        std::getline(duelDetails, challengerName, ' ');
        std::getline(duelDetails, resultStr);

        
        bool result = (resultStr == "   1");
       

        RealmShaper *challenger = shaperTree.findPlayer(challengerName);
        
        if (challenger)
        {
            shaperTree.duel(challenger, result);
        } 
        duelCounter++;

        displayGameState();
    }
    duelFile.close();
}

void GameWorld::saveGameState(const std::string &currentIsles, const std::string &currentWorld, const std::string &currentShapers, const std::string &currentPlayerTree)
{
    mapTree.writeIslesToFile(currentIsles);
    mapTree.writeToFile(currentWorld);
    shaperTree.writeToFile(currentPlayerTree);
    shaperTree.writeShapersToFile(currentShapers);
}