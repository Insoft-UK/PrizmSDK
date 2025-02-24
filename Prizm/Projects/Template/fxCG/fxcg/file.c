// The MIT License (MIT)
//
// Copyright (c) 2025 Insoft. All rights reserved.
// Originaly created 2023
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include <fxcg/file.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLS0 "//fls0/"
#define SMEM "~/Documents/Prizm/SMEM/"

static FILE *gFile[2] = {NULL, NULL};
static char _buf[1024];

typedef enum {
    kCreateMode_File = 1,
    kCreateMode_Folder = 5
} TCreateMode;


void replace_backslashes(char *str) {
    if (str == NULL) return; // Handle NULL input safely

    while (*str) {
        if (*str == '\\') {
            *str = '/';
        }
        str++;
    }
}

void replace_fls0(char *str, char *buffer, size_t buf_size) {
    char *pos = strstr(str, FLS0); // Find first occurrence
    if (!pos) {
        strncpy(buffer, str, buf_size - 1); // Copy original string if no match
        buffer[buf_size - 1] = '\0'; // Ensure null termination
        return;
    }

    // Calculate lengths
    size_t prefix_len = (size_t)(pos - str); // Text before "//fls0/"
    size_t old_len = strlen(FLS0);
    size_t new_len = strlen(SMEM);
    size_t suffix_len = strlen(pos + old_len); // Text after "//fls0/"

    // Ensure the new string fits in the buffer
    if (prefix_len + new_len + suffix_len >= buf_size) {
        printf("Buffer size too small!\n");
        return;
    }

    // Construct new string
    strncpy(buffer, str, prefix_len); // Copy prefix
    strcpy(buffer + prefix_len, SMEM); // Insert replacement
    strcpy(buffer + prefix_len + new_len, pos + old_len); // Copy suffix
}



static int Bfile_StrLength(const unsigned short* string)
{
    int i;
    for (i=0; ; i++) {
        if (string[i] == 0) return i;
    }
}

static int Bfile_GetFreeHandle(void)
{
    for (int i = 0; i < 1; i++)
    {
        if (gFile[i] == NULL) return i;
    }
    return -1;
}

// MARK: - macOS System Simulator Functions

int Bfile_CloseFile_OS( int handle )
{
    if (gFile[handle] == NULL) return -1;
    fclose(gFile[handle]);
    return handle;
}

int Bfile_CreateEntry_OS( const unsigned short*filename, int mode, size_t *size)
{
    char in[256];
    char out[256];
    Bfile_NameToStr_ncpy(in, filename, Bfile_StrLength(filename) + 1);
    
    replace_backslashes(in);
    replace_fls0(in, out, sizeof(out));
    
    if (mode == kCreateMode_File) {
        int hFile = Bfile_GetFreeHandle();
        if (hFile >= 0) {
            gFile[hFile] = fopen(out, "rb");
            if (gFile[hFile] == NULL) return -1;
            
            int length = (int)*size;
            while (length--) {
                fputc(0, gFile[hFile]);
            }
            fclose(gFile[hFile]);
            gFile[hFile] = NULL;
            return 0;
        }
    }
    
    if (mode == kCreateMode_Folder) {
       
    }
    
    return -1;
}
int Bfile_DeleteEntry( const unsigned short *filename )
{
    return -1;
}
int Bfile_RenameEntry( const unsigned short *oldpath, const unsigned short *newpath )
{
    return -1;
}
int Bfile_FindClose( int FindHandle )
{
    return -1;
}
int Bfile_FindFirst( const char *pathname, int *FindHandle, char *foundfile, void *fileinfo )
{
    return -1;
}
int Bfile_FindFirst_NON_SMEM( const char *pathname, int *FindHandle, char *foundfile, void *fileinfo )
{
    return -1;
}
int Bfile_FindNext( int FindHandle, char *foundfile, char *fileinfo )
{
    return -1;
}
int Bfile_FindNext_NON_SMEM( int FindHandle, char *foundfile, char *fileinfo )
{
    return -1;
}
int Bfile_GetFileSize_OS(int handle)
{
    if (gFile[handle] == NULL) return -1;
    int current_pos = (int)ftell(gFile[handle]);
    fseek(gFile[handle], 0, SEEK_END);
    int size = (int)ftell(gFile[handle]);
    fseek(gFile[handle], current_pos, SEEK_SET);
    return size;
}
int Bfile_OpenFile_OS(const unsigned short *filename, int mode, int null)
{
    char in[256];
    char out[256];
    
    int size = Bfile_StrLength(filename);
    Bfile_NameToStr_ncpy(in, filename, size);
    replace_backslashes(in);
    replace_fls0(in, out, sizeof(out));
    
    int h = Bfile_GetFreeHandle();
    if (h == -1) return -1;
    gFile[h] = fopen((const char *)out, "rb");
    
    return h;
}
int Bfile_ReadFile_OS( int handle, void *buf, int size, int readpos )
{
    if (gFile[handle] == NULL) return -1;
    if (readpos > -1)
        fseek(gFile[handle], readpos, SEEK_SET);
    
    return (int)fread(buf, size, 1, gFile[handle]);
}
int Bfile_SeekFile_OS( int handle, int pos )
{
    if (gFile[handle] == NULL) return -1;
    fseek(gFile[handle], pos, SEEK_SET);
    return (int)ftell(gFile[handle]);
}
int Bfile_TellFile_OS( int handle )
{
    if (gFile[handle] == NULL) return -1;
    return (int)ftell(gFile[handle]);
}
int Bfile_WriteFile_OS( int handle, const void *buf, int size )
{
    if (gFile[handle] == NULL) return -1;
    fwrite(buf, size, 1, gFile[handle]);
    return (int)ftell(gFile[handle]);
}
void Bfile_NameToStr_ncpy(char* dest, const unsigned short* source, size_t n)
{
    int i;
    for (i=0; i<n; i++) {
        dest[i] = source[i];
        if (dest[i] == 0)
            break;
    }
}
void Bfile_StrToName_ncpy(unsigned short *dest, const char *source, size_t n)
{
    int i;
    for (i=0; i<n; i++) {
        dest[i] = source[i];
        if (dest[i] == 0 || dest[i] == 0xFF)
            break;
    }
    dest[i] = 0;
}
int Bfile_Name_MatchMask( const short*mask, const short*filename  )
{
    return -1;
}
int Bfile_GetMediaFree_OS( unsigned short*media_id, int*freespace )
{
    return 16 << 20; // 16MB
}




