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

// Only working with initProject.sce
// add Project specific library

if(~ isdef('x2c_SquareInj_Slow') ) then //If ZSMT block library NOT added yet
    chdir(CurrentDir);
    x2c_setCurrentWorkingDir()
    if isdir(CurrentDir + fs + "Library") then

        jimport("at.lcm.x2c.core.librarymanager.X2cLibraryManager");
        x2cLM = jinvoke(X2cLibraryManager,"getInstance");
    
        x2cLibs = jinvoke(x2cLM, "addPath_XcosLibPathStr", CurrentDir + fs + "Library");
        
        chdir(CurrentDir + fs + "Library\MCHP_ZSMT\Scilab");
        // load ZSMT library
        loaderFile = ["loader_x64.sce"];
        if isfile(loaderFile) then
            exec(loaderFile, -1)
        end
        
        // load functions and palette
        deletefile("MCHP_ZSMT.xpal");  // delete palette to force rebuild (otherwise error would occur since block image can't be found)
		exec("starter.sce", -1)

        mprintf("Project specific library " + "MCHP_ZSMT" + " added.\n")

        chdir(CurrentDir)
    
        // clean  up
        clear("libName", "libRoot", "loaderFile", "curLib", "x2cLibs", "x2cLM")

        //mprintf("Project specific library " + libName + " added.\n")

    end
else
    mprintf("ZSMT block library already added. \n")
end
