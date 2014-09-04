//
//  Plugin.cpp
//  BundleUnity
//


/** @file
 *
 * @ingroup Jamoma Modular Library
 *
 * @brief This is a plugin for Unity using the Jamoma Modular library (file .CPP)
 *
 * @details This plugin allows the communication between i-score and video games created by Unity
 *
 * @authors Kim Dung Dang and Théo de la Hogue (created by Kim Dung Dang on 26/03/2014)
 *
 * @copyright © 2014 CNAM and GMEA, all rights reserved @n
 *
 */

#include "Plugin.h"

/** Callback function (used in C/C++) */
void DataReturnValueCallback()
{
    TTLogMessage("The parameter has been updated. \n");
}

/** Callback function (used in C/C++) to get data's value back
 @param[in] baton #TTValue
 @param[out] value #TTValue
void DataReturnValueCallback(const TTValue& baton, const TTValue& value)
{
    TTObject anObject = baton[0];
    
	// Retrieve which data has been updated
    
    for (int iParameterData = 0 ; iParameterData < numberParameterData ; iParameterData++) {
        if (anObject.instance() == mDataParameterVector[iParameterData].instance())
        {
            // Print the returned value
            TTLogMessage("The parameter %d has been updated to %s \n", iParameterData, value.toString().data());
            return;
        }
    }
    
    for (int iReturnData = 0 ; iReturnData < numberReturnData ; iReturnData++) {
        if (anObject.instance() == mDataReturnVector[iReturnData].instance())
        {
            // Print the returned value
            TTLogMessage("The return %d has been updated to %s \n", iReturnData, value.toString().data());
            return;
        }
    }
    
    if (anObject.instance() == mDataDemoMessage.instance())
    {
        // Print the returned value
        TTLogMessage("The message has been updated to %s \n", value.toString().data());
        return;
    }
    
    return;
}
*/

/** Init the Jamoma Modular library
 @param[in] folderPath Folder path where all the dylibs are */
void InitModularLibraryPlugin (char folderPath[])
{
    TTModularInit(folderPath);
}

/** Create an application manager */
void CreateApplicationManagerPlugin()
{
    mApplicationManager = TTObject("ApplicationManager");
}

/** Create a local application, a distant application and register them to the application manager
 @param[in] localAppName Name of the local application
 @param[in] distantAppName Name of the distant application
 @return 0: Cannot create the local application
 @return 1: Cannot create the distant application
 @return 2: Create the local and distant applications and register them successfully */
int CreateAndRegisterApplicationsPlugin(char localAppName[], char distantAppName[])
{
    TTErr err;
    TTValue out;
    
    err = mApplicationManager.send("ApplicationInstantiateLocal", localAppName, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the local application \n");
        return 0;
    }
    else
    {
        mApplicationLocal = out[0];
    }
    
    err = mApplicationManager.send("ApplicationInstantiateDistant", distantAppName, out);
    
    if (err) {
        TTLogError("Error: Cannot create the distant application \n");
        return 1;
    }
    else
    {
        mApplicationDistant = out[0];
    }
    
    // Get registered application names
    mApplicationManager.get("applicationNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTLogMessage("%s application is well registered into the application manager \n", name.c_str());
    }
    
    return 2;
}

/** Create a Minuit protocol unit
 @return 0: Cannot create the Minuit protocol unit
 @return 1: Create successfully the Minuit protocol unit */
int CreateMinuitProtocolUnitPlugin()
{
    TTErr err;
    TTValue out;
    
    err = mApplicationManager.send("ProtocolInstantiate", "Minuit", out);
    
    if (err) {
        TTLogError("Error: Cannot create the Minuit protocol unit \n");
        return 0;
    }
    else
    {
        mProtocolMinuit = out[0];
    }
    
    // Get Minuit Protocol attribute names and types
    mProtocolMinuit.get("parameterNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTSymbol type = mProtocolMinuit.attributeType(name);
        TTLogMessage("Minuit %s parameter is %s \n", name.c_str(), type.c_str());
    }
    
    return 1;
}

/** Register the local and distant applications to the Minuit protocol
 @param[in] localAppName Name of the local application
 @param[in] distantAppName Name of the distant application
 @param[in] portLocal Port of the local application
 @param[in] ipLocal IP adress of the local application
 @param[in] portDistant Port of the distant application
 @param[in] ipDistant IP adress of the distant application */
