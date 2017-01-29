#include "Keyboard.hpp"

#include <cmath>
#include "../Utils/Log.hpp"

void Keyboard::Update(Keyboard::Key k, State state)
{
    auto &a = states[static_cast<size_t>(k)];

    if (a != state)
        LOGVVV("Keyboard: " << k << " " << state);

    if (state == State::Up && a == State::Down &&
            onKeyReleaseEvents[static_cast<size_t>(k)]) {
        onKeyReleaseEvents[static_cast<size_t>(k)]();
        LOGVV("Keyboard: " << k << " Event");
    }

    states[static_cast<size_t>(k)] = state;
}

void Keyboard::SetEvent(Keyboard::Key k, Action a)
{
    onKeyReleaseEvents[static_cast<size_t>(k)] = a;
}

bool Keyboard::Down(Keyboard::Key k)
{
    return states[static_cast<size_t>(k)] == State::Down;
}

std::tuple<float, bool> Keyboard::Angle()
{
    int x = 0;
    int y = 0;

    if (Down(Key::Up))
        y++;
    if (Down(Key::Down))
        y--;
    if (Down(Key::Left))
        x--;
    if (Down(Key::Right))
        x++;

    if (x != 0 && y != 0)
        return {static_cast<float>(std::atan2(y, x)), true};

    return {0, false};
}

std::string toString(Keyboard::Key key)
{
    switch (key) {
    case Keyboard::Key::Down:
        return "Down";
    case Keyboard::Key::Up:
        return "Up";
    case Keyboard::Key::Left:
        return "Left";
    case Keyboard::Key::Right:
        return "Right";
    case Keyboard::Key::E:
        return "E";
    case Keyboard::Key::Esc:
        return "Esc";
    case Keyboard::Key::Enter:
        return "Enter";
    case Keyboard::Key::EnumCount:
    case Keyboard::Key::None:
    default:
        return "Unknown";
    }
}

std::string toString(Keyboard::State state)
{
    switch (state)
    {
    case Keyboard::State::Down:
        return "Pressed";
    case Keyboard::State::Up:
        return "Released";
    default:
        return "Unknown";
    }
}

std::ostream &operator<<(std::ostream &stream, Keyboard::Key obj)
{
    stream << toString(obj);
    return stream;
}

std::ostream &operator<<(std::ostream &stream, Keyboard::State obj)
{
    stream << toString(obj);
    return stream;
}
