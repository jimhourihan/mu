//
//  Copyright (c) 2010, Jim Hourihan
//  All rights reserved.
// 
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//     * Redistributions of source code must retain the above
//       copyright notice, this list of conditions and the following
//       disclaimer.
//
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials
//       provided with the distribution.
//
//     * Neither the name of stl_ext nor the names of its
//       contributors may be used to endorse or promote products
//       derived from this software without specific prior written
//       permission.
// 
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
//  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
//  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
#include <stl_ext/string_algo.h>
#include <sstream>

namespace stl_ext {
using namespace std;

void
tokenize(vector<string> &tokens, 
	 const string& str, 
	 string delimiters)
{
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (pos != string::npos || lastPos != string::npos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

string 
wrap(const string& s, 
     char wrapchar, 
     const string& breakString,
     string::size_type col)
{
    if (s.size() < col) return s;

    ostringstream str;

    for (string::size_type a = 0, b = 0, c = 0;;)
    {
        b = s.find_first_of(wrapchar, a);

        if (b == string::npos)
        {
            for (string::size_type i = a; i < s.size(); i++, c++) str << s[i];
            break;
        }
        else
        {
            for (string::size_type i = a; i < b; i++, c++) str << s[i];
            a = s.find_first_not_of(wrapchar, b);
            str << wrapchar;
        }

        if (c >= col) 
        {
            str << breakString;
            c = 0;
        }
    } 

    return str.str();
}



string 
dirname( string path )
{
    size_t lastSlash = path.rfind( "/" );
    if( lastSlash == path.npos )
    {
        return string(".");
    }

    return path.substr( 0, lastSlash );
}


string 
basename( string path )
{
    size_t lastSlash = path.rfind( "/" );
    if( lastSlash == path.npos )
    {
        return path;
    }

    return path.substr( lastSlash + 1, path.size() );
}


string 
prefix( string path )
{
    string filename( basename( path ) );
    if( filename.find( "." ) == filename.npos )
    {
        return filename;
    }
    return filename.substr( 0, filename.find( "." ) );
}


string 
extension( string path )
{
    string filename( basename( path ) );
    if( filename.find( "." ) == filename.npos )
    {
        return string("");
    }
    return filename.substr( filename.rfind(".") + 1, filename.size() );
}


unsigned long 
hash(const std::string &s)
{
    //
    //	Taken from the ELF format hash function
    //

    unsigned long h=0,g;
    
    for (int i=0; i<s.size(); i++)
    {
	h = (h << 4) + s[i];
	if ( (g = h & 0xf0000000) ) h ^= g >> 24;
	h &= ~g;
    }
    
    return h;
}

//
//  Claimed to be fast
//

#if 0
unsigned int 
murmur_hash(const unsigned char * data, int len, unsigned int h)
{
	const unsigned int m = 0x7fd652ad;
	const int r = 16;

	h += 0xdeadbeef;

	while(len >= 4)
	{
		h += *(unsigned int *)data;
		h *= m;
		h ^= h >> r;

		data += 4;
		len -= 4;
	}

	switch(len)
	{
	case 3:
		h += data[2] << 16;
	case 2:
		h += data[1] << 8;
	case 1:
		h += data[0];
		h *= m;
		h ^= h >> r;
	};

	h *= m;
	h ^= h >> 10;
	h *= m;
	h ^= h >> 17;

	return h;
}
#endif

} // namespace stl_ext
