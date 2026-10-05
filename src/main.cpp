// F1 Team Simulator - model classes demo.
// Shows the OOP design: inheritance (Staff, CarPart), polymorphism, composition (Car, PowerUnit),
// operator overloading (Money, LapTime), exceptions, and the lap-time effect of car/driver/tyres.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>

#include "core/Exceptions.h"
#include "core/LapTime.h"
#include "core/Money.h"
#include "model/Circuit.h"
#include "model/Team.h"
#include "model/TyreSet.h"

using namespace f1;

namespace {

std::shared_ptr<Driver> makeDriver(const std::string& name, const std::string& nat, int age, double salaryM, int pace,
                                   int number, const std::string& code, int aggression = 50) {
    DriverStats s;
    s.pace = pace;
    s.consistency = pace - 5;
    s.racecraft = pace - 3;
    s.aggression = aggression;
    s.tyreManagement = pace - 8;
    s.wetSkill = pace - 6;
    s.experience = pace - 10;
    s.startSkill = pace - 4;
    return std::make_shared<Driver>(name, nat, age, Money::fromMillions(salaryM), 2, Rating(pace + 5), s, number, code);
}

void section(const std::string& title) { std::cout << "\n--- " << title << " ---\n"; }

}  // namespace

int main() {
    try {
        // ---------- Circuits ----------
        Circuit monza(CircuitSpec{"monza", "Monza", "Italy", 5.793, 53, 81.0, 0.80, 0.45, 24.0, 0.60, 0.15, 0.25, -5, 0.12, 0.8});
        Circuit monaco(CircuitSpec{"monaco", "Monaco", "Monaco", 3.337, 78, 72.0, 0.70, 0.95, 19.0, 0.15, 0.35, 0.50, 5, 0.20, 0.8});

        section("Circuits");
        std::cout << monza << '\n' << monaco << '\n';
        std::cout << "Monza at 50% distance: " << monza.totalLaps(0.5) << " laps\n";

        // ---------- A team ----------
        Team team("Demo Racing", "DEM", "#E10600", Money::fromMillions(35.0), Car::createUniform(55));
        team.hire(makeDriver("Alex Rivera", "Spanish", 24, 3.0, 66, 7, "RIV", 70));
        team.hire(makeDriver("Sam Okafor", "British", 31, 2.0, 58, 21, "OKA", 40));
        team.hire(std::make_shared<Mechanic>("Joe Marsh", "British", 35, Money::fromMillions(0.4), 2, Rating(60), Rating(62), Rating(70)));
        team.hire(std::make_shared<Mechanic>("Lena Fischer", "German", 29, Money::fromMillions(0.4), 2, Rating(65), Rating(58), Rating(66)));
        team.hire(std::make_shared<PitCrew>("Crew Alpha", "Italian", 33, Money::fromMillions(1.5), 3, Rating(60), Rating(72), Rating(65), Rating(70)));
        team.hire(std::make_shared<RaceEngineer>("Priya Nair", "Indian", 30, Money::fromMillions(0.9), 2, Rating(70), Rating(68), Rating(60), Rating(64)));
        team.hire(std::make_shared<ChiefDesigner>("Hans Weber", "German", 45, Money::fromMillions(1.2), 3, Rating(60), Rating(64), Rating(58), Rating(60)));

        section("Team summary (polymorphic print of every Staff subclass)");
        team.printSummary(std::cout);

        // ---------- Polymorphism: market values ----------
        section("Market value per season (each subclass has its own formula)");
        for (const auto& s : team.allStaff())
            std::cout << std::left << std::setw(15) << s->role() << std::setw(16) << s->name() << s->marketValue() << '\n';

        // ---------- Car ----------
        section("Car parts (polymorphic print of every CarPart subclass)");
        std::cout << team.car();

        section("Car performance depends on the circuit and the wing setting");
        for (int wing : {-5, 0, 5}) {
            team.car().setWingSetting(wing);
            std::cout << "wing " << std::showpos << wing << std::noshowpos << ":  Monza score " << std::fixed
                      << std::setprecision(1) << team.car().carScore(monza) << " (lap-time cost +" << std::setprecision(2)
                      << team.carDeltaSeconds(monza) << " s)   |   Monaco score " << std::setprecision(1)
                      << team.car().carScore(monaco) << " (lap-time cost +" << std::setprecision(2)
                      << team.carDeltaSeconds(monaco) << " s)\n";
        }

        // ---------- Driver effects ----------
        section("Driver effect on lap time (dry), 1.4 s range between pace 0 and pace 100");
        for (const auto& d : team.drivers()) {
            const double delta = (100.0 - d->effectivePace(false)) / 100.0 * 1.4;
            std::cout << d->code() << ": effective pace " << std::fixed << std::setprecision(1) << d->effectivePace(false)
                      << ", delta +" << std::setprecision(2) << delta << " s, lap noise sigma " << d->lapNoiseSigma()
                      << " s, tyre wear factor " << d->wearFactor() << '\n';
        }

        // ---------- Lap time with value types ----------
        section("LapTime / Money operator overloading");
        const LapTime base = monza.baseLapTime();
        const LapTime lap = base + LapTime::fromSeconds(team.carDeltaSeconds(monza) + 0.9);
        std::cout << "Base lap " << base << ", our lap " << lap << ", difference " << (lap - base) << '\n';
        Money m = Money::fromMillions(12.5);
        m += Money::fromThousands(750);
        std::cout << "Money: " << Money::fromMillions(12.5) << " + $750K = " << m << ", half = " << m * 0.5 << '\n';

        // ---------- Tyres ----------
        section("Tyre stint on Monza (medium, 50% race distance => wear x2)");
        TyreSet tyre(TyreCompound::MEDIUM);
        const double wearPerLap = TyreSet::info(TyreCompound::MEDIUM).baseWearPerLap * monza.tyreSeverity() * 2.0 *
                                  team.drivers()[0]->wearFactor() * team.car().suspension().tyreWearFactor();
        for (int lapNo = 1; lapNo <= 16; ++lapNo) {
            tyre.addLap(wearPerLap);
            if (lapNo % 3 == 0 || tyre.pastCliff())
                std::cout << "lap " << std::setw(2) << lapNo << ": " << tyre.describe() << ", loses "
                          << std::fixed << std::setprecision(2) << tyre.performanceLossSeconds() << " s/lap"
                          << (tyre.pastCliff() ? "  <-- PAST THE CLIFF" : "") << '\n';
        }

        // ---------- Pit crew ----------
        section("Pit crew");
        std::cout << "Expected stationary time: " << std::fixed << std::setprecision(2)
                  << team.pitCrew()->expectedStationaryTime() << " s, pit-lane loss at Monza: " << monza.pitLaneLoss()
                  << " s => total stop cost ~" << team.pitCrew()->expectedStationaryTime() + monza.pitLaneLoss() << " s\n";

        // ---------- Parts wear + repair cost ----------
        section("Part wear over a 26-lap race");
        team.car().wearAllParts(26, 1.0, team.partWearMultiplier());
        Money repairBill;
        for (const CarPart* p : team.car().allParts()) repairBill += p->repairCost();
        std::cout << "Mechanic wear multiplier " << team.partWearMultiplier() << ", repair bill " << repairBill << '\n';

        // ---------- Finances ----------
        section("Finances");
        std::cout << "Budget before: " << team.budget() << '\n';
        std::cout << "Race costs paid: " << team.payRaceCosts(10) << " -> budget " << team.budget() << '\n';

        // ---------- Exceptions ----------
        section("Exceptions");
        try {
            team.hire(makeDriver("Extra Driver", "French", 22, 1.0, 50, 33, "EXT"));
        } catch (const ContractException& e) {
            std::cout << "ContractException: " << e.what() << '\n';
        }
        try {
            team.spend(Money::fromMillions(500));
        } catch (const InsufficientFundsException& e) {
            std::cout << "InsufficientFundsException: " << e.what() << '\n';
        }
        try {
            team.car().setWingSetting(9);
        } catch (const GameException& e) {
            std::cout << "GameException: " << e.what() << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
