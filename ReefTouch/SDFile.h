
/* Copyright (c) 2009, Peter Barrett  
**  
** Permission to use, copy, modify, and/or distribute this software for  
** any purpose with or without fee is hereby granted, provided that the  
** above copyright notice and this permission notice appear in all copies.  
**  
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL  
** WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED  
** WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR  
** BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES  
** OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,  
** WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  
** ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS  
** SOFTWARE.  
*/

#ifndef __SDFILE_H__
#define __SDFILE_H__

#include "Fat32.h"

class SDFile
{
public:
    static bool DiskReady();
    static bool FileInfo(const char* path, unsigned long* length);
    
	SDFile();
    ~SDFile();
    void Init();
    
    byte    Open(const char* path);
    byte    Close();
    
    byte    ReadByte();         
    int     Read(void* dst, int len);
 
	void    WriteByte(u8 b);         
    int     Write(const void* src, int len);

    const byte* GetBuffer(int* count);
    void	Skip(int count);    // within current sector
    
    unsigned long	GetFileLength();
    long    GetPos();
    void    SetPos(long pos);
    
    protected:
    void    Load(long sector);
	void	Flush();

#ifdef USE_STDIO
    SDFILE* _f;
#endif
    long	_sector;		// Current logical sector
    byte    _buffer[512];
    int     _mark;			// within _buffer
    u8		_dirty;

	ExtentInfo	_extent;	// Cluster/Extent info
};

#endif // __SDFILE_H__
