#ifndef BASE64_H_
#define BASE64_H_


void encode(char* src, int len, char* dst);
int decode(char* src, char* dst);
int isBinary();



#endif  // BASE64_H_
