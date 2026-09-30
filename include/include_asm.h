#ifndef SO3_INCLUDE_ASM_H
#define SO3_INCLUDE_ASM_H

/* tools/compile.py replaces these placeholders before the final compilation. */
#ifndef SO3_ASM_PROCESSOR
#error Compile game sources through tools/compile.py
#endif
#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)

#endif
