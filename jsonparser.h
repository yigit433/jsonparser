#ifndef _JSONPARSER_H_ 
#define _JSONPARSER_H_ 

extern void jsonParse(char* payload, size_t payloadSize, JsonKv** output, size_t* outputSize);

#endif