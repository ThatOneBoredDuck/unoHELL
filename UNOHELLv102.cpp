#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>
//<number> means number of the rule on the list, don't be that stupid.
//del <number>: delete a permanent rule.
//delrules <number>: delete a rule.
//delevent: delete an event.
//addrule: add a rule.
//addprule: add a permanent rule.
//addevent: add an event.
using namespace std;

void typeText(const string& text, int delayMs = 10)
{
    cout << "\033[34m";
    for(char c : text)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    cout << "\033[0m" << endl;
}
void typeRed(const string& text)
{
    cout << "\033[31m" << text << "\033[0m" << endl;
}
vector<string> activePermanentRules;
vector<string> activeRules;
    void showActiveRules()
    {
        typeText("\n===== ACTIVE RULES =====", 2);
    
        if(activeRules.empty())
        {
            typeText("None", 2);
            return;
        }
    
        for(size_t i = 0; i < activeRules.size(); i++)
        {
            typeText(to_string(i + 1) + ". " + activeRules[i], 1);
        }
    }
string activeEvent = "";
    void showActiveEvent()
    {
        typeText("\n===== ACTIVE EVENT =====", 2);
    
        if(activeEvent.empty())
        {
            typeText("None", 2);
            return;
        }
    
        typeText(activeEvent, 2);
    }
void showPermanentRules()
{
    typeText("\n===== ACTIVE PERMANENT RULES =====", 2);

    if(activePermanentRules.empty())
    {
        typeText("None", 2);
        return;
    }

    for(size_t i = 0; i < activePermanentRules.size(); i++)
        typeText(to_string(i + 1) + ". " + activePermanentRules[i], 1);
}

