/* 
 * The MIT License
 *
 * Copyright 2020 The OpenNARS authors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>

/*-------*/
/* Flags */
/*-------*/
//Whether debug mode should be on
#define DEBUG false
//Whether input should be printed
#define PRINT_INPUT_INITIAL true
//Whether derivations should be printed
#define PRINT_DERIVATIONS_INITIAL false
//Whether control information should be printed
#define PRINT_CONTROL_INFO false
//Priority threshold for printing derivations
#define PRINT_DERIVATIONS_PRIORITY_THRESHOLD 0.0

//Debug macros, debug printing, assert:
#define DEBUG_INFO(x) {if(DEBUG == 1){}}
#ifdef DEBUG
#define PRINTD printf
#else
#define PRINTD(format, args...) ((void)0)
#endif
#define IN_DEBUG(x) {if(DEBUG){ x } }
void assert(bool b, char* message);
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#endif
