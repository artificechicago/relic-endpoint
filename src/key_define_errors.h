#ifndef __RELIC_KEY_DEFINITION_ERRORS_H__
#define __RELIC_KEY_DEFINITION_ERRORS_H__

#ifndef MSGKEYVAL1
#error You must define 4 32-bit values for the encryption key (1/4)!
#endif

#ifndef MSGKEYVAL2
#error You must define 4 32-bit values for the encryption key (2/4)!
#endif

#ifndef MSGKEYVAL3
#error You must define 4 32-bit values for the encryption key (3/4)!
#endif

#ifndef MSGKEYVAL4
#error You must define 4 32-bit values for the encryption key (4/4)!
#endif

#ifndef MACKEYVAL1
#error You must define 4 32-bit values for the MAC key (1/4)!
#endif

#ifndef MACKEYVAL2
#error You must define 4 32-bit values for the MAC key (2/4)!
#endif

#ifndef MACKEYVAL3
#error You must define 4 32-bit values for the MAC key (3/4)!
#endif

#ifndef MACKEYVAL4
#error You must define 4 32-bit values for the MAC key (4/4)!
#endif

#endif