#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

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

        typeWriter("\nDo you:\n");
        typeWriter("1. Confront Commander Hayes immediately.\n");
        typeWriter("2. Continue gathering more evidence before making a move.\n");

        typeWriter("You quietly follow a security officer and overhear a whispered conversation:\n");
        typeWriter("\"The temporal containment must remain intact. Any interference will jeopardize the project.\"\n");

        typeWriter("You jot down notes in your mind — these could incriminate a suspect later.\n");

        typeWriter("\nWhile scanning the sector, you discover:\n");
        typeWriter("- A suspiciously unmarked audio recorder behind a console.\n");
        typeWriter("- A lab notebook with encrypted codes.\n");
        typeWriter("- Personnel logs highlighting unusual overtime shifts.\n");

        typeWriter("\nEvery discovery increases your suspicion:\n");
        typeWriter("- Commander Hayes: calm but secretive.\n");
        typeWriter("- Dr. Chen Wei: high access to the Temporal Engine.\n");
        typeWriter("- Sarah Mitchell: technical anomalies in system logs.\n");

        typeWriter("\nYou realize that piecing together these clues is essential to uncovering the mastermind.\n");
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
        typeWriter("You must decide: confront now, or prepare and gather more evidence?\n");

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

        typeWriter("\nRegardless of choice, critical events occur:");
        typeWriter("- Temporal Engine instability rises.\n");
        typeWriter("- Security alerts sound across the facility.\n");
        typeWriter("- Your action history records every step for future loops.\n");

        typeWriter("\nYou find a terminal with partial override codes — this may allow stabilizing the engine temporarily.\n");

        typeWriter("\nDo you:\n");
        typeWriter("1. Attempt to stabilize the engine now.\n");
        typeWriter("2. Retreat and plan the next move, preserving memory for the loop.\n");

        typeWriter("\nEvery choice impacts the upcoming loops and the story’s consequence points.\n");
        typeWriter("\nChapter 5 ends here — the Research Wing has revealed the manipulator's true intentions, and the Temporal Engine teeters on the edge.\n");
        typeWriter("--- End of Chapter 5 ---\n");
    }

    void Chapter6() {
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

        typeWriter("══════════════════════════════════════════════");
        typeWriter("END OF CHAPTER 6");
        typeWriter("══════════════════════════════════════════════\n");
    }

    void Chapter7() {
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

        typeWriter("[DSA] Traversing Decision Tree...\n");

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


    void Chapter8(int depth = 1) {
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

    if (depth < 3) {
        typeWriter("The system forces a deeper dive.\n");
        typeWriter("Re-entering memory layer...\n");

        Chapter8(depth + 1);   // Recursive call
    } else {
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

        void Chapter9() {
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

    void Chapter10() {
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

int main() {
    Story story;


    story.chapter1();  // Call chapter 1 only
    story.chapter2();  // Call Chapter 2
    story.chapter3();
    story.chapter4();
    story.chapter5();
    story.Chapter6();
    story.Chapter7();
    story.Chapter8();
    story.Chapter9();
    story.Chapter10();

    return 0;
}
