#include <Geode/Geode.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;
using namespace keybinds;

auto* GM = GameManager::sharedState();

// Flags to manage switching state for each setting
bool isSwitching[100] = {false};

// Toggle function template for settings
void toggleSetting(const std::string& gameVar, int index) {
    if (!isSwitching[index]) {
        isSwitching[index] = true;

        bool currentValue = GM->getGameVariable(gameVar.c_str());
        GM->setGameVariable(gameVar.c_str(), !currentValue);

        isSwitching[index] = false;
    }
}

$execute {
    std::vector<std::pair<std::string, std::string>> settings = {
//      {"ID"  , "Name"       , "Whether your dad exists or not"},
        {"0026", "Auto Retry"},
        {"0010", "Flip 2P Controls"},
        {"0011", "Always Limit Controls"},
        {"0024", "Show Cursor In-Game"},
        {"0028", "Disable Thumbstick"},
        {"0040", "Show Percent"},
        {"0052", "Fast Reset"},
        {"0074", "Restart Button"},
        {"0109", "Extra Info"},
        {"0113", "Flip Platformer Controls"},
        {"0126", "Decimal Percent"},
        {"0130", "Orb Labels"},
        {"0134", "Hide Attempts"},
        {"0163", "Quick Keys"},
        {"0167", "Confirm Exit"},
        {"0174", "Hide Playtest Text"},
        {"0015", "Flip Pause Button"},
        {"0153", "Explode Player on Death"},
        {"0060", "Default Mini Icon"},
        {"0061", "Switch Spider Teleport Color"},
        {"0062", "Switch Dash Fire Color"},
        {"0096", "Switch Wave Trail Color"},
        {"0019", "Load Songs into Memory"},
        {"0022", "Higher Audio Quality"},
        {"0033", "Change Song Path"},
        {"0018", "No Song Limit"},
        {"0125", "Normal Music in Editor"},
        {"0142", "Reduce Audio Quality"},
        {"0159", "Audio Fix 01"},
        {"0095", "Do Not..."},
        {"0072", "Disable Gravity Effect"},
        {"0073", "New Completed Filter"},
        {"0083", "Disable Song Alert"},
        {"0084", "Manual Level Order"},
        {"0099", "Show Leaderboard Percent"},
        {"0168", "Fast Menu"},
        {"0090", "Autoload Comments"},
        {"0094", "More Comments Mode"},
        {"0075", "Disable Comments"},
        {"0076", "Disable Account Comments"},
        {"0077", "Featured Levels Only"},
        {"0023", "Smooth Fix"},
        {"0065", "Move Optimization"},
        {"0101", "Force Smooth Fix"},
        {"0102", "Smooth Fix in the Editor"},
        {"0128", "Lock Cursor In-Game"},
        {"0108", "Auto LDM"},
        {"0136", "Extra LDM"},
        {"0042", "Increase Max Levels"},
        {"0056", "Disable Object Alert"},
        {"0127", "Save Gauntlet Levels"},
        {"0093", "Increase Local Levels Per Page"},
        {"0066", "High Capacity Mode"},
        {"0014", "Disable Explosion Shake"},
        {"0140", "Disable Orb Scale"},
        {"0081", "Disable Shake Effect"},
        {"0082", "Disable High Object Alert"},
        {"0155", "Disable Shader Anti-Aliasing"},
        {"0141", "Disable Trigger Orb Scale"},
        {"0027", "Auto Checkpoints"},
        {"0067", "High Start Position Accuracy"},
        {"0068", "Quick Checkpoint Mode"},
        {"0071", "Hide Practice Button"},
        {"0100", "Practice Death Effect"},
        {"0135", "Hide Attempts in Practice"}
    };

    // Register keybinds magically mystically wouuu!
    for (int i = 0; i < settings.size(); ++i) {
        const auto& setting = settings[i];

        // Register keybind
        BindManager::get()->registerBindable({
            fmt::format("mobmastermind.more_vanilla_keybinds/{}", setting.first),
            fmt::format("{}", setting.second),
            fmt::format("Toggles the {} setting when pressed.", setting.second),
            {}, // default key (your dad)
            "More Vanilla Keybinds", // Category
            false
        });

        // Event listener for each keybind
        new EventListener([=](InvokeBindEvent* event) {
            if (!event->isDown()) toggleSetting(setting.first, i); // Toggle the setting by game variable ID
            return ListenerResult::Propagate;
        }, InvokeBindFilter(nullptr, fmt::format("mobmastermind.more_vanilla_keybinds/{}", setting.first)));
    }
}

// Reset the switching flags in MenuLayer
struct ModifiedMenuLayer : Modify<ModifiedMenuLayer, MenuLayer> {
    bool init() {
        std::fill(std::begin(isSwitching), std::end(isSwitching), false); // Reset all flags
        return MenuLayer::init();
    }
};
