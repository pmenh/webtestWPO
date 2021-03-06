/******************************************************************************
Copyright (c) 2013, Google Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, 
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of the <ORGANIZATION> nor the names of its contributors 
    may be used to endorse or promote products derived from this software 
    without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include "StdAfx.h"
#include "util.h"

/*-----------------------------------------------------------------------------
-----------------------------------------------------------------------------*/
CStringA JSONEscapeA(CStringA src) {
  src.Replace("\\", "\\\\");
  src.Replace("\"", "\\\"");
  src.Replace("/", "\\/");
  src.Replace("\b", "\\b");
  src.Replace("\r", "\\r");
  src.Replace("\n", "\\n");
  src.Replace("\t", "\\t");
  src.Replace("\f", "\\f");
  return src;
}

/*-----------------------------------------------------------------------------
  Escape the supplied string for JSON
-----------------------------------------------------------------------------*/
CStringA JSONEscape(CString src) {
  return JSONEscapeA((LPCSTR)CT2A(src, CP_UTF8));
}

/*-----------------------------------------------------------------------------
-----------------------------------------------------------------------------*/
void QueryPerfCounter(__int64 &counter) {
  LARGE_INTEGER counter_struct;
  counter_struct.QuadPart = 0;
  QueryPerformanceCounter(&counter_struct);
  counter = counter_struct.QuadPart;
}

/*-----------------------------------------------------------------------------
-----------------------------------------------------------------------------*/
void QueryPerfFrequency(__int64 &freq) {
  LARGE_INTEGER freq_struct;
  freq_struct.QuadPart = 0;
  QueryPerformanceFrequency(&freq_struct);
  freq = freq_struct.QuadPart;
}

/*-----------------------------------------------------------------------------
  Scan the content to see if it is a binary content type
  https://mimesniff.spec.whatwg.org/#sniffing-a-mislabeled-binary-resource
-----------------------------------------------------------------------------*/
bool IsBinaryContent(LPBYTE content, DWORD len) {
  bool is_binary = false;

  if (content) {
    if (len >= 2 &&
        (content[0] == 0xFE && content[1] == 0xFF) ||
        (content[0] == 0xFF && content[1] == 0xFE)) {
      // UTF 16 BOM
      is_binary = false;
    } else if (len >= 3 && content[0] == 0xEF &&
               content[1] == 0xBB && content[2] == 0xBF) {
      // UTF 8 BOM
      is_binary = false;
    } else if (len > 0) {
      DWORD index = 0;
      while (index < len && !is_binary) {
        BYTE val = content[index];
        if (val <= 0x08 || 
            val == 0x0B ||
            (val >= 0x0E && val <= 0x1A) ||
            (val >= 0x1C && val <= 0x1F)) {
          is_binary = true;
        }
        index++;
      }
    }
  }

  return is_binary;
}