void RegisterApplicationsToMinuitPlugin(char localAppName[], char distantAppName[], int portLocal, char ipLocal[], int portDistant, char ipDistant[])
{
    TTValue out;
    
    // Register the local and distant applications to the Minuit protocol
    mProtocolMinuit.send("ApplicationRegister", localAppName, out);
    mProtocolMinuit.send("ApplicationRegister", distantAppName, out);
    
    // Select the local application to set its protocol parameters
    mProtocolMinuit.send("ApplicationSelect", localAppName, out);
    mProtocolMinuit.set("port", portLocal);
    mProtocolMinuit.set("ip", ipLocal);
    
    // Select the distant application to set its protocol parameters
    mProtocolMinuit.send("ApplicationSelect", distantAppName, out);
    mProtocolMinuit.set("port", portDistant);
    mProtocolMinuit.set("ip", ipDistant);
    
    // Get Minuit parameters for each registered application
    mProtocolMinuit.get("applicationNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        
        mProtocolMinuit.send("ApplicationSelect", name, out);
        TTLogMessage("Minuit setup for the %s application: \n", name.c_str());
        
        TTValue v;
        mProtocolMinuit.get("ip", v);
        TTSymbol ip = v[0];
        TTLogMessage("- ip = %s \n", ip.c_str());
        
        mProtocolMinuit.get("port", v);
        TTUInt16 port = v[0];
        TTLogMessage("- port = %d \n", port);
    }
}

/** Run the Minuit protocol */
void RunMinuitProtocolPlugin()
{
    // Enable Minuit communication
    mProtocolMinuit.send("Run");
    
    TTLogMessage("\n*** Current Minuit Protocol Setup ***\n");
    
    // Get protocol names
    TTValue out;
    mApplicationManager.get("protocolNames", out);
    for (TTElementIter it = out.begin() ; it != out.end() ; it++) {
        TTSymbol name = TTElement(*it);
        TTLogMessage("%s protocol is well registered into the application manager \n", name.c_str());
    }
}

/** Set the author's name of the local application
 @param[in] authorName The author's name */
void SetAuthorNamePlugin(char authorName[])
{
    mApplicationLocal.set("author", authorName);
}

/** Get the author's name of the local application
 @return Author's name of the local application */
const char* GetAuthorNamePlugin()
{
    TTValue v;
    mApplicationLocal.get("author", v);
    
    TTSymbol sym = v[0];
    const char* value = sym.c_str();
        
    return value;
}

/** Set the version name of the local application
 @param[in] versionName The version name of the local appliation */
void SetVersionPlugin(char versionName[])
{
    mApplicationLocal.set("version", versionName);
}

/** Get the version name of the local application
 @return Version name of the local application */
const char* GetVersionPlugin()
{
    TTValue v;
    mApplicationLocal.get("version", v);
    
    TTSymbol sym = v[0];
    const char* value = sym.c_str();
        
    return value;
}

/** Create a parameter data (type "integer" or "decimal") at an address (without the callback function in Unity)
 @param[in] paramaterAddress Address of this parameter registered in the local application
 @param[in] type "type" attribute of this parameter
 @param[in] rangeBoundMin Min bound of the "rangeBounds" attribute of this parameter
 @param[in] rangeBoundMax Max bound of the "rangeBounds" attribute of this parameter
 @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
 @param[in] rampDrive "rampDrive" attribute of this parameter
 @param[in] description "description" attribute of this parameter
 @return 0: Cannot create the parameter data at this address
 @return 1: Create successfully the parameter data at this address */
int CreateNumberParameterDataPlugin(char paramaterAddress[], char type[], float rangeBoundMin, float rangeBoundMax, char rangeClipmode[], char rampDrive[], char description[])
{
    int indexParameter = numberParameterData;
    numberParameterData++;
    
    // Create a parameter data and set its callback function and baton and some attributes
    TTObject mNewDataParameter = TTObject("Data", "parameter");
    auto parameterVector = mDataParameterVector.end();
    parameterVector = mDataParameterVector.insert(parameterVector, mNewDataParameter);
    
    // Setup the callback mechanism to get the value back
    TTValue args;
    args = TTValue(mDataParameterVector[indexParameter]);
    mDataParameterVector[indexParameter].set("baton", args);
    mDataParameterVector[indexParameter].set("function", TTPtr(&DataReturnValueCallback));
    
    // Setup the data attributes depending of its use inside the application
    mDataParameterVector[indexParameter].set("type", type);
    TTValue rangeBounds = TTValue(rangeBoundMin, rangeBoundMax);
    mDataParameterVector[indexParameter].set("rangeBounds", rangeBounds);
    mDataParameterVector[indexParameter].set("rangeClipmode", rangeClipmode);
    mDataParameterVector[indexParameter].set("rampDrive", rampDrive);
    mDataParameterVector[indexParameter].set("description", description);
    
    // Register the parameter data into the local application at an address
    args = TTValue(paramaterAddress, mDataParameterVector[indexParameter]);
    
    TTErr err;
    TTValue out;
    
    err = mApplicationLocal.send("ObjectRegister", args, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the parameter data at the %s address \n", paramaterAddress);
        
        // Erase this parameter in the vector of parameters and reduce "numberParameterData"
        mDataParameterVector.erase (mDataParameterVector.begin() + indexParameter);
        numberParameterData--;
        
        return 0;
    }
    else
    {
        TTAddress address;
        address = out[0];
        TTLogMessage("\n %s: effective registration address is %s \n", paramaterAddress, address.c_str());
        
        return 1;
    }
}

