/*
  RF Attenuator Example.

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
#include <Arduino.h>
#include "afnAttenuator.h"
/*
                                            SPI pins
-----------------+----------------+----------------+----------------+----------------+----------------+
  Arduino Board  |      MOSI      |       MISO     |       SCK      |    SS (slave)  |  SS (master)   |
-----------------+----------------+----------------+----------------+----------------+----------------|
Uno/Duemilanove	 |  11 or ICSP-4  |  12 or ICSP-1  |  13 or ICSP-3	|        10	     |       x        |
Mega2560	     |  51 or ICSP-4  |  50 or ICSP-1  |  52 or ICSP-3	|        53	     |       x        |
Leonardo	     |  ICSP-4        |     ICSP-1     |     ICSP-3	    |         x	     |       x        |
Due	             |  ICSP-4        |     ICSP-1     |     ICSP-3	    |         x      |    4, 10, 52   |
-----------------+----------------+----------------+----------------+----------------+----------------+


 *****************
**  Connections  **
 *****************

// Check the table above
Connect MOSI to 'D'
Connect SCK  to 'C'
Connect SS   to 'L'
Connect 3.3V to '+3'
Connect GND  to 'G'

*/

afnAttenuator mAtt;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    char prompt[80];
    snprintf(prompt, sizeof(prompt) - 1, "Enter Attenuation [%d..%d] ?", mAtt.GetMin(), mAtt.GetMax());

    while (1)
    {
        if (Serial)
        {
            char buf[80] = "";

            Serial.println(prompt);

            while (!Serial.available())
                delay(10);

            Serial.readBytesUntil('\n', buf, sizeof(buf) - 1);

            if (!strlen(buf))
                continue;

            if ((buf[0] == '+')  || (buf[0] == '-'))
            {
                byte step = 1;

                if (strlen(buf) > 1)
                    step = atoi(&buf[1]);

                byte oV = mAtt.GetValue();
                byte oD = oV;

                Serial.print(" > Inc/Dec(");
                Serial.print(step, DEC);
                Serial.print("): ");

                if (buf[0] == '+')
                {
                    mAtt.Inc(step);
                    oD += step;
                }
                else if (buf[0] == '-')
                {
                    mAtt.Dec(step);
                    oD -= step;
                }

                if (oD == mAtt.GetValue())
                    Serial.print("  ** Success: ");
                else
                {
                    Serial.print("  !! Failure: ");
                    Serial.print("Asked: ");
                    Serial.print(oD, DEC);
                    Serial.print(" Sets: ");
                    Serial.print(mAtt.GetValue(), DEC);
                    Serial.print(" - ");
                }

                Serial.print("Attenuation sets to ");
                Serial.print(mAtt.GetValue(), DEC);
                Serial.println("dB.");

                break;

            }

            int attv = atoi(buf);
            Serial.print(" > Setting attenuation to ");
            Serial.print(attv, DEC);
            Serial.print("dB: ");

            byte ret;
            if ((ret = mAtt.SetValue(attv)) == attv)
                Serial.print("  ** Success: ");
            else
                Serial.print("  !! Failure: ");

            Serial.print("Attenuation sets to ");
            Serial.print(ret, DEC);
            Serial.println("dB.");
        }

        delay(50);
    }
}
