#include <monapi/terminal/CommandCreator.h>
#include <monapi/uitoa.h>

using namespace MonAPI;
using namespace MonAPI::terminal;

CommandCreator::CommandCreator()
{
}

CommandCreator::~CommandCreator()
{
}

Command CommandCreator::clearScreen()
{
    static const uint8_t COMMAND[] = {0x1b, '[', '2', 'J'};
    const uint32_t COMMAND_SIZE = sizeof(COMMAND);
    return Command(COMMAND, COMMAND_SIZE);
}

Command CommandCreator::backSpace()
{
    _logprintf("%s:%d\n", __FILE__, __LINE__);
    static const uint8_t COMMAND[] = {0x08};
    const uint32_t COMMAND_SIZE = sizeof(COMMAND);
    return Command(COMMAND, COMMAND_SIZE);
}

// ESC [ Ps Direction
Command CommandCreator::moveCursorTo(uint32_t n, char direction)
{
    MONA_ASSERT(n >= 0);
    MONA_ASSERT('A' <= direction && direction <= 'D');
    static uint8_t command[32];
    command[0] = 0x1b;
    command[1] = '[';
    uitoa((char*)(&command[2]), n);
    uint32_t length = strlen((char*)(&command[2]));
    command[length + 2] = direction;
    return Command(command, length + 3);
}

// ESC [ Ps ; Ps H
Command CommandCreator::moveCursor(uint32_t x, uint32_t y)
{
    MONA_ASSERT(x > 0 && y > 0);
    static uint8_t command[32];
    command[0] = 0x1b;
    command[1] = '[';
    uitoa((char*)(&command[2]), x);
    uint32_t length = strlen((char*)(&command[2])) + 2;
    command[length] = ';';
    length += 1;
    uitoa((char*)(&command[length]), y);
    length += strlen((char*)(&command[length]));
    command[length] = 'H';
    length += 1;
    return Command(command, length);
}

Command CommandCreator::moveCursorUp(uint32_t n)
{
    return moveCursorTo(n, Command::CURSOR_UP);
}

Command CommandCreator::moveCursorDown(uint32_t n)
{
    return moveCursorTo(n, Command::CURSOR_DOWN);
}

Command CommandCreator::moveCursorLeft(uint32_t n)
{
    return moveCursorTo(n, Command::CURSOR_LEFT);
}

Command CommandCreator::moveCursorRight(uint32_t n)
{
    return moveCursorTo(n, Command::CURSOR_RIGHT);
}
