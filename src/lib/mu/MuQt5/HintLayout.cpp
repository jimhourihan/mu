//
//  Copyright (c) 2009, Jim Hourihan
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
//     * Neither the name of the Jim Hourihan nor the names of its
//       contributors may be used to endorse or promote products
//       derived from this software without specific prior written
//       permission.
// 
//  THIS SOFTWARE IS PROVIDED BY Jim Hourihan ''AS IS'' AND ANY EXPRESS
//  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL Jim Hourihan BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
//  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
//  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
//
#include "qtUtils.h"
#include "HintLayout.h"

namespace Mu {
using namespace std;

HintLayout::HintLayout(QWidget* parent, QSize size) 
    : QLayout(parent),
      m_size(size)
{
}

HintLayout::~HintLayout()
{
    QLayoutItem *item;
    while (item = takeAt(0)) delete item;
}

void HintLayout::addItem(QLayoutItem *item) 
{
    m_itemList.append(item); 
}

int HintLayout::count() const 
{ 
    return m_itemList.size(); 
}

QLayoutItem *
HintLayout::itemAt(int index) const 
{
    return m_itemList.value(index); 
}

QLayoutItem *
HintLayout::takeAt(int index)
{
    if (index >= 0 && index < m_itemList.size())
    {
        return m_itemList.takeAt(index);
    }
    else
    {
        return 0;
    }
}

QSize
HintLayout::sizeHint() const
{
    return m_size;
}

} // Mu
