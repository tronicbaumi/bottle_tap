// (c) 2020 Microchip Technology Inc. and its subsidiaries
// Subject to your compliance with these terms, you may use Microchip software and any derivatives exclusively 
// with Microchip products. You’re responsible for complying with 3rd party license terms applicable to your use 
// of 3rd party software (including open source software) that may accompany Microchip software. 
// SOFTWARE IS “AS IS.” NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
// IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP 
// BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
// KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR 
// THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP’S TOTAL LIABILITY ON ALL CLAIMS RELATED 
// TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

//https://www.microchip.com/en-us/tools-resources/reference-designs/portable-power-tool-reference-design
//AN4740
if isdef(['boardName'])==%F then
    mprintf("[Warning] - No boardName defined, defining this now.");
    boardName = 'MCLV48 board';
else
    if boardName == 'MCLV48 board'

        fPWM = 10000;               // in Hz
        
        Rshunt = 0.003;             // in ohms
	    Vbus = 24;                  // in volts
        
        Igain = -25;              // unitless
        
        I_max = 22;     // in A max current I can measure based on the amplification on the board
        maxCurrentCommand = 5;
    end
end