/** Create a parameter data (type "integer" or "decimal") at an address (with the callback function in Unity)
 @param[in] paramaterAddress Address of this parameter registered in the local application
 @param[in] type "type" attribute of this parameter
 @param[in] rangeBoundMin Min bound of the "rangeBounds" attribute of this parameter
 @param[in] rangeBoundMax Max bound of the "rangeBounds" attribute of this parameter
 @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
 @param[in] rampDrive "rampDrive" attribute of this parameter
 @param[in] description "description" attribute of this parameter
 @param[in] valueCallback The callback function corresponding to this parameter
 @return 0: Cannot create the parameter data at this address
 @return 1: Create successfully the parameter data at this address */
int CreateNumberParameterDataPluginWithCallbackUnity(char paramaterAddress[], char type[], float rangeBoundMin, float rangeBoundMax, char rangeClipmode[], char rampDrive[], char description[], ValueCallback valueCallback)
{
    int indexParameter = numberParameterData;
    numberParameterData++;
    
    // Create a parameter data and set its callback function and baton and some attributes
    TTObject mNewDataParameter = TTObject("Data", "parameter");
    auto parameterVector = mDataParameterVector.end();
    parameterVector = mDataParameterVector.insert(parameterVector, mNewDataParameter);
    
    // Setup the callback mechanism to get the value back
    TTValue args;
    args = TTValue(mDataParameterVector[indexParameter]);
    mDataParameterVector[indexParameter].set("baton", args);
    mDataParameterVector[indexParameter].set("function", TTPtr(valueCallback));
    
    // Setup the data attributes depending of its use inside the application
    mDataParameterVector[indexParameter].set("type", type);
    TTValue rangeBounds = TTValue(rangeBoundMin, rangeBoundMax);
    mDataParameterVector[indexParameter].set("rangeBounds", rangeBounds);
    mDataParameterVector[indexParameter].set("rangeClipmode", rangeClipmode);
    mDataParameterVector[indexParameter].set("rampDrive", rampDrive);
    mDataParameterVector[indexParameter].set("description", description);
    
    // Register the parameter data into the local application at an address
    args = TTValue(paramaterAddress, mDataParameterVector[indexParameter]);
    
    TTErr err;
    TTValue out;
    
    err = mApplicationLocal.send("ObjectRegister", args, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the parameter data at the %s address \n", paramaterAddress);
        
        // Erase this parameter in the vector of parameters and reduce "numberParameterData"
        mDataParameterVector.erase (mDataParameterVector.begin() + indexParameter);
        numberParameterData--;
        
        return 0;
    }
    else
    {
        TTAddress address;
        address = out[0];
        TTLogMessage("\n %s: effective registration address is %s \n", paramaterAddress, address.c_str());
        
        return 1;
    }
}

/** Create a parameter data (type "boolean") at an address (without the callback function in Unity)
 @param[in] paramaterAddress Address of this parameter registered in the local application
 @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
 @param[in] rampDrive "rampDrive" attribute of this parameter
 @param[in] description "description" attribute of this parameter
 @return 0: Cannot create the parameter data at this address
 @return 1: Create successfully the parameter data at this address */
int CreateBooleanParameterDataPlugin(char paramaterAddress[], char rangeClipmode[], char rampDrive[], char description[])
{
    int indexParameter = numberParameterData;
    numberParameterData++;
    
    // Create a parameter data and set its callback function and baton and some attributes
    TTObject mNewDataParameter = TTObject("Data", "parameter");
    auto parameterVector = mDataParameterVector.end();
    parameterVector = mDataParameterVector.insert(parameterVector, mNewDataParameter);
    
    // Setup the callback mechanism to get the value back
    TTValue args;
    args = TTValue(mDataParameterVector[indexParameter]);
    mDataParameterVector[indexParameter].set("baton", args);
    mDataParameterVector[indexParameter].set("function", TTPtr(&DataReturnValueCallback));
    
    // Setup the data attributes depending of its use inside the application
    mDataParameterVector[indexParameter].set("type", "boolean");
    mDataParameterVector[indexParameter].set("rangeClipmode", rangeClipmode);
    mDataParameterVector[indexParameter].set("rampDrive", rampDrive);
    mDataParameterVector[indexParameter].set("description", description);
    
    // Register the parameter data into the local application at an address
    args = TTValue(paramaterAddress, mDataParameterVector[indexParameter]);
    
    TTErr err;
    TTValue out;
    
    err = mApplicationLocal.send("ObjectRegister", args, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the parameter data at the %s address \n", paramaterAddress);
        
        // Erase this parameter in the vector of parameters and reduce "numberParameterData"
        mDataParameterVector.erase (mDataParameterVector.begin() + indexParameter);
        numberParameterData--;
        
        return 0;
    }
    else
    {
        TTAddress address;
        address = out[0];
        TTLogMessage("\n %s: effective registration address is %s \n", paramaterAddress, address.c_str());
        
        return 1;
    }
}

