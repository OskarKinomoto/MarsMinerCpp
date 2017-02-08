#pragma once

#include "../Utils/Action.hpp"
#include <array>
#include <tuple>
#include <string>
#include <ostream>

class Keyboard {
public:
    Keyboard();

    enum class Key{
        Up,
        Down,
        Left,
        Right,
        Enter,
        Esc,
        E,

        //end
        EnumCount,
        None,
    };

    enum class State {
        Up,
        Down,
    };

    void Update(Key k, State state);
    void SetEvent(Key, Action);
    bool Down(Key k);
    std::tuple<float, bool> Angle();

private:
    std::array<State, static_cast<size_t>(Key::EnumCount)> states;
    std::array<Action, static_cast<size_t>(Key::EnumCount)> onKeyReleaseEvents;
};

std::string toString(Keyboard::Key key);
std::string toString(Keyboard::State state);

std::ostream &operator<<(std::ostream& stream, Keyboard::Key obj);
std::ostream &operator<<(std::ostream& stream, Keyboard::State obj);
