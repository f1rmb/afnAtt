/*
  RF Attenuator Management Class, designed to work with PE4306 chip
  based card from SV1AFN: https://www.sv1afn.com/rfattenuator.html

  Version: 0.0.1

  Copyright (C) 2014 F1RMB, Daniel Caujolle-Bert <f1rmb.daniel@gmail.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "afnAttenuator.h"

const uint8_t afnAttenuator::ATTENUATION_MIN   = 0;
const uint8_t afnAttenuator::ATTENUATION_MAX   = 31;
const float   afnAttenuator::SLOPE             = 0.9628758065;
const float   afnAttenuator::OFFSET            = 1.6597935484;

afnAttenuator::afnAttenuator(uint8_t rate) : m_Att(ATTENUATION_MIN)
{
    //ctor
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE3);
    SPI.setClockDivider(rate); // SPI_CLOCK_DIV4 by default (4MHz)

    SetValue(m_Att, true);
}

afnAttenuator::~afnAttenuator()
{
    //dtor
    //SetValue(ATTENUATION_MIN);
}

uint8_t afnAttenuator::GetValue()
{
    return m_Att;
}

double afnAttenuator::GetRealValue()
{
    return ((static_cast<double>(m_Att) * SLOPE) + OFFSET);
}

uint8_t afnAttenuator::SetValue(const uint8_t &val, bool force)
{
    uint8_t oldAtt = m_Att;

    m_Att = constrain(val, ATTENUATION_MIN, ATTENUATION_MAX);

    if ((oldAtt != m_Att) || force)
    {
        digitalWrite(SS, LOW);
        SPI.transfer(((m_Att << 1) | 0x40));
        digitalWrite(SS, HIGH);
    }

    return m_Att;
}

uint8_t afnAttenuator::Inc(uint8_t val)
{
    return SetValue(GetValue() + val);
}

uint8_t afnAttenuator::Dec(uint8_t val)
{
    if (val >= GetValue())
        return SetValue(ATTENUATION_MIN);

    return SetValue(GetValue() - val);
}

uint8_t afnAttenuator::GetMin()
{
    return ATTENUATION_MIN;
}

uint8_t afnAttenuator::GetMax()
{
    return ATTENUATION_MAX;
}
