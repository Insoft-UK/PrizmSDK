//
//  base.h
//  Template
//
//  Created by Richie on 14/03/2025.
//

#ifndef base_h
#define base_h

#ifndef __clang__
#define AddIn_main main

#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/system.h>
#include <fxcg/misc.h>

#else

#include <display.h>
#include <keyboard.h>
#include <system.h>
#include <misc.h>

#endif

#define true 1
#define false 0

#define loop while(true)

#endif /* base_h */