/** Create a parameter data (type "boolean") at an address (with the callback function in Unity)
 @param[in] paramaterAddress Address of this parameter registered in the local application
 @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
 @param[in] rampDrive "rampDrive" attribute of this parameter
 @param[in] description "description" attribute of this parameter
 @param[in] valueCallback The callback function corresponding to this parameter
 @return 0: Cannot create the parameter data at this address
 @return 1: Create successfully the parameter data at this address */
int CreateBooleanParameterDataPluginWithCallbackUnity(char paramaterAddress[], char rangeClipmode[], char rampDrive[], char description[], ValueCallback valueCallback)
{
    int indexParameter = numberParameterData;
    numberParameterData++;
    
    // Create a parameter data and set its callback function and baton and some attributes
    TTObject mNewDataParameter = TTObject("Data", "parameter");
    auto parameterVector = mDataParameterVector.end();
    parameterVector = mDataParameterVector.insert(parameterVector, mNewDataParameter);
    
    // Setup the callback mechanism to get the value back
    TTValue args;
    args = TTValue(mDataParameterVector[indexParameter]);
    mDataParameterVector[indexParameter].set("baton", args);
    mDataParameterVector[indexParameter].set("function", TTPtr(valueCallback));
    
    // Setup the data attributes depending of its use inside the application
    mDataParameterVector[indexParameter].set("type", "boolean");
    mDataParameterVector[indexParameter].set("rangeClipmode", rangeClipmode);
    mDataParameterVector[indexParameter].set("rampDrive", rampDrive);
    mDataParameterVector[indexParameter].set("description", description);
    
    // Register the parameter data into the local application at an address
    args = TTValue(paramaterAddress, mDataParameterVector[indexParameter]);
    
    TTErr err;
    TTValue out;
    
    err = mApplicationLocal.send("ObjectRegister", args, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the parameter data at the %s address \n", paramaterAddress);
        
        // Erase this parameter in the vector of parameters and reduce "numberParameterData"
        mDataParameterVector.erase (mDataParameterVector.begin() + indexParameter);
        numberParameterData--;
        
        return 0;
    }
    else
    {
        TTAddress address;
        address = out[0];
        TTLogMessage("\n %s: effective registration address is %s \n", paramaterAddress, address.c_str());
        
        return 1;
    }
}

/** Create a parameter data (type "string") at an address (without the callback function in Unity)
 @param[in] paramaterAddress Address of this parameter registered in the local application
 @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
 @param[in] rampDrive "rampDrive" attribute of this parameter
 @param[in] description "description" attribute of this parameter
 @return 0: Cannot create the parameter data at this address
 @return 1: Create successfully the parameter data at this address */
int CreateStringParameterDataPlugin(char paramaterAddress[], char rangeClipmode[], char rampDrive[], char description[])
{
    int indexParameter = numberParameterData;
    numberParameterData++;
    
    // Create a parameter data and set its callback function and baton and some attributes
    TTObject mNewDataParameter = TTObject("Data", "parameter");
    auto parameterVector = mDataParameterVector.end();
    parameterVector = mDataParameterVector.insert(parameterVector, mNewDataParameter);
    
    // Setup the callback mechanism to get the value back
    TTValue args;
    args = TTValue(mDataParameterVector[indexParameter]);
    mDataParameterVector[indexParameter].set("baton", args);
    mDataParameterVector[indexParameter].set("function", TTPtr(&DataReturnValueCallback));
    
    // Setup the data attributes depending of its use inside the application
    mDataParameterVector[indexParameter].set("type", "string");
    mDataParameterVector[indexParameter].set("rangeClipmode", rangeClipmode);
    mDataParameterVector[indexParameter].set("rampDrive", rampDrive);
    mDataParameterVector[indexParameter].set("description", description);
    
    // Register the parameter data into the local application at an address
    args = TTValue(paramaterAddress, mDataParameterVector[indexParameter]);
    
    TTErr err;
    TTValue out;
    
    err = mApplicationLocal.send("ObjectRegister", args, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the parameter data at the %s address \n", paramaterAddress);
        
        // Erase this parameter in the vector of parameters and reduce "numberParameterData"
        mDataParameterVector.erase (mDataParameterVector.begin() + indexParameter);
        numberParameterData--;
        
        return 0;
    }
    else
    {
        TTAddress address;
        address = out[0];
        TTLogMessage("\n %s: effective registration address is %s \n", paramaterAddress, address.c_str());
        
        return 1;
    }
}


/** Create a parameter data (type "string") at an address (with the callback function in Unity)
 @param[in] paramaterAddress Address of this parameter registered in the local application
 @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
 @param[in] rampDrive "rampDrive" attribute of this parameter
 @param[in] description "description" attribute of this parameter
 @param[in] valueCallback The callback function corresponding to this parameter
 @return 0: Cannot create the parameter data at this address
 @return 1: Create successfully the parameter data at this address */
