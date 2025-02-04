# IslandTree

This project involves a new character class called "Realm Shapers" and the associated game mechanics.

1. New Character Class: Realm Shapers
   
Shaper Tree: Realm Shapers are placed in a hierarchy within the game world. This hierarchy is defined by a Shaper Tree, structured as a binary tree. New players are always added from left to right in this tree, and their ranking level is connected to the islands they can access.

Duels: Realm Shapers can engage in duels with their superior players (i.e., their parents) to gain a chance to rise in rank. Winning a duel changes the players' ranking positions.

Access: The number of islands players can explore in the game world is based on their position in the Shaper Tree. The players' access levels are calculated based on their depth in the tree.

2. Game World: AVL Trees

World Tree (Map): The world consists of islands, and the World Tree is balanced using an AVL tree structure. This ensures quick access to the islands in the game world. The islands can contain special items, which Realm Shapers can collect.

Items: Items consist of various types of resources (e.g., Goldium, Einsteinium, Amazonite) and are placed on the islands based on certain rules. For example:

Every third island is enriched with Goldium using post-order traversal.

Every fifth island is enriched with Einsteinium using pre-order traversal.

Every third balancing operation in the AVL tree results in an Amazonite item being placed on one of the islands.

Tree Balancing and Destruction: If an island is visited by a Realm Shaper beyond its capacity, the island will be destroyed, and the world will rebalance itself.

3. Game Mechanics

Game Logs: The game is driven by access and duel logs:

Access Log (access.log): Players attempt to access islands.

Duel Log (duels.log): Players engage in duels with each other.

Every five access logs will trigger a duel log entry, and after each action, the Shaper Tree and World Tree will be displayed in the terminal.

4. Files: Input/Output
   
initial_realm_shapers.txt: This file contains the names and details of the players used to test the Realm Shaper class. These players should be added to the Shaper Tree in the same order.

current_realm_shapers.txt: This file stores the updated player information after the game starts.

initial_world.txt and current_isles.txt: Files that contain information about the islands on the map. These files store the status of the islands and related item data.

Extra Features: Single Player Demo

In a single-player demo mode, players can:

Menu System: Players can engage in duels, explore islands, and create new islands.
Dynamic Updates: After every action, the Shaper Tree and World Tree will be displayed in the terminal.
Duel: Players answer questions to engage in duels, and won duels affect their ranking.

Project Goal

This project focuses on key software engineering topics such as binary trees (AVL trees), dynamic memory management, file I/O, operator overloading, and game world simulation.
