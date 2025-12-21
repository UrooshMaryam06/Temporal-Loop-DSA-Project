#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
using namespace std;

// =====================
// Helper Functions
// =====================
void typeWriter(const string &text, int delayMs = 25) {
    for (char c : text) {
        cout << c;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    cout << endl;
}

class GameFileManager {
private:
    string saveFileName;
    string progressFileName;
    string highScoreFileName;

public:
    GameFileManager() {
        saveFileName = "temporal_savegame.txt";
        progressFileName = "temporal_progress.txt";
        highScoreFileName = "temporal_highscores.txt";
    }

    // Save complete game state
    bool saveGameState(string playerName, int currentChapter, int currentRoom, 
                       int playerScore, int loopCount, 
                       bool cluesCollected[10], int suspicionLevels[4]) {
        ofstream outFile(saveFileName);
        
        if (!outFile.is_open()) {
            cout << "\n>>> ERROR: Could not save game!\n";
            return false;
        }

        outFile << "PLAYER_NAME:" << playerName << endl;
        outFile << "CHAPTER:" << currentChapter << endl;
        outFile << "ROOM:" << currentRoom << endl;
        outFile << "SCORE:" << playerScore << endl;
        outFile << "LOOP_COUNT:" << loopCount << endl;

        outFile << "CLUES:";
        for (int i = 0; i < 10; i++) {
            outFile << cluesCollected[i] << " ";
        }
        outFile << endl;

        outFile << "SUSPICIONS:";
        for (int i = 0; i < 4; i++) {
            outFile << suspicionLevels[i] << " ";
        }
        outFile << endl;

        outFile.close();
        
        cout << "\n==> Game saved successfully to " << saveFileName << "\n";
        return true;
    }

    // Load complete game state
    bool loadGameState(string &playerName, int &currentChapter, int &currentRoom,
                       int &playerScore, int &loopCount,
                       bool cluesCollected[10], int suspicionLevels[4]) {
        ifstream inFile(saveFileName);
        
        if (!inFile.is_open()) {
            return false;
        }

        string line;
        
        getline(inFile, line);
        if (line.find("PLAYER_NAME:") != string::npos) {
            playerName = line.substr(12);
        }

        getline(inFile, line);
        if (line.find("CHAPTER:") != string::npos) {
            currentChapter = stoi(line.substr(8));
        }

        getline(inFile, line);
        if (line.find("ROOM:") != string::npos) {
            currentRoom = stoi(line.substr(5));
        }

        getline(inFile, line);
        if (line.find("SCORE:") != string::npos) {
            playerScore = stoi(line.substr(6));
        }

        getline(inFile, line);
        if (line.find("LOOP_COUNT:") != string::npos) {
            loopCount = stoi(line.substr(11));
        }

        getline(inFile, line);
        if (line.find("CLUES:") != string::npos) {
            string clueData = line.substr(6);
            int idx = 0;
            for (int i = 0; i < 10 && idx < clueData.length(); i++) {
                cluesCollected[i] = (clueData[idx] == '1');
                idx += 2;
            }
        }

        getline(inFile, line);
        if (line.find("SUSPICIONS:") != string::npos) {
            string suspData = line.substr(11);
            int idx = 0, suspIdx = 0;
            string numStr = "";
            for (int i = 0; i < suspData.length(); i++) {
                if (suspData[i] == ' ') {
                    if (numStr != "" && suspIdx < 4) {
                        suspicionLevels[suspIdx++] = stoi(numStr);
                        numStr = "";
                    }
                } else {
                    numStr += suspData[i];
                }
            }
            if (numStr != "" && suspIdx < 4) {
                suspicionLevels[suspIdx] = stoi(numStr);
            }
        }

        inFile.close();
        
        cout << "\n==> Game loaded: " << playerName << " | Chapter " << currentChapter 
             << " | Score " << playerScore << "\n";
        return true;
    }

    // Save chapter completion log
    void saveChapterProgress(int chapter, string chapterName, int score) {
        ofstream outFile(progressFileName, ios::app);
        
        if (outFile.is_open()) {
            outFile << "CHAPTER_" << chapter << ":" << chapterName 
                   << ":SCORE_" << score << endl;
            outFile.close();
        }
    }

    // Save final high score
    void saveHighScore(string playerName, int finalScore, int loopCount) {
        ofstream outFile(highScoreFileName, ios::app);
        
        if (outFile.is_open()) {
            outFile << playerName << "," << finalScore << "," << loopCount << endl;
            outFile.close();
            cout << "\n==> High score saved to " << highScoreFileName << "\n";
        }
    }

    // Display all high scores
    void displayHighScores() {
        ifstream inFile(highScoreFileName);
        
        cout << "\n============================================\n";
        cout << "           HIGH SCORES\n";
        cout << "============================================\n";
        
        if (!inFile.is_open()) {
            cout << "  No high scores yet!\n";
            return;
        }

        string line;
        int rank = 1;
        while (getline(inFile, line)) {
            cout << rank++ << ". " << line << endl;
        }
        
        inFile.close();
    }

    // Export suspect data to file
    void exportSuspectData(string names[4], int suspicions[4]) {
        ofstream outFile("temporal_suspects.txt");
        
        if (outFile.is_open()) {
            outFile << "=== SUSPECT DATABASE EXPORT ===\n\n";
            for (int i = 0; i < 4; i++) {
                outFile << "Suspect: " << names[i] << endl;
                outFile << "Suspicion Level: " << suspicions[i] << "/10" << endl;
                outFile << "Status: " << (suspicions[i] >= 7 ? "HIGH RISK" : "MONITORING") << endl;
                outFile << "-----------------------------------\n";
            }
            outFile.close();
            cout << "==> Suspect data exported to temporal_suspects.txt\n";
        }
    }
};
// Add this as a member variable in Story class:
GameFileManager fileManager;

// Add this helper method in Story class:
void autoSaveProgress(int chapter, string chapterName, int score) {
    fileManager.saveChapterProgress(chapter, chapterName, score);
    cout << "==> Progress auto-saved.\n";
}
// Read choice from user with validation
int readChoice(int minOption, int maxOption) {
    int choice;
    bool valid = false;

    while (!valid) {
        cout << "Enter your choice (" << minOption << "-" << maxOption << "): ";
        if (cin >> choice) {
            if (choice >= minOption && choice <= maxOption) valid = true;
            else cout << "Invalid option. Try again.\n";
        } else {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
        }
        cin.ignore(1000, '\n');
    }

    return choice;
}

//                                        ===================================
//                                                  Global Game Data
//                                        ===================================

//Initializing Timeline Function 
void displayChapterTimeline(int chapter);


// ===============================
// LINKED LIST OF SUSPECTS
// ===============================
    struct SuspectNode {
        int id;
        string name;
        string role;
        int suspicionLevel;
        string lastKnownLocation;
        string alibi;
        SuspectNode* next;
    };

    class SuspectLinkedList {
    private:
        SuspectNode* head;
        int count;

    public:
        SuspectLinkedList() {
            head = nullptr;
            count = 0;
            initializeSuspects();
        }

        void initializeSuspects() {
            addSuspect(1, "Dr. Elena Markov", "Lead Scientist", 7, "Research Wing", 
                    "Claims was running diagnostics");
            addSuspect(2, "Commander Hayes", "Security Chief", 5, "Security Sector", 
                    "Says was monitoring perimeter");
            addSuspect(3, "Dr. Chen Wei", "Temporal Engineer", 8, "Control Hall", 
                    "Working on engine calibration");
            addSuspect(4, "Sarah Mitchell", "Systems Analyst", 4, "Data Archives", 
                    "Reviewing system logs");
        }

        void addSuspect(int id, string name, string role, int suspicion, 
                    string location, string alibi) {
            SuspectNode* newNode = new SuspectNode;
            newNode->id = id;
            newNode->name = name;
            newNode->role = role;
            newNode->suspicionLevel = suspicion;
            newNode->lastKnownLocation = location;
            newNode->alibi = alibi;
            newNode->next = head;
            head = newNode;
            count++;
        }

        void updateSuspicion(string name, int newLevel) {
            SuspectNode* temp = head;
            while (temp) {
                if (temp->name == name) {
                    temp->suspicionLevel = newLevel;
                    cout << "\n==> " << name << " suspicion updated to " << newLevel << "/10\n";
                    return;
                }
                temp = temp->next;
            }
            cout << "\n-� Suspect not found!\n";
        }

        void sortBySuspicion() {
            if (!head || !head->next) return;

            bool swapped;
            do {
                swapped = false;
                SuspectNode* curr = head;
                SuspectNode* prev = nullptr;
                SuspectNode* next = head->next;

                while (next) {
                    if (curr->suspicionLevel < next->suspicionLevel) {
                        swapped = true;
                        if (prev) {
                            prev->next = next;
                        } else {
                            head = next;
                        }
                        curr->next = next->next;
                        next->next = curr;
                        prev = next;
                        next = curr->next;
                    } else {
                        prev = curr;
                        curr = next;
                        next = next->next;
                    }
                }
            } while (swapped);

            cout << "\n✓ Suspects sorted by suspicion level\n";
        }

        void displaySuspects() {
            cout << "\n============================================================================================================================================================================\n";
            cout << "||              SUSPECT DATABASE                         ||\n";
            cout << "==============================================================================================================================================================================\n";
            
            if (!head) {
                cout << "  No suspects identified.\n";
                return;
            }

            SuspectNode* temp = head;
            int num = 1;
            while (temp) {
                cout << "\n" << num++ << ". " << temp->name << " (" << temp->role << ")\n";
                cout << "   Suspicion Level: " << temp->suspicionLevel << "/10\n";
                cout << "   Last Location: " << temp->lastKnownLocation << "\n";
                cout << "   Alibi: " << temp->alibi << "\n";
                temp = temp->next;
            }
            cout << "\nTotal Suspects: " << count << "\n";
        }

        ~SuspectLinkedList() {
            while (head) {
                SuspectNode* temp = head;
                head = head->next;
                delete temp;
            }
        }
    };

    // ===============================
    // TIMELINE ARRAYS (All Chapters)
    // ===============================
    class TimelineManager {
    private:
        string timelineEvents[10][5];
        int eventCounts[10];

    public:
        TimelineManager() {
            for (int i = 0; i < 10; i++) {
                eventCounts[i] = 0;
            }
            initializeTimelines();
        }

        void initializeTimelines() {
            timelineEvents[0][0] = "07:00 AM - Alarm systems activate";
            timelineEvents[0][1] = "07:05 AM - Scientists rush through halls";
            timelineEvents[0][2] = "07:10 AM - Temporal Engine status: 47%";
            timelineEvents[0][3] = "07:15 AM - Warning lights flash";
            timelineEvents[0][4] = "07:20 AM - Everything fades to white";
            eventCounts[0] = 5;

            timelineEvents[1][0] = "07:00 AM - You wake up... again";
            timelineEvents[1][1] = "07:02 AM - Deja vu overwhelming";
            timelineEvents[1][2] = "07:05 AM - You remember the pattern";
            timelineEvents[1][3] = "07:08 AM - First conscious loop begins";
            timelineEvents[1][4] = "07:10 AM - Memory advantage realized";
            eventCounts[1] = 5;

            timelineEvents[2][0] = "Explore Control Hall";
            timelineEvents[2][1] = "Navigate to Research Wing";
            timelineEvents[2][2] = "Discover Data Archives entrance";
            timelineEvents[2][3] = "Locate Security Sector";
            timelineEvents[2][4] = "Map complete interconnections";
            eventCounts[2] = 5;

            timelineEvents[3][0] = "T+15min - Power flicker detected";
            timelineEvents[3][1] = "T+30min - System malfunction warning";
            timelineEvents[3][2] = "T+45min - Security alert triggered";
            timelineEvents[3][3] = "T+60min - Critical failure imminent";
            timelineEvents[3][4] = "T+75min - Point of no return";
            eventCounts[3] = 5;

            timelineEvents[4][0] = "Confront scientist prematurely";
            timelineEvents[4][1] = "Security protocols activate";
            timelineEvents[4][2] = "Temporal Engine destabilizes";
            timelineEvents[4][3] = "CRITICAL FAILURE DETECTED";
            timelineEvents[4][4] = "TIME RESET TRIGGERED";
            eventCounts[4] = 5;

            timelineEvents[5][0] = "Find corrupted system log";
            timelineEvents[5][1] = "Discover handwritten note";
            timelineEvents[5][2] = "Obtain security clearance key";
            timelineEvents[5][3] = "Piece together pattern";
            timelineEvents[5][4] = "Truth begins to emerge";
            eventCounts[5] = 5;

            timelineEvents[6][0] = "Observe Dr. Markov's behavior";
            timelineEvents[6][1] = "Track Commander Hayes movements";
            timelineEvents[6][2] = "Monitor Dr. Chen's reactions";
            timelineEvents[6][3] = "Analyze Sarah Mitchell's actions";
            timelineEvents[6][4] = "Cross-reference all suspects";
            eventCounts[6] = 5;

            timelineEvents[7][0] = "Critical decision point reached";
            timelineEvents[7][1] = "Multiple paths diverge";
            timelineEvents[7][2] = "Consequences become clear";
            timelineEvents[7][3] = "Reality branches observed";
            timelineEvents[7][4] = "Choice defines outcome";
            eventCounts[7] = 5;

            timelineEvents[8][0] = "Discover pre-loop evidence";
            timelineEvents[8][1] = "Find previous investigator logs";
            timelineEvents[8][2] = "Loop was intentional creation";
            timelineEvents[8][3] = "Safeguard mechanism revealed";
            timelineEvents[8][4] = "Recursive depth understood";
            eventCounts[8] = 5;

            timelineEvents[9][0] = "Sort events by urgency";
            timelineEvents[9][1] = "Organize suspects by threat";
            timelineEvents[9][2] = "Arrange logs chronologically";
            timelineEvents[9][3] = "Data patterns emerge";
            timelineEvents[9][4] = "Truth becomes visible";
            eventCounts[9] = 5;
        }

        void displayChapterTimeline(int chapter) {
            if (chapter < 0 || chapter >= 10) return;
            
            cout << "\n============================================================================================================================================================================\n";
            cout << "||         CHAPTER " << chapter << " TIMELINE EVENTS                     ||\n";
            cout << "==============================================================================================================================================================================\n";
            
            for (int i = 0; i < eventCounts[chapter]; i++) {
                cout << "  " << (i + 1) << ". " << timelineEvents[chapter][i] << "\n";
            }
            cout << "\n";
        }
    };

// ===============================
// STACK FOR ACTION HISTORY
// ===============================
struct ActionNode {
    string action;
    int timestamp;
    string location;
    int chapterNum;
};

class ActionStack {
private:
    ActionNode* stack;
    int top;
    int capacity;

public:
    ActionStack(int cap = 100) {
        capacity = cap;
        stack = new ActionNode[capacity];
        top = -1;
    }

    void push(string action, int time, string loc, int chapter) {
        if (top < capacity - 1) {
            top++;
            stack[top].action = action;
            stack[top].timestamp = time;
            stack[top].location = loc;
            stack[top].chapterNum = chapter;
        }
    }

    ActionNode pop() {
        if (top >= 0) {
            return stack[top--];
        }
        return {"", 0, "", 0};
    }

    bool isEmpty() {
        return top == -1;
    }

    void rewindTime(int steps) {
        cout << "\n==> REWINDING TIME...\n";
        cout << "...........................................................................................................................\n";
        
        int rewound = 0;
        while (!isEmpty() && rewound < steps) {
            ActionNode action = pop();
            cout << "⏪ Undoing: " << action.action << "\n";
            rewound++;
        }
        
        cout << "==> Rewound " << rewound << " action(s)\n";
    }

    void display() {
        cout << "\n============================================================================================================================================================================\n";
        cout << "||           ACTION HISTORY (Most Recent First)          ||\n";
        cout << "==============================================================================================================================================================================\n";
        
        if (isEmpty()) {
            cout << "  No actions recorded yet.\n";
            return;
        }

        for (int i = top; i >= 0; i--) {
            cout << "  " << (top - i + 1) << ". [T+" << stack[i].timestamp 
                 << "min] " << stack[i].location << ": " << stack[i].action << "\n";
        }
    }

    ~ActionStack() {
        delete[] stack;
    }
};

// ===============================
// BINARY DECISION TREE (Chapters 7 & 10)
// ===============================
struct DecisionTreeNode {
    int nodeId;
    string scenario;
    string choiceA;
    string choiceB;
    int scoreA;
    int scoreB;
    DecisionTreeNode* left;
    DecisionTreeNode* right;
};

class BinaryDecisionTree {
private:
    DecisionTreeNode* root;

    DecisionTreeNode* createNode(int id, string scenario, 
                                 string cA, string cB, int sA, int sB) {
        DecisionTreeNode* node = new DecisionTreeNode;
        node->nodeId = id;
        node->scenario = scenario;
        node->choiceA = cA;
        node->choiceB = cB;
        node->scoreA = sA;
        node->scoreB = sB;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    void deleteTree(DecisionTreeNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    BinaryDecisionTree() {
        root = nullptr;
    }

    void buildChapter7Tree() {
        root = createNode(1, 
            "You stand before the Temporal Engine.\nMultiple options flash on screen.",
            "Shut down the engine immediately",
            "Override safety protocols",
            -30, 40);

        root->left = createNode(2,
            "Shutdown initiated. Timeline unstable!",
            "Force emergency shutdown",
            "Restore partial systems",
            20, 60);

        root->right = createNode(3,
            "Override accepted. Systems stabilizing.",
            "Continue override",
            "Switch to manual control",
            70, 40);
    }

    void buildChapter10Tree() {
        root = createNode(10,
            "FINAL CHOICE - THE FATE OF TIME\n"
            "The loop was created to prevent catastrophe.\n"
            "Now you must decide.",
            "DESTROY THE LOOP - Restore natural time",
            "PRESERVE THE LOOP - Maintain containment",
            100, 150);

        root->left = createNode(11,
            "Loop destruction sequence initiated.\n"
            "Reality begins to crack.",
            "Force complete destruction",
            "Allow gradual dissolution",
            120, 90);

        root->right = createNode(12,
            "You preserve the loop.\n"
            "You become its eternal guardian.",
            "Accept the sacrifice willingly",
            "Maintain it reluctantly",
            180, 140);
    }

    int traverseTree(DecisionTreeNode* node, int &totalScore) {
        if (!node) return 0;

        cout << "\n===========================================================================================================================\n";
        cout << "DECISION NODE #" << node->nodeId << "\n";
        cout << "=============================================================================================================================\n";
        cout << node->scenario << "\n\n";
        cout << "1. " << node->choiceA << " [Score: " << node->scoreA << "]\n";
        cout << "2. " << node->choiceB << " [Score: " << node->scoreB << "]\n";
        cout << "\nYour choice (1/2): ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "\n You chose-> " << node->choiceA << "\n";
            totalScore += node->scoreA;
            cout << "  Score gained: +" << node->scoreA << "\n";
            
            if (node->left) {
                return traverseTree(node->left, totalScore);
            }
            return node->scoreA;
        } else {
            cout << "\n You chose-> " << node->choiceB << "\n";
            totalScore += node->scoreB;
            cout << "  Score gained: +" << node->scoreB << "\n";
            
            if (node->right) {
                return traverseTree(node->right, totalScore);
            }
            return node->scoreB;
        }
    }

    void playChapter7(int &score) {
        buildChapter7Tree();
        traverseTree(root, score);
    }

    void playChapter10(int &score) {
        buildChapter10Tree();
        traverseTree(root, score);
    }

    ~BinaryDecisionTree() {
        deleteTree(root);
    }
};

// ===============================
// ROOM MOVEMENT SYSTEM (Array-based Graph)
// ===============================
class RoomNavigator {
private:
    string roomNames[5] = {
        "Control Hall",
        "Research Wing",
        "Data Archives",
        "Security Sector",
        "Maintenance Bay"
    };
    
    string roomDescriptions[5] = {
        "Central command center. Monitors display unstable readings.",
        "Labs filled with experimental equipment and scattered notes.",
        "Rows of servers storing classified temporal research data.",
        "Armed security personnel monitor all facility access points.",
        "Dark corridors with humming machinery and flickering lights."
    };
    
    // Adjacency matrix (1 = connected, 0 = not connected)
    int connections[5][5] = {
        {0, 1, 1, 0, 0},  // Control Hall connects to Research Wing, Data Archives
        {1, 0, 0, 1, 1},  // Research Wing connects to Control Hall, Security, Maintenance
        {1, 0, 0, 1, 0},  // Data Archives connects to Control Hall, Security
        {0, 1, 1, 0, 0},  // Security connects to Research Wing, Data Archives
        {0, 1, 0, 0, 0}   // Maintenance connects to Research Wing
    };

public:
    void displayCurrentRoom(int roomId) {
        cout << "\n===========================================================================================================================\n";
        cout << "==> LOCATION: " << roomNames[roomId] << "\n";
        cout << "=============================================================================================================================\n";
        cout << roomDescriptions[roomId] << "\n\n";
        cout << "Connected rooms:\n";
        
        int count = 1;
        for (int i = 0; i < 5; i++) {
            if (connections[roomId][i] == 1) {
                cout << "  " << count++ << ". " << roomNames[i] << "\n";
            }
        }
    }
    
    int moveToRoom(int currentRoom, int choice) {
        int count = 0;
        for (int i = 0; i < 5; i++) {
            if (connections[currentRoom][i] == 1) {
                count++;
                if (count == choice) {
                    cout << "\n==> Moving to " << roomNames[i] << "...\n";
                    return i;
                }
            }
        }
        cout << "\n� Invalid room choice!\n";
        return currentRoom;
    }
    
    string getRoomName(int id) {
        return roomNames[id];
    }
};
    // ===============================
    // CLUE COLLECTION SYSTEM (Array)
    // ===============================
    class ClueCollector {
    private:
        struct Clue {
            string name;
            string description;
            int roomId;
            bool collected;
        };
        
        Clue clues[10];
        int totalClues;

    public:
        ClueCollector() {
            totalClues = 10;
            
            clues[0] = {"System Log", "Corrupted log file from 6 hours ago", 2, false};
            clues[1] = {"Handwritten Note", "Note reads: 'It was intentional'", 1, false};
            clues[2] = {"Red Keycard", "High-level security clearance card", 3, false};
            clues[3] = {"Audio Recording", "Unknown voice warning of danger", 2, false};
            clues[4] = {"Blueprint", "Temporal Engine schematics", 1, false};
            clues[5] = {"Photo", "Picture of the research team", 0, false};
            clues[6] = {"Tool", "Strange calibration device", 4, false};
            clues[7] = {"Document", "Project Ouroboros classified file", 0, false};
            clues[8] = {"Badge", "Dr. Markov's access badge", 1, false};
            clues[9] = {"Sample", "Unusual temporal energy reading", 4, false};
        }
        
        void searchRoom(int roomId, int &score) {
            cout << "\n🔍 Searching the room...\n";
            
            bool foundSomething = false;
            for (int i = 0; i < totalClues; i++) {
                if (clues[i].roomId == roomId && !clues[i].collected) {
                    cout << "\n✓ CLUE FOUND: " << clues[i].name << "\n";
                    cout << "  " << clues[i].description << "\n";
                    clues[i].collected = true;
                    score += 20;
                    foundSomething = true;
                }
            }
            
            if (!foundSomething) {
                cout << "\n✗ No new clues found in this room.\n";
            }
        }
        
        void displayCollectedClues() {
            cout << "\n============================================================================================================================================================================\n";
            cout << "||              COLLECTED CLUES                          ||\n";
            cout << "==============================================================================================================================================================================\n";
            
            int count = 0;
            for (int i = 0; i < totalClues; i++) {
                if (clues[i].collected) {
                    count++;
                    cout << "\n" << count << ". " << clues[i].name << "\n";
                    cout << "   " << clues[i].description << "\n";
                }
            }
            
            if (count == 0) {
                cout << "\n  No clues collected yet.\n";
            } else {
                cout << "\nTotal: " << count << "/" << totalClues << " clues collected\n";
            }
        }
    };

    // ===============================
    // INVENTORY SYSTEM (Queue)
    // ===============================
    class InventoryQueue {
    private:
        string items[20];
        int front, rear, size, capacity;

    public:
        InventoryQueue() {
            capacity = 20;
            front = 0;
            rear = -1;
            size = 0;
        }
        
        void addItem(string item) {
            if (size < capacity) {
                rear = (rear + 1) % capacity;
                items[rear] = item;
                size++;
                cout << "==> Added to inventory: " << item << "\n";
            } else {
                cout << ">>> Inventory full!\n";
            }
        }
        
        void useItem() {
            if (size > 0) {
                string used = items[front];
                front = (front + 1) % capacity;
                size--;
                cout << "==> Used item: " << used << "\n";
            } else {
                cout << ">>> Inventory is empty!\n";
            }
        }
        
        void display() {
            cout << "\n============================================================================================================================================================================\n";
            cout << "||               INVENTORY                           ||\n";
            cout << "==============================================================================================================================================================================\n";
            
            if (size == 0) {
                cout << "  Inventory is empty.\n";
                return;
            }
            
            int idx = front;
            for (int i = 0; i < size; i++) {
                cout << "  " << (i + 1) << ". " << items[idx] << "\n";
                idx = (idx + 1) % capacity;
            }
            cout << "\nItems: " << size << "/" << capacity << "\n";
        }
    };

    // ===============================
    // MINI-PUZZLES
    // ===============================
    class AlarmCodePuzzle {
    public:
        bool solvePuzzle(int &score) {
            cout << "\n============================================================================================================================================================================\n";
            cout << "||            PUZZLE: ALARM CODE CRACKER                ||\n";
            cout << "==============================================================================================================================================================================\n";
            cout << "\nThe alarm requires a 4-digit code.\n";
            cout << "Clue: Chronos founding year. Starts with 19, ends in 84\n\n";
            
            int attempts = 3;
            int correctCode = 1984;
            
            while (attempts > 0) {
                cout << "Enter code (Attempts: " << attempts << "): ";
                int code;
                cin >> code;
                cin.ignore();
                
                if (code == correctCode) {
                    cout << "\n==> ALARM DEACTIVATED!\n";
                    score += 50;
                    return true;
                } else {
                    attempts--;
                    if (attempts > 0) {
                        cout << "✗ Incorrect! Try again.\n";
                    }
                }
            }
            cout << "==> ALARM TRIGGERED!\n";
            return false;
        }
    };

    class KeycardSearchPuzzle {
    public:
        bool solvePuzzle(int &score) {
            cout << "\n============================================================================================================================================================================\n";
            cout << "||       PUZZLE: KEYCARD SEARCH                        ||\n";
            cout << "==============================================================================================================================================================================\n";
            cout << "\nFind the RED keycard. Search 3 locations max.\n\n";
            
            string locations[8] = {
                "Control Hall Desk", "Research Wing Locker",
                "Data Archives Terminal", "Security Office Drawer",
                "Break Room Cabinet", "Maintenance Closet",
                "Storage Shelf", "Emergency Panel"
            };
            
            int keycardLoc = 5; // Maintenance Closet
            
            for (int i = 0; i < 8; i++) {
                cout << (i + 1) << ". " << locations[i] << "\n";
            }
            
            int searches = 0;
            while (searches < 3) {
                cout << "\nSearch location (1-8): ";
                int choice;
                cin >> choice;
                cin.ignore();
                
                searches++;
                
                if (choice - 1 == keycardLoc) {
                    cout << "\n==> KEYCARD FOUND at " << locations[choice - 1] << "!\n";
                    score += 40;
                    return true;
                } else {
                    if (searches < 3) {
                        if (choice - 1 < keycardLoc) {
                            cout << "� Not here. Try HIGHER numbers.\n";
                        } else {
                            cout << "� Not here. Try LOWER numbers.\n";
                        }
                    }
                }
            }
            cout << "� Search failed! Keycard was at: " << locations[keycardLoc] << "\n";
            return false;
        }
    };

    class RecursiveLoopPuzzle {
    private:
        bool checkLoop(int depth, int maxDepth, int &score) {
            for (int i = 0; i < depth; i++) cout << "  ";
            cout << "==> Loop Level " << depth << "\n";
            
            if (depth >= maxDepth) {
                cout << "\n Loop complete!\n";
                return true;
            }
            
            cout << "   Question: " << (depth + 1) << " * 2 = ? ";
            int answer;
            cin >> answer;
            cin.ignore();
            
            if (answer == (depth + 1) * 2) {
                cout << " Correct!\n\n";
                score += 10;
                return checkLoop(depth + 1, maxDepth, score);
            } else {
                cout << "� Wrong! Loop failed.\n";
                return false;
            }
        }

    public:
        bool solvePuzzle(int &score) {
            cout << "\n============================================================================================================================================================================\n";
            cout << "||         PUZZLE: RECURSIVE LOOP CHECK                  ||\n";
            cout << "==============================================================================================================================================================================\n";
            cout << "\nNavigate 5 nested time loops. Answer at each level.\n\n";
            
            return checkLoop(0, 5, score);
        }
    };

    // ===============================
    // SAVE/LOAD SYSTEM
    // ===============================
    class SaveSystem {
    public:
        static void saveGame(string name, int score, int room, int chapter) {
            ofstream out("temporalloop_save.txt");
            if (out.is_open()) {
                out << name << endl;
                out << score << endl;
                out << room << endl;
                out << chapter << endl;
                out.close();
                cout << "\n==> � Game saved!\n";
            }
        }
        
        static bool loadGame(string &name, int &score, int &room, int &chapter) {
            ifstream in("temporalloop_save.txt");
            if (in.is_open()) {
                getline(in, name);
                in >> score >> room >> chapter;
                in.close();
                cout << "\n Game loaded!\n";
                return true;
            }
            return false;
        }
    };

// =====================
// Chapter Class (The Entire Story Line)
// =====================
    class Story {
    public:
        void typeWriter(const string &text, int delayMs = 30) {
            for (char c : text) {
                cout << c;
                cout.flush();
                this_thread::sleep_for(chrono::milliseconds(delayMs));
            }
            cout << endl;
        }

    // Initialize suspects linked list
    SuspectLinkedList suspects;

    ActionStack actionStack;

        // ===============================
        // CHAPTER 1
        // ===============================
        void chapter1() {
        // ======== Local game objects ========
        RoomNavigator roomNavigator;
        ClueCollector clueCollector;
        int playerScore = 0;

        typeWriter("═══════════════════════════════════════════════════\n");
        typeWriter("CHAPTER 1 — MEMORY THAT SHOULDN'T EXIST\n");
        typeWriter("═══════════════════════════════════════════════════\n\n");

        typeWriter("You wake up again.\n");
        typeWriter("The alarms blare. The clocks read 07:00 AM.\n");
        typeWriter("Everything looks familiar, yet eerily strange.\n\n");

        typeWriter("Your mind flashes with memories that shouldn't exist.\n");
        typeWriter("You've lived this moment before.\n\n");

        typeWriter("A scientist rushes past you:\n");
        typeWriter("\"We need to stabilize the Temporal Engine!\"\n\n");

        typeWriter("You are the only variable that did not reset.\n");
        typeWriter("Memory is your greatest weapon.\n\n");

        typeWriter("You glance around. Where do you want to go?\n");

        int currentRoom = 0; // Start at Control Hall
        bool chapterActive = true;

        while (chapterActive) {
            roomNavigator.displayCurrentRoom(currentRoom);
            cout << "\nEnter choice (room number to move, 0 to search for clues, 9 to end chapter): ";
            int choice;
            cin >> choice;

            if (choice == 9) {
                typeWriter("\nYou pause and prepare for the next steps...\n");
                chapterActive = false;
            } else if (choice == 0) {
                clueCollector.searchRoom(currentRoom, playerScore);
            } else {
                currentRoom = roomNavigator.moveToRoom(currentRoom, choice);
            }
        }

        typeWriter("\nChapter summary:\n");
        typeWriter("Score: " + to_string(playerScore) + "\n");
        clueCollector.displayCollectedClues();

        typeWriter("\n═══════════════════════════════════════════════════\n");
        typeWriter("END OF CHAPTER 1\n");
        typeWriter("═══════════════════════════════════════════════════\n");
    }


    void chapter2() {
        typeWriter("═══════════════════════════════════════════════════\n");
        typeWriter("CHAPTER 2 — THE RESEARCH WING AND FIRST CLUES\n");
        typeWriter("═══════════════════════════════════════════════════\n\n");

        typeWriter("You decide to investigate the Research Wing.\n");
        typeWriter("Rows of labs stretch before you, filled with strange machinery and flickering monitors.\n\n");

        // STORY MEMORY
        actionStack.push("Entered Research Wing", 10, "Research Wing", 2);

        typeWriter("A voice echoes in your memory:\n");
        typeWriter("\"The loops were not an accident... someone is controlling the Temporal Engine from within.\"\n\n");

        typeWriter("Your heart races. Could one of the staff be responsible?\n\n");

        typeWriter("You notice scattered papers and a half-open terminal.\n");
        typeWriter("One paper catches your eye:\n");
        typeWriter("\"If anyone finds this note, know that it was intentional. —Dr. Unknown\"\n\n");

        // CLUE FOUND
        actionStack.push("Found Dr. Unknown note", 12, "Research Wing", 2);

        typeWriter("You spot a lab assistant working on a console.\n\n");
        typeWriter("What do you do?\n");
        typeWriter("1. Approach the assistant and ask questions.\n");
        typeWriter("2. Search the lab quietly for more clues.\n");

        int choice;
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            actionStack.push("Questioned lab assistant", 15, "Research Wing", 2);
            typeWriter("\nThe assistant looks nervous and avoids eye contact...\n");
            typeWriter("Something is clearly being hidden.\n");
        }
        else if (choice == 2) {
            actionStack.push("Searched lab secretly", 15, "Research Wing", 2);
            typeWriter("\nYou move quietly between tables and shelves...\n");
        }
        else {
            typeWriter("\nInvalid choice. Timeline destabilizes slightly.\n");
        }

        typeWriter("\nAmong the scattered lab notes, you discover a RED SECURITY CLEARANCE KEYCARD.\n");
        typeWriter("This could grant access to restricted areas.\n\n");

        // IMPORTANT ITEM
        actionStack.push("Obtained red security keycard", 18, "Research Wing", 2);

        typeWriter("Your awareness of the loop allows you to memorize everything.\n");
        typeWriter("Evidence is your weapon.\n\n");

        typeWriter("Choices made here will affect future chapters.\n");
        typeWriter("--- End of Chapter 2 ---\n");
    }


    void chapter3() {
        typeWriter("═══════════════════════════════════════════════════\n");
        typeWriter("CHAPTER 3 — SECURITY SECTOR: SHADOWS AND SUSPECTS\n");
        typeWriter("═══════════════════════════════════════════════════\n\n");

        typeWriter("The security doors hiss as you enter the Security Sector.\n");
        typeWriter("Armed personnel move with precision, unaware that you know this layout by heart.\n");
        typeWriter("Monitors display feeds from every corner of the facility, but one screen flickers oddly.\n");

        actionStack.push("Entered Security Sector", 20, "Security Sector", 3);

        typeWriter("A familiar voice in your mind whispers:\n");
        typeWriter("\"Commander Hayes always seems too calm. Something about him doesn’t fit.\"\n");

        typeWriter("You notice a RED SECURITY CLEARANCE KEYCARD in the drawer.\n");
        actionStack.push("Found red security keycard (duplicate)", 22, "Security Sector", 3);

        typeWriter("\nYou check a terminal with unusual activity logs:\n");
        typeWriter("- 07:30 — Unauthorized override detected.\n");
        typeWriter("- 07:45 — Temporal Engine diagnostics accessed remotely.\n");

        actionStack.push("Checked unusual activity logs", 23, "Security Sector", 3);

        typeWriter("\nYou overhear a whispered conversation:\n");
        typeWriter("\"The temporal containment must remain intact. Any interference will jeopardize the project.\"\n");

        actionStack.push("Overheard conversation", 24, "Security Sector", 3);

        typeWriter("\nWhile scanning the sector, you discover:\n");
        typeWriter("- A suspiciously unmarked audio recorder behind a console.\n");
        typeWriter("- A lab notebook with encrypted codes.\n");
        typeWriter("- Personnel logs highlighting unusual overtime shifts.\n");

        actionStack.push("Found audio recorder", 25, "Security Sector", 3);
        actionStack.push("Found lab notebook with encrypted codes", 26, "Security Sector", 3);
        actionStack.push("Checked personnel logs for anomalies", 27, "Security Sector", 3);

        // Update suspicion levels
        suspects.updateSuspicion("Commander Hayes", 7);
        suspects.updateSuspicion("Dr. Chen Wei", 9);
        suspects.updateSuspicion("Sarah Mitchell", 6);

        suspects.sortBySuspicion();
        suspects.displaySuspects(); // optional

        typeWriter("\nEvery discovery increases your suspicion levels.\n");
        typeWriter("Memory of the loop gives you the advantage to remember every detail.\n");

        typeWriter("\nChoices in this chapter will influence suspects' suspicion levels in future loops.\n");
        typeWriter("--- End of Chapter 3 ---\n");
    }



  // ===============================
// CHAPTER 4
// ===============================
void chapter4() {
    // ======== Local game objects ========
    RoomNavigator roomNavigator;
    ClueCollector clueCollector;
    int playerScore = 0;

    typeWriter("═══════════════════════════════════════════════════\n");
    typeWriter("CHAPTER 4 — DATA ARCHIVES: SECRETS OF THE TEMPORAL ENGINE\n");
    typeWriter("═══════════════════════════════════════════════════\n\n");

    typeWriter("You enter the Data Archives, the temperature drops slightly as the massive server racks hum.\n");
    typeWriter("Rows upon rows of encrypted data stretch into darkness, flickering with dim red lights.\n");

    actionStack.push("Entered Data Archives", 40, "Data Archives", 4);

    typeWriter("Your memory from previous loops guides your steps — you know where the most sensitive files are.\n");
    typeWriter("A digital lock panel blinks: access code required.\n");

    actionStack.push("Approached digital lock panel", 41, "Data Archives", 4);

    int currentRoom = 2; // Data Archives
    bool chapterActive = true;

    while (chapterActive) {
        roomNavigator.displayCurrentRoom(currentRoom);
        cout << "\nEnter choice (room number to move, 0 to search for clues, 9 to end chapter): ";
        int choice;
        cin >> choice;

        if (choice == 9) {
            typeWriter("\nChapter 4 ends here, but your choices will ripple through the loops.\n");
            chapterActive = false;
        } else if (choice == 0) {
            clueCollector.searchRoom(currentRoom, playerScore);

            // Story-driven events when searching Data Archives
            if (currentRoom == 2) {
                typeWriter("\nYou recall a note you found in the Research Wing — it hints at a master access code.\n");
                actionStack.push("Recalled master access code clue", 42, "Data Archives", 4);

                typeWriter("Access granted. The terminal lights up with project files: 'Project Ouroboros', 'Temporal Engine Logs', 'Unauthorized Overrides'.\n");
                actionStack.push("Accessed critical project files", 43, "Data Archives", 4);

                typeWriter("As you scroll through the logs, a chilling realization hits you:\n");
                typeWriter("\"Someone has been manipulating the loops, forcing events to happen at precise times.\"\n");
                actionStack.push("Realized timeline manipulation", 44, "Data Archives", 4);

                typeWriter("You find an **audio log** marked 06:45 — the voice warns: \n");
                typeWriter("\"Do not interfere. The timeline is fragile.\"\n");
                actionStack.push("Found audio log warning", 45, "Data Archives", 4);

                typeWriter("Another log points directly to Dr. Chen Wei's manipulations in the Temporal Engine control sequences.\n");
                actionStack.push("Discovered Dr. Chen Wei's manipulations", 46, "Data Archives", 4);

                suspects.updateSuspicion("Dr. Chen Wei", 9);
                suspects.displaySuspects();
            }

        } else {
            currentRoom = roomNavigator.moveToRoom(currentRoom, choice);
        }
    }

    // Show summary of collected clues
    typeWriter("\nChapter summary:\n");
    typeWriter("Score: " + to_string(playerScore) + "\n");
    clueCollector.displayCollectedClues();

    typeWriter("\n═══════════════════════════════════════════════════\n");
    typeWriter("END OF CHAPTER 4\n");
    typeWriter("═══════════════════════════════════════════════════\n");
}


void chapter5() {
    // ======== Local game objects ========
    RoomNavigator roomNavigator;
    ClueCollector clueCollector;
    int playerScore = 0;

    typeWriter("═══════════════════════════════════════════════════\n");
    typeWriter("CHAPTER 5 — RESEARCH WING: CONFRONTATION AND CONSEQUENCES\n");
    typeWriter("═══════════════════════════════════════════════════\n\n");

    int currentRoom = 1; // Research Wing
    bool chapterActive = true;

    while (chapterActive) {
        roomNavigator.displayCurrentRoom(currentRoom);
        cout << "\nEnter choice (room number to move, 0 to search for clues, 9 to end chapter): ";
        int choice;
        cin >> choice;

        if (choice == 9) {
            typeWriter("\nChapter 5 ends here — events in the Research Wing will affect future loops.\n");
            chapterActive = false;
        } else if (choice == 0) {
            clueCollector.searchRoom(currentRoom, playerScore);

            // Story-driven events when searching Research Wing
            if (currentRoom == 1) {
                typeWriter("\nYou find a terminal with partial override codes — this may allow stabilizing the engine temporarily.\n");
                actionStack.push("Found terminal with partial override codes", 57, "Research Wing", 5);

                typeWriter("You quietly scan consoles, noting timestamps of unauthorized actions.\n");
                actionStack.push("Observed and gathered evidence silently", 54, "Research Wing", 5);
            }

        } else {
            currentRoom = roomNavigator.moveToRoom(currentRoom, choice);

            // Story-triggered events when moving
            if (currentRoom == 1) {
                typeWriter("\nYou notice traces of unauthorized temporal manipulation.\n");
                actionStack.push("Noticed traces of unauthorized manipulation", 51, "Research Wing", 5);
            }
        }
    }

    // Update suspicion based on chapter events
    suspects.updateSuspicion("Dr. Chen Wei", 10);
    suspects.sortBySuspicion();
    suspects.displaySuspects();

    // Chapter summary
    typeWriter("\nChapter summary:\n");
    typeWriter("Score: " + to_string(playerScore) + "\n");
    clueCollector.displayCollectedClues();

    typeWriter("\n═══════════════════════════════════════════════════\n");
    typeWriter("END OF CHAPTER 5\n");
    typeWriter("═══════════════════════════════════════════════════\n");
}

    void chapter6() {
    // ======== Local game objects ========
    RoomNavigator roomNavigator;
    ClueCollector clueCollector;
    InventoryQueue inventory;
    int playerScore = 0;

    typeWriter("══════════════════════════════════════════════\n");
    typeWriter("CHAPTER 6 — PEOPLE WHO CHANGE\n");
    typeWriter("══════════════════════════════════════════════\n\n");

    int currentRoom = 3; // Corridor observation area
    bool chapterActive = true;

    // Story intro
    typeWriter("The corridor is quieter than before.");
    typeWriter("No alarms.");
    typeWriter("No rushing footsteps.");
    typeWriter("Just silence.\n");

    typeWriter("You have walked this path before.");
    typeWriter("Multiple times.");
    typeWriter("Yet something feels... different.\n");

    typeWriter("The people.");
    typeWriter("They never react the same way twice.\n");

    typeWriter("Through the observation glass, you see them.\n");

    typeWriter("Dr. Elena Markov stands near the console.");
    typeWriter("Her expression is calm.");
    typeWriter("Too calm.\n");

    typeWriter("Commander Hayes leans against the wall.");
    typeWriter("Arms crossed.");
    typeWriter("Jaw clenched.\n");

    typeWriter("Sarah Mitchell types furiously.");
    typeWriter("She stops the moment you enter.");
    typeWriter("She doesn’t look at you.\n");

    typeWriter("Your memory stirs.\n");
    typeWriter("Last loop, Hayes spoke without hesitation.");
    typeWriter("Two loops ago, Sarah refused to speak at all.");
    typeWriter("And Markov...");
    typeWriter("Markov always knew something.\n");

    typeWriter("You realize something unsettling.\n");
    typeWriter("Suspicion is not fixed.");
    typeWriter("It evolves.\n");

    typeWriter("[SYSTEM] Suspect list updated.");
    typeWriter("[DSA] Linked List modified dynamically.\n");

    typeWriter("Commander Hayes notices you watching.");
    typeWriter("\"You shouldn’t be here,\" he says.");
    typeWriter("His voice trembles — just slightly.\n");

    typeWriter("Sarah finally speaks.");
    typeWriter("\"Did the loop reset again?\"");
    typeWriter("Her eyes widen as she realizes what she said.\n");

    typeWriter("Dr. Markov turns toward you.");
    typeWriter("\"Careful,\" she says softly.");
    typeWriter("\"Some truths damage the mind beyond repair.\"\n");

    typeWriter("Your heart pounds.\n");
    typeWriter("They remember fragments.");
    typeWriter("Not fully.");
    typeWriter("But enough.\n");

    typeWriter("You silently adjust your internal list:\n");
    typeWriter("• Hayes — suspicion increased.");
    typeWriter("• Sarah — flagged for observation.");
    typeWriter("• Markov — unresolved.\n");

    typeWriter("[DSA] Linked List reordered based on suspicion level.\n");

    typeWriter("A warning flashes on a nearby terminal:\n");
    typeWriter("\"TEMPORAL MEMORY DEVIATION DETECTED\"\n");

    typeWriter("You step back into the shadows.");
    typeWriter("You are no longer the only variable.\n");

    typeWriter("If others begin to remember...");
    typeWriter("The loop will become uncontrollable.\n");

    typeWriter("People change.");
    typeWriter("And in broken time...");
    typeWriter("Change is dangerous.\n");

    // ===== Interactive gameplay loop =====
    while (chapterActive) {
        roomNavigator.displayCurrentRoom(currentRoom);
        cout << "\nEnter choice (room number to move, 0 to search for clues, 9 to end chapter): ";
        int choice;
        cin >> choice;

        if (choice == 9) {
            typeWriter("\nChapter 6 ends here.\n");
            chapterActive = false;
        } else if (choice == 0) {
            clueCollector.searchRoom(currentRoom, playerScore);

            // Dynamic story events while searching
            typeWriter("\nThrough the observation glass, you notice subtle changes in the people’s behavior.\n");
            actionStack.push("Observed people differently", 62, "Observation Glass", 6);

            // Update suspicion dynamically
            suspects.updateSuspicion("Commander Hayes", 6);
            suspects.updateSuspicion("Sarah Mitchell", 5);
            suspects.updateSuspicion("Dr. Elena Markov", 7);
            suspects.sortBySuspicion();
            suspects.displaySuspects();

            typeWriter("[SYSTEM] Suspect list updated and sorted.\n");
            actionStack.push("Updated suspicion levels", 67, "Corridor", 6);

        } else {
            currentRoom = roomNavigator.moveToRoom(currentRoom, choice);
        }
    }

    // Chapter summary
    typeWriter("\nChapter summary:\n");
    typeWriter("Score: " + to_string(playerScore) + "\n");
    clueCollector.displayCollectedClues();
    inventory.display();

    typeWriter("══════════════════════════════════════════════\n");
    typeWriter("END OF CHAPTER 6\n");
    typeWriter("══════════════════════════════════════════════\n");
}

 // ===============================
// CHAPTER 7
// ===============================
void chapter7() {
    // ======== Local game objects ========
    RoomNavigator roomNavigator;
    ClueCollector clueCollector;
    int playerScore = 0;

    typeWriter("══════════════════════════════════════════════\n");
    typeWriter("CHAPTER 7 — THE CHOICE THAT BREAKS TIME\n");
    typeWriter("══════════════════════════════════════════════\n\n");

    typeWriter("The system does not reset.\n");
    actionStack.push("Observed loop not resetting", 70, "Temporal Core", 7);

    typeWriter("For the first time, the loop hesitates.\nMilliseconds stretch into something heavier.\nAlmost like fear.\n");
    actionStack.push("Felt loop hesitation", 71, "Temporal Core", 7);

    typeWriter("A terminal lights up ahead.\nIts screen flickers — unstable.\n[SYSTEM] TEMPORAL CORE ACCESS GRANTED\n");
    actionStack.push("Gained temporal core access", 72, "Temporal Core", 7);

    typeWriter("Every loop you survived flashes before you.\nEvery mistake.\nEvery death narrowly avoided.\n");
    actionStack.push("Reflected on past loops", 73, "Temporal Core", 7);

    typeWriter("The console displays a branching diagram.\nNot lines.\nNot paths.\nChoices.\n[DSA] Binary Decision Tree initialized.\n");
    actionStack.push("Decision tree observed", 74, "Temporal Core", 7);

    typeWriter("Left branch:\n\"Terminate the Temporal Loop\"\n— All systems reset permanently.\n— No more rewinds.\n— No second chances.\n");
    typeWriter("Right branch:\n\"Stabilize the Temporal Loop\"\n— Infinite corrections possible.\n— Memory fragments will spread.\n— Time will never truly heal.\n");
    actionStack.push("Branches observed: Terminate or Stabilize", 75, "Temporal Core", 7);

    typeWriter("You remember Chapter One.\nThe alarm.\nThe panic.\nThe first reset you didn’t understand.\nBack then, time was a tool.\nNow... It is a weapon.\n");
    actionStack.push("Remembered Chapter 1 events", 76, "Temporal Core", 7);

    typeWriter("A warning appears in red:\n\"DECISION NODE LOCKING IN 10 SECONDS\"\n");
    actionStack.push("Decision node warning", 77, "Temporal Core", 7);

    typeWriter("Dr. Markov’s voice echoes over the intercom.\n\"You think this is about saving them,\" she says.\n\"It’s about deciding who deserves tomorrow.\"\n");
    typeWriter("Commander Hayes pounds on the sealed door.\n\"End it!\" he shouts.\n\"No one should live like this!\"\n");
    typeWriter("Sarah whispers through a broken channel.\n\"If you stop it…\"\n\"Will we forget you?\"\n");
    actionStack.push("Heard intercom messages", 78, "Temporal Core", 7);

    typeWriter("This is no longer a system problem.\nIt is a moral one.\n");

    // Update suspicion dynamically
    suspects.updateSuspicion("Commander Hayes", 7);
    suspects.updateSuspicion("Sarah Mitchell", 6);
    suspects.sortBySuspicion();
    suspects.displaySuspects();

    // === INTERACTIVE ROOM AND CLUE NAVIGATION IN TEMPORAL CORE ===
    int currentRoom = 0; // Temporal Core starting point
    bool chapterActive = true;

    while (chapterActive) {
        roomNavigator.displayCurrentRoom(currentRoom);
        cout << "\nEnter choice (room number to move, 0 to search for clues, 9 to proceed to decision): ";
        int choice;
        cin >> choice;

        if (choice == 9) {
            typeWriter("\nYou approach the decision node to make your choice...\n");
            chapterActive = false;
        } else if (choice == 0) {
            clueCollector.searchRoom(currentRoom, playerScore);
        } else {
            currentRoom = roomNavigator.moveToRoom(currentRoom, choice);
        }
    }

    // === BINARY DECISION TREE INTEGRATION ===
    int totalScore = 0;
    BinaryDecisionTree decisionTree;
    decisionTree.playChapter7(totalScore);

    typeWriter("\nYour choices in the decision tree added a total score of: " + to_string(totalScore) + "\n");

    // Show chapter summary with clues
    typeWriter("\nChapter summary:\n");
    typeWriter("Score: " + to_string(playerScore) + "\n");
    clueCollector.displayCollectedClues();

    typeWriter("══════════════════════════════════════════════\n");
    typeWriter("END OF CHAPTER 7\n");
    typeWriter("══════════════════════════════════════════════\n");
}



    void chapter8(int depth = 1) {
        // ======== Local game objects ========
        RoomNavigator roomNavigator;
        ClueCollector clueCollector;
        InventoryQueue inventory;
        int playerScore = 0;

        typeWriter("══════════════════════════════════════════════\n");
        typeWriter("CHAPTER 8 — THE LOOP WITHIN THE LOOP\n");
        typeWriter("══════════════════════════════════════════════\n\n");

        int currentRoom = 5; // Temporal Paradox Zone entry
        bool chapterActive = true;

        // Story narration intro
        typeWriter("The decision does not execute.\n");
        typeWriter("Instead, the system freezes.");
        typeWriter("Not a crash.");
        typeWriter("Not a reset.");
        typeWriter("A pause.\n");

        typeWriter("[SYSTEM] TEMPORAL PARADOX DETECTED\n");

        typeWriter("Your surroundings distort.");
        typeWriter("Walls stretch.");
        typeWriter("Lights flicker backward.\n");

        typeWriter("A hidden log opens on the terminal.\n");
        typeWriter("\"Iteration Count: " + to_string(depth) + "\"\n");
        typeWriter("You read the file header:\n");
        typeWriter("\"USER_ID: UNKNOWN\"");
        typeWriter("\"STATUS: AWARE\"");
        typeWriter("\"FIRST LOOP: UNRECORDED\"\n");

        typeWriter("Your stomach drops.\n");
        typeWriter("Someone else was here before you.");
        typeWriter("Someone who remembered.");
        typeWriter("Someone who went deeper.\n");

        typeWriter("The log repeats itself.");
        typeWriter("Same lines.");
        typeWriter("Same warnings.");
        typeWriter("Same failure.\n");

        typeWriter("[DSA] Recursive timeline call detected.\n");

            // ======= Recursive Loop Puzzle =======
            RecursiveLoopPuzzle loopPuzzle;
            if (loopPuzzle.solvePuzzle(playerScore)) {
                typeWriter("\nYou successfully navigated the nested loops.\n");
                actionStack.push("Nested loop puzzle solved", 83 + depth, "Temporal Paradox Zone", 8);
            } else {
                typeWriter("\nYou failed to navigate the loops correctly. Time destabilizes momentarily.\n");
                actionStack.push("Nested loop puzzle failed", 83 + depth, "Temporal Paradox Zone", 8);
            }

        // ===== Interactive gameplay loop =====
        while (chapterActive) {
            roomNavigator.displayCurrentRoom(currentRoom);
            cout << "\nEnter choice (room number to move, 0 to search for clues, 9 to exit this depth): ";
            int choice;
            cin >> choice;

            if (choice == 9) {
                typeWriter("\nExiting current memory layer...\n");
                chapterActive = false;
            } else if (choice == 0) {
                clueCollector.searchRoom(currentRoom, playerScore);

                // Story-driven events during search
                typeWriter("\n[SYSTEM] Observing temporal distortions at depth " + to_string(depth) + "...\n");
                actionStack.push("Temporal paradox observed", 82 + depth, "Temporal Paradox Zone", 8);

                // Update suspicion based on depth
                if (depth == 1 || depth == 2) {
                    suspects.updateSuspicion("Commander Hayes", 1);
                    suspects.updateSuspicion("Sarah Mitchell", 1);
                    suspects.updateSuspicion("Dr. Elena Markov", 2);
                }
                suspects.sortBySuspicion();
                suspects.displaySuspects();
            } else {
                currentRoom = roomNavigator.moveToRoom(currentRoom, choice);
            }
        }

        // Recursive story dive
        if (depth < 3) {
            typeWriter("The system forces a deeper dive...\nRe-entering memory layer...\n");
            chapter8(depth + 1);
        } else {
            // Final depth narration
            typeWriter("The recursion stabilizes.\n");
            actionStack.push("Recursion stabilized", 90, "Temporal Paradox Zone", 8);

            typeWriter("A final message appears:\n\"TIME CANNOT BE FIXED FROM INSIDE THE LOOP\"\n\"ONLY OBSERVED. ONLY CONTAINED.\"\n");
            actionStack.push("Final paradox message observed", 91, "Temporal Paradox Zone", 8);

            typeWriter("You finally understand.\nThe loop was never broken.\nIt was nested.\nEach reset buried inside another.\n");
            actionStack.push("Realized nested loops", 92, "Temporal Paradox Zone", 8);

            typeWriter("A loop...");
            typeWriter("Inside a loop...");
            typeWriter("Inside a loop.\n");

            typeWriter("You were not chosen to escape.");
            typeWriter("You were chosen to reach this depth.\n");
        }

        // Chapter summary
        typeWriter("\nChapter summary:\n");
        typeWriter("Score: " + to_string(playerScore) + "\n");
        clueCollector.displayCollectedClues();
        inventory.display();

        typeWriter("══════════════════════════════════════════════\n");
        typeWriter("EXITING CHAPTER 8\n");
        typeWriter("══════════════════════════════════════════════\n");
    }

 void chapter9() {
    // ======== Local game objects ======== 
    RoomNavigator roomNavigator;
    ClueCollector clueCollector;
    InventoryQueue inventory;
    AlarmCodePuzzle alarmPuzzle;
    int playerScore = 0;

    typeWriter("══════════════════════════════════════════════\n");
    typeWriter("CHAPTER 9 — ORDER FROM CHAOS\n");
    typeWriter("══════════════════════════════════════════════\n\n");

    int currentRoom = 2; // Archive Core
    bool chapterActive = true;

    actionStack.push("Entered Data Archives", 100, "Archive Core", 9);

    while (chapterActive) {
        roomNavigator.displayCurrentRoom(currentRoom);
        cout << "\nEnter choice (room number to move, 0 to search for clues, 1 to solve alarm, 9 to end chapter): ";
        int choice;
        cin >> choice;

        if (choice == 9) {
            typeWriter("\nChapter 9 ends here. Order has been restored, but the cost is heavy.\n");
            chapterActive = false;
        } else if (choice == 0) {
            clueCollector.searchRoom(currentRoom, playerScore);

            // Story-driven events for Archive Core
            typeWriter("\nScreens flicker endlessly with raw data.\nNumbers, dates, events stacked upon events.\n");
            actionStack.push("Observed chaotic data", 101, "Archive Core", 9);

            typeWriter("You begin to sort the events by priority and timestamp.\nOrder forms.\nThe timeline stabilizes.\n");
            actionStack.push("Timeline stabilized", 109, "Archive Core", 9);

            typeWriter("One entry keeps repeating...\nYou perform a binary search and locate the origin of the loop.\n");
            actionStack.push("Origin point located", 112, "Archive Core", 9);

            typeWriter("Dr. Elena Markov is revealed as the one maintaining the loop.\n");
            actionStack.push("Identified Dr. Elena Markov as controller", 115, "Archive Core", 9);

            // Update suspects dynamically
            suspects.updateSuspicion("Commander Hayes", 2);
            suspects.updateSuspicion("Sarah Mitchell", 2);
            suspects.updateSuspicion("Dr. Elena Markov", 3);
            suspects.sortBySuspicion();
            suspects.displaySuspects();
        } else if (choice == 1) {
            typeWriter("\nYou find an alarm system threatening to overload the archive.\n");
            if (alarmPuzzle.solvePuzzle(playerScore)) {
                inventory.addItem("Deactivated Alarm Key");
                actionStack.push("Alarm deactivated", 124, "Archive Core", 9);
            } else {
                typeWriter("⚠️ System instability increases!\n");
                actionStack.push("Alarm triggered, instability increased", 125, "Archive Core", 9);
            }
        } else {
            currentRoom = roomNavigator.moveToRoom(currentRoom, choice);
        }
    }

    // Show summary of collected clues and inventory
    typeWriter("\nChapter summary:\n");
    typeWriter("Score: " + to_string(playerScore) + "\n");
    clueCollector.displayCollectedClues();
    inventory.display();

    typeWriter("\n══════════════════════════════════════════════\n");
    typeWriter("END OF CHAPTER 9\n");
    typeWriter("══════════════════════════════════════════════\n");
}


void chapter10() {
    typeWriter("══════════════════════════════════════════════\n");
    typeWriter("CHAPTER 10 — THE FINAL REVELATION\n");
    typeWriter("══════════════════════════════════════════════\n\n");

    actionStack.push("Entered deepest Data Archives", 130, "Archive Root", 10);
    typeWriter("The deepest level of the Data Archives unlocks.\nNo alarms.\nNo warnings.\nOnly silence.\n");

    actionStack.push("Observed terminal untouched by resets", 131, "Archive Root", 10);
    typeWriter("The door slides open slowly.\nInside, a single terminal glows.\nOlder than the rest.\nUntouched by resets.\n");

    actionStack.push("Root access granted", 132, "Archive Root", 10);
    typeWriter("You approach.\n[SYSTEM] TEMPORAL ROOT ACCESS GRANTED\n");

    actionStack.push("Memories of all loops retrieved", 133, "Archive Root", 10);
    typeWriter("Your memories surge.\nEvery loop.\nEvery failure.\nEvery rewind.\nThey were never erased.\nThey were stored.\n");

    actionStack.push("Full action history visualized", 134, "Archive Root", 10);
    typeWriter("[DSA] Stack accessed — full action history retrieved.\nTerminal projects timeline tree with branching futures.\n");

    actionStack.push("Identified stable branch", 135, "Archive Root", 10);
    typeWriter("One branch pulses brighter than the rest.\nA stable loop.\nA controlled future.\n");

    actionStack.push("Dr. Markov's recorded message plays", 136, "Archive Root", 10);
    typeWriter("A voice echoes through the chamber.\n\"If you are seeing this, then the loop worked.\"\n");

    actionStack.push("Dr. Markov recording observed", 137, "Archive Root", 10);
    typeWriter("Dr. Elena Markov appears on the screen.\nNot live.\nA recording.\n");

    actionStack.push("Markov explains loop purpose", 138, "Archive Root", 10);
    typeWriter("\"We searched every outcome. Sorted them by survival. This was the least destructive future.\"\n");

    actionStack.push("Player identified as memory carrier", 139, "Archive Root", 10);
    typeWriter("She continues:\n\"Someone had to remain aware. Someone had to carry memory across resets. That person is you.\"\n");

    actionStack.push("Player realizes purpose", 140, "Archive Root", 10);
    typeWriter("Your chest tightens.\nThe truth settles heavily.\nYou were not trapped by the loop. You were chosen.\n");

    // Update suspects dynamically
    suspects.updateSuspicion("Commander Hayes", 3);
    suspects.updateSuspicion("Sarah Mitchell", 3);
    suspects.updateSuspicion("Dr. Elena Markov", 5);
    suspects.sortBySuspicion();
    suspects.displaySuspects();

    // === BINARY DECISION TREE FOR FINAL CHOICE ===
    int totalScore = 0;
    BinaryDecisionTree decisionTree;
    decisionTree.playChapter10(totalScore);

    typeWriter("\nYour final decision added a total score of: " + to_string(totalScore) + "\n");

    actionStack.push("Player makes final decision with score: " + to_string(totalScore), 145, "Archive Root", 10);

    // Optional: log full action stack
    actionStack.display();

    typeWriter("══════════════════════════════════════════════\n");
    typeWriter("END OF CHAPTER 10\n");
    typeWriter("══════════════════════════════════════════════\n");
}
    };

    /* =====================================================
    GAME FLOW FUNCTIONS
    - YAHAN STORY + TIMELINE MILTI HAI
    ===================================================== */
    void playChapter(int chapter, Story &story, TimelineManager &timeline) {
        switch (chapter) {
            case 0: story.chapter1(); break;
            case 1: story.chapter2(); break;
            case 2: story.chapter3(); break;
            case 3: story.chapter4(); break;
            case 4: story.chapter5(); break;
            case 5: story.chapter6(); break;
            case 6: story.chapter7(); break;
            case 7: story.chapter8(); break;
            case 8: story.chapter9(); break;
            case 9: story.chapter10(); break;
        }
        timeline.displayChapterTimeline(chapter);
    }


// =====================
// Main Function
// =====================
int main() {
    // Initialize file manager
    GameFileManager fileManager;
    
    // Game state tracking
    string playerName = "Detective";
    int currentChapter = 0;
    int currentRoom = 0;
    int playerScore = 0;
    int loopCount = 0;
    bool cluesCollected[10] = {false};
    int suspicionLevels[4] = {7, 5, 8, 4};
    
    Story story;
    
    // Auto-save before each chapter
    cout << "\n==> Starting Temporal Loop...\n";
    fileManager.saveGameState(playerName, 0, 0, 0, 0, cluesCollected, suspicionLevels);
    
    // Chapter 1
    story.chapter1();
    fileManager.saveChapterProgress(1, "Memory That Shouldn't Exist", playerScore);
    fileManager.saveGameState(playerName, 1, currentRoom, playerScore, loopCount, cluesCollected, suspicionLevels);
    
    // Chapter 2
    story.chapter2();
    fileManager.saveChapterProgress(2, "Research Wing", playerScore);
    fileManager.saveGameState(playerName, 2, currentRoom, playerScore, loopCount, cluesCollected, suspicionLevels);
    
    // Chapter 3
    story.chapter3();
    fileManager.saveChapterProgress(3, "Security Sector", playerScore);
    fileManager.saveGameState(playerName, 3, currentRoom, playerScore, loopCount, cluesCollected, suspicionLevels);
    
    // Chapter 4
    story.chapter4();
    fileManager.saveChapterProgress(4, "Data Archives", playerScore);
    fileManager.saveGameState(playerName, 4, currentRoom, playerScore, loopCount, cluesCollected, suspicionLevels);
    
    // Chapter 5
    story.chapter5();
    fileManager.saveChapterProgress(5, "Research Wing Confrontation", playerScore);
    fileManager.saveGameState(playerName, 5, currentRoom, playerScore, loopCount, cluesCollected, suspicionLevels);
    
    // Chapter 6
    story.chapter6();
    fileManager.saveChapterProgress(6, "People Who Change", playerScore);
    fileManager.saveGameState(playerName, 6, currentRoom, playerScore, loopCount, cluesCollected, suspicionLevels);
    
    // Chapter 7
    story.chapter7();
    fileManager.saveChapterProgress(7, "The Choice That Breaks Time", playerScore);
    fileManager.saveGameState(playerName, 7, currentRoom, playerScore, loopCount, cluesCollected, suspicionLevels);
    
    // Chapter 8
    story.chapter8();
    fileManager.saveChapterProgress(8, "The Loop Within The Loop", playerScore);
    fileManager.saveGameState(playerName, 8, currentRoom, playerScore, loopCount, cluesCollected, suspicionLevels);
    
    // Chapter 9
    story.chapter9();
    fileManager.saveChapterProgress(9, "Order From Chaos", playerScore);
    fileManager.saveGameState(playerName, 9, currentRoom, playerScore, loopCount, cluesCollected, suspicionLevels);
    
    // Chapter 10 - Final
    story.chapter10();
    fileManager.saveChapterProgress(10, "The Final Revelation", playerScore);
    fileManager.saveGameState(playerName, 10, currentRoom, playerScore, loopCount, cluesCollected, suspicionLevels);
    
    // Save final high score
    fileManager.saveHighScore(playerName, playerScore, loopCount);
    
    // Export final suspect data
    string suspectNames[4] = {"Dr. Elena Markov", "Commander Hayes", "Dr. Chen Wei", "Sarah Mitchell"};
    fileManager.exportSuspectData(suspectNames, suspicionLevels);
    
    // Display completion
    cout << "\n\n+--------------------------------------------------------+\n";
    cout << "�              GAME COMPLETE!                           �\n";
    cout << "+--------------------------------------------------------+\n";
    cout << "Final Score: " << playerScore << "\n";
    cout << "Time Loops: " << loopCount << "\n";
    
    // Show high scores
    fileManager.displayHighScores();
    
    cout << "\n==> All game data saved to files:\n";
    cout << "    - temporal_savegame.txt (Game state)\n";
    cout << "    - temporal_progress.txt (Chapter log)\n";
    cout << "    - temporal_highscores.txt (High scores)\n";
    cout << "    - temporal_suspects.txt (Suspect data)\n";
    
    return 0;
}