int CreateStringParameterDataPluginWithCallbackUnity(char paramaterAddress[], char rangeClipmode[], char rampDrive[], char description[], ValueCallback valueCallback)
{
    int indexParameter = numberParameterData;
    numberParameterData++;
    
    // Create a parameter data and set its callback function and baton and some attributes
    TTObject mNewDataParameter = TTObject("Data", "parameter");
    auto parameterVector = mDataParameterVector.end();
    parameterVector = mDataParameterVector.insert(parameterVector, mNewDataParameter);
    
    // Setup the callback mechanism to get the value back
    TTValue args;
    args = TTValue(mDataParameterVector[indexParameter]);
    mDataParameterVector[indexParameter].set("baton", args);
    mDataParameterVector[indexParameter].set("function", TTPtr(valueCallback));
    
    // Setup the data attributes depending of its use inside the application
    mDataParameterVector[indexParameter].set("type", "string");
    mDataParameterVector[indexParameter].set("rangeClipmode", rangeClipmode);
    mDataParameterVector[indexParameter].set("rampDrive", rampDrive);
    mDataParameterVector[indexParameter].set("description", description);
    
    // Register the parameter data into the local application at an address
    args = TTValue(paramaterAddress, mDataParameterVector[indexParameter]);
    
    TTErr err;
    TTValue out;
    
    err = mApplicationLocal.send("ObjectRegister", args, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the parameter data at the %s address \n", paramaterAddress);
        
        // Erase this parameter in the vector of parameters and reduce "numberParameterData"
        mDataParameterVector.erase (mDataParameterVector.begin() + indexParameter);
        numberParameterData--;
        
        return 0;
    }
    else
    {
        TTAddress address;
        address = out[0];
        TTLogMessage("\n %s: effective registration address is %s \n", paramaterAddress, address.c_str());
        
        return 1;
    }
}

/** Create a return data at an address (without the callback function in Unity)
 @param[in] returnAddress Address of this return registered in the local application
 @param[in] type "type" attribute of this return (type is "decimal" or "integer" or "boolean")
 @param[in] description "description" attribute of this return
 @return 0: Cannot create the return data at this return
 @return 1: Create successfully the return data at this address */
int CreateReturnDataPlugin(char returnAddress[], char type[], char description[])
{
    int indexReturn = numberReturnData;
    numberReturnData++;
    
    // Create a return data and set its callback function and baton and some attributes
    TTObject mNewDataReturn = TTObject("Data", "return");
    auto returnVector = mDataReturnVector.end();
    returnVector = mDataReturnVector.insert(returnVector, mNewDataReturn);
    
    // Setup the callback mechanism to get the value back
    TTValue args;
    args = TTValue(mDataReturnVector[indexReturn]);
    mDataReturnVector[indexReturn].set("baton", args);
    mDataReturnVector[indexReturn].set("function", TTPtr(&DataReturnValueCallback));
    
    // Setup the data attributes depending of its use inside the application
    mDataReturnVector[indexReturn].set("type", type);
    mDataReturnVector[indexReturn].set("description", description);
    
    // Register the return data into the local application at an address
    args = TTValue(returnAddress, mDataReturnVector[indexReturn]);
    
    TTErr err;
    TTValue out;
    
    err = mApplicationLocal.send("ObjectRegister", args, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the return data at the %s address \n", returnAddress);
        
        // Erase this return in the vector of returns and reduce "numberReturnData"
        mDataReturnVector.erase (mDataReturnVector.begin() + indexReturn);
        numberReturnData--;
        
        return 0;
    }
    else
    {
        TTAddress address;
        address = out[0];
        TTLogMessage("\n %s: effective registration address is %s \n", returnAddress, address.c_str());
        
        return 1;
    }
}

/** Create a return data at an address (with the callback function in Unity)
 @param[in] returnAddress Address of this return registered in the local application
 @param[in] type "type" attribute of this return (type is "decimal" or "integer" or "boolean")
 @param[in] description "description" attribute of this return
 @param[in] valueCallback The callback function corresponding to this parameter
 @return 0: Cannot create the return data at this return
 @return 1: Create successfully the return data at this address */
