#ifndef TURING_MACHINE_SIM_H
#define TURING_MACHINE_SIM_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

using tape_t = std::string;

enum PointerAction {
    S, // stop/stand
    R, // right
    L  // left
};

// forward declare
struct Uebergang;
struct Zustand;

struct Uebergang {
    /// the action for the pointer of the TM
    PointerAction action;
    /// character to be read
    char read;
    /// character to write
    char write;
    /// target Zustand of the Übergang
    std::shared_ptr<const Zustand> target;\
};

struct Zustand {
    /// list of Übergänge
    std::vector<Uebergang> uebergaenge;
    /// if we can terminate on this Zustand
    bool is_end = false;
};

struct TM {
    /// reference to the starting Zustand
    std::shared_ptr<const Zustand> start;
    /// list of Zustände
    std::vector<std::shared_ptr<Zustand>> zustaende;

    tape_t run(tape_t tape) {
        auto zustand_p = this->start;
        int32_t tape_p = 0;

        while (true) {
            // increase tape length
            {
                // tape length
                auto n = tape.size();
                // if tape to small
                if (tape_p < 0) {
                    // increase tape to the left
                    tape.insert(0, 1, '@');
                    tape_p += 1;
                } else if (tape_p >= n) {
                    // increase tape to the right
                    tape.append(1, '@');
                }
                // else: tape is long enough, so do nothing
            }

            // find Übergang, which we can take
            bool found_uebergang_flag = false;
            for (const auto& e: zustand_p->uebergaenge) {
                // skip to next uebergang, when this is not the correct edge
                if (e.read != tape[tape_p]) {
                    continue;
                }

                found_uebergang_flag = true;

                tape[tape_p] = e.write;

                // move tape pointer to the left, right or stand
                switch (e.action) {
                    case PointerAction::R:
                        tape_p += 1;
                        break;
                    case PointerAction::L:
                        tape_p -= 1;
                        break;
                    case PointerAction::S:
                        tape_p = tape_p;
                        break;
                }

                zustand_p = e.target;
            }

            if (zustand_p->is_end) {
                return tape;
            }

            if (not found_uebergang_flag) {
                throw std::runtime_error("No Übergang found");
            }
        }
    }
};

#endif //TURING_MACHINE_SIM_H
