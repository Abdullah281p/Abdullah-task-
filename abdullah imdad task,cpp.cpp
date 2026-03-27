
//BY ABDULLAH IMDAD === Repeated student of bs Ai (4th semester )==== //

// Assignment - fantasy battle aera //

/*
    ============================================================
    Fantasy Battle Arena
    Object Oriented Programming - C++ Assignment
    ============================================================

    This program simulates a mini fantasy battle game.
    We have three types of heroes: Warrior, Mage, and Archer.
    Each hero has their own way of attacking and defending.

    I used inheritance to avoid repeating common hero data,
    and virtual functions so each hero can fight in their own style.
    ============================================================
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


// ============================================================
//  BASE CLASS: Hero
//  This is the general template for every hero in the game.
//  All three hero types (Warrior, Mage, Archer) will inherit
//  their basic info from here.
// ============================================================
class Hero {

private:
    // Every hero in the game shares these five pieces of info
    string heroName;          // The hero's name
    string heroType;          // What kind of hero they are
    int    healthPoints;      // How much health they have
    int    powerLevel;        // Their general strength
    double experiencePoints;  // How much experience they've earned so far

public:

    // Constructor: sets up a hero with all their basic info
    Hero(string name, string type, int hp, int power, double xp) {
        heroName         = name;
        heroType         = type;
        healthPoints     = hp;
        powerLevel       = power;
        experiencePoints = xp;
    }

    // Virtual destructor - good habit when using inheritance
    virtual ~Hero() {}

    // Simple getters so the child classes can read the base values
    string getName()  const { return heroName; }
    string getType()  const { return heroType; }
    int    getHP()    const { return healthPoints; }
    int    getPower() const { return powerLevel; }
    double getXP()    const { return experiencePoints; }


    // ----------------------------------------------------------
    //  Q3 - Two virtual battle functions
    //  These are left empty here on purpose. Every hero type
    //  MUST write their own version because each fights differently.
    // ----------------------------------------------------------

    // How does this hero attack? (each hero answers this differently)
    virtual double attack() const = 0;

    // How does this hero protect themselves? (again, each hero is unique)
    virtual double defend() const = 0;


    // ----------------------------------------------------------
    //  Q4 - One shared function (same output for every hero)
    //  This prints a welcome message and the basic game rules.
    //  It never changes, no matter which hero calls it.
    // ----------------------------------------------------------
    void showGameMessage() const {
        cout << "\n";
        cout << "  +----------------------------------------------+\n";
        cout << "  |       Welcome to the Fantasy Battle Arena!   |\n";
        cout << "  |                                              |\n";
        cout << "  |  Game Rules:                                 |\n";
        cout << "  |   1. Every hero gets one attack turn.        |\n";
        cout << "  |   2. Every hero gets one defense turn.       |\n";
        cout << "  |   3. Higher attack value wins the round.     |\n";
        cout << "  |   4. Defense reduces the damage taken.       |\n";
        cout << "  |   5. May the best hero win!                  |\n";
        cout << "  +----------------------------------------------+\n";
        cout << "\n";
    }


    // ----------------------------------------------------------
    //  Base profile display - child classes will call this first
    //  and then add their own special attributes below it.
    // ----------------------------------------------------------
    virtual void displayProfile() const {
        cout << "  +------------------------------------------+\n";
        cout << "  |            HERO PROFILE                  |\n";
        cout << "  +------------------------------------------+\n";
        cout << "  |  Name        : " << left << setw(26) << heroName        << "|\n";
        cout << "  |  Type        : " << left << setw(26) << heroType        << "|\n";
        cout << "  |  Health      : " << left << setw(26) << healthPoints    << "|\n";
        cout << "  |  Power Level : " << left << setw(26) << powerLevel      << "|\n";
        cout << "  |  Experience  : " << left << setw(26) << fixed
             << setprecision(1) << experiencePoints                           << "|\n";
    }
};


// ============================================================
//  WARRIOR CLASS
//  A tough close-range fighter who relies on brute strength,
//  heavy armor, and pure rage to win battles.
// ============================================================
class Warrior : public Hero {

private:
    string weaponName;    // The weapon this warrior carries
    int    armorStrength; // How strong their armor is (higher = more protection)
    int    rageLevel;     // Rage makes attacks hit much harder

public:

    // Sets up the warrior with both common and warrior-specific info
    Warrior(string name, int hp, int power, double xp,
            string weapon, int armor, int rage)
        : Hero(name, "Warrior", hp, power, xp) {
        weaponName    = weapon;
        armorStrength = armor;
        rageLevel     = rage;
    }


    // ----------------------------------------------------------
    //  Q5 - Warrior's attack
    //  A warrior fights up close, so raw power and rage matter most.
    //  Formula: (power x 1.5) + (rage x 2.0)
    //  The higher the rage, the more dangerous this warrior becomes.
    // ----------------------------------------------------------
    double attack() const override {
        return (getPower() * 1.5) + (rageLevel * 2.0);
    }


    // ----------------------------------------------------------
    //  Q5 - Warrior's defense
    //  Warriors tank damage using their armor and large health pool.
    //  Formula: armorStrength + (health x 0.1)
    // ----------------------------------------------------------
    double defend() const override {
        return armorStrength + (getHP() * 0.1);
    }


    // Shows full warrior profile including their special attributes
    void displayProfile() const override {
        Hero::displayProfile();  // print the common part first
        cout << "  +------------------------------------------+\n";
        cout << "  |  -- Warrior Special Attributes --        |\n";
        cout << "  |  Weapon       : " << left << setw(25) << weaponName    << "|\n";
        cout << "  |  Armor Str    : " << left << setw(25) << armorStrength << "|\n";
        cout << "  |  Rage Level   : " << left << setw(25) << rageLevel     << "|\n";
        cout << "  +------------------------------------------+\n";
        cout << "  |  Attack Value : " << left << setw(25) << fixed
             << setprecision(2) << attack()                                   << "|\n";
        cout << "  |  Defense Value: " << left << setw(25) << fixed
             << setprecision(2) << defend()                                   << "|\n";
        cout << "  +------------------------------------------+\n";
    }
};


// ============================================================
//  MAGE CLASS
//  A spell-caster who stays far from danger and destroys
//  enemies using powerful magic and large mana reserves.
// ============================================================
class Mage : public Hero {

private:
    string spellName;       // The name of their signature spell
    int    manaPoints;      // Mana is the fuel for casting spells
    double magicMultiplier; // Boosts how powerful each spell is

public:

    Mage(string name, int hp, int power, double xp,
         string spell, int mana, double magicMult)
        : Hero(name, "Mage", hp, power, xp) {
        spellName       = spell;
        manaPoints      = mana;
        magicMultiplier = magicMult;
    }


    // ----------------------------------------------------------
    //  Q6 - Mage's attack
    //  Mages pour mana into spells to deal massive damage.
    //  Formula: (mana x magicMultiplier) + powerLevel
    //  A mage with high mana and a big multiplier is very scary.
    // ----------------------------------------------------------
    double attack() const override {
        return (manaPoints * magicMultiplier) + getPower();
    }


    // ----------------------------------------------------------
    //  Q6 - Mage's defense
    //  Mages are physically weak but use magic shields for protection.
    //  Formula: (power x 0.5) + (mana x 0.3)
    // ----------------------------------------------------------
    double defend() const override {
        return (getPower() * 0.5) + (manaPoints * 0.3);
    }


    void displayProfile() const override {
        Hero::displayProfile();
        cout << "  +------------------------------------------+\n";
        cout << "  |  -- Mage Special Attributes --           |\n";
        cout << "  |  Spell Name   : " << left << setw(25) << spellName     << "|\n";
        cout << "  |  Mana Points  : " << left << setw(25) << manaPoints    << "|\n";
        cout << "  |  Magic Mult   : " << left << setw(25) << fixed
             << setprecision(2) << magicMultiplier                            << "|\n";
        cout << "  +------------------------------------------+\n";
        cout << "  |  Attack Value : " << left << setw(25) << fixed
             << setprecision(2) << attack()                                   << "|\n";
        cout << "  |  Defense Value: " << left << setw(25) << fixed
             << setprecision(2) << defend()                                   << "|\n";
        cout << "  +------------------------------------------+\n";
    }
};


// ============================================================
//  ARCHER CLASS
//  A swift long-range fighter who wins through speed,
//  precision shots, and smart positioning on the battlefield.
// ============================================================
class Archer : public Hero {

private:
    string bowType;      // The type of bow they use
    int    numArrows;    // How many arrows they have left
    double accuracyRate; // How accurate their shots are (0.0 to 1.0)

public:

    Archer(string name, int hp, int power, double xp,
           string bow, int arrows, double accuracy)
        : Hero(name, "Archer", hp, power, xp) {
        bowType      = bow;
        numArrows    = arrows;
        accuracyRate = accuracy;
    }


    // ----------------------------------------------------------
    //  Q7 - Archer's attack
    //  Archers deal damage through rapid, accurate shots.
    //  Formula: power x accuracy x (arrows x 0.5)
    //  Great aim with lots of arrows makes for a deadly archer.
    // ----------------------------------------------------------
    double attack() const override {
        return getPower() * accuracyRate * (numArrows * 0.5);
    }


    // ----------------------------------------------------------
    //  Q7 - Archer's defense
    //  Archers stay light on their feet and dodge incoming hits.
    //  Formula: (health x 0.2) + (accuracy x 50)
    //  The better their aim, the better they are at evading too.
    // ----------------------------------------------------------
    double defend() const override {
        return (getHP() * 0.2) + (accuracyRate * 50);
    }


    void displayProfile() const override {
        Hero::displayProfile();
        cout << "  +------------------------------------------+\n";
        cout << "  |  -- Archer Special Attributes --         |\n";
        cout << "  |  Bow Type     : " << left << setw(25) << bowType       << "|\n";
        cout << "  |  Arrows       : " << left << setw(25) << numArrows     << "|\n";
        cout << "  |  Accuracy     : " << left << setw(25) << fixed
             << setprecision(2) << accuracyRate                               << "|\n";
        cout << "  +------------------------------------------+\n";
        cout << "  |  Attack Value : " << left << setw(25) << fixed
             << setprecision(2) << attack()                                   << "|\n";
        cout << "  |  Defense Value: " << left << setw(25) << fixed
             << setprecision(2) << defend()                                   << "|\n";
        cout << "  +------------------------------------------+\n";
    }
};


// ============================================================
//  MAIN FUNCTION
//  This is where the game actually runs.
//  We create our three heroes, show their profiles,
//  simulate their battle actions, and print a final summary.
// ============================================================
int main() {

    // ----------------------------------------------------------
    //  Q8 - Create one object for each hero type
    //  I picked realistic values so each hero feels true to their role:
    //  Warrior is tough and angry, Mage is smart with lots of mana,
    //  Archer is accurate and quick.
    // ----------------------------------------------------------
    Warrior warrior("Ragnar Ironclad", 200, 85, 1500.0, "Greatsword",    60, 40);
    Mage    mage   ("Seraphina Dusk",  120, 70, 2200.0, "Inferno Blast", 150, 2.5);
    Archer  archer ("Lyra Swiftwind",  150, 65, 1800.0, "Elven Longbow",  30, 0.92);

    // Store all three heroes in an array of base-class pointers
    // This lets us loop through them and call functions polymorphically
    Hero* heroes[3] = { &warrior, &mage, &archer };

    // Show the shared welcome message once (same for all heroes - Q9)
    heroes[0]->showGameMessage();

    // ----------------------------------------------------------
    //  Q9 - Display each hero's full profile, then call
    //  their attack and defend functions one by one
    // ----------------------------------------------------------
    cout << "\n";
    cout << "  ==========================================\n";
    cout << "       HERO PROFILES AND BATTLE STATS\n";
    cout << "  ==========================================\n";

    for (int i = 0; i < 3; i++) {
        cout << "\n";
        heroes[i]->displayProfile();

        // Show the result of this hero's attack action
        cout << "\n  -> " << heroes[i]->getName()
             << " swings into battle and deals "
             << fixed << setprecision(2) << heroes[i]->attack()
             << " damage!\n";

        // Show the result of this hero's defense action
        cout << "  -> " << heroes[i]->getName()
             << " braces for impact with a shield value of "
             << fixed << setprecision(2) << heroes[i]->defend()
             << "!\n";

        // Print the shared game message after each hero (Q9)
        heroes[i]->showGameMessage();
    }


    // ----------------------------------------------------------
    //  Q10 - Final summary table comparing all three heroes
    //  Also announces who had the highest attack this round
    // ----------------------------------------------------------
    cout << "\n";
    cout << "  +------------------------------------------------+\n";
    cout << "  |              BATTLE SUMMARY                    |\n";
    cout << "  +------------------------------------------------+\n";
    cout << "  |  Hero              Attack        Defense       |\n";
    cout << "  |  ────────────────────────────────────────────  |\n";

    double highestAttack = -1.0;
    string topHero       = "";

    for (int i = 0; i < 3; i++) {
        double atk = heroes[i]->attack();
        double def = heroes[i]->defend();

        cout << "  |  " << left  << setw(18) << heroes[i]->getName()
             << setw(14) << fixed << setprecision(2) << atk
             << setw(14) << def  << "|\n";

        // Keep track of who hit the hardest
        if (atk > highestAttack) {
            highestAttack = atk;
            topHero       = heroes[i]->getName();
        }
    }

    cout << "  +------------------------------------------------+\n";
    cout << "  |  Champion (Highest Attack): "
         << left << setw(21) << topHero << "|\n";
    cout << "  |  Winning Attack Value     : "
         << left << setw(21) << fixed << setprecision(2) << highestAttack << "|\n";
    cout << "  +------------------------------------------------+\n\n";

    return 0;
}
