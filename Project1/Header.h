
// #pragma once is the same as including header guards around the file
#pragma once

// Header guards!
#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE
// Unique name function here
#endif

// Example. If Header.h has not been defined before, then we will define it now.
// The next time Header.h is come accross, we will check if it is NOT defined and we won't define it a second time.

// NOTE: It is generally a GOOD IDEA to name your header guards something unique to you and your program alone. That way, if someone else has a header guard called HEADER_H, the two won't be mixed up with eachother and cause compile error.
#ifndef HEADER_H_1_16_2020
#define HEADER_H_1_16_2020

int add(int, int);

#endif
