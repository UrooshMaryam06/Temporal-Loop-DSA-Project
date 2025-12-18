#include <iostream>
#include <string>
using namespace std;

/* -------------------- MANUAL STRUCTURES -------------------- */

// ---------------- Stack for player actions ----------------
struct Stack {
    string arr[100];
    int top;
    Stack() { top = -1; }
    void push(string val) { arr[++top] = val; }
    void pop() { if(top >= 0) top--; }
    string peek() { return (top >= 0) ? arr[top] : ""; }
    bool empty() { return top == -1; }
} actionHistory;

// ---------------- Queue for timeline events ----------------
struct Queue {
    string arr[100];
    int front, rear;
    Queue() { front = 0; rear = -1; }
    void enqueue(string val) { arr[++rear] = val; }
    void dequeue() { if(front <= rear) front++; }
    string peek() { return (front <= rear) ? arr[front] : ""; }
    bool empty() { return front > rear; }
} eventQueue;

// ---------------- Priority Queue for critical events (Min Heap) ----------------
struct Event {
    string name;
    int priority;
};

struct PriorityQueue {
    Event heap[100];
    int size;
    PriorityQueue() { size = 0; }

    void swap(int i, int j) { Event temp = heap[i]; heap[i] = heap[j]; heap[j] = temp; }

    void heapifyUp(int index) {
        if(index == 0) return;
        int parent = (index - 1)/2;
        if(heap[index].priority < heap[parent].priority) {
            swap(index, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int left = 2*index + 1;
        int right = 2*index + 2;
        int smallest = index;
        if(left < size && heap[left].priority < heap[smallest].priority) smallest = left;
        if(right < size && heap[right].priority < heap[smallest].priority) smallest = right;
        if(smallest != index) { swap(index, smallest); heapifyDown(smallest); }
    }

    void push(string name, int priority) {
        heap[size].name = name;
        heap[size].priority = priority;
        heapifyUp(size);
        size++;
    }

    Event top() { return (size > 0) ? heap[0] : Event{"", -1}; }
    void pop() { if(size == 0) return; heap[0] = heap[size-1]; size--; heapifyDown(0); }
    bool empty() { return size == 0; }
} criticalEvents;

// ---------------- Linked List for suspects ----------------
struct Node {
    string name;
    Node* next;
    Node(string n) { name = n; next = nullptr; }
};
Node* suspectsHead = nullptr;
void addSuspect(string name) {
    Node* newNode = new Node(name);
    if(!suspectsHead) { suspectsHead = newNode; return; }
    Node* temp = suspectsHead;
    while(temp->next) temp = temp->next;
    temp->next = newNode;
}

// ---------------- Hash Table (Array) for clues ----------------
struct Clue {
    int id;
    string description;
};
Clue clues[100];
int clueCount = 0;
void addClue(int id, string desc) {
    clues[clueCount].id = id;
    clues[clueCount].description = desc;
    clueCount++;
}
void findClue(int id) {
    for(int i=0;i<clueCount;i++) {
        if(clues[i].id == id) { cout<<"Clue Found: "<<clues[i].description<<endl; return; }
    }
    cout<<"Clue not found.\n";
}

// ---------------- Graph (Adjacency Matrix) for locations ----------------
string locations[4] = {"Control Hall","Research Wing","Data Archives","Security Sector"};
int locationGraph[4][4]; // 1 = connected
int getLocationIndex(string loc) {
    for(int i=0;i<4;i++) if(locations[i]==loc) return i;
    return -1;
}

// ---------------- Tree for decision paths ----------------
struct DecisionNode {
    string choice;
    DecisionNode* left;
    DecisionNode* right;
    DecisionNode(string c) { choice = c; left = right = nullptr; }
};

/* -------------------- INITIALIZATION -------------------- */
string timelineEvents[10];
int timelineSize = 0;

void initializeTimeline() {
    timelineEvents[0] = "Alarm Rings";
    timelineEvents[1] = "Power Flicker";
    timelineEvents[2] = "Security Alert";
    timelineEvents[3] = "System Malfunction";
    timelineSize = 4;
    for(int i=0;i<timelineSize;i++) eventQueue.enqueue(timelineEvents[i]);
}

void initializeLocations() {
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) locationGraph[i][j]=0;
    locationGraph[0][1]=1; locationGraph[0][2]=1;
    locationGraph[1][3]=1; locationGraph[2][0]=1;
}

void initializeSuspects() {
    addSuspect("Dr. Hale");
    addSuspect("Engineer Nova");
    addSuspect("Security Chief Orion");
}

void initializeClues() {
    addClue(1,"Corrupted system log");
    addClue(2,"Handwritten note");
    addClue(3,"Security override key");
}

/* -------------------- GAME MECHANICS -------------------- */
void performAction(string action) {
    actionHistory.push(action);
    cout<<"Action performed: "<<action<<endl;
}

void resetTime() {
    cout<<"\n--- TIME RESET ---\n";
    while(!actionHistory.empty()) actionHistory.pop();
    cout<<"All actions reverted.\n";
}

void processEventQueue() {
    if(!eventQueue.empty()) {
        cout<<"Event Triggered: "<<eventQueue.peek()<<endl;
        eventQueue.dequeue();
    }
}

void addCriticalEvent(string name, int priority) {
    criticalEvents.push(name,priority);
}

void movePlayer(string current, string destination) {
    int c = getLocationIndex(current);
    int d = getLocationIndex(destination);
    if(c==-1 || d==-1) { cout<<"Invalid location.\n"; return; }
    if(locationGraph[c][d]==1) cout<<"Moved from "<<current<<" to "<<destination<<endl;
    else cout<<"Invalid move.\n";
}

/* -------------------- RECURSIVE TIME LOOP -------------------- */
void gameLoop(int loopCount) {
    if(loopCount>3) return; // stop demo

    cout<<"\n--- LOOP "<<loopCount<<" ---\n";

    performAction("Investigate Control Hall");
    processEventQueue();

    if(loopCount==2) {
        cout<<"Critical failure occurred!\n";
        resetTime();
        addCriticalEvent("Reactor Failure",1);
        gameLoop(loopCount+1);
    }
}

/* -------------------- STORY DECISION TREE -------------------- */
DecisionNode* buildDecisionTree() {
    DecisionNode* root = new DecisionNode("Final Decision");
    root->left = new DecisionNode("Destroy the Temporal Loop");
    root->right = new DecisionNode("Preserve the Temporal Loop");
    return root;
}

/* -------------------- MAIN FUNCTION -------------------- */
int main() {
    cout<<"===== TEMPORAL LOOP =====\n";
    cout<<"A DSA-Based Time Travel Adventure Game\n";

    initializeTimeline();
    initializeLocations();
    initializeSuspects();
    initializeClues();

    gameLoop(1);

    DecisionNode* ending = buildDecisionTree();
    cout<<"\nChoose your ending:\n";
    cout<<"1. "<<ending->left->choice<<endl;
    cout<<"2. "<<ending->right->choice<<endl;

    cout<<"\nGame Over.\n";
    return 0;
}
