# QUnit
The stupidly simple, but beautiful, unit testing framework.

Literally three macros (with some optional assertion macros). That's it.

## Usage

```c
#include "qunit.h"

const char *some_test(void) {
  if (true)
    return 0; /* success */
  else
    return "there was some sort of error"; /* error */
}

q_start();
q_test(some_test);
/* ... */
q_end();
```

# License
Released to the Public Domain by JD Ballard.
Written for the [AERO File Format](https://github.com/AERO-ff)
for the Kleos [Foundation](https://github.com/KleosMD).