int CreateReturnDataPluginWithCallbackUnity(char returnAddress[], char type[], char description[], ValueCallback valueCallback)
{
    int indexReturn = numberReturnData;
    numberReturnData++;
    
    // Create a return data and set its callback function and baton and some attributes
    TTObject mNewDataReturn = TTObject("Data", "return");
    auto returnVector = mDataReturnVector.end();
    returnVector = mDataReturnVector.insert(returnVector, mNewDataReturn);
    
    // Setup the callback mechanism to get the value back
    TTValue args;
    args = TTValue(mDataReturnVector[indexReturn]);
    mDataReturnVector[indexReturn].set("baton", args);
    mDataReturnVector[indexReturn].set("function", TTPtr(valueCallback));
    
    // Setup the data attributes depending of its use inside the application
    mDataReturnVector[indexReturn].set("type", type);
    mDataReturnVector[indexReturn].set("description", description);
    
    // Register the return data into the local application at an address
    args = TTValue(returnAddress, mDataReturnVector[indexReturn]);
    
    TTErr err;
    TTValue out;
    
    err = mApplicationLocal.send("ObjectRegister", args, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the return data at the %s address \n", returnAddress);
        
        // Erase this return in the vector of returns and reduce "numberReturnData"
        mDataReturnVector.erase (mDataReturnVector.begin() + indexReturn);
        numberReturnData--;
        
        return 0;
    }
    else
    {
        TTAddress address;
        address = out[0];
        TTLogMessage("\n %s: effective registration address is %s \n", returnAddress, address.c_str());
        
        return 1;
    }
}

/** Create a message data at an address (without the callback function in Unity)
 @param[in] messageAddress Address of this message registered in the local application
 @param[in] type "type" attribute of this message
 @param[in] description "description" attribute of this message
 @return 0: Cannot create the message data at this address
 @return 1: Create successfully the message data at this address */
int CreateMessageDataPlugin(char messageAddress[], char type[], char description[])
{
    // Create a message data and set its callback function and baton and some attributes
    mDataDemoMessage = TTObject("Data", "message");
    
    // Setup the callback mechanism to get the value back
    TTValue args;
    args = TTValue(mDataDemoMessage);
    mDataDemoMessage.set("baton", args);
    mDataDemoMessage.set("function", TTPtr(&DataReturnValueCallback));
    
    // Setup the data attributes depending of its use inside the application
    mDataDemoMessage.set("type", type);
    mDataDemoMessage.set("description", description);
    
    // Register the message data into the local application at an address
    args = TTValue(messageAddress, mDataDemoMessage);
    
    TTErr err;
    TTValue out;
    
    err = mApplicationLocal.send("ObjectRegister", args, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the message data at the %s address \n", messageAddress);
        
        return 0;
    }
    else
    {
        TTAddress address;
        address = out[0];
        TTLogMessage("\n %s: effective registration address is %s \n", messageAddress, address.c_str());
        
        return 1;
    }
}

/** Create a message data at an address (with the callback function in Unity)
 @param[in] messageAddress Address of this message registered in the local application
 @param[in] type "type" attribute of this message
 @param[in] description "description" attribute of this message
 @param[in] valueCallback The callback function corresponding to this message
 @return 0: Cannot create the message data at this address
 @return 1: Create successfully the message data at this address */
int CreateMessageDataPluginWithCallbackUnity(char messageAddress[], char type[], char description[], ValueCallback valueCallback)
{
    // Create a message data and set its callback function and baton and some attributes
    mDataDemoMessage = TTObject("Data", "message");
    
    // Setup the callback mechanism to get the value back
    TTValue args;
    args = TTValue(mDataDemoMessage);
    mDataDemoMessage.set("baton", args);
    mDataDemoMessage.set("function", TTPtr(valueCallback));
    
    // Setup the data attributes depending of its use inside the application
    mDataDemoMessage.set("type", type);
    mDataDemoMessage.set("description", description);
    
    // Register the message data into the local application at an address
    args = TTValue(messageAddress, mDataDemoMessage);
    
    TTErr err;
    TTValue out;
    
    err = mApplicationLocal.send("ObjectRegister", args, out);
    
    if (err)
    {
        TTLogError("Error: Cannot create the message data at the %s address \n", messageAddress);
        
        return 0;
    }
    else
    {
        TTAddress address;
        address = out[0];
        TTLogMessage("\n %s: effective registration address is %s \n", messageAddress, address.c_str());
        
        return 1;
    }
}

/** Setup the control of i-score from an external Tick message */
void SetupMessageTickPlugin()
{
    TTValue     v, out;
    
    v = TTValue("/Main:externalTick", 1);
    mApplicationDistant.send("ObjectSend", v, out);
}

/** Send a Tick message to i-score to control it */
void SendMessageTickPlugin()
{
    TTValue     v, out;
    
    v = TTValue("/Main:Tick");
    mApplicationDistant.send("ObjectSend", v, out);
}

/** Set a new value for an attribute of a parameter (only applied to "type, rangeClipmode, rampDrive, description" attributes)
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @param[in] nameAttribute Name of this attribute
 @param[in] newValue The new value set to this attribute */
void SetAttributeParameterPlugin(int indexParameter, char nameAttribute[], char newValue[])
{
    mDataParameterVector[indexParameter].set(nameAttribute, newValue);
}

/** Get the current value of an attribute of a parameter (only applied to "type, rangeClipmode, rampDrive, description" attributes)
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @param[in] nameAttribute Name of this attribute
 @return Current value of this attribute */
