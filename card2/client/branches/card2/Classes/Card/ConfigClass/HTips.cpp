//
//  HTips.cpp
//  card
//
//  Created by zhou gang on 13-8-6.
//
//

#include "../../headers.h"
#include "HTips.h"

vector<string> HTips::strings;

int HTips::load()
{
    LOAD_STRING("config/tips.txt");
        
    return strings.size();
}

const char* HTips::roll()
{
    return strings[rand() % strings.size()].c_str();
}
