/************************************************************
 *  TEMPORAL LOOP
 *  A DSA-Based Time Travel Adventure Game
 *
 *  CS-221 Semester Project
 *
 *  NOTE FOR SIR:
 *  Each chapter demonstrates a practical use of
 *  Data Structures & Algorithms integrated with gameplay.
 ************************************************************/

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
                    cout << "\n✓ " << name << " suspicion updated to " << newLevel << "/10\n";
                    return;
                }
                temp = temp->next;
            }
            cout << "\n✗ Suspect not found!\n";
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
            cout << "\n╔════════════════════════════════════════════════════════╗\n";
            cout << "║              SUSPECT DATABASE                         ║\n";
            cout << "╚════════════════════════════════════════════════════════╝\n";
            
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
            
            cout << "\n╔════════════════════════════════════════════════════════╗\n";
            cout << "║         CHAPTER " << chapter << " TIMELINE EVENTS                     ║\n";
            cout << "╚════════════════════════════════════════════════════════╝\n";
            
            for (int i = 0; i < eventCounts[chapter]; i++) {
                cout << "  " << (i + 1) << ". " << timelineEvents[chapter][i] << "\n";
            }
            cout << "\n";
        }
    };

    // ===============================
// 3. STACK FOR ACTION HISTORY
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
        cout << "\n🔄 REWINDING TIME...\n";
        cout << "═══════════════════════════════════════════\n";
        
        int rewound = 0;
        while (!isEmpty() && rewound < steps) {
            ActionNode action = pop();
            cout << "⏪ Undoing: " << action.action << "\n";
            rewound++;
        }
        
        cout << "✓ Rewound " << rewound << " action(s)\n";
    }

    void display() {
        cout << "\n╔════════════════════════════════════════════════════════╗\n";
        cout << "║           ACTION HISTORY (Most Recent First)          ║\n";
        cout << "╚════════════════════════════════════════════════════════╝\n";
        
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
// 4. BINARY DECISION TREE (Chapters 7 & 10)
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

        cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        cout << "DECISION NODE #" << node->nodeId << "\n";
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        cout << node->scenario << "\n\n";
        cout << "1. " << node->choiceA << " [Score: " << node->scoreA << "]\n";
        cout << "2. " << node->choiceB << " [Score: " << node->scoreB << "]\n";
        cout << "\nYour choice (1/2): ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "\n→ You chose: " << node->choiceA << "\n";
            totalScore += node->scoreA;
            cout << "  Score gained: +" << node->scoreA << "\n";
            
            if (node->left) {
                return traverseTree(node->left, totalScore);
            }
            return node->scoreA;
        } else {
            cout << "\n→ You chose: " << node->choiceB << "\n";
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
// 5. ROOM MOVEMENT SYSTEM (Array-based Graph)
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
        cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        cout << "📍 LOCATION: " << roomNames[roomId] << "\n";
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
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
                    cout << "\n✓ Moving to " << roomNames[i] << "...\n";
                    return i;
                }
            }
        }
        cout << "\n✗ Invalid room choice!\n";
        return currentRoom;
    }
    
    string getRoomName(int id) {
        return roomNames[id];
    }
};
    // ===============================
    // 6. CLUE COLLECTION SYSTEM (Array)
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
            cout << "\n╔════════════════════════════════════════════════════════╗\n";
            cout << "║              COLLECTED CLUES                          ║\n";
            cout << "╚════════════════════════════════════════════════════════╝\n";
            
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
    // 7. INVENTORY SYSTEM (Queue)
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
                cout << "📦 Added to inventory: " << item << "\n";
            } else {
                cout << "⚠️  Inventory full!\n";
            }
        }
        
        void useItem() {
            if (size > 0) {
                string used = items[front];
                front = (front + 1) % capacity;
                size--;
                cout << "✓ Used item: " << used << "\n";
            } else {
                cout << "✗ Inventory is empty!\n";
            }
        }
        
        void display() {
            cout << "\n╔════════════════════════════════════════════════════════╗\n";
            cout << "║                 INVENTORY                             ║\n";
            cout << "╚════════════════════════════════════════════════════════╝\n";
            
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
    // 8. MINI-PUZZLES
    // ===============================
    class AlarmCodePuzzle {
    public:
        bool solvePuzzle(int &score) {
            cout << "\n╔════════════════════════════════════════════════════════╗\n";
            cout << "║            PUZZLE: ALARM CODE CRACKER                 ║\n";
            cout << "╚════════════════════════════════════════════════════════╝\n";
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
                    cout << "\n✓ ALARM DEACTIVATED!\n";
                    score += 50;
                    return true;
                } else {
                    attempts--;
                    if (attempts > 0) {
                        cout << "✗ Incorrect! Try again.\n";
                    }
                }
            }
            cout << "✗ ALARM TRIGGERED!\n";
            return false;
        }
    };

    class KeycardSearchPuzzle {
    public:
        bool solvePuzzle(int &score) {
            cout << "\n╔════════════════════════════════════════════════════════╗\n";
            cout << "║         PUZZLE: KEYCARD SEARCH                        ║\n";
            cout << "╚════════════════════════════════════════════════════════╝\n";
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
                    cout << "\n✓ KEYCARD FOUND at " << locations[choice - 1] << "!\n";
                    score += 40;
                    return true;
                } else {
                    if (searches < 3) {
                        if (choice - 1 < keycardLoc) {
                            cout << "✗ Not here. Try HIGHER numbers.\n";
                        } else {
                            cout << "✗ Not here. Try LOWER numbers.\n";
                        }
                    }
                }
            }
            cout << "✗ Search failed! Keycard was at: " << locations[keycardLoc] << "\n";
            return false;
        }
    };

    class RecursiveLoopPuzzle {
    private:
        bool checkLoop(int depth, int maxDepth, int &score) {
            for (int i = 0; i < depth; i++) cout << "  ";
            cout << "→ Loop Level " << depth << "\n";
            
            if (depth >= maxDepth) {
                cout << "\n✓ Loop complete!\n";
                return true;
            }
            
            cout << "   Question: " << (depth + 1) << " * 2 = ? ";
            int answer;
            cin >> answer;
            cin.ignore();
            
            if (answer == (depth + 1) * 2) {
                cout << "   ✓ Correct!\n\n";
                score += 10;
                return checkLoop(depth + 1, maxDepth, score);
            } else {
                cout << "   ✗ Wrong! Loop failed.\n";
                return false;
            }
        }

    public:
        bool solvePuzzle(int &score) {
            cout << "\n╔════════════════════════════════════════════════════════╗\n";
            cout << "║         PUZZLE: RECURSIVE LOOP CHECK                  ║\n";
            cout << "╚════════════════════════════════════════════════════════╝\n";
            cout << "\nNavigate 5 nested time loops. Answer at each level.\n\n";
            
            return checkLoop(0, 5, score);
        }
    };

    // ===============================
    // 9. SAVE/LOAD SYSTEM
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
                cout << "\n💾 Game saved!\n";
            }
        }
        
        static bool loadGame(string &name, int &score, int &room, int &chapter) {
            ifstream in("temporalloop_save.txt");
            if (in.is_open()) {
                getline(in, name);
                in >> score >> room >> chapter;
                in.close();
                cout << "\n📂 Game loaded!\n";
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


        void chapter1() {
            typeWriter("═══════════════════════════════════════════════════");
            typeWriter("CHAPTER 1 — MEMORY THAT SHOULDN'T EXIST\n");
            typeWriter("═══════════════════════════════════════════════════\n");

            typeWriter("You wake up again.\nThe alarms blare. The clocks read 07:00 AM. Everything looks familiar, yet eerily strange.\n");
            typeWriter("Your mind flashes with memories that shouldn't exist.\n");
            typeWriter("You recall walking through these halls, seeing the same events unfold over and over, but nobody else remembers.\n");

            typeWriter("A scientist rushes past you:\n");
            typeWriter("\"We need to stabilize the Temporal Engine!\" he shouts, panic in his voice.\n");

            typeWriter("You remember exactly what happens next. The alarms, the system errors, the critical failure...\n");
            typeWriter("But this time, you are aware. You are the only variable that did not reset.\n");

            typeWriter("Every action you take from this point onward is recorded — because memory is your greatest weapon.\n");
            typeWriter("You feel a strange energy coursing through your mind as you realize you can manipulate the loop.\n");

            typeWriter("Do you:\n");
            typeWriter("1. Head to the Control Hall to check the Temporal Engine.\n");
            typeWriter("2. Investigate the Research Wing for clues about what caused the loops.\n");

            typeWriter("\n--- End of Chapter 1 ---\n");
        }

        void chapter2() {
            typeWriter("═══════════════════════════════════════════════════");
            typeWriter("CHAPTER 2 — THE RESEARCH WING AND FIRST CLUES\n");
            typeWriter("═══════════════════════════════════════════════════\n");

            typeWriter("You decide to investigate the Research Wing.\n");
            typeWriter("Rows of labs stretch before you, filled with strange machinery and flickering monitors.\n");

            typeWriter("A voice echoes in your memory:\n");
            typeWriter("\"The loops were not an accident... someone is controlling the Temporal Engine from within.\"\n");
            typeWriter("Your heart races. Could one of the staff be responsible?\n");

            typeWriter("You notice scattered papers and a half-open terminal.\n");
            typeWriter("One paper catches your eye. It reads:\n");
            typeWriter("\"If anyone finds this note, know that it was intentional. —Dr. Unknown\"\n");

            typeWriter("You also spot a lab assistant working on a console, oblivious to your presence.\n");
            typeWriter("Do you:\n");
            typeWriter("1. Approach the assistant and ask questions.\n");
            typeWriter("2. Continue searching the lab for more clues without alerting anyone.\n");

            typeWriter("You move quietly, scanning the shelves and tables.\n");
            typeWriter("Among the scattered lab notes, you discover a **red security clearance keycard**.\n");
            typeWriter("This could allow access to restricted areas — perhaps even the Temporal Engine control room.\n");

            typeWriter("Your awareness of the loop allows you to memorize the positions of all clues and people.\n");
            typeWriter("You realize that gathering evidence is your path to understanding who is behind the loops.\n");

            typeWriter("\nChoices made in this chapter will affect later events.\n");
            typeWriter("--- End of Chapter 2 ---\n");
        }

    void chapter3() {


    typeWriter("═══════════════════════════════════════════════════");
    typeWriter("CHAPTER 3 — SECURITY SECTOR: SHADOWS AND SUSPECTS\n");
    typeWriter("═══════════════════════════════════════════════════\n");

    typeWriter("The security doors hiss as you enter the Security Sector.\n");
    typeWriter("Armed personnel move with precision, unaware that you know this layout by heart.\n");
    typeWriter("Monitors display feeds from every corner of the facility, but one screen flickers oddly.\n");

    typeWriter("A familiar voice in your mind whispers:\n");
    typeWriter("\"Commander Hayes always seems too calm. Something about him doesn’t fit.\"\n");

    typeWriter("As you move between consoles, you notice a **red security clearance keycard** in the drawer.\n");
    typeWriter("This matches what you found in the Research Wing — clearly someone is trying to manipulate access.\n");

    typeWriter("Your eyes catch a terminal with unusual activity logs:\n");
    typeWriter("- Timestamp 07:30 — Unauthorized override detected.\n");
    typeWriter("- Timestamp 07:45 — Temporal Engine diagnostics accessed remotely.\n");

    typeWriter("It becomes clear: someone is tampering with the timeline.\n");

    // Scenario choice: player observes clues — update suspicion levels
    typeWriter("\nYou quietly follow a security officer and overhear a whispered conversation:");
    typeWriter("\"The temporal containment must remain intact. Any interference will jeopardize the project.\"\n");

    typeWriter("You jot down notes in your mind — these could incriminate a suspect later.\n");

    typeWriter("\nWhile scanning the sector, you discover:");
    typeWriter("- A suspiciously unmarked audio recorder behind a console.");
    typeWriter("- A lab notebook with encrypted codes.");
    typeWriter("- Personnel logs highlighting unusual overtime shifts.\n");

    // Update suspicion levels based on discoveries
    suspects.updateSuspicion("Commander Hayes", 7);  // calm but secretive
    suspects.updateSuspicion("Dr. Chen Wei", 9);     // high access to Temporal Engine
    suspects.updateSuspicion("Sarah Mitchell", 6);   // anomalies in system logs

    // Sort suspects by suspicion for next loops
    suspects.sortBySuspicion();

    // Display updated suspect list (optional, for debugging or player awareness)
    suspects.displaySuspects();

    typeWriter("\nEvery discovery increases your suspicion:");
    typeWriter("- Commander Hayes: calm but secretive.");
    typeWriter("- Dr. Chen Wei: high access to the Temporal Engine.");
    typeWriter("- Sarah Mitchell: technical anomalies in system logs.\n");

    typeWriter("You realize that piecing together these clues is essential to uncovering the mastermind.\n");
    typeWriter("Memory of the loop gives you the advantage to remember every detail and avoid mistakes.\n");

    typeWriter("\nChoices in this chapter will influence the suspects' suspicion levels in future loops.\n");
    typeWriter("--- End of Chapter 3 ---\n");
}


void chapter4() {
    typeWriter("═══════════════════════════════════════════════════");
    typeWriter("CHAPTER 4 — DATA ARCHIVES: SECRETS OF THE TEMPORAL ENGINE\n");
    typeWriter("═══════════════════════════════════════════════════\n");

    typeWriter("You enter the Data Archives, the temperature drops slightly as the massive server racks hum.\n");
    typeWriter("Rows upon rows of encrypted data stretch into darkness, flickering with dim red lights.\n");

    typeWriter("Your memory from previous loops guides your steps — you know where the most sensitive files are.\n");
    typeWriter("A digital lock panel blinks: access code required.\n");

    typeWriter("You recall a note you found in the Research Wing — it hints at a master access code.\n");
    typeWriter("By combining the clue from the note and the security logs, you deduce the code.\n");

    typeWriter("Access granted. The terminal lights up with project files: 'Project Ouroboros', 'Temporal Engine Logs', 'Unauthorized Overrides'.\n");

    typeWriter("As you scroll through the logs, a chilling realization hits you:\n");
    typeWriter("\"Someone has been manipulating the loops, forcing events to happen at precise times.\"\n");

    typeWriter("You find an **audio log** marked with a timestamp 06:45 — the voice warns: \n");
    typeWriter("\"Do not interfere. The timeline is fragile.\"\n");

    typeWriter("Another log points directly to Dr. Chen Wei's manipulations in the Temporal Engine control sequences.\n");

    typeWriter("\nDo you:\n");
    typeWriter("1. Copy all critical files to your portable drive for later investigation.\n");
    typeWriter("2. Attempt to trace the current location of the manipulator using system logs.\n");

    typeWriter("While investigating, a sudden **alarm** blares across the facility.\n");
    typeWriter("Emergency lights flash red; the Temporal Engine is showing early signs of instability.\n");

    typeWriter("Your heart races. Every second counts.\n");
    typeWriter("Memory of the loops allows you to recall subtle discrepancies in the system readings.\n");

    typeWriter("\nYou quickly:\n");
    typeWriter("- Mark the critical timeline events in your mind.\n");
    typeWriter("- Collect all discoverable clues: corrupted logs, encrypted lab notebooks, and audio recordings.\n");
    typeWriter("- Record every action in your action history for future loops.\n");

    typeWriter("\nA faint shadow moves in the corner — someone is watching. Could it be Dr. Chen Wei?\n");

    // UPDATE SUSPICION BASED ON DISCOVERIES
    suspects.updateSuspicion("Dr. Chen Wei", 9);  // example: after logs discovery
    suspects.displaySuspects();

    typeWriter("\nChapter 4 ends here, but your choices will ripple through the loops.\n");
    typeWriter("--- End of Chapter 4 ---\n");
}

void chapter5() {
    typeWriter("═══════════════════════════════════════════════════");
    typeWriter("CHAPTER 5 — RESEARCH WING: CONFRONTATION AND CONSEQUENCES\n");
    typeWriter("═══════════════════════════════════════════════════\n");

    typeWriter("You move to the Research Wing. The room is dimly lit, the hum of machinery vibrating through the floor.\n");
    typeWriter("Familiar lab equipment is scattered around — vials, monitors, experimental consoles — but something feels off.\n");

    typeWriter("Your memory tells you: Dr. Chen Wei was here before you, leaving traces of unauthorized temporal manipulations.\n");

    typeWriter("Suddenly, a shadow moves — it's Dr. Chen Wei!\n");
    typeWriter("He glares at you: \"I knew someone would notice. But it’s too late to stop the sequence.\"\n");

    typeWriter("\nDo you:\n");
    typeWriter("1. Confront Dr. Chen Wei directly and demand an explanation.\n");
    typeWriter("2. Observe silently and gather more evidence before acting.\n");

    typeWriter("\nIf you choose to confront directly:");
    typeWriter("\"Explain yourself! Why are you manipulating the loops?\" you demand.\n");
    typeWriter("Dr. Chen Wei smirks: \"The future is fragile. Only I can ensure it doesn't collapse.\"\n");
    typeWriter("He activates a console, triggering a sudden spike in the Temporal Engine readings.\n");
    typeWriter("Warning lights flash: the facility shakes slightly — a critical event has begun!\n");

    typeWriter("\nIf you choose to gather evidence:");
    typeWriter("You quietly scan the consoles, copying encrypted data and noting timestamps of unauthorized actions.\n");
    typeWriter("Dr. Chen Wei is unaware for now, giving you an advantage for future loops.\n");
    typeWriter("Memory of previous loops allows you to record this without triggering suspicion.\n");

    typeWriter("\nRegardless of choice, critical events occur:\n");
    typeWriter("- Temporal Engine instability rises.\n");
    typeWriter("- Security alerts sound across the facility.\n");
    typeWriter("- Your action history records every step for future loops.\n");

    typeWriter("\nYou find a terminal with partial override codes — this may allow stabilizing the engine temporarily.\n");

    // UPDATE SUSPICION BASED ON CONFRONTATION/OBSERVATION
    suspects.updateSuspicion("Dr. Chen Wei", 10);  // fully suspicious after Chapter 5
    suspects.sortBySuspicion();
    suspects.displaySuspects();

    typeWriter("\nChapter 5 ends here — the Research Wing has revealed the manipulator's true intentions, and the Temporal Engine teeters on the edge.\n");
    typeWriter("--- End of Chapter 5 ---\n");
}


// Assume this is global or in main scope
SuspectLinkedList suspects;

void chapter6() {
    typeWriter("══════════════════════════════════════════════");
    typeWriter("CHAPTER 6 — PEOPLE WHO CHANGE");
    typeWriter("══════════════════════════════════════════════\n");

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

    // Update suspicion levels
    suspects.updateSuspicion("Commander Hayes", 6);  // Increased
    suspects.updateSuspicion("Sarah Mitchell", 5);   // Flagged
    suspects.updateSuspicion("Dr. Elena Markov", 7); // Unresolved / keep high

    // Sort suspects based on suspicion
    suspects.sortBySuspicion();

    // Display suspects for debugging / story purposes
    suspects.displaySuspects();

    typeWriter("[SYSTEM] Suspect list updated and sorted.\n");

    typeWriter("A warning flashes on a nearby terminal:\n");
    typeWriter("\"TEMPORAL MEMORY DEVIATION DETECTED\"\n");

    typeWriter("You step back into the shadows.");
    typeWriter("You are no longer the only variable.\n");

    typeWriter("If others begin to remember...");
    typeWriter("The loop will become uncontrollable.\n");

    typeWriter("People change.");
    typeWriter("And in broken time...");
    typeWriter("Change is dangerous.\n");

    typeWriter("══════════════════════════════════════════════");
    typeWriter("END OF CHAPTER 6");
    typeWriter("══════════════════════════════════════════════\n");
}

void chapter7() {
    typeWriter("══════════════════════════════════════════════");
    typeWriter("CHAPTER 7 — THE CHOICE THAT BREAKS TIME");
    typeWriter("══════════════════════════════════════════════\n");

    typeWriter("The system does not reset.\n");

    typeWriter("For the first time, the loop hesitates.");
    typeWriter("Milliseconds stretch into something heavier.");
    typeWriter("Almost like fear.\n");

    typeWriter("A terminal lights up ahead.");
    typeWriter("Its screen flickers — unstable.\n");

    typeWriter("[SYSTEM] TEMPORAL CORE ACCESS GRANTED\n");

    typeWriter("You step closer.");
    typeWriter("Every loop you survived flashes before you.");
    typeWriter("Every mistake.");
    typeWriter("Every death narrowly avoided.\n");

    typeWriter("The console displays a branching diagram.\n");
    typeWriter("Not lines.");
    typeWriter("Not paths.");
    typeWriter("Choices.\n");

    typeWriter("[DSA] Binary Decision Tree initialized.\n");

    typeWriter("Left branch:");
    typeWriter("\"Terminate the Temporal Loop\"");
    typeWriter("— All systems reset permanently.");
    typeWriter("— No more rewinds.");
    typeWriter("— No second chances.\n");

    typeWriter("Right branch:");
    typeWriter("\"Stabilize the Temporal Loop\"");
    typeWriter("— Infinite corrections possible.");
    typeWriter("— Memory fragments will spread.");
    typeWriter("— Time will never truly heal.\n");

    typeWriter("Your hands tremble.\n");

    typeWriter("You remember Chapter One.");
    typeWriter("The alarm.");
    typeWriter("The panic.");
    typeWriter("The first reset you didn’t understand.\n");

    typeWriter("Back then, time was a tool.");
    typeWriter("Now...");
    typeWriter("It is a weapon.\n");

    typeWriter("A warning appears in red:\n");
    typeWriter("\"DECISION NODE LOCKING IN 10 SECONDS\"\n");

    typeWriter("Dr. Markov’s voice echoes over the intercom.");
    typeWriter("\"You think this is about saving them,\" she says.");
    typeWriter("\"It’s about deciding who deserves tomorrow.\"\n");

    typeWriter("Commander Hayes pounds on the sealed door.");
    typeWriter("\"End it!\" he shouts.");
    typeWriter("\"No one should live like this!\"\n");

    typeWriter("Sarah whispers through a broken channel.");
    typeWriter("\"If you stop it…\"");
    typeWriter("\"Will we forget you?\"\n");

    typeWriter("Your breath catches.\n");

    typeWriter("This is no longer a system problem.");
    typeWriter("It is a moral one.\n");

    // Optional: update suspicion based on choices here as well
    suspects.updateSuspicion("Commander Hayes", 7);
    suspects.updateSuspicion("Sarah Mitchell", 6);

    suspects.sortBySuspicion();
    suspects.displaySuspects();

    typeWriter("[DSA] Traversing Decision Tree and suspect evaluation complete.\n");

    typeWriter("Left or right.");
    typeWriter("Destroy or preserve.");
    typeWriter("Freedom or control.\n");

    typeWriter("Your finger hovers over the input key.\n");

    typeWriter("Once chosen...");
    typeWriter("There will be no rewind.\n");

    typeWriter("Time holds its breath.\n");

    typeWriter("══════════════════════════════════════════════");
    typeWriter("END OF CHAPTER 7");
    typeWriter("══════════════════════════════════════════════\n");
 }

        void chapter8(int depth = 1) {
        typeWriter("══════════════════════════════════════════════");
        typeWriter("CHAPTER 8 — THE LOOP WITHIN THE LOOP");
        typeWriter("══════════════════════════════════════════════\n");

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

            if (depth == 1) {
            suspects.updateSuspicion("Commander Hayes", 1);
            suspects.updateSuspicion("Sarah Mitchell", 1);
            suspects.updateSuspicion("Dr. Elena Markov", 2);
        } else if (depth == 2) {
            suspects.updateSuspicion("Commander Hayes", 1);
            suspects.updateSuspicion("Sarah Mitchell", 1);
            suspects.updateSuspicion("Dr. Elena Markov", 2);
        }

        suspects.sortBySuspicion();
        suspects.displaySuspects();

        if (depth < 3) {
            typeWriter("The system forces a deeper dive.\n");
            typeWriter("Re-entering memory layer...\n");

            chapter8(depth + 1);   // Recursive call
        } 
         else {
            typeWriter("The recursion stabilizes.\n");

            typeWriter("A final message appears:\n");
            typeWriter("\"TIME CANNOT BE FIXED FROM INSIDE THE LOOP\"");
            typeWriter("\"ONLY OBSERVED. ONLY CONTAINED.\"\n");

            typeWriter("You finally understand.\n");

            typeWriter("The loop was never broken.");
            typeWriter("It was nested.\n");

            typeWriter("Each reset buried inside another.");
            typeWriter("A loop...");
            typeWriter("Inside a loop...");
            typeWriter("Inside a loop.\n");

            typeWriter("You were not chosen to escape.");
            typeWriter("You were chosen to reach this depth.\n");
        }

        typeWriter("══════════════════════════════════════════════");
        typeWriter("EXITING CHAPTER 8");
        typeWriter("══════════════════════════════════════════════\n");
    }

    void chapter9() {
        typeWriter("══════════════════════════════════════════════");
        typeWriter("CHAPTER 9 — ORDER FROM CHAOS");
        typeWriter("══════════════════════════════════════════════\n");

        typeWriter("The Data Archives breathe.\n");
        typeWriter("Screens flicker endlessly.");
        typeWriter("Numbers.");
        typeWriter("Dates.");
        typeWriter("Events stacked upon events.\n");

        typeWriter("This is not information.");
        typeWriter("This is noise.\n");

        typeWriter("You step into the archive core.\n");

        typeWriter("A holographic message appears:\n");
        typeWriter("\"TEMPORAL DATA OVERLOAD\"");
        typeWriter("\"STRUCTURAL FAILURE IMMINENT\"\n");

        typeWriter("Your pulse quickens.\n");

        typeWriter("Raw data floods the system:\n");
        typeWriter("• Power fluctuations");
        typeWriter("• Memory deviations");
        typeWriter("• Security overrides");
        typeWriter("• Reactor anomalies");
        typeWriter("• Human interference logs\n");

        typeWriter("None of it makes sense.");
        typeWriter("Not yet.\n");

        typeWriter("You understand what must be done.\n");
        typeWriter("Chaos cannot be destroyed.");
        typeWriter("It must be organized.\n");

        typeWriter("[SYSTEM] INITIATING DATA SORT\n");
        typeWriter("[DSA] Sorting events by priority and timestamp.\n");

        typeWriter("Events rearrange themselves.");
        typeWriter("Urgent anomalies rise to the top.");
        typeWriter("Minor fluctuations sink below.\n");

        typeWriter("Order begins to form.\n");

        typeWriter("The screen stabilizes.");
        typeWriter("For the first time since the loop began...\n");
        typeWriter("You can read the timeline.\n");

        typeWriter("One entry keeps reappearing.\n");
        typeWriter("You narrow the dataset.\n");

        typeWriter("[DSA] Binary Search initiated on sorted logs.\n");
        typeWriter("Searching for origin point...");
        typeWriter("Searching for first deviation...\n");

        typeWriter("MATCH FOUND.\n");
        typeWriter("Timestamp:");
        typeWriter("06:59:58 AM — TWO SECONDS BEFORE FIRST LOOP\n");

        typeWriter("Your breath catches.\n");
        typeWriter("An event recorded before the loop existed.");
        typeWriter("Impossible.\n");

        typeWriter("You scroll further.\n");
        typeWriter("Another match.");
        typeWriter("And another.");
        typeWriter("All identical.\n");

        typeWriter("Same authorization.");
        typeWriter("Same access level.\n");

        typeWriter("OMEGA CLEARANCE.\n");
        typeWriter("A name appears repeatedly:\n");
        typeWriter("Dr. Elena Markov\n");

        typeWriter("Your hands tighten.\n");
        typeWriter("She wasn’t reacting to the loop.");
        typeWriter("She was maintaining it.\n");

        typeWriter("[DSA] Sequential search confirms pattern across loops.\n");

        // Update suspects dynamically
        suspects.updateSuspicion("Commander Hayes", 2);
        suspects.updateSuspicion("Sarah Mitchell", 2);
        suspects.updateSuspicion("Dr. Elena Markov", 3);

        suspects.sortBySuspicion();
        suspects.displaySuspects();

        typeWriter("Every catastrophic outcome was logged.");
        typeWriter("Every successful containment preserved.\n");

        typeWriter("The realization settles slowly.\n");

        typeWriter("The loop was not a mistake.");
        typeWriter("It was a solution.\n");

        typeWriter("Someone sorted futures.");
        typeWriter("Someone searched outcomes.");
        typeWriter("Someone chose the least destructive path.\n");

        typeWriter("And now...");
        typeWriter("That responsibility has shifted to you.\n");

        typeWriter("[SYSTEM] DATA INTEGRITY: 100%");
        typeWriter("[SYSTEM] TRUTH STATUS: UNLOCKED\n");

        typeWriter("The room falls silent.\n");
        typeWriter("Order has been restored.\n");
        typeWriter("But order comes with a cost.\n");

        typeWriter("Because now you know:\n");
        typeWriter("Chaos was never the threat.");
        typeWriter("Uncontrolled choice was.\n");

        typeWriter("══════════════════════════════════════════════");
        typeWriter("END OF CHAPTER 9");
        typeWriter("══════════════════════════════════════════════\n");
    }


void chapter10() {
    typeWriter("══════════════════════════════════════════════");
    typeWriter("CHAPTER 10 — THE FINAL REVELATION");
    typeWriter("══════════════════════════════════════════════\n");

    typeWriter("The deepest level of the Data Archives unlocks.\n");

    typeWriter("No alarms.");
    typeWriter("No warnings.");
    typeWriter("Only silence.\n");

    typeWriter("The door slides open slowly.\n");

    typeWriter("Inside, a single terminal glows.");
    typeWriter("Older than the rest.");
    typeWriter("Untouched by resets.\n");

    typeWriter("You approach.\n");

    typeWriter("[SYSTEM] TEMPORAL ROOT ACCESS GRANTED\n");

    typeWriter("Your memories surge.\n");

    typeWriter("Every loop.");
    typeWriter("Every failure.");
    typeWriter("Every rewind.\n");

    typeWriter("They were never erased.");
    typeWriter("They were stored.\n");

    typeWriter("[DSA] Stack accessed — full action history retrieved.\n");

    typeWriter("The terminal projects a timeline tree.\n");
    typeWriter("Branches stretch endlessly.");
    typeWriter("Some collapse.");
    typeWriter("Some stabilize.");
    typeWriter("Most end in ruin.\n");

    typeWriter("[DSA] Decision Tree traversal completed.\n");

    typeWriter("One branch pulses brighter than the rest.\n");
    typeWriter("A stable loop.");
    typeWriter("A controlled future.\n");

    typeWriter("A voice echoes through the chamber.\n");
    typeWriter("\"If you are seeing this,\"");
    typeWriter("\"then the loop worked.\"\n");

    typeWriter("Dr. Elena Markov appears on the screen.\n");
    typeWriter("Not live.");
    typeWriter("A recording.\n");

    typeWriter("\"We searched every outcome,\" she says.");
    typeWriter("\"Sorted them by survival.\"");
    typeWriter("\"This was the least destructive future.\"\n");

    typeWriter("Your chest tightens.\n");

    typeWriter("She continues:\n");
    typeWriter("\"Someone had to remain aware.\"");
    typeWriter("\"Someone had to carry memory across resets.\"");
    typeWriter("\"That person is you.\"\n");

    typeWriter("You stagger back.\n");
    typeWriter("The truth settles heavily.\n");
    typeWriter("You were not trapped by the loop.");
    typeWriter("You were chosen.\n");

    typeWriter("[DSA] Priority Queue resolved — critical future identified.\n");

    // Update suspects based on the final revelation
    suspects.updateSuspicion("Commander Hayes", 3);
    suspects.updateSuspicion("Sarah Mitchell", 3);
    suspects.updateSuspicion("Dr. Elena Markov", 5);

    suspects.sortBySuspicion();
    suspects.displaySuspects();

    typeWriter("The terminal presents two final commands.\n");

    typeWriter("OPTION 1:");
    typeWriter("Destroy the Temporal Loop.");
    typeWriter("Restore natural time.");
    typeWriter("Release the future — uncertain, uncontrolled.\n");

    typeWriter("OPTION 2:");
    typeWriter("Preserve the Temporal Loop.");
    typeWriter("Maintain containment.");
    typeWriter("Sacrifice freedom for survival.\n");

    typeWriter("Your hands hover over the console.\n");

    typeWriter("You understand now.\n");
    typeWriter("This is not a system choice.");
    typeWriter("This is a human one.\n");

    typeWriter("Every structure.");
    typeWriter("Every algorithm.");
    typeWriter("Every loop.\n");
    typeWriter("They all led here.\n");

    typeWriter("You inhale slowly.\n");
    typeWriter("And make your decision.\n");

    typeWriter("══════════════════════════════════════════════");
    typeWriter("END OF CHAPTER 10");
    typeWriter("══════════════════════════════════════════════\n");
}
};

// =====================
// Main Function
// =====================
int main() {
    Story story;

    // Call chapters in order
    story.chapter1();
    story.chapter2();
    story.chapter3();
    story.chapter4();
    story.chapter5();
    story.chapter6();
    story.chapter7();
    story.chapter8();
    story.chapter9();
    story.chapter10();
    return 0;
}