const char* GetAttributeParameterPlugin(int indexParameter, char nameAttribute[])
{
    TTValue v;
    mDataParameterVector[indexParameter].get(nameAttribute, v);
    
    TTSymbol sym = v[0];
    const char* value = sym.c_str();
            
    return value;
}

/** Set a new value for the "rangeBounds" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @param[in] rangeBoundMin Min bound of the "rangeBounds" attribute of the new value
 @param[in] rangeBoundMax Max bound of the "rangeBounds" attribute of the new value */
void SetRangeBoundsParameterPlugin(int indexParameter, float rangeBoundMin, float rangeBoundMax)
{
    TTValue rangeBounds = TTValue(rangeBoundMin, rangeBoundMax);
    mDataParameterVector[indexParameter].set("rangeBounds", rangeBounds);
}

/** Get the current value of the min bound of the "rangeBounds" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @return Current value of the min bound of the "rangeBounds" attribute of this parameter */
float GetMinRangeBoundParameterPlugin(int indexParameter)
{
    TTValue v;
    mDataParameterVector[indexParameter].get("rangeBounds", v);
    
    float rangeBoundMin = (float) v[0];
        
    return rangeBoundMin;
}

/** Get the current value of the max bound of the "rangeBounds" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @return Current value of the max bound of the "rangeBounds" attribute of this parameter */
float GetMaxRangeBoundParameterPlugin(int indexParameter)
{
    TTValue v;
    mDataParameterVector[indexParameter].get("rangeBounds", v);
    
    float rangeBoundMax = (float) v[1];
        
    return rangeBoundMax;
}

/** Set a new value (type "decimal") for the "value" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @param[in] newValue The new value set to this attribute */
void SetValueFloatParameterPlugin(int indexParameter, float newValue)
{
    mDataParameterVector[indexParameter].set("value", newValue);
}

/** Set a new value (type "integer") for the "value" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @param[in] newValue The new value set to this attribute */
void SetValueIntegerParameterPlugin(int indexParameter, int newValue)
{
    mDataParameterVector[indexParameter].set("value", newValue);
}

/** Set a new value (type "boolean") for the "value" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @param[in] newValue The new value set to this attribute */
void SetValueBooleanParameterPlugin(int indexParameter, bool newValue)
{
    mDataParameterVector[indexParameter].set("value", newValue);
}

/** Set a new value (type "string") for the "value" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @param[in] newValue The new value set to this attribute */
void SetValueStringParameterPlugin(int indexParameter, char newValue[])
{
    mDataParameterVector[indexParameter].set("value", newValue);
}

/** Get the current value (type "decimal") of the "value" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @return Current value of the "value" attribute of this parameter */
float GetValueFloatParameterPlugin(int indexParameter)
{
    TTValue v;
    mDataParameterVector[indexParameter].get("value", v);
    
    float value = v[0];
        
    return value;
}

/** Get the current value (type "integer") of the "value" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @return Current value of the "value" attribute of this parameter */
int GetValueIntegerParameterPlugin(int indexParameter)
{
    TTValue v;
    mDataParameterVector[indexParameter].get("value", v);
    
    int value = v[0];
        
    return value;
}

/** Get the current value (type "boolean") of the "value" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @return Current value of the "value" attribute of this parameter */
bool GetValueBooleanParameterPlugin(int indexParameter)
{
    TTValue v;
    mDataParameterVector[indexParameter].get("value", v);
    
    bool value = v[0];
        
    return value;
}

/** Get the current value (type "string") of the "value" attribute of a parameter
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
 @return Current value of the "value" attribute of this parameter */
const char* GetValueStringParameterPlugin(int indexParameter)
{
    TTValue v;
    mDataParameterVector[indexParameter].get("value", v);
    
    TTSymbol sym = v[0];
            
    const char* value = sym.c_str();
            
    return value;
}

/** Set a new value for an attribute of a return (only applied to "type, description" attributes)
 @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
 @param[in] nameAttribute Name of this attribute
 @param[in] newValue The new value set to this attribute */
void SetAttributeReturnPlugin(int indexReturn, char nameAttribute[], char newValue[])
{
    mDataReturnVector[indexReturn].set(nameAttribute, newValue);
}

/** Get the current value of an attribute of a return (only applied to "type, description" attributes)
 @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
 @param[in] nameAttribute Name of this attribute
 @return Current value of this attribute */
const char* GetAttributeReturnPlugin(int indexReturn, char nameAttribute[])
{
    TTValue v;
    mDataReturnVector[indexReturn].get(nameAttribute, v);
    
    TTSymbol sym = v[0];
    const char* value = sym.c_str();
    
    return value;
}

/** Set a new value (type "decimal") for the "value" attribute of a return
 @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
 @param[in] newValue The new value set to this attribute */
void SetValueFloatReturnPlugin(int indexReturn, float newValue)
{
    mDataReturnVector[indexReturn].set("value", newValue);
}

/** Set a new value (type "integer") for the "value" attribute of a return
 @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
 @param[in] newValue The new value set to this attribute */
