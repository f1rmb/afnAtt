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
#ifndef AFNATTENUATOR_H
#define AFNATTENUATOR_H

#include <Arduino.h>
#include <SPI.h>

class afnAttenuator
{
    static const uint8_t ATTENUATION_MIN;
    static const uint8_t ATTENUATION_MAX;

    public:
        afnAttenuator(uint8_t rate = SPI_CLOCK_DIV4);
        virtual ~afnAttenuator();
        uint8_t                     GetValue();
        double                      GetRealValue();
        uint8_t                     SetValue(const uint8_t &val, bool force = false);
        uint8_t                     Inc(uint8_t val = 1);
        uint8_t                     Dec(uint8_t val = 1);
        uint8_t                     GetMin();
        uint8_t                     GetMax();

    private:
        uint8_t     m_Att;
        double      m_correctionFactor;
};

#endif // AFNATTENUATOR_H
