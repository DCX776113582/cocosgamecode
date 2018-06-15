//
//  curlNet.hpp
//  DefendTheRadish
//
//  Created by mac on 18/4/19.
//
//

#ifndef curlNet_hpp
#define curlNet_hpp
#include <stdio.h>
struct MemoryStruct{
    char* memory;
    size_t size;
};
static size_t WritrMemoryCallback(void *contents,size_t size,size_t nmemb,void *userp)
{
    size_t realsize = size*nmemb;
    struct MemoryStruct * mem = (struct MemoryStruct*)userp;
    mem->memory = (char*)realloc(mem->memory,mem->size+realsize+1);
    if (mem->memory == NULL) {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}


#endif /* curlNet_hpp */