void SetValueIntegerReturnPlugin(int indexReturn, int newValue)
{
    mDataReturnVector[indexReturn].set("value", newValue);
}

/** Set a new value (type "boolean") for the "value" attribute of a return
 @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
 @param[in] newValue The new value set to this attribute */
void SetValueBooleanReturnPlugin(int indexReturn, bool newValue)
{
    mDataReturnVector[indexReturn].set("value", newValue);
}

/** Get the current value (type "decimal") of the "value" attribute of a return
 @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
 @return Current value of the "value" attribute of this return */
float GetValueFloatReturnPlugin(int indexReturn)
{
    TTValue v;
    mDataReturnVector[indexReturn].get("value", v);
    
    float value = v[0];
    
    return value;
}

/** Get the current value (type "integer") of the "value" attribute of a return
 @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
 @return Current value of the "value" attribute of this return */
int GetValueIntegerReturnPlugin(int indexReturn)
{
    TTValue v;
    mDataReturnVector[indexReturn].get("value", v);
    
    int value = v[0];
    
    return value;
}

/** Get the current value (type "boolean") of the "value" attribute of a return
 @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
 @return Current value of the "value" attribute of this return */
bool GetValueBooleanReturnPlugin(int indexReturn)
{
    TTValue v;
    mDataReturnVector[indexReturn].get("value", v);
    
    bool value = v[0];
    
    return value;
}

/** Save the namespace of the local applicatioin in a XML file
 @param[in] filePath Path leading to this file */
void SaveToXMLPlugin(char filePath[])
{
    TTValue     out;
    TTObject    xmlHandler("XmlHandler");
    
    // Save the namespace in a XML file
    xmlHandler.set("object", mApplicationLocal);
    xmlHandler.send("Write", filePath, out);
}

/** Unregister the parameter data at an address in the local application
 @param[in] paramaterAddress Address of this parameter in the local application
 @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...) 
 @return 0: Cannot unregister the parameter data at this address
 @return 1: Unregister successfully the parameter data at this address */
int UnregisterParameterDataPlugin(char paramaterAddress[], int indexParameter)
{
    TTValue out;
    
    TTLogMessage("\n Release the parameter data at the %s address \n", paramaterAddress);
    
    // Unregister the parameter data
    if (mApplicationLocal.send("ObjectUnregister", paramaterAddress, out))
    {
        TTLogError("Error: Cannot unregister the parameter data at the %s address \n", paramaterAddress);
        
        return 0;
    }
    else
    {
        // Erase the corresponding element in the vector of parameters and reduce "numberParameterData"
        mDataParameterVector.erase (mDataParameterVector.begin() + indexParameter);
        numberParameterData--;
        
        return 1;
    }
}

/** Unregister the return data at an address in the local application
 @param[in] returnAddress Address of this return in the local application
 @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
 @return 0: Cannot unregister the return data at this address
 @return 1: Unregister successfully the return data at this address */
int UnregisterReturnDataPlugin(char returnAddress[], int indexReturn)
{
    TTValue out;
    
    TTLogMessage("\n Release the return data at the %s address \n", returnAddress);
    
    // Unregister the return data
    if (mApplicationLocal.send("ObjectUnregister", returnAddress, out))
    {
        TTLogError("Error: Cannot unregister the return data at the %s address \n", returnAddress);
        
        return 0;
    }
    else
    {
        // Erase the corresponding element in the vector of returns and reduce "numberReturnData"
        mDataReturnVector.erase (mDataReturnVector.begin() + indexReturn);
        numberReturnData--;

        return 1;
    }
}

/** Unregister the message data at an address in the local application
 @param[in] messageAddress Address of this message in the local application 
 @return 0: Cannot unregister the message data at this address
 @return 1: Unregister successfully the message data at this address */
int UnregisterMessageDataPlugin(char messageAddress[])
{
    TTValue out;
    
    TTLogMessage("\n Release the message data \n");
    
    // Unregister the message data
    if (mApplicationLocal.send("ObjectUnregister", messageAddress, out))
    {
        TTLogError("Error: Cannot unregister the message data at the %s address \n", messageAddress);
        
        return 0;
    }
    else
    {
        return 1;
    }
}

/** Release the Minuit protocol */
void ReleaseMinuitProtocolPlugin()
{
    TTValue out;
    
    TTLogMessage("\n Release the Minuit protocol \n");
    
    mApplicationManager.send("ProtocolRelease", "Minuit", out);
}

/** Release the local and distant applications
 @param[in] localAppName Name of the local application
 @param[in] distantAppName Name of the distant application */
void ReleaseApplicationsPlugin(char localAppName[], char distantAppName[])
{
    TTValue out;
    
    TTLogMessage("\n Release the local and distant applications \n");
    
    mApplicationManager.send("ApplicationRelease", distantAppName, out);
    mApplicationManager.send("ApplicationRelease", localAppName, out);
}
