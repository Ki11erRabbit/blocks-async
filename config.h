#ifndef CONFIG_H
#define CONFIG_H

// String used to delimit block outputs in the status.
#define DELIMITER "  "

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 45

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 1

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 0

// Define blocks for the status feed as X(icon, cmd, interval, signal).
#define BLOCKS(X)             \
    X("", "block_weather.sh", 3600, 5) \
    X("", "block_memory.sh", 30, 4) \
    X("", "block_volume.sh", 0, 3) \
    X("", "block_power.sh", 300, 2) \
    X("", "block_clock.sh", 1, 1)

#endif  // CONFIG_H
