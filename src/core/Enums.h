#pragma once

#include <string>

namespace f1 {

enum class TyreCompound { SOFT, MEDIUM, HARD, INTERMEDIATE, WET };

enum class PartType {
    FRONT_WING, REAR_WING, FLOOR,
    SUSPENSION, CHASSIS, BRAKES, GEARBOX,
    ICE, TURBO, ERS, CONTROL_ELECTRONICS
};

inline std::string toString(TyreCompound c) {
    switch (c) {
        case TyreCompound::SOFT:         return "Soft";
        case TyreCompound::MEDIUM:       return "Medium";
        case TyreCompound::HARD:         return "Hard";
        case TyreCompound::INTERMEDIATE: return "Intermediate";
        case TyreCompound::WET:          return "Wet";
    }
    return "?";
}

inline std::string toString(PartType t) {
    switch (t) {
        case PartType::FRONT_WING:          return "Front Wing";
        case PartType::REAR_WING:           return "Rear Wing";
        case PartType::FLOOR:               return "Floor";
        case PartType::SUSPENSION:          return "Suspension";
        case PartType::CHASSIS:             return "Chassis";
        case PartType::BRAKES:              return "Brakes";
        case PartType::GEARBOX:             return "Gearbox";
        case PartType::ICE:                 return "Engine (ICE)";
        case PartType::TURBO:               return "Turbo";
        case PartType::ERS:                 return "ERS";
        case PartType::CONTROL_ELECTRONICS: return "Control Electronics";
    }
    return "?";
}

}  // namespace f1
