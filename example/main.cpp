#include <string>
#include <memory>

#include "tm/tm.h"

TM generate_tm() {
    // Create Zustand instances
    std::shared_ptr<Zustand> z1 = std::make_shared<Zustand>(Zustand());
    std::shared_ptr<Zustand> z2 = std::make_shared<Zustand>(Zustand());
    std::shared_ptr<Zustand> z3 = std::make_shared<Zustand>(Zustand());
    std::shared_ptr<Zustand> z4 = std::make_shared<Zustand>(Zustand {.is_end = true});

    // create Uebergaenge instances
    // z1->z2 : a/b,R
    Uebergang z1_z2 {
            .action = PointerAction::R,
            .read = 'a',
            .write = 'b',
            .target = z2
    };
    // z2->z2 : b/c,R
    Uebergang z2_z2 {
            .action = PointerAction::R,
            .read = 'b',
            .write = 'c',
            .target = z2
    };
    // z2->z1 : @/@,L
    Uebergang z2_z1 {
            .action = PointerAction::L,
            .read = '@',
            .write = '@',
            .target = z1
    };
    // z1->z3 : c/a,S
    Uebergang z1_z3 {
            .action = PointerAction::S,
            .read = 'c',
            .write = 'a',
            .target = z3
    };
    // z3->z3 : a/a,L; b/b,L; c/c,L
    Uebergang z3_z3_a {
            .action = PointerAction::L,
            .read = 'a',
            .write = 'a',
            .target = z3
    };
    Uebergang z3_z3_b {
            .action = PointerAction::L,
            .read = 'b',
            .write = 'b',
            .target = z3
    };
    Uebergang z3_z3_c {
            .action = PointerAction::L,
            .read = 'c',
            .write = 'c',
            .target = z3
    };
    // z3->z4 : @/@,R
    Uebergang z3_z4 {
            .action = PointerAction::R,
            .read = '@',
            .write = '@',
            .target = z4
    };

    // add Uebergaenge instances to the Zustand instances
    z1->uebergaenge = { z1_z2, z1_z3 };
    z2->uebergaenge = { z2_z1, z2_z2 };
    z3->uebergaenge = { z3_z3_a, z3_z3_b, z3_z3_c, z3_z4 };

    return TM {
            .start = z1,
            .zustaende = { z1, z2, z3, z4 },
    };
}

int main() {
    std::string input = "abbb";

    auto tm = generate_tm();

    auto output = tm.run(input);

    std::cout << "input: " << input << " generated: " << output << std::endl;
}