int main()
{
    random_device rd;
    mt19937 rng(rd());

    vector<string> chaosRules =
    {
        "All rules cannot be removed until this rule is removed."
        "If this rule gets removed, add 3 rolls, everyone loses 3 cards. (Cannot reduce cards below 2)",
        "All black cards count as 7s.",
        "All red cards count as Draw 2s.",
        "Every 7 rolls an extra +1 roll.",
        "Draw cards stack by +2 extra each time it gets stacked.",
        "Draw cards cannot be played until there's a new rule.",
        "All number cards are Wild cards.",
        "All action cards are number cards.",
        "Blue cards cannot be the last card.",
        "Red cards cannot be used to change colors.",
        "Green cards cannot be used to stack.",
        "Yellow cards cannot be played unless it's the last cards of yours.",
        "1s and 0s count as 7s."
        "All 2s count as a black card.",
        "All 4s count as Reverse cards.",
        "All 5s count as Wild cards.",
        "All 6s count as Draw 2s.",
        "All 8s count as Reverse cards.",
        "All 9s played removes 1 rules.",
        "Playing a 7 rolls an extra +1 roll.",
        "Playing a Wild rolls 2 extra rules.",
        "Playing a Draw card rolls an extra roll.",
        "Playing a Reverse remove 2 rules.",
        "Wild cards cannot change to the current color.",
        "Wild Draw 4s may be played at any time.",
        "Wild cards count as every color simultaneously.",
        "Reverses stack with Reverses.",
        "Draw cards stack regardless of value.",
        "Draw effects are doubled.",
        "Draw effects affect every player.",
        "If you draw a playable card, you cannot play it immediately.",
        "Your first card each turn must be a number card if possible.",
        "Your first card each turn must be an action card if possible.",
        "The current color changes randomly every 3 turns.",
        "The current color becomes the color of the last card drawn.",
        "The current color cannot repeat twice in a row.",
        "Players with more than 10 cards draw 2 extra.",
        "Players with fewer than 3 cards draw 1 extra.",
        "The player with the fewest cards draws 2 cards.",
        "Every 0 swaps hands with a random player.",
        "Every 1 steals a random card.",
        "Every 2 forces the next player to draw 2.",
        "Every 5 changes the current color randomly.",
        "Every 9 reverses turn order twice.",
        "If your hand reaches 15 cards, discard 3.",
        "If your hand reaches 20 cards, discard 5.",
        "Reveal your hand for the rest of the round if you forgot to say UNO.",
        "Saying UNO makes you draw 2 cards. You don't need to say UNO.",
        "The player who triggered this rule remove this rule and 2 more rules.",
        "Failing to call UNO adds 4 cards instead of 2.",
        "The winner keeps drawing until everyone else finishes.",
        "The first player out chooses a new permanent rule.",
        "The first player out removes a permanent rule.",
        "Black cards add 2 rules when played.",
        "9s are counted as action cards.",
        "Black cards cannot be stacked with color cards. Color cards can be stacked with black cards.",
        "The first card played each round becomes forbidden.",
        "The last card played cannot be played again this round.",
        "The discard pile's top color is always considered Wild.",
        "Even numbers may stack with even numbers.",
        "Odd numbers may stack with odd numbers.",
        "Prime numbers act as Wild cards.",
        "Playing the same number twice in a row grants another turn.",
        "Playing the same color twice in a row grants another turn.",
        "Playing a card matching both color and number grants another turn.",
        "Remove 1 normal rule.",
        "Remove 1 normal rule.",
        "Remove 1 normal rule.",
        "Remove 1 normal rule.",
        "Remove 1 normal rule.",
        "Remove 1 normal rule.",
        "Remove 1 normal rule.",
        "Remove 1 normal rule.",
        "Remove 1 normal rule.",
        "Remove 1 normal rule.",
        "Remove 2 normal rule.",
        "Remove 2 normal rule.",
        "Remove 2 normal rule.",
        "Remove 2 normal rule.",
        "Remove 2 normal rule.",
        "Remove 2 normal rule.",
        "Remove 3 normal rule.",
        "Remove 3 normal rule.",
        "Remove 3 normal rule.",
        "Remove 3 normal rule.",
        "Remove 1 permanent rule.",
        "Remove 1 permanent rule.",
        "Remove 1 permanent rule.",
        "Remove 1 permanent rule.",
        "Remove 1 permanent rule.",
    };

    vector<string> specialEvents =
    {
        "Rule Violation: No rules can be removed until this event is over."
        "Danger Avoiding: Draw 5 cards to not be affected by a rule.",
        "Meteor Strike: Everyone draws 4 cards, and pick 2 cards to remove.",
        "UNO Lottery: Every player discards 4 cards, cannot reach less than 2 cards.",
        "Time Warp: Turn order reverses.",
        "Mirror World: Everyone swaps hands to the right person.",
        "Not Today, Thank You: Any player that won, that person draws 3 cards. Effects until this event ends.",
        "Card Taxing: Everytime you draw by a draw card, draw an extra 3 cards.",
        "Card Flood: Everyone draws 3 cards.",
        "Card Drought: Everyone discards 2 cards.",
        "Color Shift: Current color becomes random.",
        "Number Shift: Choose a number. All cards of that number become Wilds.",
        "Double Trouble: The next Draw card played activates twice.",
        "Hand Rotation: Pass your hand to the player on your right.",
        "Hand Rotation Reverse: Pass your hand to the player on your left.",
        "Equalizer: Everyone draws until they have 7 cards.",
        "Overload: Players with more than 10 cards draw 2 extra.",
        "Relief Fund: Players with fewer than 3 cards draw 2.",
        "Black Hole: Discard the top 5 cards of the draw pile.",
        "Recycling Program: Shuffle the discard pile into the draw pile.",
        "Color Tax: Every player discards one card matching the current color.",
        "Number Tax: Every player discards one card matching the top card's number.",
        "Color Flood: All cards matching the current color become Wilds this round.",
        "Wild Surge: All Wild cards count as Draw 2s.",
        "Wild Collapse: Wild cards cannot be played until the next event.",
        "Wild Festival: Wild cards may be stacked.",
        "Black Card Boom: Every black card counts as a 7 until replaced.",
        "Rainbow Mode: Any color can be played on any color this round.",
        "Reverse Mania: Reverse cards activate twice.",
        "Draw Frenzy: All draw effects gain +2 cards.",
        "Draw Shield: The next draw effect is ignored.",
        "Chain Reaction: Draw cards may stack regardless of type.",
        "Lucky Seven: Every 7 rolls an extra rule.",
        "Zero Hour: Every 0 swaps hands with the next player.",
        "Number Chaos: All even numbers become odd numbers.",
        "Mirror Numbers: 6s become 9s and 9s become 6s.",
        "Identity Theft: Choose a number; it copies another number's effect.",
        "Treasure Chest: Discard 2 cards, draw 4 cards.",
        "Market Crash: The most common color cannot be played this round.",
        "Market Boom: The least common color becomes Wild.",
        "Color Lock: The current color cannot change for one round.",
        "Color Storm: The current color changes after every card played.",
        "Action Rush: Action cards may be chained together.",
        "Number Rush: Number cards may be chained together.",
        "Combo Bonus: Playing two cards at once lets you discard one extra.",
        "Combo Breaker: Only one card may be played per turn.",
        "Quick Draw: If you draw a playable card, immediately play it.",
        "Heavy Hand: Everyone draws 5 cards. Cannot reduce to less than 2 cards.",
        "Light Hand: Everyone discards 3 cards. Cannot reduce to less than 2 cards.",
        "Balance Patch: Everyone with more than 8 cards gives 1 card to the player with the fewest cards.",
        "Card Donation: Every player passes 2 random cards to the left.",
        "Card Migration: Every player passes 2 random cards to the right.",
        "Rule Jackpot: Add a permanent rule.",
        "Rule Collapse: Remove a random permanent rule.",
        "Rule Mutation: Replace a random permanent rule.",
        "Pandora's Box: Add 3 permanent rules.",
        "Rule Refresh: Remove the oldest permanent rule and add a new one."
    };

    vector<string> permanentRules = chaosRules;

    typeText("=== UNO HELL RULE GENERATOR v1.0.2 ===");
    typeText("Press ENTER to roll.");
    typeText("Type anything and press ENTER to quit.");

    string input;

    while(true)
    {
        getline(cin, input);
        if(input == "delevent")
        {
            if(activeEvent.empty())
            {
                typeText("There is no active event.");
            }
            else
            {
                typeText("Removed Event: " + activeEvent);
                activeEvent = "";
            }
        
            showActiveEvent();
            showActiveRules();
            showPermanentRules();
            continue;
        }
        if(input == "addrule")
        {
            int idx = uniform_int_distribution<int>(
                0, (int)chaosRules.size() - 1)(rng);
        
            activeRules.push_back(chaosRules[idx]);
        
            typeText("[ADMIN RULE] " + chaosRules[idx]);
        
            showActiveEvent();
            showActiveRules();
            showPermanentRules();
            continue;
        }
        if(input == "addprule")
        {
        int idx = uniform_int_distribution<int>(
            0, (int)permanentRules.size() - 1)(rng);
    
        activePermanentRules.push_back(permanentRules[idx]);
    
        typeText("[ADMIN PERMANENT RULE] " + permanentRules[idx]);
    
        showActiveEvent();
        showActiveRules();
        showPermanentRules();
        continue;
        }
        if(input == "addevent")
        {
            int idx = uniform_int_distribution<int>(
                0, (int)specialEvents.size() - 1)(rng);
        
            activeEvent = specialEvents[idx];
        
            typeText("[ADMIN EVENT] " + activeEvent);
        
            showActiveEvent();
            showActiveRules();
            showPermanentRules();
            continue;
        }
                if(input.rfind("delrules ", 0) == 0)
        {
            try
            {
                int ruleNum = stoi(input.substr(9));
        
                if(ruleNum >= 1 && ruleNum <= (int)activeRules.size())
                {
                    typeText("Removed Rule: " + activeRules[ruleNum - 1]);
        
                    activeRules.erase(
                        activeRules.begin() + ruleNum - 1
                    );
                }
                else
                {
                    typeText("Invalid rule number.");
                }
            }
            catch(...)
            {
                typeText("Usage: delrules <number>");
            }
        
            showActiveEvent();
            showActiveRules();
            showPermanentRules();
            continue;
        }
        // Delete permanent rule: del 3
        if(input.rfind("del ", 0) == 0)
        {
            try
            {
                int ruleNum = stoi(input.substr(4));
        
                if(ruleNum >= 1 && ruleNum <= (int)activePermanentRules.size())
                {
                    typeText("Removed: " + activePermanentRules[ruleNum - 1]);
                    activePermanentRules.erase(activePermanentRules.begin() + ruleNum - 1);
                }
                else
                {
                    typeText("Invalid rule number.");
                }
            }
            catch(...)
            {
                typeText("Usage: del <rule number>");
            }
        
            showPermanentRules();
            continue;
        }
        
        // Quit command
        if(input == "quit")
            break;
        
        // Empty input = roll
        if(!input.empty())
        {
            typeText("Unknown command. Use ENTER, admin commands, or quit.");
            continue;
        }
        string result;
        int roll = uniform_int_distribution<int>(1,100)(rng);

        if(roll <= 25)
        {
            int idx = uniform_int_distribution<int>(0,(int)permanentRules.size()-1)(rng);
        int count = 1;
        
        int extraRoll = uniform_int_distribution<int>(1,100)(rng);
        
        if(extraRoll <= 20)
            count = 2;        // 20% chance
        
        if(extraRoll <= 10)
            count = 3;        // 10% chance
        
        result = "[PERMANENT RULES]\n";
        
        for(int i = 0; i < count; i++)
        {
            int idx = uniform_int_distribution<int>(0,
                (int)permanentRules.size()-1)(rng);
        
            activePermanentRules.push_back(permanentRules[idx]);
            result += "- " + permanentRules[idx] + "\n";
        }
        }
        else if(roll <= 35)
        {
            int idx = uniform_int_distribution<int>(0,(int)specialEvents.size()-1)(rng);
        
            activeEvent = specialEvents[idx];
        
            result = "[EVENT] " + activeEvent;
        }
        else
        {
            int idx = uniform_int_distribution<int>(0,(int)chaosRules.size()-1)(rng);
        
            activeRules.push_back(chaosRules[idx]);
        
            result = "[RULE] " + chaosRules[idx];
        }

        typeRed(result);
        showActiveEvent();
        showActiveRules();
        showPermanentRules();
    }

    return 0;
}
